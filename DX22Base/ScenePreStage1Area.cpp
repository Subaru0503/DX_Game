//=================================================================
//
//	ScenePreStage1Area.cpp
//	ステージ前関連
//
//=================================================================

//----インクルード部----
#include "ScenePreStage1Area.h"
#include "Geometory.h"
#include "CameraPlayer.h"
#include "CameraDebug.h"
#include "CameraEvent.h"
#include "Collision.h"

//----定数・マクロ定義----
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)

CScenePreStage1Area::CScenePreStage1Area(CSceneMng* pSceneMng, int Stage)
	: CSceneStageBase(pSceneMng, Stage, DirectX::XMFLOAT3(0.0f, 0.0f, -15.0f))
{
	m_nMainCamera = CAM_PLAYER;
	// モデル読み込み
	m_pStageModel = new Model();
	if (!m_pStageModel->Load("Assets/Model/PreStageArea/Stage1/PreStageArea.fbx", 1.0f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "ScenePreStage1Area.cpp ステージモデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel->SetVertexShader(m_pVS);
	m_pPlayer->SetEventFlg(false);	// イベントフラグ下げ
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer, -30.0f, 40.0f, 10.0f);
	m_pCamera[CAM_DEBUG] = new CameraDebug();
	m_pCamera[CAM_EVENT] = nullptr;
	m_pPlayer->SetCamera(m_pCamera[CAM_PLAYER]);
}

CScenePreStage1Area::~CScenePreStage1Area()
{
	SAFE_DELETE(m_pStageModel);
	for (int i = 0; i < MAX_CAMERA; i++)
	{
		if (m_pCamera[i])
		{
			delete m_pCamera[i];
			m_pCamera[i] = nullptr;
		}
	}
}

void CScenePreStage1Area::Update(float tick)
{
	m_pPlayer->Update();

	m_pCollisionAreaMng->Update();

	if (m_nMainCamera != CAM_PLAYER) return;
	m_pCamera[CAM_PLAYER]->Update();
	m_pUI->Update();
}

void CScenePreStage1Area::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	DirectX::XMFLOAT4X4 mat[3];

	mat[1] = m_pCamera[m_nMainCamera]->GetViewMatrix();
	mat[2] = m_pCamera[m_nMainCamera]->GetProjectionMatrix();

	//---Geometory用の変換行列を設定
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	// ステージモデル描画
	DrawStage(mat, m_pVS);

	//----プレイヤーの描画----
	m_pPlayer->Draw();
	//----フィールドの描画----
	//m_pField->Draw();

	// イベント中だったら描画しない
	if (m_nMainCamera == CAM_EVENT) return;
	//----UI描画----
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	m_pUI->Draw();
}

// ステージを描画する
void CScenePreStage1Area::DrawStage(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;

	//---Geometory用の変換行列を計算
	world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixRotationX(0.0f) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---変換行列を設定
	vs->WriteBuffer(0, mat);
	m_pStageModel->SetVertexShader(vs);
	m_pStageModel->Draw();
}
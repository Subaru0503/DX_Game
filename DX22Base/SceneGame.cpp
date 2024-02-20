//=================================================================
//
//	SceneGame.cpp
//	ステージ前関連
//
//=================================================================

//----インクルード部----
#include "SceneGame.h"
#include "Geometory.h"
#include "CameraPlayer.h"
#include "CameraDebug.h"
#include "CameraEvent.h"
#include "Collision.h"

//----定数・マクロ定義----
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)

CSceneGame::CSceneGame(CSceneMng* pSceneMng, int Stage)
	: CSceneStageBase(pSceneMng, Stage, DirectX::XMFLOAT3(-5.0f, 0.0f, 0.0f))
{
	m_nMainCamera = CAM_PLAYER;
	// モデル読み込み
	// 地面
	m_pStageModel[0] = new Model();
	if (!m_pStageModel[0]->Load("Assets/Model/Stage/fruitsStage.fbx", 1.0f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "ステージモデル読み込み失敗", "Error", MB_OK);
	}

	// 川
	m_pStageModel[1] = new Model();
	if (!m_pStageModel[1]->Load("Assets/Model/river/river.fbx", 1.0f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "川モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[2] = new Model();
	if (!m_pStageModel[2]->Load("Assets/Model/river/river.fbx", 1.0f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "川モデル読み込み失敗", "Error", MB_OK);
	}
	m_pPlayer->SetEventFlg(false);	// イベントフラグ下げ
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer, 90.0f, 40.0f, 12.0f);
	m_pCamera[CAM_DEBUG] = new CameraDebug();
	m_pCamera[CAM_EVENT] = nullptr;
	//CameraEvent *pEvent = new CameraEvent();
	m_pPlayer->SetCamera(m_pCamera[CAM_PLAYER]);
	//pEvent->SetEvent(DirectX::XMFLOAT3(0.0f, 1.0f, 6.0f), DirectX::XMFLOAT3(0.0f, 3.0f, 0.0f), 4.0f);
	//m_pCamera[CAM_EVENT] = pEvent;
}

CSceneGame::~CSceneGame()
{
	for (int i = 0; i < MAX_STADE_MODEL; i++)
	{
		SAFE_DELETE(m_pStageModel[i]);
	}
	for (int i = 0; i < MAX_CAMERA; i++)
	{
		if (m_pCamera[i])
		{
			delete m_pCamera[i];
			m_pCamera[i] = nullptr;
		}
	}
}

void CSceneGame::Update(float tick)
{
	if (m_nMainCamera == CAM_EVENT)
	{
		m_pCamera[CAM_EVENT]->Update();
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_nMainCamera]);
		if (!pEvent->IsEvent())
		{
			m_nMainCamera = CAM_PLAYER;
			m_pPlayer->SetCamera(m_pCamera[m_nMainCamera]);
			m_pPlayer->SetEventFlg(false);
		}
	}
	if (IsKeyTrigger('3'))
	{
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[CAM_EVENT]);
		pEvent->SetEvent(DirectX::XMFLOAT3(0.0f, 1.0f, 6.0f), DirectX::XMFLOAT3(0.0f, 3.0f, 0.0f), 4.0f);
		m_nMainCamera = CAM_EVENT;
	}

	// レイの作成
	//Collision::Ray ray;
	m_pPlayer->Update();
	m_pObjectMng->Update(tick);
	//ray.start = m_pPlayer->GetPos();
	//ray.start.y += 1.0f;
	//ray.direction = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);

	//// すべてのフィールドとレイの当たり判定を実行
	//for (int i = 0; i < m_pField->GetDataNum(); i++)
	//{
	//	Collision::Result collision = Collision::CheckRayPlane(ray, m_pField->GetPlaneInfo(i));
	//	if (collision.hit)
	//	{
	//		for (int j = 0; j < 2; j++)
	//		{
	//			Collision::Result triCollision = Collision::CheckPointTriangle(collision.point, m_pField->GetTriangleInfo(i, j));
	//			if (triCollision.hit)
	//			{
	//				// プレイヤーを地面に立てる(下方向の移動量も0にできるといい)
	//				m_pPlayer->SetPos(collision.point);
	//				m_pPlayer->ResetGravity();	// 重力リセット
	//				m_pPlayer->ResetJumpFlg();	// ジャンプフラグ下げ
	//			}
	//		}
	//	}
	//}

	// エリアに当たり判定
	m_pCollisionAreaMng->Update();
	if (m_pCollisionAreaMng->GetNextScene())	// 次のシーンがセットされていたら
	{
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind(m_pCollisionAreaMng->GetNextScene()), 1);
	}
	m_pCollision->Update();
	//// 床に当たっているか
	//if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_StagePos, m_pPlayer->GetSize(), m_StageSize))
	//{
	//	m_pPlayer->SetPosY(m_StagePos.y + 0.5f);	// 床の上に戻す
	//	m_pPlayer->ResetGravity();	// 重力リセット
	//	m_pPlayer->ResetJumpFlg();	// 着地フラグ上げ
	//}

	if (m_nMainCamera != CAM_PLAYER) return;
	m_pCamera[CAM_PLAYER]->Update();
	m_pUI->Update();
}

void CSceneGame::Draw()
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

	//----オブジェクトの描画----
	m_pObjectMng->Draw(mat);
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
void CSceneGame::DrawStage(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;

	for (int i = 0; i < MAX_STADE_MODEL; i++)
	{
		switch (i)
		{
		case 0:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, -1.5f, 16.8f);
			break;
		case 2:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, -1.5f, -16.8f);
			break;
		}

		world = DirectX::XMMatrixTranspose(world);
		DirectX::XMStoreFloat4x4(&mat[0], world);

		//---変換行列を設定
		vs->WriteBuffer(0, mat);
		m_pStageModel[i]->SetVertexShader(vs);
		m_pStageModel[i]->Draw();
	}
}
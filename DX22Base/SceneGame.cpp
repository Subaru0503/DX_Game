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
#define FRAME (1)
#define TUTORIAL_FRAME (1)

CSceneGame::CSceneGame(CSceneMng* pSceneMng, int Stage, CSoundMng* pSoundMng)
	: CSceneStageBase(pSceneMng, Stage, DirectX::XMFLOAT3(8.0f, 0.0f, 0.0f), pSoundMng)
	, m_fFrameCnt(0.0f)
{
	m_nMainCamera = CAM_EVENT;
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

	// 空
	m_pStageModel[3] = new Model();
	if (!m_pStageModel[3]->Load("Assets/Model/Sky/Sky.fbx", 1.8f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "空モデル読み込み失敗", "Error", MB_OK);
	}

	// 背景
	m_pStageModel[4] = new Model();
	if (!m_pStageModel[4]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.8f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 背景
	m_pStageModel[5] = new Model();
	if (!m_pStageModel[5]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.3f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 背景
	m_pStageModel[6] = new Model();
	if (!m_pStageModel[6]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.5f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 岩
	m_pStageModel[7] = new Model();
	if (!m_pStageModel[7]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[8] = new Model();
	if (!m_pStageModel[8]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[9] = new Model();
	if (!m_pStageModel[9]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[10] = new Model();
	if (!m_pStageModel[10]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 背景
	m_pStageModel[11] = new Model();
	if (!m_pStageModel[11]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.8f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 背景
	m_pStageModel[12] = new Model();
	if (!m_pStageModel[12]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.3f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 背景
	m_pStageModel[13] = new Model();
	if (!m_pStageModel[13]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.5f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	// 岩
	m_pStageModel[14] = new Model();
	if (!m_pStageModel[14]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[15] = new Model();
	if (!m_pStageModel[15]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[16] = new Model();
	if (!m_pStageModel[16]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}

	m_pStageModel[17] = new Model();
	if (!m_pStageModel[17]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "背景モデル読み込み失敗", "Error", MB_OK);
	}
	//m_pPlayer->SetEventFlg(false);	// イベントフラグ下げ
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer, 90.0f, 40.0f, 15.0f);
	m_pCamera[CAM_DEBUG] = new CameraDebug();
	CameraEvent *pEvent = new CameraEvent(90.0f, 40.0f, 15.0f);
	m_pPlayer->SetCamera(pEvent);
	m_pTutorial->SetCamera(pEvent);
	pEvent->SetEvent(m_pPlayer->GetPos(), DirectX::XMFLOAT3(-10.0f, 0.0f, -3.0f), 1.0f, 9.8f);
	m_pCamera[CAM_EVENT] = pEvent;
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
	// 経過時間が制限時間を超えていたら
	if (m_pTimeUI->GetElapsedTime() >= m_pTimeUI->GetTimeLimit())
	{
		m_nTotalScore = m_pPlayer->GetScore();		// 合計スコア
		m_nMinusScore = m_pPlayer->GetMinusScore();	// ー合計スコア
		m_nFruitsNum = m_pPlayer->GetFruitsNum();	// あつめたフルーツの数
		m_nCanNum = m_pPlayer->GetCanNum();			// あつめたカンの数
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT, 1);	// リザルトシーンへ
		return;	// 以降のシートを処理しない
	}
	if (m_nMainCamera == CAM_EVENT)
	{
		m_pCamera[CAM_EVENT]->Update();
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_nMainCamera]);
		if (pEvent->GetMoveFlg())
		{
			m_pObjectMng->SetMoveFlg(pEvent->GetMoveFlg());
			m_pObjectMng->TutorialUpdate(tick);
			m_pCollision->Update();
			// カウントが立ってたらパネルの中のフルーツの描画フラグをリセットする
			if (m_fFrameCnt / 60.0f > FRAME)
			{
				// フラグリセット
				m_pTutorial->SetResetFlg(false);
				m_pUI->ResetDrawFlg();
				m_pUI->SetJudge(false, false, false);
				m_fFrameCnt = 0.0f;	// カウントリセット
			}
			// フラグが立ってたら
			if (m_pTutorial->GetResetFlg())
			{
				m_fFrameCnt++;	// カウントアップ
			}
		}
		if (!pEvent->IsEvent())
		{
			// フラグリセット
			m_pTutorial->SetResetFlg(false);
			m_pUI->ResetDrawFlg();
			m_fFrameCnt = 0.0f;	// カウントリセット
			m_pUI->SetJudge(false, false, false);
			m_pCollision->SetTutorialFlg(false);
			m_nMainCamera = CAM_PLAYER;
			m_pPlayer->SetCamera(m_pCamera[m_nMainCamera]);
			m_pPlayer->SetEventFlg(false);
			m_pObjectMng->SetObject();	// 初期オブジェクトをセット
		}

	}

	if (m_nMainCamera != CAM_PLAYER) return;

	// カウントが立ってたらパネルの中のフルーツの描画フラグをリセットする
	if (m_fFrameCnt / 60.0f > FRAME)
	{
		// フラグリセット
		m_pPlayer->SetResetFlg(false);
		m_pUI->ResetDrawFlg();
		m_fFrameCnt = 0.0f;	// カウントリセット
	}

	m_pPlayer->Update();							// プレイヤー更新
	m_pObjectMng->Update(tick);						// オブジェクトマネージャー更新
	m_pUI->Update();								// アイテムUI描画
	m_pScoreUI->SetScore(m_pPlayer->GetScore());	// スコア更新

	// エリアに当たり判定
	m_pCollisionAreaMng->Update();
	m_pCollision->Update();

	m_pCamera[CAM_PLAYER]->Update();
	//----UI----
	m_pTimeUI->Update();	// 時間更新

	// フラグが立ってたら
	if (m_pPlayer->GetResetFlg())
	{
		m_fFrameCnt++;	// カウントアップ
	}
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

	// イベント中だったら描画しない
	if (m_nMainCamera == CAM_EVENT)
	{
		//----チュートリアル描画----
		m_pTutorial->Draw();
		//----UI描画----
		pRTV = GetDefaultRTV();
		SetRenderTargets(1, &pRTV, nullptr);
		m_pUI->Draw();		// アイテム描画
		return;
	}
	//----UI描画----
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//m_pUI->Draw();
	m_pScoreUI->Draw();	// スコア描画
	m_pUI->Draw();		// アイテム描画
	m_pTimeUI->Draw();	// 時間描画
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
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.6f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, -1.5f, 18.8f);
			break;
		case 2:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.6f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, -1.5f, -18.8f);
			break;
		case 3:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			break;
		case 4:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-21.5f, -2.0f, 0.0f);
			break;
		case 5:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-20.0f, -2.0f, 10.0f);
			break;
		case 6:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-21.0f, -2.0f, -9.0f);
			break;
		case 7:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-20.0f, -0.0f, 18.5f);
			break;
		case 8:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-17.0f, 0.0f, 6.0f);
			break;
		case 9:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-17.0f, 0.0f, -6.0f);
			break;
		case 10:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-20.0f, 0.0f, -18.5f);
			break;
		case 11:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(21.5f, -2.0f, 0.0f);
			break;
		case 12:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(20.0f, -2.0f, 10.0f);
			break;
		case 13:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(21.0f, -2.0f, -9.0f);
			break;
		case 14:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(20.0f, -0.0f, 18.5f);
			break;
		case 15:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(17.0f, 0.0f, 6.0f);
			break;
		case 16:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(17.0f, 0.0f, -6.0f);
			break;
		case 17:
			//---Geometory用の変換行列を計算
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(20.0f, 0.0f, -18.5f);
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
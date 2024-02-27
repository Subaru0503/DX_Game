//=================================================================
//
//	SceneStageBase.cpp
//	ステージシーンの共通部分
//
//=================================================================

#include "SceneStageBase.h"

CSceneStageBase::CSceneStageBase(CSceneMng* pSceneMng, int Stage, DirectX::XMFLOAT3 PlayerPos, CSoundMng* pSoundMng)
	: m_pSceneMng(pSceneMng)
	, m_pSoundMng(pSoundMng)
{
	// ----- 頂点シェーダー読み込み -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// ----- データ作成 -----
	m_pObjectMng = new CObjectMng;
	m_pPlayer = new Player(PlayerPos);
	m_pPlayer->SetSoundMng(m_pSoundMng);
	m_pObjectMng->SetPlayer(m_pPlayer);
	m_pCollisionAreaMng = new CCollisionAreaMng(Stage);
	m_pCollisionAreaMng->SetPlayer(m_pPlayer);
	m_pCollision = new Collision();
	m_pCollision->SetPlayer(m_pPlayer);
	m_pCollision->SetObjectManager(m_pObjectMng);
	m_pCollision->SetTutorialFlg(true);
	m_pUI = new ItemUI;
	m_pPlayer->SetItemUI(m_pUI);
	m_pScoreUI = new CScoreUI(m_pPlayer->GetScore());
	m_pTimeUI = new CTimeUI();
	m_pTutorial = new Tutorial(DirectX::XMFLOAT3(-10.0f, 0.0f, -3.0f));
	m_pTutorial->SetItemUI(m_pUI);
	m_pCollision->SetTutorial(m_pTutorial);

}

CSceneStageBase::~CSceneStageBase()
{
	// ----- データが存在したら削除 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pTutorial);
	SAFE_DELETE(m_pScoreUI);
	SAFE_DELETE(m_pTimeUI);
	SAFE_DELETE(m_pObjectMng);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollisionAreaMng);
	SAFE_DELETE(m_pCollision);

}

int CSceneStageBase::GetTotalScore()	// 合計スコア情報ゲット
{
	return m_nTotalScore;
}

int CSceneStageBase::GetMinusScore()	// ー合計スコア情報ゲット
{
	return m_nMinusScore;
}

int CSceneStageBase::GetFruitsNum()		// あつめたフルーツの数情報ゲット
{
	return m_nFruitsNum;
}

int CSceneStageBase::GetCanNum()		// あつめたカンの数
{
	return m_nCanNum;
}

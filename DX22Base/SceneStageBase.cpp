//=================================================================
//
//	SceneStageBase.cpp
//	ステージシーンの共通部分
//
//=================================================================

#include "SceneStageBase.h"

CSceneStageBase::CSceneStageBase(CSceneMng* pSceneMng, int Stage, DirectX::XMFLOAT3 PlayerPos)
	: m_pSceneMng(pSceneMng)
{
	// ----- 頂点シェーダー読み込み -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// ----- データ作成 -----
	m_pObjectMng = new CObjectMng;
	m_pPlayer = new Player(PlayerPos);
	m_pObjectMng->SetPlayer(m_pPlayer);
	m_pCollisionAreaMng = new CCollisionAreaMng(Stage);
	m_pCollisionAreaMng->SetPlayer(m_pPlayer);
	m_pCollision = new Collision();
	m_pCollision->SetPlayer(m_pPlayer);
	m_pCollision->SetObjectManager(m_pObjectMng);
	m_pUI = new ItemUI;
	m_pScoreUI = new CScoreUI(m_pPlayer->GetScore());
	m_pTimeUI = new CTimeUI();

}

CSceneStageBase::~CSceneStageBase()
{
	// ----- データが存在したら削除 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pScoreUI);
	SAFE_DELETE(m_pTimeUI);
	SAFE_DELETE(m_pObjectMng);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollisionAreaMng);
	SAFE_DELETE(m_pCollision);

}
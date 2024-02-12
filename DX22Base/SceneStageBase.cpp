//=================================================================
//
//	SceneStageBase.cpp
//	ステージシーンの共通部分
//
//=================================================================

#include "SceneStageBase.h"

CSceneStageBase::CSceneStageBase()
{
	// ----- 頂点シェーダー読み込み -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// ----- データ作成 -----
	m_pPlayer = new Player;
	m_pUI = new ItemUI;

}

CSceneStageBase::~CSceneStageBase()
{
	// ----- データが存在したら削除 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pPlayer);

}
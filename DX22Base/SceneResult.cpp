//=================================================================
//
//	SceneResult.cpp
//	タイトルシーン
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneResult.h"
#include "Input.h"

// ========== コンストラクタ ==========
CSceneResult::CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear)
	: m_pushEsc(false)
	, m_select(true)
	, m_pSceneMng(pSceneMng)
{

}

// ========== デストラクタ ==========
CSceneResult::~CSceneResult()
{

}

// ========== Update関数 ==========
void CSceneResult::Update()
{

	// =-=-= リザルト画面 =-=-=
	  // ----- ゲームスタート -----
	if (IsKeyTrigger(VK_RETURN)) {
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_TITLE, 1);
	}

}

// ========== Draw関数 ==========
void CSceneResult::Draw()
{

}
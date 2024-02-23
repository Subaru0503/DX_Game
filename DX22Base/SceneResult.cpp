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
	: m_pSceneMng(pSceneMng)
{
	m_pResultBackGround = new CResultBackGround();
}

// ========== デストラクタ ==========
CSceneResult::~CSceneResult()
{
	SAFE_DELETE(m_pResultBackGround);
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
	RenderTarget* pRTV = GetDefaultRTV();
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//----背景描画----
	m_pResultBackGround->Draw();
}
//=================================================================
//
//	SceneTitle.cpp
//	タイトルシーン
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneTitle.h"
#include "Input.h"

// ========== コンストラクタ ==========
CSceneTitle::CSceneTitle(CSceneMng* pSceneMng)
	: m_pSceneMng(pSceneMng)
{
	m_pTitleBackGround = new CTitleBackGround();
}

// ========== デストラクタ ==========
CSceneTitle::~CSceneTitle()
{
	SAFE_DELETE(m_pTitleBackGround);
}

// ========== Update関数 ==========
void CSceneTitle::Update()
{

	// =-=-= タイトル画面 =-=-=
	{	// 終了確認画面を開いていない
	   //if (IsKeyTrigger(VK_ESCAPE))	m_pushEsc = true;		// ESCで確認画面開く

	   // ----- ゲームスタート -----
		if (IsKeyTrigger(VK_RETURN)) {
			//m_pSoundMng->playSound(CSoundMng::SystemSE::Tstrat);
			//animestart = true;
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_GAME, 1);
		}
	}

}

// ========== Draw関数 ==========
void CSceneTitle::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//----背景描画----
	m_pTitleBackGround->Draw();
}
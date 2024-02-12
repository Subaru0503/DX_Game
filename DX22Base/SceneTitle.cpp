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
	: m_pushEsc(false)
	, m_select(true)
	, m_pSceneMng(pSceneMng)
{

}

// ========== デストラクタ ==========
CSceneTitle::~CSceneTitle()
{

}

// ========== Update関数 ==========
void CSceneTitle::Update()
{

	// =-=-= ゲーム終了確認画面 =-=-=
	//キーボード操作
	//if (m_pushEsc) {
	//	// ----- ボタン選択状況：はい -----
	//	if (m_select) {
	//		if (IsKeyTrigger('D') || IsKeyTrigger(VK_RIGHT))			// いいえにカーソル移動
	//		{
	//			m_select ^= 1;
	//			m_pEscape->SetNo();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::select);

	//		}
	//		else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE))	// ゲーム終了
	//		{
	//			m_pSceneMng->SetGameEnd();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
	//		}
	//	}
	//	// ----- ボタン選択状況：いいえ -----
	//	else {
	//		if (IsKeyTrigger('A') || IsKeyTrigger(VK_LEFT))				// はいにカーソル移動
	//		{
	//			m_select ^= 1;
	//			m_pEscape->SetYes();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::select);
	//		}
	//		else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE))	// 確認画面を閉じる
	//		{
	//			m_pushEsc = false;
	//			m_pEscape->SetWindowAnime();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
	//		}
	//	}
	//}

	// =-=-= タイトル画面 =-=-=
	{	// 終了確認画面を開いていない
	   //if (IsKeyTrigger(VK_ESCAPE))	m_pushEsc = true;		// ESCで確認画面開く

	   // ----- ゲームスタート -----
		if (IsKeyTrigger(VK_RETURN)) {
			//m_pSoundMng->playSound(CSoundMng::SystemSE::Tstrat);
			//animestart = true;
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_STAGE1, 1);
		}
	}

	//if (animestart)
	//{
	//	animefin = m_pTitle->AnimeButton();
	//	if (animefin)
	//	{
	//		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
	//		animestart = false;
	//	}
	//}
}

// ========== Draw関数 ==========
void CSceneTitle::Draw()
{
	
}
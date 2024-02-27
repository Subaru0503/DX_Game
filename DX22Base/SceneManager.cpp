//=================================================================
//
//	sceneManager.cpp
//	シーン管理
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneManager.h"
#include "SceneTitle.h"				// タイトル
#include "SceneGame.h"				// ゲームシーン
#include "SceneResult.h"			// リザルト

// ========== 定数・マクロ定義 ==========
#define FADE_IN			(true)
#define FADE_OUT		(false)
#define FADE_IN_TIME	(1.0f)
#define FADE_OUT_TIME	(1.0f)

// ========== コンストラクタ ==========
CSceneMng::CSceneMng()
	: m_scene(SCENE_GAME)
	, m_nextScene(SCENE_GAME)
	, m_GameEnd(false)
	, m_nResetNo(0)
	, m_nClear(0)
{
	//m_pTitle = new CSceneTitle(this);
	m_pSoundMng = new CSoundMng();		// サウンド
	m_pFade = new Fade();				// フェード
	m_pSceneGame = new CSceneGame(this, SCENE_GAME, m_pSoundMng);
	m_pSoundMng->playSound(CSoundMng::BGM::game);	// 次のシーンのBGMを再生
}

// ========== デストラクタ ==========
CSceneMng::~CSceneMng()
{
	// =-=-= シーンに応じたデータ削除 =-=-=
	// 存在していれば削除
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_GAME:	SAFE_DELETE(m_pSceneGame);  break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult); break;
	default: break;
	}
	SAFE_DELETE(m_pSoundMng);
	SAFE_DELETE(m_pFade);
}

// ========== 更新 ==========
void CSceneMng::Update(float tick)
{
	if (!m_pFade->IsPlay()) {			//いろんな処理はフェード処理が終わってから。
		if (m_scene != m_nextScene){	// シーンチェンジが行われていれば遷移
			SceneSwap();
		}
	}

	// =-=-= シーンに応じた更新 =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Update();			break;
	case SCENE_GAME:	m_pSceneGame->Update(tick); 	break;
	case SCENE_RESULT:	m_pResult->Update();	break;
	default: break;
	}

	// ----- 各種更新 -----
	m_pSoundMng->DeleteSpeaker();	// 再生終了したスピーカーを破棄
	m_pFade->Update();
}

// ========== 描画 ==========
void CSceneMng::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Draw();	break;
	case SCENE_GAME:	m_pSceneGame->Draw();	break;
	case SCENE_RESULT:	m_pResult->Draw();	break;
	default: break;
	}
	m_pFade->Draw();
}

// ========== シーン切り替え設定 ==========
// 引　数：SceneKind 遷移先シーン
// 戻り値：なし
// 指定のシーンを遷移先に設定。
// ======================================
void CSceneMng::SetNextScene(SceneKind scene, int Deth)
{
	// フェード中は次のシーンを予約しない
	if (m_pFade->IsPlay())
	{
		return;
	}

	m_nextScene = scene;	// 次シーン予約

	// ----- フェード -----
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::BLACK);	break;
	case SCENE_GAME:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::BLACK);	break;
	case SCENE_RESULT:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::BLACK);	break;
	}
}

// ========== シーン切り替え ==========
// 引　数：なし
// 戻り値：なし
// 指定のシーンに切り替え、必要情報を引き継ぐ
// ==================================
void CSceneMng::SceneSwap()
{
	//switch (m_scene)	// 遊んだステージの情報を格納
	//{
	//case SCENE_GAME:	m_oldPlayStage = SCENE_GAME;	break;
	//case SCENE_STAGE2:	m_oldPlayStage = SCENE_STAGE2;	break;
	//case SCENE_STAGE3:	m_oldPlayStage = SCENE_STAGE3;	break;
	//}

	// =-=-= 新しいシーンの読み込み =-=-=
	m_pSoundMng->AllDeleteSpeaker();
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pTitle = new CSceneTitle(this);	// シーン遷移処理呼び出しのためSceneMng*受け渡し
		m_pSoundMng->playSound(CSoundMng::BGM::title);	// 次のシーンのBGMを再生
		break;
	case SCENE_GAME: m_pSceneGame = new CSceneGame(this, SCENE_GAME, m_pSoundMng);
		m_pSoundMng->playSound(CSoundMng::BGM::game);	// 次のシーンのBGMを再生
		break;

	case SCENE_RESULT:
		m_pResult = new CSceneResult(this, m_nResetNo, m_nClear);
		m_pSoundMng->playSound(CSoundMng::BGM::result);	// 次のシーンのBGMを再生
		break;
	}

	// =-=-= 必要情報引継ぎ =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	break;
	case SCENE_GAME:	if (m_nextScene == SCENE_RESULT)PassData(m_pSceneGame, m_pResult);	break;	// リザルトへ
	case SCENE_RESULT:	break;
	}

	// =-=-= 現在のシーン削除 =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_GAME:	SAFE_DELETE(m_pSceneGame); break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult);	m_nResetNo = 0; m_nClear = 0; break;
	default: break;
	}

	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	case SCENE_GAME:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	case SCENE_RESULT:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	default: break;
	}

	// ゲームシーンへの遷移でなければフェードイン
	m_scene = m_nextScene;	// シーン情報上書き
}

// ========== シーン間データ引継ぎ:Select → Stage==========
// 引　数：
// CSceneSelect* 
// CSceneStageBase* 
// 戻り値：なし
// ～関数概要～
// セレクトからステージシーンへ必要なデータを引き継ぐ
// ========================================================
void CSceneMng::PassData(CSceneStageBase* game, CSceneResult* result)	// Select → Stage
{
	// ----- 受け渡し -----
	result->SetTotalScore(game->GetTotalScore());	// 合計スコア情報セット
	result->SetMinusScore(game->GetMinusScore());	// ー合計スコア情報セット
	result->SetFruitsNum(game->GetFruitsNum());		// あつめたフルーツの数
	result->SetCanNum(game->GetCanNum());			// あつめたカンの数
}

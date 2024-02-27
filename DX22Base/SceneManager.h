//=================================================================
//
//	sceneManager.cpp
//	シーン管理
//
//=================================================================

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// ========== インクルード部 ==========
#include "SoundManager.h"
#include "Fade.h"

// 相互インクルード防止
class CSceneTitle;			// タイトル
class CSceneGame;			// ゲームシーン
class CSceneStageBase;		// ゲーム
class CSceneResult;			// リザルト

// ========== クラス ==========
class CSceneMng
{
public:
	enum SceneKind		// ステージの種類、総数
	{
		SCENE_TITLE = 1,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_MAX,
	};

public:
	CSceneMng();
	~CSceneMng();
	void Update(float tick);
	void Draw();

	void SetNextScene(SceneKind scene, int Deth);	// 次のシーンを設定し、遷移する

private:
	void SceneSwap();					// シーンを切り替える

	// ----- 次のシーンで必要な情報を引き継ぐ -----
	void PassData(CSceneStageBase* game, CSceneResult* result);		// Game  → Result

private:
	// ----- シーン管理 -----
	bool m_GameEnd;			// ゲームループ抜ける
	int	 m_scene;			// 現在実行中のシーン
	int	 m_nextScene;		// 次のシーン

	// ----- シーンデータ -----
	CSceneTitle*		m_pTitle;		// タイトル
	CSceneStageBase*	m_pSceneGame;	// ゲームシーン
	//CSceneGame*			m_pSceneGame;	// ゲームシーン
	CSceneResult*		m_pResult;		// リザルト

	CSoundMng*	m_pSoundMng;			// サウンド
	Fade*		m_pFade;				// フェード

	int m_nResetNo;						// リセット回数
	int m_nClear;						// クリア数
};

#endif // !__SCENE_MANAGER_H__
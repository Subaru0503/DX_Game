//=================================================================
//
//	sceneManager.cpp
//	シーン管理
//
//=================================================================

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// ========== インクルード部 ==========

// 相互インクルード防止
class CSceneTitle;
class CScenePreArea;
//class SceneStage2;
class CSceneResult;

// ========== クラス ==========
class CSceneMng
{
public:
	enum SceneKind		// ステージの種類、総数
	{
		SCENE_PRE_STAGE1_AREA,
		SCENE_STAGE1,
		SCENE_PRE_STAGE2_AREA,
		SCENE_STAGE2,
		SCENE_PRE_STAGE3_AREA,
		SCENE_STAGE3,
		MAX_STAGE,

		SCENE_TITLE = 7,
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
	void SceneSwap();					// シーンを切り替える\


private:
	// ----- シーン管理 -----
	bool m_GameEnd;			// ゲームループ抜ける
	int	 m_scene;			// 現在実行中のシーン
	int	 m_nextScene;		// 次のシーン

	// ----- シーンデータ -----
	CSceneTitle*		m_pTitle;		// タイトル
	CScenePreArea*	m_pScenePreArea;	// エリア前
	//SceneStage2* m_pStage2;				// ステージ2
	CSceneResult*		m_pResult;		// リザルト
	int m_nResetNo;						// リセット回数
	int m_nClear;						// クリア数
};

#endif // !__SCENE_MANAGER_H__
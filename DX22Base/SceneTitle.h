//=================================================================
//
//	SceneTitle.cpp
//	タイトルシーン
//
//=================================================================
#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

// ========== インクルード部 ==========
#include "SceneManager.h"		// シーン遷移処理用
#include "TitleBackGround.h"	// タイトル背景

// ========== クラス ==========
class CSceneTitle
{
public:
	CSceneTitle(CSceneMng* pSceneMng);
	~CSceneTitle();
	void Update();
	void Draw();

private:
	CSceneMng* m_pSceneMng;
	CTitleBackGround* m_pTitleBackGround;
};

#endif // !__SCENE_TITLE_H__
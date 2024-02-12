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

// ========== クラス ==========
class CSceneTitle
{
public:
	CSceneTitle(CSceneMng* pSceneMng);
	~CSceneTitle();
	void Update();
	void Draw();

private:
	bool m_pushEsc, m_select;

	CSceneMng* m_pSceneMng;
};

#endif // !__SCENE_TITLE_H__
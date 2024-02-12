//=================================================================
//
//	SceneResult.h
//	リザルトシーン
//
//=================================================================
#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__

// ========== インクルード部 ==========
#include "SceneManager.h"		// シーン遷移処理用

// ========== クラス ==========
class CSceneResult
{
public:
	CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear);
	~CSceneResult();
	void Update();
	void Draw();

private:
	bool m_pushEsc, m_select;

	CSceneMng* m_pSceneMng;
};

#endif // !__SCENE_RESULT_H__
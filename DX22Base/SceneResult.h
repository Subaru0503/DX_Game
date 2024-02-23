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
#include "ResultBackGround.h"	// リザルト背景

// ========== クラス ==========
class CSceneResult
{
public:
	CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear);
	~CSceneResult();
	void Update();
	void Draw();

private:
	CSceneMng* m_pSceneMng;
	CResultBackGround* m_pResultBackGround;
};

#endif // !__SCENE_RESULT_H__
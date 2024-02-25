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
#include "ResultMozi.h"			// リザルト文字
#include "ResultScore.h"		// リザルトスコア

// ========== クラス ==========
class CSceneResult
{
public:
	CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear);
	~CSceneResult();
	void Update();
	void Draw();

	void SetTotalScore(int score);			// 合計スコアセット
	void SetMinusScore(int minusScore);		// ー合計スコアセット
	void SetFruitsNum(int FruitsNum);		// あつめたフルーツの数
	void SetCanNum(int CanNum);				// あつめたカンの数

private:
	void ScoreSet();	// スコアセット
private:
	CSceneMng* m_pSceneMng;
	CResultBackGround* m_pResultBackGround;
	CResultMozi* m_pResultMozi;
	CResultScore* m_pResultScore;

	int m_nTotalScore;	// 合計スコア
	int m_nPlusScore;	// ＋合計スコア
	int m_nMinusScore;	// ー合計スコア
	int m_nFruitsNum;	// あつめたフルーツの数
	int m_nCanNum;		// あつめたカンの数

	int m_nInitFlg;	// 初期化フラグ
};

#endif // !__SCENE_RESULT_H__
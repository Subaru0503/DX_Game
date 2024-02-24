//=================================================================
//
//	SceneResult.cpp
//	タイトルシーン
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneResult.h"
#include "Input.h"

// ========== コンストラクタ ==========
CSceneResult::CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear)
	: m_pSceneMng(pSceneMng)
	, m_nPlusScore(0)
	, m_nInitFlg(0)
{
	m_pResultBackGround = new CResultBackGround();
	m_pResultMozi = new CResultMozi();
	m_pResultScore = new CResultScore();
}

// ========== デストラクタ ==========
CSceneResult::~CSceneResult()
{
	SAFE_DELETE(m_pResultBackGround);
	SAFE_DELETE(m_pResultMozi);
	SAFE_DELETE(m_pResultScore);
}

// ========== Update関数 ==========
void CSceneResult::Update()
{
	if (!m_nInitFlg)
	{
		ScoreSet();	// スコアセット
		m_nInitFlg = true;
	}

	// =-=-= リザルト画面 =-=-=
	  // ----- ゲームスタート -----
	if (IsKeyTrigger(VK_RETURN)) {
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_TITLE, 1);
	}

}

// ========== Draw関数 ==========
void CSceneResult::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//----背景描画----
	m_pResultBackGround->Draw();
	//----文字描画----
	m_pResultMozi->Draw();
	//----スコア描画----
	m_pResultScore->Draw();
}

void CSceneResult::SetTotalScore(int score)		// 合計スコアセット
{
	m_nTotalScore = score;
}

void CSceneResult::SetMinusScore(int minusScore)	// ー合計スコアセット
{
	m_nMinusScore = minusScore;
}

void CSceneResult::ScoreSet()	// スコアセット
{
	m_nPlusScore = m_nTotalScore + m_nMinusScore;	// プラスだけのスコアを計算
	m_pResultScore->SetScore(m_nPlusScore, 0);
	m_pResultScore->SetScore(m_nMinusScore, 1);
}

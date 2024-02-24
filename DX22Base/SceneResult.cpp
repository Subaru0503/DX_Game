//=================================================================
//
//	SceneResult.cpp
//	�^�C�g���V�[��
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneResult.h"
#include "Input.h"

// ========== �R���X�g���N�^ ==========
CSceneResult::CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear)
	: m_pSceneMng(pSceneMng)
	, m_nPlusScore(0)
	, m_nInitFlg(0)
{
	m_pResultBackGround = new CResultBackGround();
	m_pResultMozi = new CResultMozi();
	m_pResultScore = new CResultScore();
}

// ========== �f�X�g���N�^ ==========
CSceneResult::~CSceneResult()
{
	SAFE_DELETE(m_pResultBackGround);
	SAFE_DELETE(m_pResultMozi);
	SAFE_DELETE(m_pResultScore);
}

// ========== Update�֐� ==========
void CSceneResult::Update()
{
	if (!m_nInitFlg)
	{
		ScoreSet();	// �X�R�A�Z�b�g
		m_nInitFlg = true;
	}

	// =-=-= ���U���g��� =-=-=
	  // ----- �Q�[���X�^�[�g -----
	if (IsKeyTrigger(VK_RETURN)) {
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_TITLE, 1);
	}

}

// ========== Draw�֐� ==========
void CSceneResult::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//----�w�i�`��----
	m_pResultBackGround->Draw();
	//----�����`��----
	m_pResultMozi->Draw();
	//----�X�R�A�`��----
	m_pResultScore->Draw();
}

void CSceneResult::SetTotalScore(int score)		// ���v�X�R�A�Z�b�g
{
	m_nTotalScore = score;
}

void CSceneResult::SetMinusScore(int minusScore)	// �[���v�X�R�A�Z�b�g
{
	m_nMinusScore = minusScore;
}

void CSceneResult::ScoreSet()	// �X�R�A�Z�b�g
{
	m_nPlusScore = m_nTotalScore + m_nMinusScore;	// �v���X�����̃X�R�A���v�Z
	m_pResultScore->SetScore(m_nPlusScore, 0);
	m_pResultScore->SetScore(m_nMinusScore, 1);
}

//=================================================================
//
//	SceneResult.h
//	���U���g�V�[��
//
//=================================================================
#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"		// �V�[���J�ڏ����p
#include "ResultBackGround.h"	// ���U���g�w�i
#include "ResultMozi.h"			// ���U���g����
#include "ResultScore.h"		// ���U���g�X�R�A

// ========== �N���X ==========
class CSceneResult
{
public:
	CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear);
	~CSceneResult();
	void Update();
	void Draw();

	void SetTotalScore(int score);			// ���v�X�R�A�Z�b�g
	void SetMinusScore(int minusScore);		// �[���v�X�R�A�Z�b�g
	void SetFruitsNum(int FruitsNum);		// ���߂��t���[�c�̐�
	void SetCanNum(int CanNum);				// ���߂��J���̐�

private:
	void ScoreSet();	// �X�R�A�Z�b�g
private:
	CSceneMng* m_pSceneMng;
	CResultBackGround* m_pResultBackGround;
	CResultMozi* m_pResultMozi;
	CResultScore* m_pResultScore;

	int m_nTotalScore;	// ���v�X�R�A
	int m_nPlusScore;	// �{���v�X�R�A
	int m_nMinusScore;	// �[���v�X�R�A
	int m_nFruitsNum;	// ���߂��t���[�c�̐�
	int m_nCanNum;		// ���߂��J���̐�

	int m_nInitFlg;	// �������t���O
};

#endif // !__SCENE_RESULT_H__
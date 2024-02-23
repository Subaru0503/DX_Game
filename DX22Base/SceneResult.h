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

// ========== �N���X ==========
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
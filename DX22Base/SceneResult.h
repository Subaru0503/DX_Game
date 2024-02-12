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

// ========== �N���X ==========
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
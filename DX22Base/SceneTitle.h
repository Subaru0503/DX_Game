//=================================================================
//
//	SceneTitle.cpp
//	�^�C�g���V�[��
//
//=================================================================
#ifndef __SCENE_TITLE_H__
#define __SCENE_TITLE_H__

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"		// �V�[���J�ڏ����p

// ========== �N���X ==========
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
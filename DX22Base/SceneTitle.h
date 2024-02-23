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
#include "TitleBackGround.h"	// �^�C�g���w�i

// ========== �N���X ==========
class CSceneTitle
{
public:
	CSceneTitle(CSceneMng* pSceneMng);
	~CSceneTitle();
	void Update();
	void Draw();

private:
	CSceneMng* m_pSceneMng;
	CTitleBackGround* m_pTitleBackGround;
};

#endif // !__SCENE_TITLE_H__
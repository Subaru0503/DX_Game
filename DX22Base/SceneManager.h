//=================================================================
//
//	sceneManager.cpp
//	�V�[���Ǘ�
//
//=================================================================

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// ========== �C���N���[�h�� ==========
#include "SoundManager.h"
#include "Fade.h"

// ���݃C���N���[�h�h�~
class CSceneTitle;			// �^�C�g��
class CSceneGame;			// �Q�[���V�[��
class CSceneStageBase;		// �Q�[��
class CSceneResult;			// ���U���g

// ========== �N���X ==========
class CSceneMng
{
public:
	enum SceneKind		// �X�e�[�W�̎�ށA����
	{
		SCENE_TITLE = 1,
		SCENE_GAME,
		SCENE_RESULT,
		SCENE_MAX,
	};

public:
	CSceneMng();
	~CSceneMng();
	void Update(float tick);
	void Draw();

	void SetNextScene(SceneKind scene, int Deth);	// ���̃V�[����ݒ肵�A�J�ڂ���

private:
	void SceneSwap();					// �V�[����؂�ւ���

	// ----- ���̃V�[���ŕK�v�ȏ��������p�� -----
	void PassData(CSceneStageBase* game, CSceneResult* result);		// Game  �� Result

private:
	// ----- �V�[���Ǘ� -----
	bool m_GameEnd;			// �Q�[�����[�v������
	int	 m_scene;			// ���ݎ��s���̃V�[��
	int	 m_nextScene;		// ���̃V�[��

	// ----- �V�[���f�[�^ -----
	CSceneTitle*		m_pTitle;		// �^�C�g��
	CSceneStageBase*	m_pSceneGame;	// �Q�[���V�[��
	//CSceneGame*			m_pSceneGame;	// �Q�[���V�[��
	CSceneResult*		m_pResult;		// ���U���g

	CSoundMng*	m_pSoundMng;			// �T�E���h
	Fade*		m_pFade;				// �t�F�[�h

	int m_nResetNo;						// ���Z�b�g��
	int m_nClear;						// �N���A��
};

#endif // !__SCENE_MANAGER_H__
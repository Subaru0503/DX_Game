//=================================================================
//
//	sceneManager.cpp
//	�V�[���Ǘ�
//
//=================================================================

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

// ========== �C���N���[�h�� ==========

// ���݃C���N���[�h�h�~
class CSceneTitle;			// �^�C�g��
class CScenePreArea;		// �Q�[���V�[��
class CScenePreStage1Area;	// �X�e�[�W�O�G���A
class CSceneResult;			// ���U���g

// ========== �N���X ==========
class CSceneMng
{
public:
	enum SceneKind		// �X�e�[�W�̎�ށA����
	{
		SCENE_PRE_STAGE1_AREA = 1,
		SCENE_STAGE1,
		SCENE_PRE_STAGE2_AREA,
		SCENE_STAGE2,
		SCENE_PRE_STAGE3_AREA,
		SCENE_STAGE3,
		MAX_STAGE,

		SCENE_TITLE = 8,
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
	void SceneSwap();					// �V�[����؂�ւ���\


private:
	// ----- �V�[���Ǘ� -----
	bool m_GameEnd;			// �Q�[�����[�v������
	int	 m_scene;			// ���ݎ��s���̃V�[��
	int	 m_nextScene;		// ���̃V�[��

	// ----- �V�[���f�[�^ -----
	CSceneTitle*		m_pTitle;		// �^�C�g��
	CScenePreArea*	m_pScenePreArea;	// �Q�[���V�[��
	CScenePreStage1Area* m_pPreStage1;	// �X�e�[�W1�O�G���A
	CSceneResult*		m_pResult;		// ���U���g
	int m_nResetNo;						// ���Z�b�g��
	int m_nClear;						// �N���A��
};

#endif // !__SCENE_MANAGER_H__
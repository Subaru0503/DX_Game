//=================================================================
//
//	sceneManager.cpp
//	�V�[���Ǘ�
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"
#include "SceneTitle.h"				// �^�C�g��
#include "SceneGame.h"				// �Q�[���V�[��
#include "SceneResult.h"			// ���U���g

// ========== �萔�E�}�N����` ==========
#define FADE_IN			(true)
#define FADE_OUT		(false)
#define FADE_IN_TIME	(1.0f)
#define FADE_OUT_TIME	(1.0f)

// ========== �R���X�g���N�^ ==========
CSceneMng::CSceneMng()
	: m_scene(SCENE_GAME)
	, m_nextScene(SCENE_GAME)
	, m_GameEnd(false)
	, m_nResetNo(0)
	, m_nClear(0)
{
	//m_pTitle = new CSceneTitle(this);
	m_pSceneGame = new CSceneGame(this, SCENE_GAME);
	m_pFade = new Fade();				// �t�F�[�h
}

// ========== �f�X�g���N�^ ==========
CSceneMng::~CSceneMng()
{
	// =-=-= �V�[���ɉ������f�[�^�폜 =-=-=
	// ���݂��Ă���΍폜
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_GAME:	SAFE_DELETE(m_pSceneGame);  break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult); break;
	default: break;
	}
	SAFE_DELETE(m_pFade);
}

// ========== �X�V ==========
void CSceneMng::Update(float tick)
{
	if (!m_pFade->IsPlay()) {			//�����ȏ����̓t�F�[�h�������I����Ă���B
		if (m_scene != m_nextScene){	// �V�[���`�F���W���s���Ă���ΑJ��
			SceneSwap();
		}
	}

	// =-=-= �V�[���ɉ������X�V =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Update();			break;
	case SCENE_GAME:	m_pSceneGame->Update(tick); 	break;
	case SCENE_RESULT:	m_pResult->Update();	break;
	default: break;
	}

	// ----- �e��X�V -----
	m_pFade->Update();
}

// ========== �`�� ==========
void CSceneMng::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Draw();	break;
	case SCENE_GAME:	m_pSceneGame->Draw();	break;
	case SCENE_RESULT:	m_pResult->Draw();	break;
	default: break;
	}
	m_pFade->Draw();
}

// ========== �V�[���؂�ւ��ݒ� ==========
// ���@���FSceneKind �J�ڐ�V�[��
// �߂�l�F�Ȃ�
// �w��̃V�[����J�ڐ�ɐݒ�B
// ======================================
void CSceneMng::SetNextScene(SceneKind scene, int Deth)
{
	// �t�F�[�h���͎��̃V�[����\�񂵂Ȃ�
	if (m_pFade->IsPlay())
	{
		return;
	}

	m_nextScene = scene;	// ���V�[���\��

	// ----- �t�F�[�h -----
	switch (m_nextScene)
	{
	case SCENE_GAME:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::BLACK);	break;
	}
}

// ========== �V�[���؂�ւ� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �w��̃V�[���ɐ؂�ւ��A�K�v���������p��
// ==================================
void CSceneMng::SceneSwap()
{
	//switch (m_scene)	// �V�񂾃X�e�[�W�̏����i�[
	//{
	//case SCENE_GAME:	m_oldPlayStage = SCENE_GAME;	break;
	//case SCENE_STAGE2:	m_oldPlayStage = SCENE_STAGE2;	break;
	//case SCENE_STAGE3:	m_oldPlayStage = SCENE_STAGE3;	break;
	//}

	// =-=-= �V�����V�[���̓ǂݍ��� =-=-=
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pTitle = new CSceneTitle(this);	// �V�[���J�ڏ����Ăяo���̂���SceneMng*�󂯓n��
		break;
	case SCENE_GAME: m_pSceneGame = new CSceneGame(this, SCENE_GAME);  break;
	case SCENE_RESULT:
		m_pResult = new CSceneResult(this, m_nResetNo, m_nClear);
		break;
	}


	// =-=-= ���݂̃V�[���폜 =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_GAME:	SAFE_DELETE(m_pSceneGame); break;
	case SCENE_RESULT:	SAFE_DELETE(m_pResult);	m_nResetNo = 0; m_nClear = 0; break;
	default: break;
	}

	switch (m_nextScene)
	{
	//case SCENE_TITLE:
	//	if (m_scene == SCENE_ENDING || m_scene == SCENE_OPENING) {
	//		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::WHITE);	break;
	//	}
	case SCENE_GAME:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	default: break;
	}

	// �Q�[���V�[���ւ̑J�ڂłȂ���΃t�F�[�h�C��
	m_scene = m_nextScene;	// �V�[�����㏑��
}
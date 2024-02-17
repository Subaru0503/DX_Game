//=================================================================
//
//	sceneManager.cpp
//	�V�[���Ǘ�
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneManager.h"
#include "SceneTitle.h"				// �^�C�g��
#include "ScenePreArea.h"			// �Q�[���V�[��
#include "ScenePreStage1Area.h"		// �X�e�[�W1�O�G���A
#include "SceneResult.h"			// ���U���g

// ========== �萔�E�}�N����` ==========

// ========== �R���X�g���N�^ ==========
CSceneMng::CSceneMng()
	: m_scene(SCENE_TITLE)
	, m_nextScene(SCENE_TITLE)
	, m_GameEnd(false)
	, m_nResetNo(0)
	, m_nClear(0)
{
	m_pTitle = new CSceneTitle(this);
}

// ========== �f�X�g���N�^ ==========
CSceneMng::~CSceneMng()
{
	// =-=-= �V�[���ɉ������f�[�^�폜 =-=-=
	// ���݂��Ă���΍폜
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_GAME:	SAFE_DELETE(m_pScenePreArea);  break;
	case SCENE_PRE_STAGE1_AREA:	SAFE_DELETE(m_pPreStage1); break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	SAFE_DELETE(m_pResult); break;
	default: break;
	}
}

// ========== �X�V ==========
void CSceneMng::Update(float tick)
{
	//if (!m_pFade->IsPlay()) {	//�����ȏ����̓t�F�[�h�������I����Ă���B
	//	if (m_scene != m_nextScene)	SceneSwap();	// �V�[���`�F���W���s���Ă���ΑJ��
	//}
	//else {
	//	// �t�F�[�h�ɍ��킹��BGM�̃{�����[������(�K�v�ɂȂ����炱���Ɏ���)
	//}

	if (m_scene != m_nextScene)
	{
		SceneSwap();
	}

	// =-=-= �V�[���ɉ������X�V =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Update();			break;
	case SCENE_GAME:	m_pScenePreArea->Update(tick); 	break;
	case SCENE_PRE_STAGE1_AREA: m_pPreStage1->Update(tick);	break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	m_pResult->Update();	break;
	default: break;
	}

	// ----- �e��X�V -----
	//m_pFade->Update();
}

// ========== �`�� ==========
void CSceneMng::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Draw();	break;
	case SCENE_GAME:	m_pScenePreArea->Draw();	break;
	case SCENE_PRE_STAGE1_AREA: m_pPreStage1->Draw();	break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	m_pResult->Draw();	break;
	default: break;
	}
	//m_pFade->Draw();
}

// ========== �V�[���؂�ւ��ݒ� ==========
// ���@���FSceneKind �J�ڐ�V�[��
// �߂�l�F�Ȃ�
// �w��̃V�[����J�ڐ�ɐݒ�B
// ======================================
void CSceneMng::SetNextScene(SceneKind scene, int Deth)
{
	//// �t�F�[�h���͎��̃V�[����\�񂵂Ȃ�
	//if (m_pFade->IsPlay())
	//{
	//	return;
	//}

	m_nextScene = scene;	// ���V�[���\��

	//// ----- �t�F�[�h -----
	//switch (m_nextScene)
	//{
	//case SCENE_GAME:
	//case SCENE_STAGE2:
	//case SCENE_STAGE3:
	//	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::TIPS);	break;
	//	break;
	//default:
	//	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);	break;
	//	break;
	//}
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
	case SCENE_GAME: m_pScenePreArea = new CScenePreArea(this, SCENE_GAME);  break;
	case SCENE_PRE_STAGE1_AREA: m_pPreStage1 = new CScenePreStage1Area(this, SCENE_PRE_STAGE1_AREA);	break;
	case SCENE_STAGE3:
	case SCENE_RESULT:
		m_pResult = new CSceneResult(this, m_nResetNo, m_nClear);
		break;
	}


	// =-=-= ���݂̃V�[���폜 =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_GAME:	SAFE_DELETE(m_pScenePreArea); break;
	case SCENE_PRE_STAGE1_AREA: SAFE_DELETE(m_pPreStage1);	break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	SAFE_DELETE(m_pResult);	m_nResetNo = 0; m_nClear = 0; break;
	default: break;
	}

	// �Q�[���V�[���ւ̑J�ڂłȂ���΃t�F�[�h�C��
	m_scene = m_nextScene;	// �V�[�����㏑��
}
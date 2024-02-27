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
	m_pSoundMng = new CSoundMng();		// �T�E���h
	m_pFade = new Fade();				// �t�F�[�h
	m_pSceneGame = new CSceneGame(this, SCENE_GAME, m_pSoundMng);
	m_pSoundMng->playSound(CSoundMng::BGM::game);	// ���̃V�[����BGM���Đ�
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
	SAFE_DELETE(m_pSoundMng);
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
	m_pSoundMng->DeleteSpeaker();	// �Đ��I�������X�s�[�J�[��j��
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
	case SCENE_TITLE:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::BLACK);	break;
	case SCENE_GAME:
		m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::BLACK);	break;
	case SCENE_RESULT:
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
	m_pSoundMng->AllDeleteSpeaker();
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pTitle = new CSceneTitle(this);	// �V�[���J�ڏ����Ăяo���̂���SceneMng*�󂯓n��
		m_pSoundMng->playSound(CSoundMng::BGM::title);	// ���̃V�[����BGM���Đ�
		break;
	case SCENE_GAME: m_pSceneGame = new CSceneGame(this, SCENE_GAME, m_pSoundMng);
		m_pSoundMng->playSound(CSoundMng::BGM::game);	// ���̃V�[����BGM���Đ�
		break;

	case SCENE_RESULT:
		m_pResult = new CSceneResult(this, m_nResetNo, m_nClear);
		m_pSoundMng->playSound(CSoundMng::BGM::result);	// ���̃V�[����BGM���Đ�
		break;
	}

	// =-=-= �K�v�����p�� =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	break;
	case SCENE_GAME:	if (m_nextScene == SCENE_RESULT)PassData(m_pSceneGame, m_pResult);	break;	// ���U���g��
	case SCENE_RESULT:	break;
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
	case SCENE_TITLE:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	case SCENE_GAME:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	case SCENE_RESULT:
		m_pFade->Start(FADE_IN, FADE_IN_TIME, Fade::BLACK);	break;
	default: break;
	}

	// �Q�[���V�[���ւ̑J�ڂłȂ���΃t�F�[�h�C��
	m_scene = m_nextScene;	// �V�[�����㏑��
}

// ========== �V�[���ԃf�[�^���p��:Select �� Stage==========
// ���@���F
// CSceneSelect* 
// CSceneStageBase* 
// �߂�l�F�Ȃ�
// �`�֐��T�v�`
// �Z���N�g����X�e�[�W�V�[���֕K�v�ȃf�[�^�������p��
// ========================================================
void CSceneMng::PassData(CSceneStageBase* game, CSceneResult* result)	// Select �� Stage
{
	// ----- �󂯓n�� -----
	result->SetTotalScore(game->GetTotalScore());	// ���v�X�R�A���Z�b�g
	result->SetMinusScore(game->GetMinusScore());	// �[���v�X�R�A���Z�b�g
	result->SetFruitsNum(game->GetFruitsNum());		// ���߂��t���[�c�̐�
	result->SetCanNum(game->GetCanNum());			// ���߂��J���̐�
}

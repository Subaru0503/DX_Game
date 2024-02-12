//=================================================================
//
//	SceneTitle.cpp
//	�^�C�g���V�[��
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneTitle.h"
#include "Input.h"

// ========== �R���X�g���N�^ ==========
CSceneTitle::CSceneTitle(CSceneMng* pSceneMng)
	: m_pushEsc(false)
	, m_select(true)
	, m_pSceneMng(pSceneMng)
{

}

// ========== �f�X�g���N�^ ==========
CSceneTitle::~CSceneTitle()
{

}

// ========== Update�֐� ==========
void CSceneTitle::Update()
{

	// =-=-= �Q�[���I���m�F��� =-=-=
	//�L�[�{�[�h����
	//if (m_pushEsc) {
	//	// ----- �{�^���I���󋵁F�͂� -----
	//	if (m_select) {
	//		if (IsKeyTrigger('D') || IsKeyTrigger(VK_RIGHT))			// �������ɃJ�[�\���ړ�
	//		{
	//			m_select ^= 1;
	//			m_pEscape->SetNo();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::select);

	//		}
	//		else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE))	// �Q�[���I��
	//		{
	//			m_pSceneMng->SetGameEnd();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
	//		}
	//	}
	//	// ----- �{�^���I���󋵁F������ -----
	//	else {
	//		if (IsKeyTrigger('A') || IsKeyTrigger(VK_LEFT))				// �͂��ɃJ�[�\���ړ�
	//		{
	//			m_select ^= 1;
	//			m_pEscape->SetYes();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::select);
	//		}
	//		else if (IsKeyPress(VK_RETURN) || IsKeyTrigger(VK_SPACE))	// �m�F��ʂ����
	//		{
	//			m_pushEsc = false;
	//			m_pEscape->SetWindowAnime();
	//			m_pSoundMng->playSound(CSoundMng::SystemSE::decision);
	//		}
	//	}
	//}

	// =-=-= �^�C�g����� =-=-=
	{	// �I���m�F��ʂ��J���Ă��Ȃ�
	   //if (IsKeyTrigger(VK_ESCAPE))	m_pushEsc = true;		// ESC�Ŋm�F��ʊJ��

	   // ----- �Q�[���X�^�[�g -----
		if (IsKeyTrigger(VK_RETURN)) {
			//m_pSoundMng->playSound(CSoundMng::SystemSE::Tstrat);
			//animestart = true;
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_STAGE1, 1);
		}
	}

	//if (animestart)
	//{
	//	animefin = m_pTitle->AnimeButton();
	//	if (animefin)
	//	{
	//		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_SELECT);
	//		animestart = false;
	//	}
	//}
}

// ========== Draw�֐� ==========
void CSceneTitle::Draw()
{
	
}
//=================================================================
//
//	SoundManager.cpp
//	SE���ꌳ�Ǘ�����
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SoundManager.h"

// ========== �萔�E�}�N����` ==========
// ----- �萔 -----
#define TITLE_BGM_VOL			(0.8f)	// �^�C�g��BGM
#define GAEM_BGM_VOL			(0.7f)	// �Q�[��BGM
#define RESULT_BGM_VOL			(0.8f)	// ���U���gBGM
#define DECSION_VOL				(0.2f)	// ���� 
#define CANCEL_VOL				(1.0f)	// �L�����Z�� 
#define SELECT_VOL				(1.0f)	// �I�� 
#define TSTRAT_VOL				(1.0f)	//�Q�[���J�n(�^�C�g��)
#define SWAP_VOL				(0.5f)	//�X�e�[�W�`�F���W
#define OP_BGM_VOL				(1.0f)	//�I�[�v�j���O
#define ED_BGM_VOL				(1.0f)	//�G���f�B���O
#define GET_FRUITS_SE_VOL		(1.0f)	// �t���[�c���艹
#define EXCELLENT_SE_VOL		(0.4f)	// �G
#define GOOD_SE_VOL		(0.7f)	// ��
#define BAD_SE_VOL		(1.0f)	// ��

// ----- �}�N�� -----
#define STR(var) #var   //�����ɂ����ϐ���ϐ���������������Ƃ��ĕԂ��}�N���֐�

// ========== �R���X�g���N�^ ==========
CSoundMng::CSoundMng()
{
	// =-=-= �eBGM�ǂݍ��� =-=-=
	m_pSoundMap[STR(CSoundMng::BGM::title)] = LoadSound("Assets/BGM/�^�C�g��.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game)] = LoadSound("Assets/BGM/�Q�[��.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::result)] = LoadSound("Assets/BGM/���U���g.mp3", true);

	// ---- ���艹 ----
	m_pSoundMap[STR(CSoundMng::GetSE::fruits)] = LoadSound("Assets/SE/���艹/�t���[�c����.mp3");
	m_pSoundMap[STR(CSoundMng::JudgeSE::excellent)] = LoadSound("Assets/SE/�y�A�g�ݍ��킹/�G.mp3");
	m_pSoundMap[STR(CSoundMng::JudgeSE::good)] = LoadSound("Assets/SE/�y�A�g�ݍ��킹/��.mp3");
	m_pSoundMap[STR(CSoundMng::JudgeSE::bad)] = LoadSound("Assets/SE/�y�A�g�ݍ��킹/��.mp3");

}

// ========== �f�X�g���N�^ ==========
CSoundMng::~CSoundMng()
{
	// =-=-= ��� =-=-=
	// ----- ����map -----
	for (auto it = m_pSoundMap.begin(); it != m_pSoundMap.end();) {	// �S�T�E���h�f�[�^�����
		//delete it->second->pAudioData;						// �T�E���h�f�[�^����� Sound.h������Ă����̂ŏȗ�
		it = m_pSoundMap.erase(it);								// �|�C���^���J��
	}

	// ----- �X�s�[�J�[list -----
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();) {	// �S�X�s�[�J�[�f�[�^�����
		if ((*it)) {
			(*it)->m_Speaker->Stop();						// �Đ���~(�s�v�H)
			(*it)->m_Speaker->DestroyVoice();				// ����j��
			delete (*it);									// �K�v�H�s�v�H�H���ꏑ���ƎQ�ƃG���[�o��B	Destroy�œ��I�f�[�^�����Ă�H
			it = m_pSpeakerList.erase(it);				// �|�C���^���J��
		}
	}
}


// ========== �Đ��I���X�s�[�J�[�j�� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �Đ����I�����SE�X�s�[�J�[��j������
// ==========================================
void CSoundMng::DeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// �S�Ă�SE�X�s�[�J�[���݂�
	{
		XAUDIO2_VOICE_STATE state{ 0 };
		(*it)->m_Speaker->GetState(&state);					// �Đ��󋵎擾
		if (state.BuffersQueued == 0)						// �Đ����I����Ă�����j��
		{
			// ----- �X�s�[�J�[�폜 -----
			(*it)->m_Speaker->Stop();						// �Đ���~(�s�v�H)
			(*it)->m_Speaker->DestroyVoice();				// ����j��
			delete (*it);									// �X�s�[�J�[�\���̂̎��̉��
			it = m_pSpeakerList.erase(it);				// �|�C���^���J��
		}
		else
		{
			it++;								// ���̗v�f��
		}
	}
}

// ========== �Đ����X�s�[�J�[�S�j�� ==========
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �Đ����̑S�ẴX�s�[�J�[��j������
// ==========================================
void CSoundMng::AllDeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// �S�Ă�SE�X�s�[�J�[���݂�
	{
		// ----- �X�s�[�J�[�폜 -----
		(*it)->m_Speaker->Stop();						// �Đ���~(�s�v�H)
		(*it)->m_Speaker->DestroyVoice();				// ����j��
		delete (*it);									// �X�s�[�J�[�\���̂̎��̉��
		it = m_pSpeakerList.erase(it);					// �|�C���^���J��
	}
}

// ========== BGM�Đ� ==========
// ���@���F
// BGM �炵����BGM�ԍ�
// �߂�l�F�Ȃ�
// �w���BGM��炷
// =====================================
void CSoundMng::playSound(BGM kind)
{
	switch (kind)
	{
	case CSoundMng::BGM::title:	// �^�C�g��BGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::title)]), SpeakerKind::bTitle });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TITLE_BGM_VOL);
		break;
	case CSoundMng::BGM::game:	// �Q�[��BGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM_BGM_VOL);
		break;
	case CSoundMng::BGM::result:	// ���U���gBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::result)]), SpeakerKind::bResult });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RESULT_BGM_VOL);
		break;
	}
}

// ========== �V�X�e��SE�Đ� ==========
// ���@���F
// SystemSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃V�X�e��SE��炷
// ===================================
void CSoundMng::playSound(SystemSE kind)
{
	//switch (kind)
	//{
	//case CSoundMng::decision:	// ����
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::decision)]), SpeakerKind::sDecision });	// �X�s�[�J�[����
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(DECSION_VOL);	// �����ɏ��������(���Ԃ�0.0/*�ŏ�*/ ~ 1.0/*�ő�*/)
	//	break;
	//case CSoundMng::cancel:		// �L�����Z��
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::cancel)]), SpeakerKind::sCancel });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(CANCEL_VOL);
	//	break;
	//case CSoundMng::select:		// �I��
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::select)]), SpeakerKind::sSelect });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_VOL);
	//	break;
	//case CSoundMng::Tstrat:		// �Q�[���J�n
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::Tstrat)]), SpeakerKind::sTStrat });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(TSTRAT_VOL);
	//	break;
	//case CSoundMng::swap:		// �X�e�[�W�`�F���W
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::swap)]), SpeakerKind::sSwap });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(SWAP_VOL);
	//	break;
	//}
}

// ========== ����SE�Đ� ==========
// ���@���F
// GetSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃V�X�e��SE��炷
// ===================================
void CSoundMng::playSound(GetSE kind)
{
	switch (kind)
	{
	case CSoundMng::fruits:	// �t���[�c����
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GetSE::fruits)]), SpeakerKind::bFruits });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(GET_FRUITS_SE_VOL);	// �����ɏ��������(���Ԃ�0.0/*�ŏ�*/ ~ 1.0/*�ő�*/)
		break;
	}
}

// ========== ����SE�Đ� ==========
// ���@���F
// JudgeSE �炵����SE�ԍ�
// �߂�l�F�Ȃ�
// �w��̃V�X�e��SE��炷
// ===================================
void CSoundMng::playSound(JudgeSE kind)
{
	switch (kind)
	{
	case CSoundMng::excellent:	// �G
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::JudgeSE::excellent)]), SpeakerKind::bExcellent });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(EXCELLENT_SE_VOL);	// �����ɏ��������(���Ԃ�0.0/*�ŏ�*/ ~ 1.0/*�ő�*/)
		break;
	case CSoundMng::good:	// �G
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::JudgeSE::good)]), SpeakerKind::bGood });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(GOOD_SE_VOL);	// �����ɏ��������(���Ԃ�0.0/*�ŏ�*/ ~ 1.0/*�ő�*/)
		break;
	case CSoundMng::bad:	// �G
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::JudgeSE::bad)]), SpeakerKind::bBad });	// �X�s�[�J�[����
		m_pSpeakerList.back()->m_Speaker->SetVolume(BAD_SE_VOL);	// �����ɏ��������(���Ԃ�0.0/*�ŏ�*/ ~ 1.0/*�ő�*/)
		break;
	}
}

// ========== �V�X�e��SE�Đ��I���`�F�b�N ===============
// ���@���F
// SystemSE ���ׂ���SE�ԍ�
// �߂�l�F�Đ��I��(or �Đ����ĂȂ�) �� true
// �w��̃V�X�e��SE���Đ��I���������`�F�b�N
// ==========================================
//bool CSoundMng::CheckSoundEnd(SystemSE kind)
//{
	//for (Speaker* pSpeaker : m_pSpeakerList)
	//{
	//	switch (kind)
	//	{
	//	case CSoundMng::SystemSE::decision:
	//		if (pSpeaker->m_Kind == sDecision) return false;
	//		break;
	//	case CSoundMng::SystemSE::cancel:
	//		if (pSpeaker->m_Kind == sCancel) return false;
	//		break;
	//	case CSoundMng::SystemSE::select:
	//		if (pSpeaker->m_Kind == sSelect) return false;
	//		break;
	//	case CSoundMng::SystemSE::swap:
	//		if (pSpeaker->m_Kind == sSwap) return false;
	//		break;
	//	}
	//}

	//return true;
//}

//bool CSoundMng::CheckSoundEnd(GetSE kind)
//{
//	for (Speaker* pSpeaker : m_pSpeakerList)
//	{
//		switch (kind)
//		{
//		case CSoundMng::GetSE::fruits:
//			if (pSpeaker->m_Kind == bFruits) return false;
//			break;
//		}
//	}
//
//	return true;
//}


// ========== BGM�Đ���~ ==========
// ���@���F
// BGM ��~������BGM�ԍ�
// �߂�l�F�Ȃ�
// �w���BGM�̍Đ����~���A�X�s�[�J�[��j������
// ==========================================
void CSoundMng::StopSound(BGM kind)
{
	bool flg = false;	// �Đ���

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// �S�Đ���SE�̒�����w���SE��T��
	{
		switch (kind)
		{
		case CSoundMng::BGM::title:
			if ((*it)->m_Kind == bTitle) flg = true;
			break;
		case CSoundMng::BGM::game:
			if ((*it)->m_Kind == bGame) flg = true;
			break;
		case CSoundMng::result:
			if ((*it)->m_Kind == bResult) flg = true;
			break;
		}

		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}

void CSoundMng::StopSound(SystemSE kind)
{
	bool flg = false;	// �Đ���
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
	{
		//switch (kind)
		//{
		//case CSoundMng::SystemSE::Fpon:
		//	if ((*it)->m_Kind == sFpon) flg = true;
		//	break;
		//}
		if (flg)	// �Đ����̎w��SE���������炻���j��
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}
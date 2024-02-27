//=================================================================
//
//	SoundManager.h
//	�T�E���h���ꌳ�Ǘ�����
//
//=================================================================

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

// ========== �C���N���[�h�� ==========
#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
using namespace std;

// ========== �N���X ==========
class CSoundMng
{
public:	// �񋓌^ �O���ďo���p
	// =-=-= BGM =-=-=
	enum BGM {
		title,
		game,
		result,
	};

	// =-=-= SE =-=-=
	// ----- �V�X�e���� -----
	enum SystemSE {
		decision,		// ����
		cancel,			// �L�����Z��
		select,			// �I��
		Tstrat,			//�Q�[���J�n(�^�C�g��)
		swap,			//�X�e�[�W�`�F���W
		Fpon,			//���U���gSE
	};

	// ----- ���艹 -----
	enum GetSE {
		fruits,			// �t���[�c
		Can,			// �󂫊�
	};

	// ---- ���艹 ----
	enum JudgeSE {
		excellent,
		good,
		bad,
	};
public:	// �֐�
	CSoundMng();
	~CSoundMng();
	void DeleteSpeaker();							// �Đ��I������SE�X�s�[�J�[���폜
	void AllDeleteSpeaker();						// �Đ����̃X�s�[�J�[��S�폜

	// =-=-= �Đ� =-=-=
	// ----- BGM -----
	void playSound(BGM kind);						// BGM

	// ----- SE -----
	void playSound(SystemSE kind);					// �V�X�e����
	void playSound(GetSE kind);						// ���艹
	void playSound(JudgeSE kind);					// ���艹

	// =-=-= �Đ��I���`�F�b�N =-=-=
	// ----- BGM -----
	//bool CheckSoundEnd(BGM kind);

	// ----- SE -----
	//bool CheckSoundEnd(SystemSE kind);				// �V�X�e���w���SE���Đ��I���������`�F�b�N
	//bool CheckSoundEnd(GetSE kind);					// ����w���SE���Đ��I���������`�F�b�N

	// =-=-= �Đ���~ =-=-=
	// ----- BGM -----
	void StopSound(BGM kind);						// BGM

	// ----- SE -----
	void StopSound(SystemSE kind);				// �V�X�e����SE�Đ���~


private: // �񋓌^�@���������p
	enum SpeakerKind
	{
		//----BGM----
		bTitle,			// �^�C�g��
		bGame,			// �Q�[��
		bResult,		// ���U���g
		//----SE----
		bFruits,		// �t���[�c����
		bExcellent,		// �G
		bGood,			// ��
		bBad,			// ��
	};

	typedef struct		// �X�s�[�J�[
	{
		IXAudio2SourceVoice*	m_Speaker;		// �X�s�[�J�[
		SpeakerKind				m_Kind;				// �X�s�[�J�[�̎��
	}Speaker;

private:

	map<string, XAUDIO2_BUFFER*> m_pSoundMap;		// �����pmap
	list<Speaker*> m_pSpeakerList;					// �X�s�[�J�[�plist
};
#endif // !__SOUND_MANAGER_H__
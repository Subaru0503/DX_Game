//----�C���N���[�h�K�[�h----
#ifndef ___TIME_UI_H___
#define ___TIME_UI_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_TIME_UI (5)
#define DIGIT_TIME			(2)	//�G�t�F�N�g�̐��i�z��̐��j
#define ANIM_TIME_FRAME	(2)		//�A�j���[�V������R�}�t���[����
#define ANIM_TIME_SPLIT_X	(5)		//�摜�������i���j
#define ANIM_TIME_SPLIT_Y	(3)		//�摜�������i�c�j

//----�N���X��`----
class CTimeUI
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		frame;			//�A�j���[�V�����Ǘ��t���[��
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_TIME_PARAM;		//�p�����[�^�̍\����

	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_ADDMANEY_PARAM;		//�p�����[�^�̍\����

public:
	CTimeUI();		// �R���X�g���N�^
	~CTimeUI();				// �f�X�g���N�^
	void Update();				// �X�V
	void Draw();				// �`��
	void UpdateTimetexCoord();	// �\�����ԍX�V
	float GetTimeLimit();		// �������ԏ���Ԃ�
	float GetElapsedTime();		// �o�ߎ��ԏ���Ԃ�

private:
	ST_TIME_PARAM m_time[DIGIT_TIME + 1];
	unsigned int m_TextureTime;
	float m_fTimeLimit;			// ��������
	float m_fElapsedTime;			// �o�ߎ���
	//int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fAlpha;
	Texture* m_pTexture[MAX_TIME_UI];

};


#endif // !___TIME_UI_H___
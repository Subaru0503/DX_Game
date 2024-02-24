//----�C���N���[�h�K�[�h----
#ifndef ___SCORE_UI_H___
#define ___SCORE_UI_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_UI (1)
#define DIGIT_SCORE			(5)	//�G�t�F�N�g�̐��i�z��̐��j
#define ANIM_SCORE_FRAME	(2)		//�A�j���[�V������R�}�t���[����
#define ANIM_SCORE_SPLIT_X	(5)		//�摜�������i���j
#define ANIM_SCORE_SPLIT_Y	(3)		//�摜�������i�c�j

//----�N���X��`----
class CScoreUI
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
	}ST_SCORE_PARAM;		//�p�����[�^�̍\����

	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int		currentAnimNo;	//�A�j���[�V�����R�}�ԍ��i���ォ��O�`�j
	}ST_ADDMANEY_PARAM;		//�p�����[�^�̍\����

public:
	CScoreUI(int Score);		// �R���X�g���N�^
	~CScoreUI();				// �f�X�g���N�^
	void Update();				// �X�V
	void Draw();				// �`��
	void UpdateScoretexCoord();	// �\���X�R�A�X�V
	void SetScore(int score);	// �X�R�A�Z�b�g

private:
	ST_SCORE_PARAM m_score[DIGIT_SCORE];
	int m_nScore;
	//int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fAlpha;
	Texture* m_pTexture[MAX_UI];

};


#endif // !___SCORE_UI_H___
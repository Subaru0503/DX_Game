//----�C���N���[�h�K�[�h----
#ifndef ___RESULT_SCORE_H___
#define ___RESULT_SCORE_H___

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_RESULT_SCORE   (2)				// ���U���g����
#define DIGIT_RESULT_SCORE			(5)		//�G�t�F�N�g�̐��i�z��̐��j
#define ANIM_RESULT_SCORE_FRAME	(2)			//�A�j���[�V������R�}�t���[����
#define ANIM_RESULT_SCORE_SPLIT_X	(5)		//�摜�������i���j
#define ANIM_RESULT_SCORE_SPLIT_Y	(2)		//�摜�������i�c�j

//----�N���X��`----
class CResultScore
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

public:
	CResultScore();		// �R���X�g���N�^
	~CResultScore();				// �f�X�g���N�^
	void Update();				// �X�V
	void Draw();				// �`��
	void UpdateScoretexCoord(int index);	// �\���X�R�A�X�V
	void SetScore(int score, int index);	// �X�R�A�Z�b�g

private:
	ST_SCORE_PARAM m_score[MAX_RESULT_SCORE][DIGIT_RESULT_SCORE];
	int m_nScore;			// �X�R�A
	//int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fAlpha;
	Texture* m_pTexture[MAX_RESULT_SCORE];

};


#endif // !___RESULT_SCORE_H___
//=================================================================
//
//	ResultBackGround.cpp
//	���U���g�w�i
//
//=================================================================
#ifndef __RESULT_BACKGROUND_H__
#define __RESULT_BACKGROUND_H__

// ========== �C���N���[�h�� ==========
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_RESULT_TEXTURE (3)	// �e�N�X�`���ő吔

// ========== �N���X ==========
class CResultBackGround
{
public:
	CResultBackGround();
	~CResultBackGround();
	void Update();
	void Draw();

private:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
	}ST_RESULT_BACKGROUND_PARAM;		//�p�����[�^�̍\����
private:
	ST_RESULT_BACKGROUND_PARAM m_ResultBackGround;
	Texture* m_pTexture[MAX_RESULT_TEXTURE];	// �e�N�X�`���̐�
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
};

#endif // !__RESULT_BACKGROUND_H__
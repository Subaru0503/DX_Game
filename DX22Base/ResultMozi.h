//=================================================================
//
//	ResultMozi.cpp
//	�^�C�g���w�i
//
//=================================================================
#ifndef __RESULT_MOZI_H__
#define __RESULT_MOZI_H__

// ========== �C���N���[�h�� ==========
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_RESULT_MOZI_TEXTURE (6)	// �e�N�X�`���ő吔

// ========== �N���X ==========
class CResultMozi
{
public:
	CResultMozi();
	~CResultMozi();
	void Update();
	void Draw();

private:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
	}ST_RESULT_MOZI_PARAM;		//�p�����[�^�̍\����
private:
	ST_RESULT_MOZI_PARAM m_ResultMozi[MAX_RESULT_MOZI_TEXTURE];
	Texture* m_pTexture[MAX_RESULT_MOZI_TEXTURE];	// �e�N�X�`���̐�
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
};

#endif // !__RESULT_MOZI_H__
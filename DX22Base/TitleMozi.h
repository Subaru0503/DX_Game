//=================================================================
//
//	TitleMozi.cpp
//	�^�C�g���w�i
//
//=================================================================
#ifndef __TITLE_MOZI_H__
#define __TITLE_MOZI_H__

// ========== �C���N���[�h�� ==========
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_TEXTURE (2)	// �e�N�X�`���ő吔

// ========== �N���X ==========
class CTitleMozi
{
public:
	CTitleMozi();
	~CTitleMozi();
	void Update();
	void Draw();

private:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		float alpha;					// �����x
	}ST_TITLE_MOZI_PARAM;		//�p�����[�^�̍\����
private:
	ST_TITLE_MOZI_PARAM m_TitleMozi[MAX_TEXTURE];
	Texture* m_pTexture[MAX_TEXTURE];	// �e�N�X�`���̐�
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	int m_nAlfhaFlg;	// �����t���O
};

#endif // !__TITLE_MOZI_H__
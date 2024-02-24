//=================================================================
//
//	TitleBackGround.cpp
//	�^�C�g���w�i
//
//=================================================================
#ifndef __TITLE_BACKGROUND_H__
#define __TITLE_BACKGROUND_H__

// ========== �C���N���[�h�� ==========
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

// ========== �N���X ==========
class CTitleBackGround
{
public:
	CTitleBackGround();
	~CTitleBackGround();
	void Update();
	void Draw();

private:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
	}ST_TITLE_BACKGROUND_PARAM;		//�p�����[�^�̍\����
private:
	ST_TITLE_BACKGROUND_PARAM m_TitleBackGround;
	Texture* m_pTexture;	// �e�N�X�`���̐�
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
};

#endif // !__TITLE_BACKGROUND_H__
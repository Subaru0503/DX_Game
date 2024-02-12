// ItemUI.h

//----�C���N���[�h�K�[�h----
#ifndef __ITEM_UI_H__
#define __ITEM_UI_H__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Texture.h"

//----�N���X��`----
class ItemUI
{
public:
	ItemUI();	// �R���X�g���N�^
	~ItemUI();	// �f�X�g���N�^
	void Update();	// �X�V
	void Draw();	// �`��

private:
	Texture* m_pTexture;
};

#endif
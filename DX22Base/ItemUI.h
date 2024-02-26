// ItemUI.h

//----�C���N���[�h�K�[�h----
#ifndef __ITEM_UI_H__
#define __ITEM_UI_H__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Texture.h"

//----�萔�E�}�N����`----
#define MAX_ITEM_UI (16)	// UI�ő吔
#define MAX_ITEM_TEXTURE (8)	// �e�N�X�`���ő吔

//----�N���X��`----
class ItemUI
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//���S���W
		DirectX::XMFLOAT2 size;			//���c�T�C�Y
		DirectX::XMFLOAT2 posTexCoord;	//�e�N�X�`�����W�i����j
		DirectX::XMFLOAT2 sizeTexCoord;	//�e�N�X�`���T�C�Y�i�E���j
		int kind;						// �t���[�c�̎��
		float alpha;					// �����x
		int drawFlg;					// �`��t���O
	}ST_ITEM_PARAM;		//�p�����[�^�̍\����
public:
	ItemUI();	// �R���X�g���N�^
	~ItemUI();	// �f�X�g���N�^
	void Update();	// �X�V
	void Draw();	// �`��

	void SetUP(DirectX::XMFLOAT3 pos, int kind, int draw);	// �`��ɕK�v�ȃp�����[�^���Z�b�g Pos, kind, drawFlg
	void ResetDrawFlg();		// �`��̃t���O��������
private:
	ST_ITEM_PARAM m_Item[MAX_ITEM_UI];
	Texture* m_pTexture[MAX_ITEM_TEXTURE];
};

#endif
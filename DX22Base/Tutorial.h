//----�C���N���[�h�K�[�h----
#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Shader.h"
#include "CameraBase.h"
#include "Model.h"
#include "Texture.h"
//----UI----
#include "ItemUI.h"

//----�N���X��`----
class Tutorial
{
public:
	Tutorial(DirectX::XMFLOAT3 TutorialPos);	// �R���X�g���N�^
	~Tutorial();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	//�@�J�����̐ݒ�
	void SetCamera(CameraBase* pCamera);
	// �`���[�g���A������
	void AddScore(int kind, int color, int add);

	void SetItemUI(ItemUI* ItemUI);	// �A�C�e��UI�Z�b�g
	void SetResetFlg(int flg);		// ���Z�b�g�t���O�Z�b�g

	// ���ݒn�̎擾
	DirectX::XMFLOAT3 GetPos();
	// �v���C���[�̃T�C�Y�擾
	DirectX::XMFLOAT3 GetSize();
	// ���Z�b�g�t���O���Q�b�g
	int GetResetFlg();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;		// �J�����̎Q��
	DirectX::XMFLOAT3 m_pos;	// �v���C���[�̈ʒu
	DirectX::XMFLOAT3 m_size;	// �v���C���[�̃T�C�Y
	Texture* m_pTexture[2];

	ItemUI* m_pUI;	// UI

	int m_nPrevItem;		// �ЂƂڂɎ�ɓ��ꂽ�A�C�e��
	int m_nResetFlg;		// ���Z�b�g���Ăяo���t���O
};
#endif		// __TUTORIAL_H__

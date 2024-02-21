// Lemon.cpp

//=====�C���N���[�h=====
#include "Lemon.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CLemon::CLemon(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ)
	: Object(posX, posY, posZ)	// �e�N���X�̃R���X�g���N�^�Ɉ�����n��)
{
	// ��{����������
	Init();

	// ��������X�P�[���ݒ�
	m_scale = { sizeX, sizeY, sizeZ };

	// �폜�t���O������
	m_bDelete = false;

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	m_nKind = Object::LEMON;

	// �t���[�c�t���O�𗧂Ă�
	m_nFruits = true;

	// �F�̐ݒ�
	m_nColor = Object::YELLOW;

	// �X�R�A�ݒ�
	m_nScore = 250;

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Fruits/Lemon/Lemon.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Fruits/Lemon/Lemon.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}

	// �����������ς���
	SetAngle(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_mass = 1.2f;
}

/********************
*@brief �f�X�g���N�^
*********************/
CLemon::~CLemon()	// �f�X�g���N�^
{
	SAFE_DELETE(m_pModel);
}
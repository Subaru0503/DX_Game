// Apple.cpp

//=====�C���N���[�h=====
#include "Apple.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CApple::CApple(float posX, float posY, float posZ,
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
	m_nKind = Object::APPLE;

	// �t���[�c�t���O�𗧂Ă�
	m_nFruits = true;

	// �X�R�A�ݒ�
	m_nScore = 150;

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Fruits/Apple/Apple.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Fruits/Apple/Apple.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}

	// �����������ς���
	SetAngle(DirectX::XMFLOAT3(0.0f, 90.0f, 0.0f));

	m_mass = 1.0f;
}

/********************
*@brief �f�X�g���N�^
*********************/
CApple::~CApple()	// �f�X�g���N�^
{
	SAFE_DELETE(m_pModel);
}
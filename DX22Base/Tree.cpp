// Tree.cpp

//=====�C���N���[�h=====
#include "Tree.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief ���W���X�P�[���ݒ�����t���R���X�g���N�^
*************************************************/
CTree::CTree(float posX, float posY, float posZ,
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
	m_nKind = Object::TREE;

	// �t���[�c�t���O��������
	m_nFruits = false;

	// �F�̐ݒ�
	m_nColor = Object::NONE;

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Tree/Tree.fbx", 1.0f, Model::Flip::XFlip))	// ���f���f�[�^�ǂݍ���
	{
		MessageBox(NULL, "�hAssets/Model/Tree/Tree.fbx�h���ǂݍ��߂܂���ł���", "Error", MB_OK);	// �G���[���b�Z�[�W
	}
}

/********************
*@brief �f�X�g���N�^
*********************/
CTree::~CTree()	// �f�X�g���N�^
{
	SAFE_DELETE(m_pModel);
}
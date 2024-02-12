// ItemUI.cpp
//----�C���N���[�h��----
#include "ItemUI.h"
#include "Sprite.h"

ItemUI::ItemUI()	// �R���X�g���N�^
{
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/Star.png")))
	{
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}
}

ItemUI::~ItemUI()	// �f�X�g���N�^	
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void ItemUI::Update()	// �X�V
{

}

void ItemUI::Draw()		// �`��
{
	DirectX::XMFLOAT4X4 mat[3];

	// ���[���h�s���X��Y�݂̂��l�����č쐬
	DirectX::XMMATRIX world =
		DirectX::XMMatrixTranslation(1080.0f, 520.0f, 0.0f);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	// �P�ʍs��̐ݒ�
	// �P�ʍs��͉񐔁A�g��k�����Ȃ�
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	// �v���W�F�N�V�����s��ɂ�2D�Ƃ��ĕ\�����邽�߂̍s��ݒ�
	// ���̍s���2D�̃X�N���[���̑傫�������܂�
	// 2D�̓s�N�Z���P��
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);	// �����̒l��ς���Ό��_�̈ʒu��ς����
													// ���オ0.0, 0.0
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// �X�v���C�g�̐ݒ�
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(300.0f, -300.0f));	// �w�ʃJ�����O�̑΍��-�ɂ�����o��
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();

}
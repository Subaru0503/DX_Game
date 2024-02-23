//=================================================================
//
//	ResultBackGround.cpp
//	���U���g�w�i
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "ResultBackGround.h"
#include "Defines.h"

// ========== �R���X�g���N�^ ==========
CResultBackGround::CResultBackGround()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr, nullptr, nullptr }
{
	for (int i = 0; i < MAX_RESULT_TEXTURE; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	// �^�C�g���w�i
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/ResultBackGround.jpg")))
	{
		MessageBox(NULL, "UI ResultBackGround.jpg", "Error", MB_OK);
	}

	m_ResultBackGround.size = DirectX::XMFLOAT2(1280.0f, 720.0f);
	m_ResultBackGround.pos = DirectX::XMFLOAT3(640.0f, 360.0f, 0.0f);
	m_ResultBackGround.posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_ResultBackGround.sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
}

// ========== �f�X�g���N�^ ==========
CResultBackGround::~CResultBackGround()
{
	for (int i = 0; i < MAX_RESULT_TEXTURE; ++i)
	{
		if (m_pTexture[i])
		{
			SAFE_DELETE(m_pTexture[i]);
		}
	}
}

// ========== Update�֐� ==========
void CResultBackGround::Update()
{

}

// ========== Draw�֐� ==========
void CResultBackGround::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world;

	//���[���h�s���X,Y�݂̂��l�����č쐬

	world = DirectX::XMMatrixTranslation(m_ResultBackGround.pos.x, m_ResultBackGround.pos.y, m_ResultBackGround.pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));


	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// �w�i
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_ResultBackGround.size.x, -m_ResultBackGround.size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_ResultBackGround.posTexCoord.x, m_ResultBackGround.posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_ResultBackGround.sizeTexCoord.x, m_ResultBackGround.sizeTexCoord.y));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);
	Sprite::Draw();
}
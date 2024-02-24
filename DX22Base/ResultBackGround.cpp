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
	, m_pTexture{ nullptr, nullptr }
{
	for (int i = 0; i < MAX_RESULT_TEXTURE; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	// ���U���g�w�i
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/ResultBackGround.jpg")))
	{
		MessageBox(NULL, "UI ResultBackGround.jpg", "Error", MB_OK);
	}

	// �|�C���g�Ȃǂ̔w�i
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/TimerBackGround.png")))
	{
		MessageBox(NULL, "UI TimerBackGround.png", "Error", MB_OK);
	}

	// ���U���g�w�i
	m_ResultBackGround[0].size = DirectX::XMFLOAT2(1280.0f, 720.0f);
	m_ResultBackGround[0].pos = DirectX::XMFLOAT3(640.0f, 360.0f, 0.0f);
	m_ResultBackGround[0].alpha = 1.0f;

	// �|�C���g�Ȃǂ̔w�i
	m_ResultBackGround[1].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 1.6f, m_pTexture[0]->GetHeight() * 0.9f);
	m_ResultBackGround[1].pos = DirectX::XMFLOAT3(640.0f, 380.0f, 0.0f);
	m_ResultBackGround[1].alpha = 0.51f;

	for (int i = 0; i < MAX_RESULT_TEXTURE; i++)
	{
		m_ResultBackGround[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ResultBackGround[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
	}
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
	DirectX::XMFLOAT4X4 mat[3][MAX_RESULT_TEXTURE];

	DirectX::XMMATRIX world[MAX_RESULT_TEXTURE];

	for (int i = 0; i < MAX_RESULT_TEXTURE; i++)
	{
		//���[���h�s���X,Y�݂̂��l�����č쐬
		world[i] = DirectX::XMMatrixTranslation(m_ResultBackGround[i].pos.x, m_ResultBackGround[i].pos.y, m_ResultBackGround[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = 0; i < MAX_RESULT_TEXTURE; i++)
	{
		// �w�i�`��
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_ResultBackGround[i].size.x, -m_ResultBackGround[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_ResultBackGround[i].posTexCoord.x, m_ResultBackGround[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_ResultBackGround[i].sizeTexCoord.x, m_ResultBackGround[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_ResultBackGround[i].alpha));
		Sprite::SetTexture(m_pTexture[i]);
		Sprite::Draw();
	}
}
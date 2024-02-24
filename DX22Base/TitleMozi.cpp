//=================================================================
//
//	TitleMozi.cpp
//	�^�C�g���w�i
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "TitleMozi.h"
#include "Defines.h"

//----�萔�E�}�N����`----
#define DELTA_ALPHA (0.006f)	// �����x�ω���

// ========== �R���X�g���N�^ ==========
CTitleMozi::CTitleMozi()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
	, m_nAlfhaFlg(false)
{

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		m_pTexture[i] = new Texture();
	}

	// �^�C�g������
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Title.png")))
	{
		MessageBox(NULL, "UI Title.png", "Error", MB_OK);
	}
	// �X�^�[�g����
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/TitlePrompt.png")))
	{
		MessageBox(NULL, "UI TitlePrompt.png", "Error", MB_OK);
	}

	// �^�C�g������
	m_TitleMozi[0].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 1.8f, m_pTexture[0]->GetHeight() * 1.8f);
	m_TitleMozi[0].pos = DirectX::XMFLOAT3(640.0f, 150.0f, 0.0f);
	m_TitleMozi[0].alpha = 1.0f;

	// �X�^�[�g����
	m_TitleMozi[1].size = DirectX::XMFLOAT2(m_pTexture[1]->GetWidth(), m_pTexture[1]->GetHeight());
	m_TitleMozi[1].pos = DirectX::XMFLOAT3(640.0f, 520.0f, 0.0f);

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		m_TitleMozi[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_TitleMozi[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
		m_TitleMozi[i].alpha = 1.0f;
	}
}

// ========== �f�X�g���N�^ ==========
CTitleMozi::~CTitleMozi()
{
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (m_pTexture[i])
		{
			SAFE_DELETE(m_pTexture[i]);
		}
	}
}

// ========== Update�֐� ==========
void CTitleMozi::Update()
{
	// �����x�ω�
	if (!m_nAlfhaFlg)
	{
		m_TitleMozi[1].alpha -= DELTA_ALPHA;
		if (m_TitleMozi[1].alpha <= 0.55f)
		{
			m_nAlfhaFlg = true;
		}
	}
	else
	{
		m_TitleMozi[1].alpha += DELTA_ALPHA;
		if (m_TitleMozi[1].alpha >= 1.0f)
		{
			m_nAlfhaFlg = false;
		}
	}
}

// ========== Draw�֐� ==========
void CTitleMozi::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][MAX_TEXTURE];

	DirectX::XMMATRIX world[MAX_TEXTURE];

	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		//���[���h�s���X,Y�݂̂��l�����č쐬
		world[i] = DirectX::XMMatrixTranslation(m_TitleMozi[i].pos.x, m_TitleMozi[i].pos.y, m_TitleMozi[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	// �����`��
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_TitleMozi[i].size.x, -m_TitleMozi[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_TitleMozi[i].posTexCoord.x, m_TitleMozi[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_TitleMozi[i].sizeTexCoord.x, m_TitleMozi[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_TitleMozi[i].alpha));
		Sprite::SetTexture(m_pTexture[i]);
		Sprite::Draw();
	}
}
//=================================================================
//
//	ResultMozi.cpp
//	�^�C�g���w�i
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "ResultMozi.h"
#include "Defines.h"

//----�萔�E�}�N����`----
#define DELTA_ALPHA (0.006f)	// �����x�ω���

// ========== �R���X�g���N�^ ==========
CResultMozi::CResultMozi()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
{

	for (int i = 0; i < MAX_RESULT_MOZI_TEXTURE; i++)
	{
		m_pTexture[i] = new Texture();
	}

	// ����
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Result.png")))
	{
		MessageBox(NULL, "UI Result.png", "Error", MB_OK);
	}

	// ���߂��t���[�c
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/CollectFruits.png")))
	{
		MessageBox(NULL, "UI CollectFruits.png", "Error", MB_OK);
	}

	// ���v�{�|�C���g
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/TotalPlusPoint.png")))
	{
		MessageBox(NULL, "UI TotalPlusPoint.png", "Error", MB_OK);
	}

	// ���߂��J��
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/CollectCan.png")))
	{
		MessageBox(NULL, "UI CollectCan.png", "Error", MB_OK);
	}

	// ���v�[�|�C���g
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/TotalMinusPoint.png")))
	{
		MessageBox(NULL, "UI TotalMinusPoint.png", "Error", MB_OK);
	}

	// ���v�|�C���g
	if (FAILED(m_pTexture[5]->Create("Assets/Texture/TotalPoint.png")))
	{
		MessageBox(NULL, "UI TotalPoint.png", "Error", MB_OK);
	}

	// ����
	m_ResultMozi[0].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 1.8f, m_pTexture[0]->GetHeight() * 1.8f);
	m_ResultMozi[0].pos = DirectX::XMFLOAT3(640.0f, 120.0f, 0.0f);

	// ���߂��t���[�c
	m_ResultMozi[1].size = DirectX::XMFLOAT2(m_pTexture[1]->GetWidth(), m_pTexture[1]->GetHeight());
	m_ResultMozi[1].pos = DirectX::XMFLOAT3(310.0f, 270.0f, 0.0f);

	// ���v�{�|�C���g
	m_ResultMozi[2].size = DirectX::XMFLOAT2(m_pTexture[2]->GetWidth(), m_pTexture[2]->GetHeight());
	m_ResultMozi[2].pos = DirectX::XMFLOAT3(750.0f, 270.0f, 0.0f);

	// ���߂��J��
	m_ResultMozi[3].size = DirectX::XMFLOAT2(m_pTexture[3]->GetWidth(), m_pTexture[3]->GetHeight());
	m_ResultMozi[3].pos = DirectX::XMFLOAT3(310.0f, 360.0f, 0.0f);

	// ���v�[�|�C���g
	m_ResultMozi[4].size = DirectX::XMFLOAT2(m_pTexture[4]->GetWidth(), m_pTexture[4]->GetHeight());
	m_ResultMozi[4].pos = DirectX::XMFLOAT3(750.0f, 360.0f, 0.0f);

	// ���v�|�C���g
	m_ResultMozi[5].size = DirectX::XMFLOAT2(m_pTexture[5]->GetWidth(), m_pTexture[5]->GetHeight());
	m_ResultMozi[5].pos = DirectX::XMFLOAT3(750.0f, 450.0f, 0.0f);

	for (int i = 0; i < MAX_RESULT_MOZI_TEXTURE; i++)
	{
		m_ResultMozi[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_ResultMozi[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
	}
}

// ========== �f�X�g���N�^ ==========
CResultMozi::~CResultMozi()
{
	for (int i = 0; i < MAX_RESULT_MOZI_TEXTURE; i++)
	{
		if (m_pTexture[i])
		{
			SAFE_DELETE(m_pTexture[i]);
		}
	}
}

// ========== Update�֐� ==========
void CResultMozi::Update()
{
	//// �����x�ω�
	//if (!m_nAlfhaFlg)
	//{
	//	m_ResultMozi[1].alpha -= DELTA_ALPHA;
	//	if (m_ResultMozi[1].alpha <= 0.55f)
	//	{
	//		m_nAlfhaFlg = true;
	//	}
	//}
	//else
	//{
	//	m_ResultMozi[1].alpha += DELTA_ALPHA;
	//	if (m_ResultMozi[1].alpha >= 1.0f)
	//	{
	//		m_nAlfhaFlg = false;
	//	}
	//}
}

// ========== Draw�֐� ==========
void CResultMozi::Draw()
{
	DirectX::XMFLOAT4X4 mat[3][MAX_RESULT_MOZI_TEXTURE];

	DirectX::XMMATRIX world[MAX_RESULT_MOZI_TEXTURE];

	for (int i = 0; i < MAX_RESULT_MOZI_TEXTURE; i++)
	{
		//���[���h�s���X,Y�݂̂��l�����č쐬
		world[i] = DirectX::XMMatrixTranslation(m_ResultMozi[i].pos.x, m_ResultMozi[i].pos.y, m_ResultMozi[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));
	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	// �����`��
	for (int i = 0; i < MAX_RESULT_MOZI_TEXTURE; i++)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_ResultMozi[i].size.x, -m_ResultMozi[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_ResultMozi[i].posTexCoord.x, m_ResultMozi[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_ResultMozi[i].sizeTexCoord.x, m_ResultMozi[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[i]);
		Sprite::Draw();
	}
}
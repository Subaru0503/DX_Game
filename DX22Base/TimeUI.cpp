////////////////////
//
//	TimeUI.cpp
//	�X�R�A�֘A
//
////////////////////

//---�C���N���[�h��----
#include "TimeUI.h"
#include "Input.h"
#include "Defines.h"

#define TIME_LIMIT (60.0f)	// ��������(�b)

CTimeUI::CTimeUI()	// �R���X�g���N�^
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
	//, m_bAdd(false)
	, m_fAlpha(1.0f)
	, m_fTimeLimit(TIME_LIMIT)
	, m_fElapsedTime(0.0f)

{

	for (int i = 0; i < MAX_TIME_UI; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/number.png")))
	{
		MessageBox(NULL, "UI number.png", "Error", MB_OK);
	}


	m_basePosX = 1050.0f;
	m_basePosY = 50.0f;

	//����
	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		m_time[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.5f, m_pTexture[0]->GetHeight() * 0.5f);
		m_time[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_time[i].size.x - (i * 5.0f), m_basePosY, 0.0f);
		m_time[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_time[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_TIME_SPLIT_X, 1.0f / (float)ANIM_TIME_SPLIT_Y);

		m_time[i].frame = 0;
		m_time[i].currentAnimNo = 0;
	}
	UpdateTimetexCoord();
}


CTimeUI::~CTimeUI()
{
	for (int i = 0; i < MAX_TIME_UI; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

void CTimeUI::Update()
{
	UpdateTimetexCoord();	// �\�����ԍX�V
	m_fElapsedTime++;	// �o�ߎ���
}

void CTimeUI::Draw()
{
	//int Number = m_nTimeLimit;
	int Digit = 0;

	//if (Number <= 0)
	//{
	//	Digit = DIGIT_TIME - 1;
	//}
	//while (Number != 0)
	//{
	//	Number = Number / 10;
	//	Digit--;
	//}


	DirectX::XMFLOAT4X4 mat[3][DIGIT_TIME + 1];

	DirectX::XMMATRIX world[DIGIT_TIME + 1];

	for (int i = 0; i <= DIGIT_TIME; ++i)
	{
		//���[���h�s���X,Y�݂̂��l�����č쐬

		world[i] = DirectX::XMMatrixTranslation(m_time[i].pos.x, m_time[i].pos.y, m_time[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = Digit; i < DIGIT_TIME; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_time[i].size.x, -m_time[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_time[i].posTexCoord.x, m_time[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_time[i].sizeTexCoord.x, m_time[i].sizeTexCoord.y));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}
}

void CTimeUI::UpdateTimetexCoord()
{
	int temp = m_fTimeLimit - m_fElapsedTime / 60.0f;

	for (int i = DIGIT_TIME - 1; 0 <= i; --i)
	{
		m_time[i].currentAnimNo = temp % 10;

		m_time[i].posTexCoord.x = m_time[i].sizeTexCoord.x * (m_time[i].currentAnimNo % ANIM_TIME_SPLIT_X);
		m_time[i].posTexCoord.y = m_time[i].sizeTexCoord.y * (m_time[i].currentAnimNo / ANIM_TIME_SPLIT_X);
		temp /= 10;
	}

}

float CTimeUI::GetTimeLimit()	// �������ԏ���Ԃ�
{
	return m_fTimeLimit;
}

float CTimeUI::GetElapsedTime()	// �o�ߎ��ԏ���Ԃ�
{
	return m_fElapsedTime / 60.0f;
}
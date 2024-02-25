////////////////////
//
//	ResultScore.cpp
//	�X�R�A�֘A
//
////////////////////

//---�C���N���[�h��----
#include "ResultScore.h"
#include "Input.h"
#include "Defines.h"

CResultScore::CResultScore()	// �R���X�g���N�^
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
	//, m_bAdd(false)
	, m_fAlpha(1.0f)
	, m_nScore{ 0, 0, 0, 0, 0}			// ���v�X�R�A

{

	for (int i = 0; i < MAX_RESULT_SCORE_TEXTURE; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	// �{����
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/PlusNumber.png")))
	{
		MessageBox(NULL, "UI PlusNumber.png", "Error", MB_OK);
	}
	// �[����
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/MinusNumber.png")))
	{
		MessageBox(NULL, "UI MinusNumber.png", "Error", MB_OK);
	}



	// 3��
	//m_basePosX = 920.0f;
	m_basePosX = 380.0f;
	m_basePosY = 265.0f;

	int texture = 0;	// �e�N�X�`���Q�Ɨp
	// ����
	for (int j = 0; j < MAX_SCORE; j++)
	{
		for (int i = 0; i < DIGIT_RESULT_SCORE; ++i)
		{
			m_score[j][i].size = DirectX::XMFLOAT2(m_pTexture[texture]->GetWidth() * 0.4f, m_pTexture[texture]->GetHeight() * 0.4f);
			m_score[j][i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_score[j][i].size.x - (i * 5.0f), m_basePosY, 0.0f);
			m_score[j][i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
			m_score[j][i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_RESULT_SCORE_SPLIT_X, 1.0f / (float)ANIM_RESULT_SCORE_SPLIT_Y);

			m_score[j][i].frame = 0;
			m_score[j][i].currentAnimNo = 0;
		}
		if (j == 1)
		{
			m_basePosX = 920.0f;
			m_basePosY -= 90.0f;
		}
		else
		{
			m_basePosY += 90.0f;
		}
		texture ^= 1;
	}
}


CResultScore::~CResultScore()
{
	for (int i = 0; i < MAX_RESULT_SCORE_TEXTURE; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

void CResultScore::Update()
{

}

void CResultScore::Draw()
{

	DirectX::XMFLOAT4X4 mat[3][DIGIT_RESULT_SCORE + 1];

	DirectX::XMMATRIX world[DIGIT_RESULT_SCORE + 1];

	//�r���[�s���2d���ƃJ�����̈ʒu�����܂�֌W�Ȃ��̂ŁA�P�ʍs���ݒ肷��
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//�v���W�F�N�V�����s���2d�Ƃ��ĕ\�����邽�߂̍s���ݒ肷��
	//���̍s���2d�X�N���[���̑傫�������܂�
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));


	// �`�悷�錅�����v�Z�p
	int Number;
	int Digit;

	// �e�N�X�`���Q�Ɨp
	int texture = 0;

	// ���߂��t���[�c�A���߂��J���A���v�{�|�C���g�A���v�[�|�C���g�A���v�|�C���g�̏��ɕ`��
	for (int j = 0; j < MAX_SCORE; j++)
	{
		Number = m_nScore[j];
		Digit = DIGIT_RESULT_SCORE;
		if (Number <= 0)
		{
			Digit = DIGIT_RESULT_SCORE - 1;
		}
		while (Number > 0)
		{
			Number = Number / 10;
			Digit--;
		}

		for (int i = 0; i <= DIGIT_RESULT_SCORE; ++i)
		{
			//���[���h�s���X,Y�݂̂��l�����č쐬

			world[i] = DirectX::XMMatrixTranslation(m_score[j][i].pos.x, m_score[j][i].pos.y, m_score[j][i].pos.z);
			DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

		}

		for (int i = Digit; i < DIGIT_RESULT_SCORE; ++i)
		{
			Sprite::SetWorld(mat[0][i]);
			Sprite::SetView(mat[1][0]);
			Sprite::SetProjection(mat[2][0]);
			Sprite::SetSize(DirectX::XMFLOAT2(m_score[j][i].size.x, -m_score[j][i].size.y));
			Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[j][i].posTexCoord.x, m_score[j][i].posTexCoord.y));
			Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[j][i].sizeTexCoord.x, m_score[j][i].sizeTexCoord.y));
			Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			Sprite::SetTexture(m_pTexture[texture]);
			Sprite::Draw();
		}
		texture ^= 1;
	}
}

void CResultScore::UpdateScoretexCoord(int index)
{
	int temp = m_nScore[index];

	for (int i = DIGIT_RESULT_SCORE - 1; 0 <= i; --i)
	{
		m_score[index][i].currentAnimNo = temp % 10;

		m_score[index][i].posTexCoord.x = m_score[index][i].sizeTexCoord.x * (m_score[index][i].currentAnimNo % ANIM_RESULT_SCORE_SPLIT_X);
		m_score[index][i].posTexCoord.y = m_score[index][i].sizeTexCoord.y * (m_score[index][i].currentAnimNo / ANIM_RESULT_SCORE_SPLIT_X);
		temp /= 10;
	}

}

void CResultScore::SetScore(int score, int index)	// �X�R�A�Z�b�g
{
	m_nScore[index] = score;
	UpdateScoretexCoord(index);	// �\���X�R�A�X�V
}

////////////////////
//
//	ResultScore.cpp
//	スコア関連
//
////////////////////

//---インクルード部----
#include "ResultScore.h"
#include "Input.h"
#include "Defines.h"

CResultScore::CResultScore()	// コンストラクタ
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
	//, m_bAdd(false)
	, m_fAlpha(1.0f)
	, m_nScore(0)			// 合計スコア

{

	for (int i = 0; i < MAX_RESULT_SCORE; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	// ＋数字
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/PlusNumber2.png")))
	{
		MessageBox(NULL, "UI PlusNumber2.png", "Error", MB_OK);
	}
	// ー数字
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/MinusNumber2.png")))
	{
		MessageBox(NULL, "UI MinusNumber2.png", "Error", MB_OK);
	}


	m_basePosX = 920.0f;
	m_basePosY = 265.0f;

	//数字
	for (int j = 0; j < MAX_RESULT_SCORE; j++)
	{
		for (int i = 0; i < DIGIT_RESULT_SCORE; ++i)
		{
			m_score[j][i].size = DirectX::XMFLOAT2(m_pTexture[j]->GetWidth() * 0.4f, m_pTexture[j]->GetHeight() * 0.4f);
			m_score[j][i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_score[j][i].size.x - (i * 5.0f), m_basePosY, 0.0f);
			m_score[j][i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
			m_score[j][i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_RESULT_SCORE_SPLIT_X, 1.0f / (float)ANIM_RESULT_SCORE_SPLIT_Y);

			m_score[j][i].frame = 0;
			m_score[j][i].currentAnimNo = 0;
		}
		m_basePosY += 90.0f;
	}
}


CResultScore::~CResultScore()
{
	for (int i = 0; i < MAX_RESULT_SCORE; ++i)
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
	//int Number = m_nScore;
	int Digit = 0;

	//if (Number <= 0)
	//{
	//	Digit = DIGIT_RESULT_SCORE - 1;
	//}
	//while (Number != 0)
	//{
	//	Number = Number / 10;
	//	Digit--;
	//}


	DirectX::XMFLOAT4X4 mat[3][DIGIT_RESULT_SCORE + 1];

	DirectX::XMMATRIX world[DIGIT_RESULT_SCORE + 1];

	for (int i = 0; i <= DIGIT_RESULT_SCORE; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_score[0][i].pos.x, m_score[0][i].pos.y, m_score[0][i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = Digit; i < DIGIT_RESULT_SCORE; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_score[0][i].size.x, -m_score[0][i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[0][i].posTexCoord.x, m_score[0][i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[0][i].sizeTexCoord.x, m_score[0][i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}


	for (int i = 0; i <= DIGIT_RESULT_SCORE; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_score[1][i].pos.x, m_score[1][i].pos.y, m_score[1][i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	for (int i = Digit; i < DIGIT_RESULT_SCORE; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_score[1][i].size.x, -m_score[1][i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[1][i].posTexCoord.x, m_score[1][i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[1][i].sizeTexCoord.x, m_score[1][i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[1]);
		Sprite::Draw();
	}
}

void CResultScore::UpdateScoretexCoord(int index)
{
	int temp = m_nScore;

	for (int i = DIGIT_RESULT_SCORE - 1; 0 <= i; --i)
	{
		m_score[index][i].currentAnimNo = temp % 10;

		m_score[index][i].posTexCoord.x = m_score[index][i].sizeTexCoord.x * (m_score[index][i].currentAnimNo % ANIM_RESULT_SCORE_SPLIT_X);
		m_score[index][i].posTexCoord.y = m_score[index][i].sizeTexCoord.y * (m_score[index][i].currentAnimNo / ANIM_RESULT_SCORE_SPLIT_X);
		temp /= 10;
	}

}

void CResultScore::SetScore(int score, int index)	// スコアセット
{
	m_nScore = score;
	UpdateScoretexCoord(index);	// 表示スコア更新
}

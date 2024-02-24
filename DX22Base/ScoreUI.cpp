////////////////////
//
//	ScoreUI.cpp
//	スコア関連
//
////////////////////

//---インクルード部----
#include "ScoreUI.h"
#include "Input.h"
#include "Defines.h"

CScoreUI::CScoreUI(int Score)	// コンストラクタ
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
	//, m_bAdd(false)
	, m_fAlpha(1.0f)
	, m_nScore(Score)

{

	for (int i = 0; i < MAX_UI; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/number.png")))
	{
		MessageBox(NULL, "UI number2.png", "Error", MB_OK);
	}


	m_basePosX = 50.0f;
	m_basePosY = 50.0f;

	//数字
	for (int i = 0; i < DIGIT_SCORE; ++i)
	{
		m_score[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.5f, m_pTexture[0]->GetHeight() * 0.5f);
		m_score[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_score[i].size.x - (i * 5.0f), m_basePosY, 0.0f);
		m_score[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_score[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

		m_score[i].frame = 0;
		m_score[i].currentAnimNo = 0;
	}

	//for (int i = 0; i < DIGIT_SCORE + 1; ++i)
	//{
	//	m_add[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 6.5f, m_pTexture[0]->GetHeight() / 6.5f);
	//	m_add[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_add[i].size.x - (i *30.0f) - 30.0f, m_basePosY + 80.0f, 0.0f);
	//	m_add[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	//	m_add[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_SCORE_SPLIT_X, 1.0f / (float)ANIM_SCORE_SPLIT_Y);

	//	m_add[i].currentAnimNo = 0;
	//}
	//m_add[0].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() / 4.0f, m_pTexture[0]->GetHeight() / 4.0f);
	//m_add[0].pos = DirectX::XMFLOAT3(m_basePosX - 40.0f, m_basePosY + 80.0f, 0.0f);
	UpdateScoretexCoord();
}


CScoreUI::~CScoreUI()
{
	for (int i = 0; i < MAX_UI; ++i)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

void CScoreUI::Update()
{

}

void CScoreUI::Draw()
{
	//int Number = m_nScore;
	int Digit = 0;

	//if (Number <= 0)
	//{
	//	Digit = DIGIT_SCORE - 1;
	//}
	//while (Number != 0)
	//{
	//	Number = Number / 10;
	//	Digit--;
	//}


	DirectX::XMFLOAT4X4 mat[3][DIGIT_SCORE + 1];

	DirectX::XMMATRIX world[DIGIT_SCORE + 1];

	for (int i = 0; i <= DIGIT_SCORE; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_score[i].pos.x, m_score[i].pos.y, m_score[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	for (int i = Digit; i < DIGIT_SCORE; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_score[i].size.x, -m_score[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_score[i].posTexCoord.x, m_score[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_score[i].sizeTexCoord.x, m_score[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		Sprite::SetTexture(m_pTexture[0]);
		Sprite::Draw();
	}
}

void CScoreUI::UpdateScoretexCoord()
{
	int temp = m_nScore;

	for (int i = DIGIT_SCORE - 1; 0 <= i; --i)
	{
		m_score[i].currentAnimNo = temp % 10;

		m_score[i].posTexCoord.x = m_score[i].sizeTexCoord.x * (m_score[i].currentAnimNo % ANIM_SCORE_SPLIT_X);
		m_score[i].posTexCoord.y = m_score[i].sizeTexCoord.y * (m_score[i].currentAnimNo / ANIM_SCORE_SPLIT_X);
		temp /= 10;
	}

}

void CScoreUI::SetScore(int score)	// スコアセット
{
	m_nScore = score;
	UpdateScoretexCoord();	// 表示スコア更新
}

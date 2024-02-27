////////////////////
//
//	TimeUI.cpp
//	スコア関連
//
////////////////////

//---インクルード部----
#include "TimeUI.h"
#include "Input.h"
#include "Defines.h"

#define TIME_LIMIT (1.0f)	// 制限時間(秒)

CTimeUI::CTimeUI()	// コンストラクタ
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
	, m_fAlpha(1.0f)
	, m_fTimeLimit(TIME_LIMIT)
	, m_fElapsedTime(0.0f)

{

	for (int i = 0; i < MAX_TIME_UI; ++i)
	{
		m_pTexture[i] = new Texture();
	}

	if (FAILED(m_pTexture[0]->Create("Assets/Texture/TimerNumber.png")))
	{
		MessageBox(NULL, "UI TimerNumber.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Timer.png")))
	{
		MessageBox(NULL, "UI Timer.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/TimerBackGround.png")))
	{
		MessageBox(NULL, "UI TimerBackGround.png", "Error", MB_OK);
	}

	m_basePosX = 1150.0f;
	m_basePosY = 50.0f;

	//数字
	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		m_time[i].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.5f, m_pTexture[0]->GetHeight() * 0.5f);
		m_time[i].pos = DirectX::XMFLOAT3(m_basePosX + i * m_time[i].size.x - (i * 5.0f), m_basePosY, 0.0f);
		m_time[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_time[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f / (float)ANIM_TIME_SPLIT_X, 1.0f / (float)ANIM_TIME_SPLIT_Y);

		m_time[i].frame = 0;
		m_time[i].currentAnimNo = 0;
	}

	// 時計
	m_Timer[0].size = DirectX::XMFLOAT2(m_pTexture[1]->GetWidth() * 0.04f, m_pTexture[1]->GetHeight() * 0.04f);
	m_Timer[0].pos = DirectX::XMFLOAT3(1090.0f , 45.0f, 0.0f);
	m_Timer[0].alpha = 1.0f;

	// 時計と数字の背景
	m_Timer[1].size = DirectX::XMFLOAT2(m_pTexture[2]->GetWidth() * 0.45f, m_pTexture[2]->GetHeight() * 0.35f);
	m_Timer[1].pos = DirectX::XMFLOAT3(1160.0f, 45.0f, 0.0f);
	m_Timer[1].alpha = 0.51f;
	for (int i = 0; i < 2; i++)
	{
		m_Timer[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_Timer[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
	}

	UpdateTimetexCoord();
}


CTimeUI::~CTimeUI()
{
	for (int i = 0; i < MAX_TIME_UI; ++i)
	{
		if (m_pTexture[i])
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}

}

void CTimeUI::Update()
{
	UpdateTimetexCoord();	// 表示時間更新
	m_fElapsedTime++;	// 経過時間
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


	DirectX::XMFLOAT4X4 mat[3][DIGIT_TIME + 2];

	DirectX::XMMATRIX world[DIGIT_TIME + 2];

	// 数字
	for (int i = 0; i < DIGIT_TIME; ++i)
	{
		//ワールド行列はX,Yのみを考慮して作成

		world[i] = DirectX::XMMatrixTranslation(m_time[i].pos.x, m_time[i].pos.y, m_time[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i], DirectX::XMMatrixTranspose(world[i]));

	}

	// 時計
	for (int i = 0; i < 2; i++)
	{
		//ワールド行列はX,Yのみを考慮して作成
		world[i + 2] = DirectX::XMMatrixTranslation(m_Timer[i].pos.x, m_Timer[i].pos.y, m_Timer[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0][i + 2], DirectX::XMMatrixTranspose(world[i + 2]));
	}

	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1][0], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2][0], DirectX::XMMatrixTranspose(proj));

	// 時計と背景
	for (int i = 1; i >= 0; i--)
	{
		Sprite::SetWorld(mat[0][i + 2]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_Timer[i].size.x, -m_Timer[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_Timer[i].posTexCoord.x, m_Timer[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_Timer[i].sizeTexCoord.x, m_Timer[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_Timer[i].alpha));
		Sprite::SetTexture(m_pTexture[i + 1]);
		Sprite::Draw();
	}

	// 数字
	for (int i = Digit; i < DIGIT_TIME; ++i)
	{
		Sprite::SetWorld(mat[0][i]);
		Sprite::SetView(mat[1][0]);
		Sprite::SetProjection(mat[2][0]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_time[i].size.x, -m_time[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_time[i].posTexCoord.x, m_time[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_time[i].sizeTexCoord.x, m_time[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
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

float CTimeUI::GetTimeLimit()	// 制限時間情報を返す
{
	return m_fTimeLimit;
}

float CTimeUI::GetElapsedTime()	// 経過時間情報を返す
{
	return m_fElapsedTime / 60.0f;
}

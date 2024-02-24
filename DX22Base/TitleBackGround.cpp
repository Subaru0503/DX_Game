//=================================================================
//
//	TitleBackGround.cpp
//	タイトル背景
//
//=================================================================

// ========== インクルード部 ==========
#include "TitleBackGround.h"
#include "Defines.h"

// ========== コンストラクタ ==========
CTitleBackGround::CTitleBackGround()
	: m_Left(0.0f)
	, m_Right((float)SCREEN_WIDTH)
	, m_Bottom((float)SCREEN_HEIGHT)
	, m_Top(0.0f)
	, m_near(1.0f)
	, m_far(10.0f)
	, m_pTexture{ nullptr }
{

	m_pTexture = new Texture();

	// タイトル背景
	if (FAILED(m_pTexture->Create("Assets/Texture/TitleBackGround.jpg")))
	{
		MessageBox(NULL, "UI TitleBackGround.jpg", "Error", MB_OK);
	}

	m_TitleBackGround.size = DirectX::XMFLOAT2(1280.0f, 720.0f);
	m_TitleBackGround.pos = DirectX::XMFLOAT3(640.0f, 360.0f, 0.0f);
	m_TitleBackGround.posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_TitleBackGround.sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
}

// ========== デストラクタ ==========
CTitleBackGround::~CTitleBackGround()
{
	SAFE_DELETE(m_pTexture);
}

// ========== Update関数 ==========
void CTitleBackGround::Update()
{

}

// ========== Draw関数 ==========
void CTitleBackGround::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world;

	//ワールド行列はX,Yのみを考慮して作成

	world = DirectX::XMMatrixTranslation(m_TitleBackGround.pos.x, m_TitleBackGround.pos.y, m_TitleBackGround.pos.z);
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));


	//ビュー行列は2dだとカメラの位置があまり関係ないので、単位行列を設定する
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	//プロジェクション行列は2dとして表示するための行列を設定する
	//この行列で2dスクリーンの大きさが決まる
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_Left, m_Right, m_Bottom, m_Top, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// 背景
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(m_TitleBackGround.size.x, -m_TitleBackGround.size.y));
	Sprite::SetUVPos(DirectX::XMFLOAT2(m_TitleBackGround.posTexCoord.x, m_TitleBackGround.posTexCoord.y));
	Sprite::SetUVScale(DirectX::XMFLOAT2(m_TitleBackGround.sizeTexCoord.x, m_TitleBackGround.sizeTexCoord.y));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}
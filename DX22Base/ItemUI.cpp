// ItemUI.cpp
//----インクルード部----
#include "ItemUI.h"
#include "Sprite.h"

ItemUI::ItemUI()	// コンストラクタ
{
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/Star.png")))
	{
		MessageBox(NULL, "ItemUI Star.png", "Error", MB_OK);
	}
}

ItemUI::~ItemUI()	// デストラクタ	
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

void ItemUI::Update()	// 更新
{

}

void ItemUI::Draw()		// 描画
{
	DirectX::XMFLOAT4X4 mat[3];

	// ワールド行列はXとYのみを考慮して作成
	DirectX::XMMATRIX world =
		DirectX::XMMatrixTranslation(1080.0f, 520.0f, 0.0f);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));

	// 単位行列の設定
	// 単位行列は回数、拡大縮小しない
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixIdentity());

	// プロジェクション行列には2Dとして表示するための行列設定
	// この行列で2Dのスクリーンの大きさが決まる
	// 2Dはピクセル単位
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f, 720.0f, 0.0f, 0.1f, 10.0f);	// 引数の値を変えれば原点の位置を変えれる
													// 左上が0.0, 0.0
	DirectX::XMStoreFloat4x4(&mat[2], DirectX::XMMatrixTranspose(proj));

	// スプライトの設定
	Sprite::SetWorld(mat[0]);
	Sprite::SetView(mat[1]);
	Sprite::SetProjection(mat[2]);
	Sprite::SetSize(DirectX::XMFLOAT2(300.0f, -300.0f));	// 背面カリングの対策で-にしたら出る
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();

}
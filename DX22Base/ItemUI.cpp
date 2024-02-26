// ItemUI.cpp
//----インクルード部----
#include "ItemUI.h"
#include "Sprite.h"
#include "Object.h"

ItemUI::ItemUI()	// コンストラクタ
{
	for (int i = 0; i < MAX_ITEM_TEXTURE; i++)
	{
		m_pTexture[i] = new Texture();
	}
	// 背景(パネル)
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/TimerBackGround.png")))
	{
		MessageBox(NULL, "ItemUI TimerBackGround.png", "Error", MB_OK);
	}
	// りんご
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Apple.png")))
	{
		MessageBox(NULL, "ItemUI Apple.png", "Error", MB_OK);
	}
	// イチゴ
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/Strawberry.png")))
	{
		MessageBox(NULL, "ItemUI Strawberry.png", "Error", MB_OK);
	}
	// バナナ
	if (FAILED(m_pTexture[3]->Create("Assets/Texture/Banana.png")))
	{
		MessageBox(NULL, "ItemUI Banana.png", "Error", MB_OK);
	}
	// レモン
	if (FAILED(m_pTexture[4]->Create("Assets/Texture/Lemon.png")))
	{
		MessageBox(NULL, "ItemUI Lemon.png", "Error", MB_OK);
	}
	// スイカ
	if (FAILED(m_pTexture[5]->Create("Assets/Texture/WaterMelon.png")))
	{
		MessageBox(NULL, "ItemUI WaterMelon.png", "Error", MB_OK);
	}
	// メロン
	if (FAILED(m_pTexture[6]->Create("Assets/Texture/Melon.png")))
	{
		MessageBox(NULL, "ItemUI Melon.png", "Error", MB_OK);
	}
	// 空き缶
	if (FAILED(m_pTexture[7]->Create("Assets/Texture/Can.png")))
	{
		MessageBox(NULL, "ItemUI Can.png", "Error", MB_OK);
	}

	for (int i = 0; i < MAX_ITEM_UI; i++)
	{
		m_Item[i].posTexCoord = DirectX::XMFLOAT2(0.0f, 0.0f);
		m_Item[i].sizeTexCoord = DirectX::XMFLOAT2(1.0f, 1.0f);
		m_Item[i].kind = (int)Object::NONE;
		m_Item[i].alpha = 1.0f;
		m_Item[i].drawFlg = false;
	}

	// 背景(パネル)
	m_Item[0].pos = DirectX::XMFLOAT3(580.0f, 80.0f, 0.0f);
	m_Item[0].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.25f, m_pTexture[0]->GetHeight() * 0.7f);
	m_Item[0].alpha = 0.7f;
	m_Item[0].drawFlg = true;

	m_Item[1].pos = DirectX::XMFLOAT3(680.0f, 80.0f, 0.0f);
	m_Item[1].size = DirectX::XMFLOAT2(m_pTexture[0]->GetWidth() * 0.25f, m_pTexture[0]->GetHeight() * 0.7f);
	m_Item[1].alpha = 0.7f;
	m_Item[1].drawFlg = true;

	// りんご
	m_Item[2].size = DirectX::XMFLOAT2(m_pTexture[1]->GetWidth() * 0.09f, m_pTexture[1]->GetHeight() * 0.09f);
	m_Item[2].kind = Object::APPLE;

	m_Item[3].size = DirectX::XMFLOAT2(m_pTexture[1]->GetWidth() * 0.09f, m_pTexture[1]->GetHeight() * 0.09f);
	m_Item[3].kind = Object::APPLE;

	// イチゴ
	m_Item[4].size = DirectX::XMFLOAT2(m_pTexture[2]->GetWidth() * 0.09f, m_pTexture[2]->GetHeight() * 0.09f);
	m_Item[4].kind = Object::STRAWBERRY;

	m_Item[5].size = DirectX::XMFLOAT2(m_pTexture[2]->GetWidth() * 0.09f, m_pTexture[2]->GetHeight() * 0.09f);
	m_Item[5].kind = Object::STRAWBERRY;

	// バナナ
	m_Item[6].size = DirectX::XMFLOAT2(m_pTexture[3]->GetWidth() * 0.2f, m_pTexture[3]->GetHeight() * 0.2f);
	m_Item[6].kind = Object::BANANA;

	m_Item[7].size = DirectX::XMFLOAT2(m_pTexture[3]->GetWidth() * 0.2f, m_pTexture[3]->GetHeight() * 0.2f);
	m_Item[7].kind = Object::BANANA;

	// レモン
	m_Item[8].size = DirectX::XMFLOAT2(m_pTexture[4]->GetWidth() * 0.09f, m_pTexture[4]->GetHeight() * 0.09f);
	m_Item[8].kind = Object::LEMON;

	m_Item[9].size = DirectX::XMFLOAT2(m_pTexture[4]->GetWidth() * 0.09f, m_pTexture[4]->GetHeight() * 0.09f);
	m_Item[9].kind = Object::LEMON;

	// スイカ
	m_Item[10].size = DirectX::XMFLOAT2(m_pTexture[5]->GetWidth() * 0.09f, m_pTexture[5]->GetHeight() * 0.09f);
	m_Item[10].kind = Object::WATER_MELON;

	m_Item[11].size = DirectX::XMFLOAT2(m_pTexture[5]->GetWidth() * 0.09f, m_pTexture[5]->GetHeight() * 0.09f);
	m_Item[11].kind = Object::WATER_MELON;

	// メロン
	m_Item[12].size = DirectX::XMFLOAT2(m_pTexture[6]->GetWidth() * 0.25f, m_pTexture[6]->GetHeight() * 0.25f);
	m_Item[12].kind = Object::MELON;

	m_Item[13].size = DirectX::XMFLOAT2(m_pTexture[6]->GetWidth() * 0.25f, m_pTexture[6]->GetHeight() * 0.25f);
	m_Item[13].kind = Object::MELON;

	// 空き缶
	m_Item[14].size = DirectX::XMFLOAT2(m_pTexture[7]->GetWidth() * 0.25f, m_pTexture[7]->GetHeight() * 0.25f);
	m_Item[14].kind = Object::CAN;

	m_Item[15].size = DirectX::XMFLOAT2(m_pTexture[7]->GetWidth() * 0.25f, m_pTexture[7]->GetHeight() * 0.25f);
	m_Item[15].kind = Object::CAN;
}

ItemUI::~ItemUI()	// デストラクタ	
{
	for (int i = 0; i < MAX_ITEM_TEXTURE; i++)
	{
		if (m_pTexture[i])
		{
			SAFE_DELETE(m_pTexture[i]);
		}
	}
}

void ItemUI::Update()	// 更新
{

}

void ItemUI::Draw()		// 描画
{
	DirectX::XMFLOAT4X4 mat[3];

	DirectX::XMMATRIX world;

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

	// テクスチャ参照用
	int texture = 0;
	for (int i = 0; i < MAX_ITEM_UI; i++)
	{
		if (!m_Item[i].drawFlg) continue;

		texture = i / 2.0f;

		// ワールド行列はXとYのみを考慮して作成
		world =
			DirectX::XMMatrixTranslation(m_Item[i].pos.x, m_Item[i].pos.y, m_Item[i].pos.z);
		DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(world));


		// スプライトの設定
		Sprite::SetWorld(mat[0]);
		Sprite::SetView(mat[1]);
		Sprite::SetProjection(mat[2]);
		Sprite::SetSize(DirectX::XMFLOAT2(m_Item[i].size.x, -m_Item[i].size.y));
		Sprite::SetUVPos(DirectX::XMFLOAT2(m_Item[i].posTexCoord.x, m_Item[i].posTexCoord.y));
		Sprite::SetUVScale(DirectX::XMFLOAT2(m_Item[i].sizeTexCoord.x, m_Item[i].sizeTexCoord.y));
		Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, m_Item[i].alpha));
		Sprite::SetTexture(m_pTexture[texture]);
		Sprite::Draw();
	}

}

void ItemUI::SetUP(DirectX::XMFLOAT3 pos, int kind, int draw)	// 描画に必要なパラメータをセット Pos, kind, drawFlg
{
	// パラメータをセットする
	for (int i = 0; i < MAX_ITEM_UI; i++)
	{
		// 指定の種類以外はセットしない
		if (m_Item[i].kind != kind || m_Item[i].drawFlg) continue;

		// 座標セット
		m_Item[i].pos = pos;
		// フラグを上げる
		m_Item[i].drawFlg = true;
		return;
	}
}

void ItemUI::ResetDrawFlg()	// 描画のフラグを下げる
{
	// 描画フラグを下げる
	for (int i = 0; i < MAX_ITEM_UI; i++)
	{
		// パネルは下げない
		if (m_Item[i].kind == Object::NONE) continue;

		// フラグを下げる
		m_Item[i].drawFlg = false;
	}
}

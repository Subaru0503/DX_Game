// ItemUI.h

//----インクルードガード----
#ifndef __ITEM_UI_H__
#define __ITEM_UI_H__

//----インクルード部----
#include <DirectXMath.h>
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_ITEM_UI (16)	// UI最大数
#define MAX_ITEM_TEXTURE (8)	// テクスチャ最大数

//----クラス定義----
class ItemUI
{
public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int kind;						// フルーツの種類
		float alpha;					// 透明度
		int drawFlg;					// 描画フラグ
	}ST_ITEM_PARAM;		//パラメータの構造体
public:
	ItemUI();	// コンストラクタ
	~ItemUI();	// デストラクタ
	void Update();	// 更新
	void Draw();	// 描画

	void SetUP(DirectX::XMFLOAT3 pos, int kind, int draw);	// 描画に必要なパラメータをセット Pos, kind, drawFlg
	void ResetDrawFlg();		// 描画のフラグを下げる
private:
	ST_ITEM_PARAM m_Item[MAX_ITEM_UI];
	Texture* m_pTexture[MAX_ITEM_TEXTURE];
};

#endif
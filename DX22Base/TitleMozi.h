//=================================================================
//
//	TitleMozi.cpp
//	タイトル背景
//
//=================================================================
#ifndef __TITLE_MOZI_H__
#define __TITLE_MOZI_H__

// ========== インクルード部 ==========
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_TEXTURE (2)	// テクスチャ最大数

// ========== クラス ==========
class CTitleMozi
{
public:
	CTitleMozi();
	~CTitleMozi();
	void Update();
	void Draw();

private:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		float alpha;					// 透明度
	}ST_TITLE_MOZI_PARAM;		//パラメータの構造体
private:
	ST_TITLE_MOZI_PARAM m_TitleMozi[MAX_TEXTURE];
	Texture* m_pTexture[MAX_TEXTURE];	// テクスチャの数
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	int m_nAlfhaFlg;	// 透明フラグ
};

#endif // !__TITLE_MOZI_H__
//=================================================================
//
//	TitleBackGround.cpp
//	タイトル背景
//
//=================================================================
#ifndef __TITLE_BACKGROUND_H__
#define __TITLE_BACKGROUND_H__

// ========== インクルード部 ==========
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_TITLE_TEXTURE (3)	// テクスチャ最大数

// ========== クラス ==========
class CTitleBackGround
{
public:
	CTitleBackGround();
	~CTitleBackGround();
	void Update();
	void Draw();

private:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
	}ST_TITLE_BACKGROUND_PARAM;		//パラメータの構造体
private:
	ST_TITLE_BACKGROUND_PARAM m_TitleBackGround;
	Texture* m_pTexture[MAX_TITLE_TEXTURE];	// テクスチャの数
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
};

#endif // !__TITLE_BACKGROUND_H__
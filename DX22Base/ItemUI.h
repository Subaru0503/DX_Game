// ItemUI.h

//----インクルードガード----
#ifndef __ITEM_UI_H__
#define __ITEM_UI_H__

//----インクルード部----
#include <DirectXMath.h>
#include "Texture.h"

//----クラス定義----
class ItemUI
{
public:
	ItemUI();	// コンストラクタ
	~ItemUI();	// デストラクタ
	void Update();	// 更新
	void Draw();	// 描画

private:
	Texture* m_pTexture;
};

#endif
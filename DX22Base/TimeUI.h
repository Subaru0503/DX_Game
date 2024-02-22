//----インクルードガード----
#ifndef ___TIME_UI_H___
#define ___TIME_UI_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_TIME_UI (5)
#define DIGIT_TIME			(2)	//エフェクトの数（配列の数）
#define ANIM_TIME_FRAME	(2)		//アニメーション一コマフレーム数
#define ANIM_TIME_SPLIT_X	(5)		//画像分割数（横）
#define ANIM_TIME_SPLIT_Y	(3)		//画像分割数（縦）

//----クラス定義----
class CTimeUI
{

public:
	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		frame;			//アニメーション管理フレーム
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_TIME_PARAM;		//パラメータの構造体

	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_ADDMANEY_PARAM;		//パラメータの構造体

public:
	CTimeUI();		// コンストラクタ
	~CTimeUI();				// デストラクタ
	void Update();				// 更新
	void Draw();				// 描画
	void UpdateTimetexCoord();	// 表示時間更新
	float GetTimeLimit();		// 制限時間情報を返す
	float GetElapsedTime();		// 経過時間情報を返す

private:
	ST_TIME_PARAM m_time[DIGIT_TIME + 1];
	unsigned int m_TextureTime;
	float m_fTimeLimit;			// 制限時間
	float m_fElapsedTime;			// 経過時間
	//int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fAlpha;
	Texture* m_pTexture[MAX_TIME_UI];

};


#endif // !___TIME_UI_H___
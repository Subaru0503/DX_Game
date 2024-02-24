//----インクルードガード----
#ifndef ___SCORE_UI_H___
#define ___SCORE_UI_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_UI (1)
#define DIGIT_SCORE			(5)	//エフェクトの数（配列の数）
#define ANIM_SCORE_FRAME	(2)		//アニメーション一コマフレーム数
#define ANIM_SCORE_SPLIT_X	(5)		//画像分割数（横）
#define ANIM_SCORE_SPLIT_Y	(3)		//画像分割数（縦）

//----クラス定義----
class CScoreUI
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
	}ST_SCORE_PARAM;		//パラメータの構造体

	typedef struct
	{
		DirectX::XMFLOAT3 pos;			//中心座標
		DirectX::XMFLOAT2 size;			//横縦サイズ
		DirectX::XMFLOAT2 posTexCoord;	//テクスチャ座標（左上）
		DirectX::XMFLOAT2 sizeTexCoord;	//テクスチャサイズ（右下）
		int		currentAnimNo;	//アニメーションコマ番号（左上から０～）
	}ST_ADDMANEY_PARAM;		//パラメータの構造体

public:
	CScoreUI(int Score);		// コンストラクタ
	~CScoreUI();				// デストラクタ
	void Update();				// 更新
	void Draw();				// 描画
	void UpdateScoretexCoord();	// 表示スコア更新
	void SetScore(int score);	// スコアセット

private:
	ST_SCORE_PARAM m_score[DIGIT_SCORE];
	int m_nScore;
	//int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fAlpha;
	Texture* m_pTexture[MAX_UI];

};


#endif // !___SCORE_UI_H___
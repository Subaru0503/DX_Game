//----インクルードガード----
#ifndef ___RESULT_SCORE_H___
#define ___RESULT_SCORE_H___

//----インクルード部----
#include <DirectXMath.h>
#include "Sprite.h"
#include "Texture.h"

//----定数・マクロ定義----
#define MAX_RESULT_SCORE   (2)				// リザルト数字
#define DIGIT_RESULT_SCORE			(5)		//エフェクトの数（配列の数）
#define ANIM_RESULT_SCORE_FRAME	(2)			//アニメーション一コマフレーム数
#define ANIM_RESULT_SCORE_SPLIT_X	(5)		//画像分割数（横）
#define ANIM_RESULT_SCORE_SPLIT_Y	(2)		//画像分割数（縦）

//----クラス定義----
class CResultScore
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

public:
	CResultScore();		// コンストラクタ
	~CResultScore();				// デストラクタ
	void Update();				// 更新
	void Draw();				// 描画
	void UpdateScoretexCoord(int index);	// 表示スコア更新
	void SetScore(int score, int index);	// スコアセット

private:
	ST_SCORE_PARAM m_score[MAX_RESULT_SCORE][DIGIT_RESULT_SCORE];
	int m_nScore;			// スコア
	//int m_nAddMoney;
	float m_Left, m_Right, m_Bottom, m_Top, m_near, m_far;
	float m_basePosX, m_basePosY;
	float m_fAlpha;
	Texture* m_pTexture[MAX_RESULT_SCORE];

};


#endif // !___RESULT_SCORE_H___
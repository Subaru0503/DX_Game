//----インクルードガード----
#ifndef __PLAYER_H__
#define __PLAYER_H__

//----インクルード部----
//#include <DirectXMath.h>
#include "Shader.h"
//#include "MeshBuffer.h"
#include "CameraBase.h"
#include "Model.h"
#include "Texture.h"
//----UI----
#include "ItemUI.h"
//----エフェクト----
#include "MoveEmitter.h"
#include "Effect.h"
#include "TrailEffect.h"

//----クラス定義----
class Player
{
public:
	Player(DirectX::XMFLOAT3 PlayerPos);	// コンストラクタ
	~Player();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	// モデルの回転
	void ModelRotate();

	//　カメラの設定
	void SetCamera(CameraBase* pCamera);

	// 重力リセット
	void ResetGravity();

	// ジャンプフラグリセット
	void ResetJumpFlg();

	// スコア加算
	void AddScore(int kind, int color, int add);
	// 現在地の設定
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetPosY(float height);				// 高さ補正
	void SetEventFlg(int event);	// イベントフラグ設定
	void SetItemUI(ItemUI* ItemUI);	// アイテムUIセット
	void SetResetFlg(int flg);		// リセットフラグセット

	// 現在地の取得
	DirectX::XMFLOAT3 GetPos();
	// 過去座標の取得
	DirectX::XMFLOAT3 GetOldPos();
	// プレイヤーの中心座標取得
	DirectX::XMFLOAT3 GetCenterPos();
	// プレイヤーのサイズ取得
	DirectX::XMFLOAT3 GetSize();
	// スコア取得
	int GetScore();
	// 引かれたスコア取得
	int GetMinusScore();
	// あつめたフルーツの数取得
	int GetFruitsNum();
	// あつめたカンの数取得
	int GetCanNum();
	// リセットフラグ情報ゲット
	int GetResetFlg();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;		// カメラの参照
	DirectX::XMFLOAT3 m_pos;	// プレイヤーの位置
	DirectX::XMFLOAT3 m_oldpos;	// プレイヤーの位置
	DirectX::XMFLOAT3 m_size;	// プレイヤーのサイズ
	Texture* m_pTexture[3];

	ItemUI* m_pUI;	// UI

	Effect* m_pEffect;
	MoveEmitter* m_pMoveEmitter;

	// ポリライン
	TrailEffect* m_pTrail;
	float m_fGravity;

	DirectX::XMFLOAT3 m_Move;		// 計算した移動ベクトルの格納先
	DirectX::XMFLOAT3 m_OldMove;	// 前の移動情報
	float m_directRad, m_directAngle;									//プレイヤーラジアン角、角度(°)

	int m_nLand;	// ジャンプフラグ
	float m_fJump;	// ジャンプ量

	int m_nEventFlg;	// イベントフラグ

	int m_nPrevItem;		// ひとつ目に手に入れたアイテム
	int m_nPrevScore;		// ひとつ目に手に入れたアイテムのスコア
	int m_nLastScore;		// 最後に手に入れたアイテム(フルーツ)のスコア情報
	int m_nPrevColor;		// ひとつ目に手に入れたアイテムの色
	int m_nScore;			// スコア
	int m_nMinusScore;		// 引かれたスコアの合計
	int m_nFruitsNum;		// あつめたフルーツの数
	int m_nCanNum;			// あつめたカンの数
	int m_nResetFlg;		// リセットを呼び出すフラグ
};
#endif		// __PLAYER_H__

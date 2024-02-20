// Object.h
#ifndef __OBJECT_H__
#define __OBJECT_H__

//=====インクルード=====
#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Model.h"
#include "TrailEffect.h"
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
/******************************
*@brief	オブジェクト基底クラス
******************************/
class Object
{
public:
	// オブジェクトの種類
	enum Kind
	{
		NONE = -1,			// 未設定
		// フルーツ
		APPLE,			// リンゴ
		WATER_MELON,	// スイカ
		MAX_FRUITS,		// フルーツ最大数

		// オブジェクト
		TREE,			// 木
	};
private:
	// 線分を描画する際の頂点情報構造体
	struct LineVertex
	{
		float pos[3];
		float color[4];
	};
	// ポリゴンを描画する際の頂点情報構造体
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};
public:
	// 描画初期位置、スケール、アングルを引数に持つコンストラクタ
	Object(float posX, float posY, float posZ);
	virtual ~Object();					// デストラクタ

	void Init();				// 初期化処理
	void Uninit();				// 終了処理
	virtual void Update(float tick);	// 更新処理

	void SetWorld(DirectX::XMFLOAT4X4 world);		// 定数バッファへ送るデータにワールド座標変換行列をセット
	void SetView(DirectX::XMFLOAT4X4 view);			// 定数バッファへ送るデータにビュー座標変換行列をセット
	void SetProjection(DirectX::XMFLOAT4X4 proj);	// 定数バッファへ送るデータにプロジェクション座標変換行列をセット
	void SetBoxMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Box移動処理
	void SetSphereMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Sphere移動処理

	//void AddLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,
		//DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));	// 描画する線分を追加する処理
	//void DrawLines();	// 線分を描画する処理

	int GetKind();					// オブジェクトの種類番号を返す
	DirectX::XMFLOAT3 GetScale();	// スケールを返す
	bool GetDelete();				// 削除フラグを返す
	void SetDelete();				// 削除フラグを立てる
	void SetCreate();				// 生成フラグを立てる
	int GetCreate();				// 生成フラグを返す
	int GetScore();					// ゲットしたアイテムのスコアを返す
	DirectX::XMFLOAT3 GetAngle();	// 回転角度

	//void SetSound(CSoundMng* sound);

private:
	void MakeVS();			// 頂点シェーダ作成
	void MakePS();			// ピクセルシェーダ作成
	void MakeLineShader();	// 線分用シェーダ作成

private:
	//void MakeLine();		// 線分の頂点バッファ作成 
	//void MakeBox();			// Boxの頂点バッファ作成
	//void MakeCylinder();	// Cylinderの頂点バッファ作成
	//void MakeSphere();		// Sphereの頂点バッファ作成
	//const int MAX_LINE_NUM = 1000;	// shiran
	//const int CIRCLE_DETAIL = 16;	// shiran

private:
	MeshBuffer* m_pBox;			// Boxの頂点バッファへのポインタ
	MeshBuffer* m_pCylinder;	// Cylinderの頂点バッファへのポインタ
	MeshBuffer* m_pSphere;		// Sphereの頂点バッファへのポインタ
	MeshBuffer* m_pLines;		// 線分の頂点バッファへのポインタ
	Shader* m_pVS;				// 頂点シェーダのポインタ
	Shader* m_pPS;				// ピクセルシェーダのポインタ
	Shader* m_pLineShader[2];		// 線分用シェーダのポインタ
	DirectX::XMFLOAT4X4 m_WVP[3];	// 定数バッファへ書き込むデータのポインタ
	//void* m_pLineVtx;				// shiran
	//int m_lineCnt;					// shiran

public:
	DirectX::XMFLOAT3 GetPos();				// オブジェクトの座標を返す
	DirectX::XMFLOAT3 GetOldPos();			// 1フレーム前の座標を返す
	//DirectX::XMFLOAT3 GetDownVector();		// 下方向へのベクトルを返す
	void SetPos(DirectX::XMFLOAT3);			// 座標をセット
	void SetAngle(DirectX::XMFLOAT3 angle);	// 回転をセット
	void SetScale(DirectX::XMFLOAT3 scale);	// サイズをセット
	void SetMat(DirectX::XMFLOAT4X4*);		// 定数バッファポインタ指定用
	//void SetVelocity(float);				// 移動速度をセット
	void SetDirection(DirectX::XMVECTOR);	// 移動方向ベクトルをセット
	void SetPosX(float posx);				// X座標セット
	void SetPosY(float posy);				// Y座標セット
	void SetPosZ(float posz);				// Z座標セット
	//void SetPlayerPosY(float posY);			// プレイヤーY座標セット
	//float GetMass();						// 質量を返す
	//void SetModelManager(ModelManager* modelManager);	// モデルマネージャーをメンバにセット
	//void SetModelData();								// オブジェクトの種類に応じてモデルデータを取得 

	virtual void DrawModel(DirectX::XMFLOAT4X4* mat, VertexShader* vs);	// モデルの描画
	Model* GetModel();						// モデルデータのポインタを返す
	bool GetDraw();
	void SetDraw(bool draw);
	//std::string GetModelKey();
	//bool IsGetMoney();
	//void SetGetScore(bool getScore);
	void SetPlayerPos(DirectX::XMFLOAT3 playerPos);

protected:
	DirectX::XMFLOAT4X4* m_mat;
	DirectX::XMFLOAT3 m_pos, m_scale, m_rotate;
	float m_PlayerPosY;					// プレイヤーの座標Y
	DirectX::XMFLOAT3 m_oldPos;
	DirectX::XMFLOAT3 m_oldSize;		// Boxサイズ退避用変数
	DirectX::XMFLOAT3 m_oldScale;		// サイズ退避用変数
	DirectX::XMVECTOR m_moveDirection;	// 移動方向ベクトル
	float m_velocity;					// 速度
	float m_gravity;					// 重力
	int m_nKind;						// オブジェクトの種類
	int m_nFruits;						// フルーツフラグ
	bool m_bDelete;						// 削除フラグ
	int m_nCreate;						// 生成フラグ
	int m_nScore;						// ゲットできるスコア
	float m_mass;						// 質量
	bool m_draw;

	Model* m_pModel;				// モデルデータ格納用

	float m_modelRatio;	// モデルの拡縮率
	int m_noldTime;		// 30秒経ったか計算するための値退避
	int m_nTime;		// 現在の時間
	//float m_time;				// サイン用タイマー
	//float m_weight;				// 移動速度増減用
	//float m_radius;				// 移動可能範囲の半径
	//float m_suctionDis;			// ギミック吸い込み限界座標との比率
	float m_fallTime;			// 落下時間
	DirectX::XMFLOAT3 m_playerPos;
	DirectX::XMFLOAT3 m_endPos;	// 移動先座標

	DirectX::XMFLOAT3 m_shakePos;	// 揺れアクション時の座標情報
	//CSoundMng* m_pSoundMng;
	//TrailEffect* m_pTrail;	// 軌跡エフェクト
	//bool m_bTrailSet;			// 
	int m_nMaxRatio;
	float m_fRatio;
};

#endif // __OBJECT_H__

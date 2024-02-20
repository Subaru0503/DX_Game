//----インクルードガード----
#ifndef __COLLISION_H__
#define __COLLISION_H__

//----インクルード部----
#include <DirectXMath.h>
#include "Player.h"
#include "ObjectManager.h"
//#include "Shader.h"
//#include "CameraBase.h"
//#include "Model.h"
//#include "Texture.h"
//#include "MoveEmitter.h"
//#include "Effect.h"
//#include "TrailEffect.h"

//----クラス定義----
class Collision
{
public:
	//---- 当たり判定を行う各種形状----
	// 面
	struct Plane
	{
		DirectX::XMFLOAT3 normal;	// 面の法線
		DirectX::XMFLOAT3 pos;		// 面上の座標
	};

	// レイ
	struct Ray
	{
		DirectX::XMFLOAT3 start;		// レイの開始点
		DirectX::XMFLOAT3 direction;	// レイの方向
	};

	//----当たり判定の結果----
	struct Result
	{
		bool hit;					// 当たったかどうか
		DirectX::XMFLOAT3 point;	// ヒット位置
	};

	//----当たり判定を行う各種形状----
	struct Triangle
	{
		DirectX::XMFLOAT3 p[3];	// 三角形の頂点座標
	};
public:
	void Update();	// オブジェクトとの当たり判定

	// 面とレイの当たり判定
	static Result CheckRayPlane(Ray ray, Plane plane);

	// 点の三角形の内外判定
	static Result CheckPointTriangle(DirectX::XMFLOAT3 point, Triangle triangle);

	// 内側に当たり判定
	static int InsideCheckPoint(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2);

	static int AreaCheckCollision(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2);

	void SetPlayer(Player* player);			// Player情報設定
	void SetObjectManager(CObjectMng* objMng);	// ObjectMng設定

private:
	Player* m_pPlayer;							// Playerポインタ格納用
	CObjectMng* m_pObjMng;						// ObjectMngポインタ格納用
};
#endif			// __COLLISION_H__
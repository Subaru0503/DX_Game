//----インクルードガード----
#ifndef __FIELD_H__
#define __FIELD_H__

//----インクルード部----
#include <DirectXMath.h>
#include "Collision.h"
#include <vector>

//----クラス定義----
class Field
{
public:
	// 初期化
	Field();	// コンストラクタ
	~Field();	// デストラクタ

	void Draw();	// 描画

	// 当たり判定のデータを取得
	Collision::Plane GetPlaneInfo(int index);

	Collision::Triangle GetTriangleInfo(int index, bool first);

	// 初期化で作成したデータ数の取得
	int GetDataNum();

	// フィールドの座標の取得
	DirectX::XMFLOAT3 GetFieldCenterPos(int No);
	// フィールドのサイズ取得
	DirectX::XMFLOAT3 GetFieldSize(int No);
private:
	struct Data
	{
		DirectX::XMFLOAT3 pos;		// フィールド(天面)の位置
		DirectX::XMFLOAT3 size;		// フィールドのサイズ
		DirectX::XMFLOAT3 normal;	// フィールド(天面)の法線
	};
	std::vector<Data> m_data;		// データ配列
};

#endif		// __FIELD_H__
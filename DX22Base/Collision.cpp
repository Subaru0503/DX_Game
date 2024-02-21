//----インクルード部----
#include "Collision.h"

//----オブジェクトとの当たり判定----
void Collision::Update()
{
	// =-=-= 初期化 =-=-=
// ----- オブジェクトのポインタリストを取得 -----
	list<Object*>*  ObjectList = m_pObjMng->GetObjectList();

	//----当たり判定----
	for (Object* pObj : *ObjectList)	// 全てのオブジェクトと当たり判定を取る
	{
		switch (pObj->GetKind())		// オブジェクトの種類に応じた形で当たり判定を取る
		{
			// ----- 矩形　対　矩形 -----
		case Object::NONE:	break;
		case Object::TREE:				// 木

			//---当たり判定を取る----
			if (InsideCheckPoint(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetSize(), pObj->GetScale()))
			{
				DirectX::XMFLOAT3 newPlayerpos = m_pPlayer->GetOldPos();		// 過去座標に戻す
				newPlayerpos.y = m_pPlayer->GetPos().y;							// Y座標は戻さない
				m_pPlayer->SetPos(newPlayerpos);								// 補正
			}
			break;
		case Object::APPLE:
		case Object::BANANA:
		case Object::LEMON:
		case Object::WATER_MELON:
		case Object::CAN:

			//---当たり判定を取る----
			if (InsideCheckPoint(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetSize(), pObj->GetScale()))
			{
				pObj->SetDelete();	// 削除フラグを立てる
				pObj->SetCreate();	// 生成フラグを立てる
				m_pPlayer->AddScore(pObj->GetKind(), pObj->GetColor(), pObj->GetScore());	// スコアの処理
			}
			break;
		}
	}
}

// 面とレイの当たり判定
Collision::Result Collision::CheckRayPlane(Ray ray, Plane plane)
{
	Result result = {};

	// レイの初期値
	float rayLength;
	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&ray.start);		// レイの始点
	DirectX::XMVECTOR vRayN		= DirectX::XMLoadFloat3(&ray.direction);	// レイの方向ベクトル
	DirectX::XMVECTOR vRayEnd	= DirectX::XMVectorAdd(vRayStart, vRayN);	// レイの終点
	DirectX::XMStoreFloat(&rayLength, DirectX::XMVector3Length(vRayN));		// レイの長さ
	vRayN	= DirectX::XMVector3Normalize(vRayN);	// 方向ベクトルの正規化

	// 面の初期値
	DirectX::XMVECTOR vPlaneN = DirectX::XMLoadFloat3(&plane.normal);	// 面の法線
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);	// 面上の座標
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);	// 面の法線の正規化

	// 1)平面の座標からレイの始点までの距離
	float P1;
	DirectX::XMVECTOR vTOStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
	DirectX::XMVECTOR PP1 = DirectX::XMVector3Dot(vPlaneN, vTOStart);
	DirectX::XMStoreFloat(&P1, PP1);

	// 2)平面の座標からレイの終点までの距離
	float P2;
	DirectX::XMVECTOR vTOEnd = DirectX::XMVectorSubtract(vRayEnd, vPlanePos);
	DirectX::XMVECTOR PP2 = DirectX::XMVector3Dot(vPlaneN, vTOEnd);
	DirectX::XMStoreFloat(&P2, PP2);

	// 3)レイが面を貫通しているか
	if (P1 > 0 && P2 < 0)
	{
		result.hit = true;	// ひとまず当たっているとみなす
		float rate = P1 / (P1 + (P2 * -1));
		rayLength = rayLength * rate;
		DirectX::XMStoreFloat3(&result.point, DirectX::XMVectorAdd(
			vRayStart, DirectX::XMVectorScale(vRayN, rayLength)));
	}

	return result;
}

Collision::Result Collision::CheckPointTriangle(DirectX::XMFLOAT3 point, Triangle triangle)
{
	Result result = {false, point};

	// 辺のベクトルと点に向かうベクトルから外積を計算
	DirectX::XMVECTOR vCross[3];	// 外積の計算結果格納先
	DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);
	DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);
	for (int i = 0; i < 3; i++)
	{
		// 各ベクトルの計算
		DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[(i + 1) % 3]);
		DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart);	// 辺のベクトル
		DirectX::XMVECTOR vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);	// 点に向かうベクトル

		// 各外積を計算
		vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
		vCross[i] = DirectX::XMVector3Normalize(vCross[i]);

		// 次のループでは、現在の終点が次の始点になる
		vTriStart = vTriEnd;
	}

	// 外積のベクトル同士から内積を計算
	DirectX::XMVECTOR vDot[3] = { DirectX::XMVector3Dot(vCross[0], vCross[1]), DirectX::XMVector3Dot(vCross[1], vCross[2]),
	DirectX::XMVector3Dot(vCross[2], vCross[0]) };

	float match[3];
	for (int i = 0; i < 3; i++)
	{
		DirectX::XMStoreFloat(&match[i], vCross[i]);
	}

	if (match[0] >= 0 && match[1] >= 0 && match[2] >= 0)
	{
		result.hit = true;	// 三角形内部に点が含まれていた
		result.point = point;
	}
	return result;
}

int Collision::InsideCheckPoint(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2)
{
	Result result = { false };

	DirectX::XMFLOAT3 harfSize1;
	DirectX::XMFLOAT3 harfSize2;
	harfSize1.x = size1.x / 2.0f; harfSize1.y = size1.y / 2.0f; harfSize1.z = size1.z / 2.0f;
	harfSize2.x = size2.x / 2.0f; harfSize2.y = size2.y / 2.0f; harfSize2.z = size2.z / 2.0f;

	if (pos2.x - harfSize2.x < pos1.x + harfSize1.x && pos2.x + harfSize2.x > pos1.x - harfSize1.x)
	{
		if (pos2.y - harfSize2.y < pos1.y + harfSize1.y && pos2.y + harfSize2.y > pos1.y - harfSize1.y)
		{
			if (pos2.z - harfSize2.z < pos1.z + harfSize1.z && pos2.z + harfSize2.z > pos1.z - harfSize1.z)
			{
				result.hit = true;
			}
		}
	}

	return result.hit;
}

int Collision::AreaCheckCollision(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2)
{
	Result result = { false };

	DirectX::XMFLOAT3 harfSize1;
	DirectX::XMFLOAT3 harfSize2;
	harfSize1.x = size1.x / 2.0f; harfSize1.y = size1.y / 2.0f; harfSize1.z = size1.z / 2.0f;
	harfSize2.x = size2.x / 2.0f; harfSize2.y = size2.y / 2.0f; harfSize2.z = size2.z / 2.0f;

	if (pos2.x - harfSize2.x < pos1.x + harfSize1.x && pos2.x + harfSize2.x > pos1.x - harfSize1.x)
	{
		if (pos2.y + harfSize2.y > pos1.y - harfSize1.y)
		{
			if (pos2.z - harfSize2.z < pos1.z + harfSize1.z && pos2.z + harfSize2.z > pos1.z - harfSize1.z)
			{
				result.hit = true;
			}
		}
	}

	return result.hit;
}

// ========== SetPlayer ==========
// 引　数：CPlayer*	プレイヤーの実体のポインタ
// 戻り値：なし
// Player情報を設定する
// ==============================
void Collision::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

// ========== SetObjectManager ==========
// 引　数：CObjectMng*	オブジェクトMngの実体のポインタ
// 戻り値：なし
// ObjectMng情報を設定する
// ======================================
void Collision::SetObjectManager(CObjectMng* objMng)
{
	m_pObjMng = objMng;
}
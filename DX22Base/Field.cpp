//----インクルード部----
#include "Field.h"
#include "Geometory.h"

Field::Field()	// コンストラクタ
{
	Data initData[] = { 
		{DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),DirectX::XMFLOAT3(10.0f, 1.0f, 10.0f),DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f) },
		/*{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),DirectX::XMFLOAT3(30.0f, 1.0f, 30.0f),DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) },*/
	};
	for (int i = 0; i < _countof(initData); i++)
		m_data.push_back(initData[i]);
}

Field::~Field()	// デストラクタ
{

}

void Field::Draw()	// 描画
{
	for (int i = 0; i < m_data.size(); i++)
	{
		// 各ベクトルを用意
		DirectX::XMVECTOR vStart = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&m_data[i].normal);
		vStart = DirectX::XMVector3Normalize(vStart);
		vTarget = DirectX::XMVector3Normalize(vTarget);

		// 二つのベクトルから回転の軸を計算 (Crossはそのうち)
		DirectX::XMVECTOR vCross = DirectX::XMVector3Cross(vStart, vTarget);
		vCross = DirectX::XMVector3Normalize(vCross);

		// 二つのベクトルから回転に必要な角度を計算
		float angle;
		DirectX::XMVECTOR vDot;
		vDot = DirectX::XMVector3Dot(vStart, vTarget);
		DirectX::XMStoreFloat(&angle, vDot);
		angle = acos(angle);

		// フィールド表示に必要な行列を計算
		DirectX::XMMATRIX mSize =
			DirectX::XMMatrixScaling(m_data[i].size.x, m_data[i].size.y, m_data[i].size.z);
		DirectX::XMMATRIX mPos =
			DirectX::XMMatrixTranslation(m_data[i].pos.x, m_data[i].pos.y, m_data[i].pos.z);
		DirectX::XMMATRIX mOffset =
			DirectX::XMMatrixTranslation(0.0f, -m_data[i].size.y * 0.5f, 0.0f);
		DirectX::XMMATRIX mRot = angle > 0.0f ? // 角度が0度だとvCrossの値が不安定になるため
			DirectX::XMMatrixRotationAxis(vCross, angle) :
			DirectX::XMMatrixIdentity();
		//DirectX::XMMATRIX mAngle =
		//	DirectX::XMMatrixRotationX(m_data[i].angle.x) *
		//	DirectX::XMMatrixRotationY(m_data[i].angle.y) *
		//	DirectX::XMMatrixRotationZ(m_data[i].angle.z);
		DirectX::XMMATRIX mWorld = mSize * mPos * mOffset * mRot/* * mAngle*/;
		mWorld = DirectX::XMMatrixTranspose(mWorld);
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, mWorld);

		// 描画
		Geometory::SetWorld(world);
		Geometory::DrawBox();	
	}
}

// 当たり判定のデータを取得
Collision::Plane Field::GetPlaneInfo(int index)
{
	Collision::Plane plane;
	plane.normal = m_data[index].normal;
	plane.pos = m_data[index].pos;

	return plane;
}

Collision::Triangle Field::GetTriangleInfo(int index, bool first)
{
	Collision::Triangle triangle;
	Data data = m_data[index];

	// 各ベクトルを用意
	DirectX::XMVECTOR vStart = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&data.normal);
	vStart = DirectX::XMVector3Normalize(vStart);
	vTarget = DirectX::XMVector3Normalize(vTarget);

	// 二つのベクトルから回転の軸を計算(2つのベクトルから求めた外積のベクトルは回転の軸として利用できる)
	DirectX::XMVECTOR vCross = DirectX::XMVector3Cross(vStart, vTarget);
	vCross = DirectX::XMVector3Normalize(vCross);

	// 二つのベクトルから回転に必要な角度を計算
	float angle;
	DirectX::XMVECTOR vDot;
	vDot = DirectX::XMVector3Dot(vStart, vTarget);
	DirectX::XMStoreFloat(&angle, vDot);
	angle = acos(angle);

	// 天面4隅の頂点を変換する行列を計算
	DirectX::XMMATRIX mSize =
		DirectX::XMMatrixScaling(data.size.x, data.size.y, data.size.z);
	DirectX::XMMATRIX mPos =
		DirectX::XMMatrixTranslation(data.pos.x, data.pos.y, data.pos.z);
	DirectX::XMMATRIX mOffset =
		DirectX::XMMatrixTranslation(0.0f, -data.size.y * 0.5f, 0.0f);
	DirectX::XMMATRIX mRot = angle > 0.0f ? // 角度が0度だとvCrossの値が不安定になるため
		DirectX::XMMatrixRotationAxis(vCross, angle) :
		DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX mWorld = mSize * mPos * mOffset * mRot;

	// 頂点を行列で変換(今まではGPUで計算してもらったが、描画以外で変換後の頂点が必要な場合、自前で計算する)
	DirectX::XMFLOAT3 point[2][3] =	// 三角形の頂点情報
	{
		{ {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f} },	// 三角形その1
		{ {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f, -0.5f} },	// 三角形その2
	};
	for (int i = 0; i < 3; i++)
	{
		DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point[first][i]);
		vPoint = DirectX::XMVector3TransformCoord(vPoint, mWorld);	// 頂点を行列で変換
		DirectX::XMStoreFloat3(&triangle.p[i], vPoint);
	}

	return triangle;
}

int Field::GetDataNum()
{
	return m_data.size();
}

DirectX::XMFLOAT3 Field::GetFieldCenterPos(int No)	// フィールドの座標の取得
{
	DirectX::XMFLOAT3 m_centerpos;
	m_centerpos = m_data[No].pos;
	m_centerpos.y -= m_data[No].size.y / 2.0f;

	return m_centerpos;
}

DirectX::XMFLOAT3 Field::GetFieldSize(int No)	// フィールドのサイズ取得
{
	return m_data[No].size;
}
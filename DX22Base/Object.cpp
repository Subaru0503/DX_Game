#include "Object.h"
#include <math.h>
#include "Player.h"
#include "Geometory.h"
#include "Input.h"

//=====マクロ定義=====
#define PI (3.14159)
#define GRAVITY (0.05f)
#define DOWN_GRAVITY (0.4f)	// 落下時の重力減衰計算用

float m_BoxMoveX;
float m_BoxMoveY;
float m_BoxMoveZ;

float m_SphereMoveX;
float m_SphereMoveY;
float m_SphereMoveZ;

//const float DROP_GRAVITY = 7.6f;		// 1秒当たりの重力（ドロップ中）

float shakeTime;	// 揺れ

/**
*@brief	描画初期情報設定付きコンストラクタ
*@param [in] posX,posY,posZ				描画初期座標
*@param [in] scaleX,scaleY,scaleZ		描画初期スケール
*@param [in] rotateX,rotateY,rotateZ	描画初期アングル
*/
Object::Object(float posX, float posY, float posZ)
	: m_pos(posX, posY, posZ)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_rotate(0.0f, 0.0f, 0.0f)
	, m_oldPos(0.0f, 0.0f, 0.0f)
	, m_oldSize(0.0f, 0.0f, 0.0f)
	, m_oldScale(1.0f, 1.0f, 1.0f)
	, m_velocity(0)
	, m_gravity(0.0f)
	, m_moveDirection{ 0.0f,0.0f,0.0f,0.0f }
	, m_nKind(NONE)
	, m_bDelete(false)
	, m_nCreate(false)
	, m_nScore(0)
	, m_mass(1.0f)
	, m_pModel(nullptr)
	, m_modelRatio(1.0)
	//, m_pModelManager(nullptr)
	, m_draw(true)
	, m_shakePos(0.0f, 0.0f, 0.0f)
	//, m_amplitude(0.5f)
	//, m_time(0.0f)
	//, m_weight(1.0f)
	//, m_suctionDis(0.0f)
	, m_nMaxRatio(0)
	, m_fRatio(1.0f)
	, m_nTime(0)
	, m_fallTime(0.0f)
{

}

Object::~Object()
{
	Uninit();
}

void Object::Init()
{
	for (int i = 0; i < 3; ++i)
		DirectX::XMStoreFloat4x4(&m_WVP[i], DirectX::XMMatrixIdentity());
	//MakeBox();
	////MakeCylinder();
	////MakeSphere();
	//MakeVS();
	//MakePS();
	//MakeLineShader();
	//MakeLine();
	/*SetBoxMove();*/
}
void Object::Uninit()
{
	/*SAFE_DELETE_ARRAY(m_pLineVtx);*/
	//SAFE_DELETE(m_pLineShader[1]);
	//SAFE_DELETE(m_pLineShader[0]);
	//SAFE_DELETE(m_pPS);
	//SAFE_DELETE(m_pVS);
	/*SAFE_DELETE(m_pLines);*/
	//SAFE_DELETE(m_pSphere);
	//SAFE_DELETE(m_pCylinder);
	/*SAFE_DELETE(m_pBox);*/
}

void Object::Update(float tick)
{
	// フルーツなら処理をする
	if (m_nFruits)
	{
		m_pos.y -= 0.01f + (GRAVITY * m_mass) * (m_nTime / 60.0f);	// 落下させる
		if (m_pos.y < -1.0f)	// 地面よりしたなら消す
		{
			m_bDelete = true;
			m_nCreate = true;
		}
		m_nTime++;
	}
}

void Object::SetWorld(DirectX::XMFLOAT4X4 world)
{
	m_WVP[0] = world;
}
void Object::SetView(DirectX::XMFLOAT4X4 view)
{
	m_WVP[1] = view;
}
void Object::SetProjection(DirectX::XMFLOAT4X4 proj)
{
	m_WVP[2] = proj;
}

void Object::SetBoxMove(float x, float y, float z)
{
	m_BoxMoveX = x;
	m_BoxMoveY = y;
	m_BoxMoveZ = z;
}

void Object::SetSphereMove(float x, float y, float z)
{
	m_SphereMoveX = x;
	m_SphereMoveY = y;
	m_SphereMoveZ = z;
}

int Object::GetKind()
{
	return m_nKind;
}

int Object::GetColor()				// オブジェクトの色の種類を返す
{
	return m_nColor;
}

DirectX::XMFLOAT3 Object::GetScale()
{
	return m_scale;
}

bool Object::GetDelete()
{
	return m_bDelete;
}

void Object::SetDelete()
{
	m_bDelete = true;
}

void Object::SetCreate()	// 生成フラグを立てる
{
	m_nCreate = true;
}

int Object::GetCreate()		// 生成フラグを返す
{
	return m_nCreate;
}

int Object::GetScore()
{
	return m_nScore;
}

DirectX::XMFLOAT3 Object::GetAngle()
{
	return m_rotate;
}

//void Object::SetSound(CSoundMng * sound)
//{
//	m_pSoundMng = sound;
//}

void Object::MakeVS()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.uv = vin.uv;
	return vout;
})EOT";

	m_pVS = new VertexShader();
	m_pVS->Compile(VSCode);
}

void Object::MakePS()
{
#ifdef _DEBUG
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	float4 color = float4(1,1,1,1);
	float2 halfGrid = floor(abs(pin.uv) * 2.0f);
	float2 quatGrid = floor(abs(pin.uv) * 8.0f);

	float half = fmod(halfGrid.x + halfGrid.y, 2.0f);
	float quat = fmod(quatGrid.x + quatGrid.y, 2.0f);

	color.rgb = ((half * 0.1f) * quat + 0.45f) + (1 - quat) * 0.05f;
	return color;
})EOT";
#else
	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return float4(1.0f, 0.0f, 1.0f, 1.0f);
})EOT";
#endif

	m_pPS = new PixelShader();
	m_pPS->Compile(PSCode);
}
void Object::MakeLineShader()
{
	const char* VSCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float4 color : COLOR0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
cbuffer Matrix : register(b0) {
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);
	vout.color = vin.color;
	return vout;
})EOT";

	const char* PSCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return pin.color;
})EOT";

	m_pLineShader[0] = new VertexShader();
	m_pLineShader[0]->Compile(VSCode);
	m_pLineShader[1] = new PixelShader();
	m_pLineShader[1]->Compile(PSCode);
}
//void Object::MakeLine()
//{
//	m_pLineVtx = new LineVertex[MAX_LINE_NUM * 2];
//	m_lineCnt = 0;
//	MeshBuffer::Description desc = {};
//	desc.pVtx = m_pLineVtx;
//	desc.vtxCount = MAX_LINE_NUM * 2;
//	desc.vtxSize = sizeof(LineVertex);
//	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
//	desc.isWrite = true;
//	m_pLines = new MeshBuffer(desc);
//}

//void Object::MakeBox()
//{
//	// 元データの作成
//	Vertex vtx[] =
//	{
//		// -X面
//		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// -Y面
//		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
//		{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// -Z面
//		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
//		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ { 0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// X面
//		{ { 0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
//		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ { 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f} },
//
//		// Y面
//		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
//		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// Z面
//		{ { 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f} },
//		{ {-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f} },
//	};
//	int idx[] = {
//		 0,  1,  2,  1,  3,  2,	// -X面
//		 4,  5,  6,  5,  7,  6,	// -Y面
//		 8,  9, 10,  9, 11, 10,	// -Z面
//		12, 13, 14, 13, 15, 14,	//  X面
//		16, 17, 18, 17, 19, 18,	//  Y面
//		20, 21, 22, 21, 23, 22,	//  Z面
//	};
//	// バッファの作成
//	MeshBuffer::Description desc = {};
//	desc.pVtx = vtx;
//	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); 配列のサイズを返す //24;	// 頂点の数
//	desc.vtxSize = sizeof(Vertex); // 20;	// 頂点一つ当たりのデータサイズ
//	desc.pIdx = idx;
//	desc.idxCount = _countof(idx);	// インデックスの数
//	desc.idxSize = sizeof(int); //4;	// インデックス一つ当たりのデータサイズ
//	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	m_pBox = new MeshBuffer(desc);
//}
//
//void Object::MakeCylinder()
//{
//	float r;      //作る円柱の半径
//	float radian; //ラジアン角
//	float uv;
//	float height; //高さ
//
//	radian = 2 * PI / 8;  //八角形のラジアンの角度
//	uv = 1.0f / 8.0f;
//
//	r = 1.5f;
//	height = 1.5f;
//
//	Vertex vtx[]
//	{
//		//上面
//		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0), sinf((float)radian * 0)}},
//		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1), sinf((float)radian * 1)}},
//		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2), sinf((float)radian * 2)}},
//		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3), sinf((float)radian * 3)}},
//		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4), sinf((float)radian * 4)}},
//		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5), sinf((float)radian * 5)}},
//		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6), sinf((float)radian * 6)}},
//		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7), sinf((float)radian * 7)}},
//
//		//側面
//		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {uv * 0, 0.0f}},
//		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {uv * 1, 0.0f}},
//		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {uv * 0, 1.0f}},
//		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {uv * 1, 1.0f}},
//
//		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {uv * 1, 0.0f}},
//		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {uv * 2, 0.0f}},
//		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {uv * 1, 1.0f}},
//		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {uv * 2, 1.0f}},
//
//		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {uv * 2, 0.0f}},
//		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {uv * 3, 0.0f}},
//		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {uv * 2, 1.0f}},
//		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {uv * 3, 1.0f}},
//
//		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {uv * 3, 0.0f}},
//		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {uv * 4, 0.0f}},
//		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {uv * 3, 1.0f}},
//		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {uv * 4, 1.0f}},
//
//		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {uv * 4, 0.0f}},
//		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {uv * 5, 0.0f}},
//		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {uv * 4, 1.0f}},
//		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {uv * 5, 1.0f}},
//
//		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {uv * 5, 0.0f}},
//		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {uv * 6, 0.0f}},
//		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {uv * 5, 1.0f}},
//		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {uv * 6, 1.0f}},
//
//		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {uv * 6, 0.0f}},
//		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {uv * 7, 0.0f}},
//		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {uv * 6, 1.0f}},
//		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {uv * 7, 1.0f}},
//
//		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {uv * 7, 0.0f}},
//		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {uv * 8, 0.0f}},
//		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {uv * 7, 1.0f}},
//		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {uv * 8, 1.0f}},
//
//		//裏面
//		{{cosf((float)radian * 0) * r, -height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0),sinf((float)radian * 0)}},
//		{{cosf((float)radian * 1) * r, -height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1),sinf((float)radian * 1)}},
//		{{cosf((float)radian * 2) * r, -height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2),sinf((float)radian * 2)}},
//		{{cosf((float)radian * 3) * r, -height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3),sinf((float)radian * 3)}},
//		{{cosf((float)radian * 4) * r, -height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4),sinf((float)radian * 4)}},
//		{{cosf((float)radian * 5) * r, -height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5),sinf((float)radian * 5)}},
//		{{cosf((float)radian * 6) * r, -height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6),sinf((float)radian * 6)}},
//		{{cosf((float)radian * 7) * r, -height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7),sinf((float)radian * 7)}},
//
//
//	};
//
//	//インデックスの作成
//	int idx[] = {
//		//上面
//		2,1,0,2,0,3,
//		3,0,4,4,0,5,
//		5,0,6,6,0,7,
//
//		//側面
//		 8, 9,10,10, 9,11,
//		12,13,14,14,13,15,
//		16,17,18,18,17,19,
//		20,21,22,22,21,23,
//		24,25,26,26,25,27,
//		28,29,30,30,29,31,
//		32,33,34,34,33,35,
//		36,37,38,38,37,39,
//
//		//裏面
//		40,41,42,40,42,43,
//		40,43,44,40,44,45,
//		40,45,46,40,46,47,
//	};
//
//	//--- バッファの作成
//	MeshBuffer::Description desc = {};
//	desc.pVtx = vtx;
//	desc.vtxCount = _countof(vtx);
//	desc.vtxSize = sizeof(Vertex);
//	desc.pIdx = idx;
//	desc.idxCount = _countof(idx);
//	desc.idxSize = sizeof(int);
//	desc.topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	m_pCylinder = new MeshBuffer(desc);
//}
//
//void Object::MakeSphere()
//{
//	//--- 頂点の作成
//		// 元データの作成
//	Vertex vtx[] =
//	{
//		//--------------X面--------------
//		// -X面(天面)
//		{ {0.0f, 1.0f,  0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f, -0.0f}, {1.0f, 0.0f} },
//		{ {-0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {-0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },
//
//		// -X面(上側斜めの天面側)
//		{ {-0.3f,0.9f,  0.25f}, {0.0f, 0.0f} },
//		{ {-0.3f,0.9f, -0.25f}, {1.0f, 0.0f} },
//		{ {-0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X面(上側斜めの側面側)
//		{ {-0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X面(上側側面)
//		{ {-0.9f, 0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.9f, 0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {-1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
//		{ {-1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X面(下側側面)
//		{ {-1.0f,0.0f,  0.5f}, {0.0f, 0.0f} },
//		{ {-1.0f,0.0f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X面(下側斜めの側面側)
//		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X面(下側斜めの底面側)
//		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.3f,-0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {-0.3f,-0.9f, -0.25f}, {1.0f, 1.0f} },
//
//		// -X面(底面)
//		{ {-0.3f, -0.9f,0.25f}, {0.0f, 0.0f} },
//		{ {-0.3f, -0.9f,-0.25f}, {1.0f, 0.0f} },
//		{ {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
//		{ {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
//
//		// X面(天面)
//		{ {0.3f, 0.9f,  0.25f}, {0.0f, 0.0f} },
//		{ {0.3f, 0.9f, -0.25f}, {1.0f, 0.0f} },
//		{ {0.0f, 1.0f,  0.0f}, {0.0f, 1.0f} },
//		{ {0.0f, 1.0f, -0.0f}, {1.0f, 1.0f} },
//
//		// X面(上側斜めの天面側)
//		{ {0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },
//
//		// X面(上側斜めの側面側)
//		{ {0.9f,0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.9f,0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// X面(上側側面)
//		{ {1.0f, 0.0f,  0.5f}, {0.0f, 0.0f} },
//		{ {1.0f, 0.0f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// X面(下側側面)
//		{ {0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
//		{ {1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },
//
//		// X面(下側斜めの側面側)
//		{ {0.7f, -0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.7f, -0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.9f, -0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.9f, -0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// X面(下側斜めの底面側)
//		{ {0.3f, -0.9f,  0.25f}, {0.0f, 0.0f} },
//		{ {0.3f, -0.9f, -0.25f}, {1.0f, 0.0f} },
//		{ {0.7f, -0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.7f, -0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// X面(底面)
//		{ {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, -1.0f, -0.0f}, {1.0f, 0.0f} },
//		{ {0.3f, -0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {0.3f, -0.9f, -0.25f}, {1.0f, 1.0f} },
//		////--------------X面--------------
//
//		//--------------Z面--------------
//		// Z面(天面)
//		{ {0.0f,1.0f, 0.0f}, {0.0f, 0.0f} },
//		{ {0.0f,1.0f, 0.0f}, {1.0f, 0.0f} },
//		{ {0.25f,0.9f, 0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,0.9f,0.3f}, {1.0f, 1.0f} },
//
//		// Z面(上側斜めの天面側)
//		{ { 0.25f,0.9f, 0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,0.9f, 0.3f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.7f, 0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.7f, 0.7f}, {1.0f, 1.0f} },
//
//		// Z面(上側斜めの側面側)
//		{ { 0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// Z面(上側側面)
//		{ { 0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.0f,1.0f}, {1.0f, 1.0f} },
//
//		// Z面(下側側面)
//		{ { 0.5f, 0.0f,1.0f}, {0.0f, 0.0f} },
//		{ {-0.5f, 0.0f,1.0f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// Z面(下側斜めの側面側)
//		{ { 0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },
//
//		// Z面(下側斜めの底面側)
//		{ { 0.5f,-0.7f, 0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.7f, 0.7f}, {1.0f, 0.0f} },
//		{ { 0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },
//
//		// Z面(底面)
//		{ { 0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
//		{ { 0.0f,-1.0f, 0.0f}, {0.0f, 1.0f} },
//		{ { 0.0f,-1.0f, 0.0f}, {1.0f, 1.0f} },
//
//		// -Z面(天面)
//		{ { 0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
//		{ { 0.0f,1.0f, 0.0f}, {0.0f, 1.0f} },
//		{ { 0.0f,1.0f, 0.0f}, {1.0f, 1.0f} },
//
//		// -Z面(上側斜めの天面側)
//		{ { 0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
//		{ { 0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },
//
//		// -Z面(上側斜めの側面側)
//		{ { 0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },
//
//		// -Z面(上側側面)
//		{ { 0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },
//
//		// -Z面(下側側面)
//		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },
//
//		// -Z面(下側斜めの側面側)
//		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },
//
//		// -Z面(下側斜めの底面側)
//		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },
//
//		// -Z面(底面)
//		{ { 0.0f,-1.0f,0.0f}, {0.0f, 0.0f} },
//		{ { 0.0f,-1.0f,0.0f}, {1.0f, 0.0f} },
//		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },
//		////--------------Z面--------------
//
//		//-------------- -XZ面 --------------
//		// -XZ面(天面)
//		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
//		{ {-0.25f,0.9f,0.3f}, {0.0f, 1.0f} },
//		{ {-0.3f, 0.9f,0.25f}, {1.0f, 1.0f} },
//
//		// -XZ面(上側斜めの天面側)
//		{ {-0.25f,0.9f,0.3f}, {0.0f, 0.0f} },
//		{ {-0.3f,0.9f,0.25f}, {1.0f, 0.0f} },
//		{ {-0.5f,0.7f,0.7f}, {0.0f, 1.0f} },
//		{ {-0.7f,0.7f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ面(上側斜めの側面側)
//		{ {-0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
//		{ {-0.7f,0.7f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.9f,0.3f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ面(上側側面)
//		{ {-0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.9f,0.3f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
//		{ {-1.0f,0.0f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ面(下側側面)
//		{ {-0.5f,0.0f,1.0f}, {0.0f, 0.0f} },
//		{ {-1.0f,0.0f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.9f,-0.3f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ面(下側斜めの側面側)
//		{ {-0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.9f,-0.3f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
//		{ {-0.7f,-0.7f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ面(下側斜めの底面側)
//		{ {-0.5f,-0.7f,0.7f}, {0.0f, 0.0f} },
//		{ {-0.7f,-0.7f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
//		{ {-0.3f,-0.9f,0.25f}, {1.0f, 1.0f} },
//
//		// -XZ面(底面)
//		{ {-0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
//		{ {-0.3f,-0.9f,0.25f}, {1.0f, 0.0f} },
//		{ { 0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
//		{ { 0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
//		//-------------- -XZ面 --------------
//
//		//-------------- X-Z面 --------------
//		// X-Z面(天面)
//		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
//		{ {0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {0.3f, 0.9f,-0.25f}, {1.0f, 1.0f} },
//
//		// X-Z面(上側斜めの天面側)
//		{ {0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {0.3f,0.9f,-0.25f}, {1.0f, 0.0f} },
//		{ {0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {0.7f,0.7f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z面(上側斜めの側面側)
//		{ {0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {0.7f,0.7f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {0.9f,0.3f,-0.5f}, {1.0f, 1.0f} },
//
//		// -XZ面(上側側面)
//		{ {0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {0.9f,0.3f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
//		{ {1.0f,0.0f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z面(下側側面)
//		{ {0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
//		{ {1.0f,0.0f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {0.9f,-0.3f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z面(下側斜めの側面側)
//		{ {0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {0.9f,-0.3f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {0.7f,-0.7f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z面(下側斜めの底面側)
//		{ {0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {0.7f,-0.7f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {0.3f,-0.9f,-0.25f}, {1.0f, 1.0f} },
//
//		// X-Z面(底面)
//		{ {0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {0.3f,-0.9f,-0.25f}, {1.0f, 0.0f} },
//		{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
//		{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
//		//-------------- X-Z面 --------------
//
//		//-------------- XZ面 --------------
//		// XZ面(天面)
//		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
//		{ {0.3f, 0.9f,0.25f}, {0.0f, 1.0f} },
//		{ {0.25f,0.9f,0.3f}, {1.0f, 1.0f} },
//
//		// XZ面(上側斜めの天面側)
//		{ {0.3f,0.9f,0.25f}, {0.0f, 0.0f} },
//		{ {0.25f,0.9f,0.3f}, {1.0f, 0.0f} },
//		{ {0.7f,0.7f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,0.7f,0.7f}, {1.0f, 1.0f} },
//
//		// XZ面(上側斜めの側面側)
//		{ {0.7f,0.7f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
//		{ {0.9f,0.3f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// XZ面(上側側面)
//		{ {0.9f,0.3f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
//		{ {1.0f,0.0f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,0.0f,1.0f}, {1.0f, 1.0f} },
//
//		// XZ面(下側側面)
//		{ {1.0f,0.0f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,0.0f,1.0f}, {1.0f, 0.0f} },
//		{ {0.9f,-0.3f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// XZ面(下側斜めの側面側)
//		{ {0.9f,-0.3f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
//		{ {0.7f,-0.7f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },
//
//		// XZ面(下側斜めの底面側)
//		{ {0.7f,-0.7f,0.5f}, {0.0f, 0.0f} },
	//	{ {0.5f,-0.7f,0.7f}, {1.0f, 0.0f} },
	//	{ {0.3f,-0.9f,0.25f}, {0.0f, 1.0f} },
	//	{ {0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },

	//	// XZ面(底面)
	//	{ {0.3f,-0.9f,0.25f}, {0.0f, 0.0f} },
	//	{ {0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
	//	{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
	//	{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
	//	//-------------- XZ面 --------------

	//	//-------------- -X-Z面 --------------
	//	// -X-Z面(天面)
	//	{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
	//	{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
	//	{ {-0.3f, 0.9f,-0.25f}, {0.0f, 1.0f} },
	//	{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },

	//	// -X-Z面(上側斜めの天面側)
	//	{ {-0.3f,0.9f,-0.25f}, {0.0f, 0.0f} },
	//	{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
	//	{ {-0.7f,0.7f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },

	//	// -X-Z面(上側斜めの側面側)
	//	{ {-0.7f,0.7f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
	//	{ {-0.9f,0.3f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },

	//	// -X-Z面(上側側面)
	//	{ {-0.9f,0.3f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
	//	{ {-1.0f,0.0f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },

	//	// -X-Z面(下側側面)
	//	{ {-1.0f,0.0f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
	//	{ {-0.9f,-0.3f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },

	//	// -X-Z面(下側斜めの側面側)
	//	{ {-0.9f,-0.3f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
	//	{ {-0.7f,-0.7f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },

	//	// -X-Z面(下側斜めの底面側)
	//	{ {-0.7f,-0.7f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
	//	{ {-0.3f,-0.9f,-0.25f}, {0.0f, 1.0f} },
	//	{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },

	//	// -X-Z面(底面)
	//	{ {-0.3f,-0.9f,-0.25f}, {0.0f, 0.0f} },
	//	{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
	//	{ {-0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
	//	{ {-0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
	//	//-------------- -X-Z面 --------------
	//};

	////--- インデックスの作成

	//int idx[] = {
	//	//--------------X面--------------
	//	 0,  1,  2,  1,  3,  2,		// -X面(天面)
	//	 4,  5,  6,  5,  7,  6,		// -X面(上側斜めの天面側)
	//	 8,  9, 10,  9, 11, 10,		// -X面(上側斜めの側面側)
	//	 12, 13, 14, 13, 15, 14,	// -X面(上側側面)
	//	 16, 17, 18, 17, 19, 18,	// -X面(下側側面)
	//	 20, 21, 22, 21, 23, 22,	// -X面(下側斜めの側面側)
	//	 24, 25, 26, 25, 27, 26,	// -X面(下側斜めの底面側)
	//	 28, 29, 30, 29, 31, 30,	// -X面(底面)
	//	 32, 33, 34, 33, 35, 34,	//  X面(天面)
	//	 36, 37, 38, 37, 39, 38,	//  X面(上側斜めの天面側)
	//	 40, 41, 42, 41, 43, 42,	//  X面(上側斜めの側面側)
	//	 44, 45, 46, 45, 47, 46,	//  X面(上側側面)
	//	 48, 49, 50, 49, 51, 50,	//  X面(下側側面)
	//	 52, 53, 54, 53, 55, 54,	//  X面(下側斜めの側面側)
	//	 56, 57, 58, 57, 59, 58,	//  X面(下側斜めの底面側)
	//	 60, 61, 62, 61, 63, 62,	//  X面(底面)
	//	 //--------------X面--------------

	//	 //--------------Z面--------------
	//	 64, 65, 66, 65, 67, 66,	//  Z面(天面)
	//	 68, 69, 70, 69, 71, 70,	//  Z面(上側斜めの天面側)
	//	 72, 73, 74, 73, 75, 74,	//  Z面(上側斜めの側面側)
	//	 76, 77, 78, 77, 79, 78,	//  Z面(上側側面)
	//	 80, 81, 82, 81, 83, 82,	//  Z面(下側側面)
	//	 84, 85, 86, 85, 87, 86,	//  Z面(下側斜めの側面側)
	//	 88, 89, 90, 89, 91, 90,	//  Z面(下側斜めの底面側)
	//	 92, 93, 94, 93, 95, 94,	//  Z面(底面)
	//	 96, 97, 98, 97, 99, 98,	// -Z面(天面)
	//	 100,101,102,101,103,102,	// -Z面(上側斜めの天面側)
	//	 104,105,106,105,107,106,	// -Z面(上側斜めの側面側)
	//	 108,109,110,109,111,110,	// -Z面(上側側面)
	//	 112,113,114,113,115,114,	// -Z面(下側側面)
	//	 116,117,118,117,119,118,	// -Z面(下側斜めの側面側)
	//	 120,121,122,121,123,122,	// -Z面(下側斜めの底面側)
	//	 124,125,126,125,127,126,	// -Z面(底面)
	//	 //--------------Z面--------------

	//	 //-------------- -XZ面 --------------
	//	 128,129,130,129,131,130,	// -XZ面(天面)
	//	 132,133,134,133,135,134,	// -XZ面(上側斜めの天面側)
	//	 136,137,138,137,139,138,	// -XZ面(上側斜めの側面側)
	//	 140,141,142,141,143,142,	// -XZ面(上側側面)
	//	 144,145,146,145,147,146,	// -XZ面(下側側面)
	//	 148,149,150,149,151,150,	// -XZ面(下側斜めの側面側)
	//	 152,153,154,153,155,154,	// -XZ面(下側斜めの底面側)
	//	 156,157,158,157,159,158,	// -XZ面(底面)
	//	 //-------------- -XZ面 --------------

	//	 //-------------- X-Z面 --------------
	//	 160,161,162,161,163,162,	// X-Z面(天面)
	//	 164,165,166,165,167,166,	// X-Z面(上側斜めの天面側)
	//	 168,169,170,169,171,170,	// X-Z面(上側斜めの側面側)
	//	 172,173,174,173,175,174,	// X-Z面(上側側面)
	//	 176,177,178,177,179,178,	// X-Z面(下側側面)
	//	 180,181,182,181,183,182,	// X-Z面(下側斜めの側面側)
	//	 184,185,186,185,187,186,	// X-Z面(下側斜めの底面側)
	//	 188,189,190,189,191,190,	// X-Z面(底面)
	//	 //-------------- X-Z面 --------------

	//	 //-------------- XZ面 --------------
	//	 192,193,194,193,195,194,	// XZ面(天面)
	//	 196,197,198,197,199,198,	// XZ面(上側斜めの天面側)
	//	 200,201,202,201,203,202,	// XZ面(上側斜めの側面側)
	//	 204,205,206,205,207,206,	// XZ面(上側側面)
	//	 208,209,210,209,211,210,	// XZ面(下側側面)
	//	 212,213,214,213,215,214,	// XZ面(下側斜めの側面側)
	//	 216,217,218,217,219,218,	// XZ面(下側斜めの底面側)
	//	 220,221,222,221,223,222,	// XZ面(底面)
	//	 //-------------- XZ面 --------------

	//	 //-------------- -X-Z面 --------------
	//	 224,225,126,225,227,226,	// -X-Z面(天面)
	//	 228,229,230,229,231,230,	// -X-Z面(上側斜めの天面側)
	//	 232,233,234,233,235,234,	// -X-Z面(上側斜めの側面側)
	//	 236,237,238,237,239,238,	// -X-Z面(上側側面)
	//	 240,241,242,241,243,242,	// -X-Z面(下側側面)
	//	 244,245,246,245,247,246,	// -X-Z面(下側斜めの側面側)
	//	 248,249,250,249,251,250,	// -X-Z面(下側斜めの底面側)
	//	 252,253,254,253,255,254,	// -X-Z面(底面)
	//	 //-------------- -X-Z面 --------------
	//};
//
//	// バッファの作成
//	MeshBuffer::Description desc = {};
//	desc.pVtx = vtx;
//	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); 配列のサイズを返す //24;	// 頂点の数
//	desc.vtxSize = sizeof(Vertex); // 20;	// 頂点一つ当たりのデータサイズ
//	desc.pIdx = idx;
//	desc.idxCount = _countof(idx);	// インデックスの数
//	desc.idxSize = sizeof(int); //4;	// インデックス一つ当たりのデータサイズ
//	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	m_pSphere = new MeshBuffer(desc);
//}

/**
*@brief	オブジェクトの座標を返す
*/
DirectX::XMFLOAT3 Object::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 Object::GetOldPos()
{
	return m_oldPos;
}

//DirectX::XMFLOAT3 Object::GetDownVector()
//{
//	DirectX::XMFLOAT3 downVector;
//
//	// オブジェクトの位置 (pos)
//	DirectX::XMFLOAT3 pos = { m_pos.x, m_pos.y , m_pos.z };
//
//	// オブジェクトの下方向点 (focus)
//	DirectX::XMFLOAT3 focus = { m_pos.x, m_pos.y * 2.0f, m_pos.z };
//
//	// 注視点からカメラ位置へのベクトルを計算
//	DirectX::XMFLOAT3 lookDirection;
//	lookDirection.x = focus.x - pos.x;
//	lookDirection.y = focus.y - pos.y;
//	lookDirection.z = focus.z - pos.z;
//
//	// このベクトルを正規化 (長さを1にする) して下方ベクトルを得る
//	float length = sqrt(lookDirection.x * lookDirection.x + lookDirection.y * lookDirection.y + lookDirection.z * lookDirection.z);
//	downVector.x = lookDirection.x / length;
//	downVector.y = lookDirection.y / length;
//	downVector.z = lookDirection.z / length;
//
//	return downVector;
//}

/**
*@brief	オブジェクトの座標を引数の値に設定する
*@param [in] newObjectPos	設定する座標
*/
void Object::SetPos(DirectX::XMFLOAT3 newObjectPos)
{
	m_pos = newObjectPos;
}

void Object::SetAngle(DirectX::XMFLOAT3 angle)
{
	m_rotate = angle;
}

void Object::SetScale(DirectX::XMFLOAT3 scale)
{
	m_scale = scale;
}

/**
*@brief	定数バッファのポインタを引数の値に設定する
*@param [in] mat	定数バッファへの先頭アドレス
*/
void Object::SetMat(DirectX::XMFLOAT4X4* mat)
{
	m_mat = mat;
}

void Object::SetDirection(DirectX::XMVECTOR ToPlayer)
{
	m_moveDirection = ToPlayer;
}


void Object::SetPosX(float posx)
{
	m_pos.x = posx;
}

void Object::SetPosY(float posy)
{
	m_pos.y = posy;
}

void Object::SetPosZ(float posz)
{
	m_pos.z = posz;
}

//void Object::SetPlayerPosY(float posY)
//{
//	m_PlayerPosY = posY;
//}
//
//float Object::GetMass()
//{
//	return m_mass;
//}

/*****************************************************
*@brief	モデルマネージャーをメンバにセットする
******************************************************
*@param [in] modelManager モデルマネージャーのポインタ
******************************************************/
//void Object::SetModelManager(ModelManager * modelManager)
//{
//	m_pModelManager = modelManager;
//}

/*******************************************************
*@brief	オブジェクトのモデルキーに応じてモデルを取得する
********************************************************/
//void Object::SetModelData()
//{
//	m_pModel = m_pModelManager->FindModel(m_modelKey);
//}

/****************************************************
*@brief	モデルデータに基づいて描画を行う
*****************************************************
*@param [in] mat 座標を書き込む定数バッファのポインタ
*@param [in] vs	 使う頂点シェーダのポインタ
*****************************************************/
void Object::DrawModel(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	//---変換行列を計算
	world = DirectX::XMMatrixScaling(m_modelRatio *m_oldScale.x, m_modelRatio * m_oldScale.y, m_modelRatio * m_oldScale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);	// シェーダーに渡す用に転置
	DirectX::XMStoreFloat4x4(&mat[0], world);	// ワールド変換行列を設定

	//---変換行列をメンバに設定
	SetWorld(mat[0]);
	SetView(mat[1]);
	SetProjection(mat[2]);

	// デプスバッファ有りのレンダーターゲットビューを作成
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	// 変換行列をGPUの定数バッファにコピー
	vs->WriteBuffer(0, m_WVP);
	// モデル描画で使う頂点シェーダーをセット
	m_pModel->SetVertexShader(vs);
	// モデル描画
	m_pModel->Draw();

}

/***********************************
*@brief	モデルデータのポインタを返す
***********************************/
Model * Object::GetModel()
{
	return m_pModel;
}

bool Object::GetDraw()
{
	return m_draw;
}

void Object::SetDraw(bool draw)
{
	m_draw = draw;
}

//std::string Object::GetModelKey()
//{
//	return m_modelKey;
//}

//bool Object::IsGetMoney()
//{
//	return m_bGetMoney;
//}
//
//void Object::SetGetScore(bool getScore)
//{
//	m_bGetMoney = getScore;
//}

void Object::SetPlayerPos(DirectX::XMFLOAT3 playerPos)
{
	m_playerPos = playerPos;
}

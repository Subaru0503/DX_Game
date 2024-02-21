#include "Object.h"
#include <math.h>
#include "Player.h"
#include "Geometory.h"
#include "Input.h"

//=====�}�N����`=====
#define PI (3.14159)
#define GRAVITY (0.05f)
#define DOWN_GRAVITY (0.4f)	// �������̏d�͌����v�Z�p

float m_BoxMoveX;
float m_BoxMoveY;
float m_BoxMoveZ;

float m_SphereMoveX;
float m_SphereMoveY;
float m_SphereMoveZ;

//const float DROP_GRAVITY = 7.6f;		// 1�b������̏d�́i�h���b�v���j

float shakeTime;	// �h��

/**
*@brief	�`�揉�����ݒ�t���R���X�g���N�^
*@param [in] posX,posY,posZ				�`�揉�����W
*@param [in] scaleX,scaleY,scaleZ		�`�揉���X�P�[��
*@param [in] rotateX,rotateY,rotateZ	�`�揉���A���O��
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
	// �t���[�c�Ȃ珈��������
	if (m_nFruits)
	{
		m_pos.y -= 0.01f + (GRAVITY * m_mass) * (m_nTime / 60.0f);	// ����������
		if (m_pos.y < -1.0f)	// �n�ʂ�肵���Ȃ����
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

int Object::GetColor()				// �I�u�W�F�N�g�̐F�̎�ނ�Ԃ�
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

void Object::SetCreate()	// �����t���O�𗧂Ă�
{
	m_nCreate = true;
}

int Object::GetCreate()		// �����t���O��Ԃ�
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
//	// ���f�[�^�̍쐬
//	Vertex vtx[] =
//	{
//		// -X��
//		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// -Y��
//		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
//		{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// -Z��
//		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
//		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ { 0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// X��
//		{ { 0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
//		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ { 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f} },
//
//		// Y��
//		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
//		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f} },
//		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f} },
//
//		// Z��
//		{ { 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f} },
//		{ {-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f} },
//	};
//	int idx[] = {
//		 0,  1,  2,  1,  3,  2,	// -X��
//		 4,  5,  6,  5,  7,  6,	// -Y��
//		 8,  9, 10,  9, 11, 10,	// -Z��
//		12, 13, 14, 13, 15, 14,	//  X��
//		16, 17, 18, 17, 19, 18,	//  Y��
//		20, 21, 22, 21, 23, 22,	//  Z��
//	};
//	// �o�b�t�@�̍쐬
//	MeshBuffer::Description desc = {};
//	desc.pVtx = vtx;
//	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); �z��̃T�C�Y��Ԃ� //24;	// ���_�̐�
//	desc.vtxSize = sizeof(Vertex); // 20;	// ���_�������̃f�[�^�T�C�Y
//	desc.pIdx = idx;
//	desc.idxCount = _countof(idx);	// �C���f�b�N�X�̐�
//	desc.idxSize = sizeof(int); //4;	// �C���f�b�N�X�������̃f�[�^�T�C�Y
//	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	m_pBox = new MeshBuffer(desc);
//}
//
//void Object::MakeCylinder()
//{
//	float r;      //���~���̔��a
//	float radian; //���W�A���p
//	float uv;
//	float height; //����
//
//	radian = 2 * PI / 8;  //���p�`�̃��W�A���̊p�x
//	uv = 1.0f / 8.0f;
//
//	r = 1.5f;
//	height = 1.5f;
//
//	Vertex vtx[]
//	{
//		//���
//		{{cosf((float)radian * 0) * r,  height, sinf((float)radian * 0) * r}, {cosf((float)radian * 0), sinf((float)radian * 0)}},
//		{{cosf((float)radian * 1) * r,  height, sinf((float)radian * 1) * r}, {cosf((float)radian * 1), sinf((float)radian * 1)}},
//		{{cosf((float)radian * 2) * r,  height, sinf((float)radian * 2) * r}, {cosf((float)radian * 2), sinf((float)radian * 2)}},
//		{{cosf((float)radian * 3) * r,  height, sinf((float)radian * 3) * r}, {cosf((float)radian * 3), sinf((float)radian * 3)}},
//		{{cosf((float)radian * 4) * r,  height, sinf((float)radian * 4) * r}, {cosf((float)radian * 4), sinf((float)radian * 4)}},
//		{{cosf((float)radian * 5) * r,  height, sinf((float)radian * 5) * r}, {cosf((float)radian * 5), sinf((float)radian * 5)}},
//		{{cosf((float)radian * 6) * r,  height, sinf((float)radian * 6) * r}, {cosf((float)radian * 6), sinf((float)radian * 6)}},
//		{{cosf((float)radian * 7) * r,  height, sinf((float)radian * 7) * r}, {cosf((float)radian * 7), sinf((float)radian * 7)}},
//
//		//����
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
//		//����
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
//	//�C���f�b�N�X�̍쐬
//	int idx[] = {
//		//���
//		2,1,0,2,0,3,
//		3,0,4,4,0,5,
//		5,0,6,6,0,7,
//
//		//����
//		 8, 9,10,10, 9,11,
//		12,13,14,14,13,15,
//		16,17,18,18,17,19,
//		20,21,22,22,21,23,
//		24,25,26,26,25,27,
//		28,29,30,30,29,31,
//		32,33,34,34,33,35,
//		36,37,38,38,37,39,
//
//		//����
//		40,41,42,40,42,43,
//		40,43,44,40,44,45,
//		40,45,46,40,46,47,
//	};
//
//	//--- �o�b�t�@�̍쐬
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
//	//--- ���_�̍쐬
//		// ���f�[�^�̍쐬
//	Vertex vtx[] =
//	{
//		//--------------X��--------------
//		// -X��(�V��)
//		{ {0.0f, 1.0f,  0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f, -0.0f}, {1.0f, 0.0f} },
//		{ {-0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {-0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },
//
//		// -X��(�㑤�΂߂̓V�ʑ�)
//		{ {-0.3f,0.9f,  0.25f}, {0.0f, 0.0f} },
//		{ {-0.3f,0.9f, -0.25f}, {1.0f, 0.0f} },
//		{ {-0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X��(�㑤�΂߂̑��ʑ�)
//		{ {-0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X��(�㑤����)
//		{ {-0.9f, 0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.9f, 0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {-1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
//		{ {-1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X��(��������)
//		{ {-1.0f,0.0f,  0.5f}, {0.0f, 0.0f} },
//		{ {-1.0f,0.0f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X��(�����΂߂̑��ʑ�)
//		{ {-0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// -X��(�����΂߂̒�ʑ�)
//		{ {-0.7f,-0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {-0.7f,-0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {-0.3f,-0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {-0.3f,-0.9f, -0.25f}, {1.0f, 1.0f} },
//
//		// -X��(���)
//		{ {-0.3f, -0.9f,0.25f}, {0.0f, 0.0f} },
//		{ {-0.3f, -0.9f,-0.25f}, {1.0f, 0.0f} },
//		{ {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
//		{ {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },
//
//		// X��(�V��)
//		{ {0.3f, 0.9f,  0.25f}, {0.0f, 0.0f} },
//		{ {0.3f, 0.9f, -0.25f}, {1.0f, 0.0f} },
//		{ {0.0f, 1.0f,  0.0f}, {0.0f, 1.0f} },
//		{ {0.0f, 1.0f, -0.0f}, {1.0f, 1.0f} },
//
//		// X��(�㑤�΂߂̓V�ʑ�)
//		{ {0.7f, 0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.7f, 0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.3f, 0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {0.3f, 0.9f, -0.25f}, {1.0f, 1.0f} },
//
//		// X��(�㑤�΂߂̑��ʑ�)
//		{ {0.9f,0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.9f,0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.7f,0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.7f,0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// X��(�㑤����)
//		{ {1.0f, 0.0f,  0.5f}, {0.0f, 0.0f} },
//		{ {1.0f, 0.0f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.9f,0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.9f,0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// X��(��������)
//		{ {0.9f,-0.3f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.9f,-0.3f, -0.5f}, {1.0f, 0.0f} },
//		{ {1.0f,0.0f,  0.5f}, {0.0f, 1.0f} },
//		{ {1.0f,0.0f, -0.5f}, {1.0f, 1.0f} },
//
//		// X��(�����΂߂̑��ʑ�)
//		{ {0.7f, -0.7f,  0.5f}, {0.0f, 0.0f} },
//		{ {0.7f, -0.7f, -0.5f}, {1.0f, 0.0f} },
//		{ {0.9f, -0.3f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.9f, -0.3f, -0.5f}, {1.0f, 1.0f} },
//
//		// X��(�����΂߂̒�ʑ�)
//		{ {0.3f, -0.9f,  0.25f}, {0.0f, 0.0f} },
//		{ {0.3f, -0.9f, -0.25f}, {1.0f, 0.0f} },
//		{ {0.7f, -0.7f,  0.5f}, {0.0f, 1.0f} },
//		{ {0.7f, -0.7f, -0.5f}, {1.0f, 1.0f} },
//
//		// X��(���)
//		{ {0.0f, -1.0f,  0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, -1.0f, -0.0f}, {1.0f, 0.0f} },
//		{ {0.3f, -0.9f,  0.25f}, {0.0f, 1.0f} },
//		{ {0.3f, -0.9f, -0.25f}, {1.0f, 1.0f} },
//		////--------------X��--------------
//
//		//--------------Z��--------------
//		// Z��(�V��)
//		{ {0.0f,1.0f, 0.0f}, {0.0f, 0.0f} },
//		{ {0.0f,1.0f, 0.0f}, {1.0f, 0.0f} },
//		{ {0.25f,0.9f, 0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,0.9f,0.3f}, {1.0f, 1.0f} },
//
//		// Z��(�㑤�΂߂̓V�ʑ�)
//		{ { 0.25f,0.9f, 0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,0.9f, 0.3f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.7f, 0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.7f, 0.7f}, {1.0f, 1.0f} },
//
//		// Z��(�㑤�΂߂̑��ʑ�)
//		{ { 0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// Z��(�㑤����)
//		{ { 0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.0f,1.0f}, {1.0f, 1.0f} },
//
//		// Z��(��������)
//		{ { 0.5f, 0.0f,1.0f}, {0.0f, 0.0f} },
//		{ {-0.5f, 0.0f,1.0f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// Z��(�����΂߂̑��ʑ�)
//		{ { 0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },
//
//		// Z��(�����΂߂̒�ʑ�)
//		{ { 0.5f,-0.7f, 0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.7f, 0.7f}, {1.0f, 0.0f} },
//		{ { 0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },
//
//		// Z��(���)
//		{ { 0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
//		{ { 0.0f,-1.0f, 0.0f}, {0.0f, 1.0f} },
//		{ { 0.0f,-1.0f, 0.0f}, {1.0f, 1.0f} },
//
//		// -Z��(�V��)
//		{ { 0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
//		{ { 0.0f,1.0f, 0.0f}, {0.0f, 1.0f} },
//		{ { 0.0f,1.0f, 0.0f}, {1.0f, 1.0f} },
//
//		// -Z��(�㑤�΂߂̓V�ʑ�)
//		{ { 0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
//		{ { 0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },
//
//		// -Z��(�㑤�΂߂̑��ʑ�)
//		{ { 0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },
//
//		// -Z��(�㑤����)
//		{ { 0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
//		{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },
//
//		// -Z��(��������)
//		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
//		{ { 0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
//		{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },
//
//		// -Z��(�����΂߂̑��ʑ�)
//		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },
//
//		// -Z��(�����΂߂̒�ʑ�)
//		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
//		{ { 0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },
//
//		// -Z��(���)
//		{ { 0.0f,-1.0f,0.0f}, {0.0f, 0.0f} },
//		{ { 0.0f,-1.0f,0.0f}, {1.0f, 0.0f} },
//		{ { 0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },
//		////--------------Z��--------------
//
//		//-------------- -XZ�� --------------
//		// -XZ��(�V��)
//		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
//		{ {-0.25f,0.9f,0.3f}, {0.0f, 1.0f} },
//		{ {-0.3f, 0.9f,0.25f}, {1.0f, 1.0f} },
//
//		// -XZ��(�㑤�΂߂̓V�ʑ�)
//		{ {-0.25f,0.9f,0.3f}, {0.0f, 0.0f} },
//		{ {-0.3f,0.9f,0.25f}, {1.0f, 0.0f} },
//		{ {-0.5f,0.7f,0.7f}, {0.0f, 1.0f} },
//		{ {-0.7f,0.7f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ��(�㑤�΂߂̑��ʑ�)
//		{ {-0.5f,0.7f,0.7f}, {0.0f, 0.0f} },
//		{ {-0.7f,0.7f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.9f,0.3f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ��(�㑤����)
//		{ {-0.5f,0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.9f,0.3f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,0.0f,1.0f}, {0.0f, 1.0f} },
//		{ {-1.0f,0.0f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ��(��������)
//		{ {-0.5f,0.0f,1.0f}, {0.0f, 0.0f} },
//		{ {-1.0f,0.0f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.3f,0.9f}, {0.0f, 1.0f} },
//		{ {-0.9f,-0.3f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ��(�����΂߂̑��ʑ�)
//		{ {-0.5f,-0.3f,0.9f}, {0.0f, 0.0f} },
//		{ {-0.9f,-0.3f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.5f,-0.7f,0.7f}, {0.0f, 1.0f} },
//		{ {-0.7f,-0.7f,0.5f}, {1.0f, 1.0f} },
//
//		// -XZ��(�����΂߂̒�ʑ�)
//		{ {-0.5f,-0.7f,0.7f}, {0.0f, 0.0f} },
//		{ {-0.7f,-0.7f,0.5f}, {1.0f, 0.0f} },
//		{ {-0.25f,-0.9f,0.3f}, {0.0f, 1.0f} },
//		{ {-0.3f,-0.9f,0.25f}, {1.0f, 1.0f} },
//
//		// -XZ��(���)
//		{ {-0.25f,-0.9f,0.3f}, {0.0f, 0.0f} },
//		{ {-0.3f,-0.9f,0.25f}, {1.0f, 0.0f} },
//		{ { 0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
//		{ { 0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
//		//-------------- -XZ�� --------------
//
//		//-------------- X-Z�� --------------
//		// X-Z��(�V��)
//		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
//		{ {0.25f,0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {0.3f, 0.9f,-0.25f}, {1.0f, 1.0f} },
//
//		// X-Z��(�㑤�΂߂̓V�ʑ�)
//		{ {0.25f,0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {0.3f,0.9f,-0.25f}, {1.0f, 0.0f} },
//		{ {0.5f,0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {0.7f,0.7f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z��(�㑤�΂߂̑��ʑ�)
//		{ {0.5f,0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {0.7f,0.7f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {0.9f,0.3f,-0.5f}, {1.0f, 1.0f} },
//
//		// -XZ��(�㑤����)
//		{ {0.5f,0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {0.9f,0.3f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,0.0f,-1.0f}, {0.0f, 1.0f} },
//		{ {1.0f,0.0f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z��(��������)
//		{ {0.5f,0.0f,-1.0f}, {0.0f, 0.0f} },
//		{ {1.0f,0.0f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,-0.3f,-0.9f}, {0.0f, 1.0f} },
//		{ {0.9f,-0.3f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z��(�����΂߂̑��ʑ�)
//		{ {0.5f,-0.3f,-0.9f}, {0.0f, 0.0f} },
//		{ {0.9f,-0.3f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.5f,-0.7f,-0.7f}, {0.0f, 1.0f} },
//		{ {0.7f,-0.7f,-0.5f}, {1.0f, 1.0f} },
//
//		// X-Z��(�����΂߂̒�ʑ�)
//		{ {0.5f,-0.7f,-0.7f}, {0.0f, 0.0f} },
//		{ {0.7f,-0.7f,-0.5f}, {1.0f, 0.0f} },
//		{ {0.25f,-0.9f,-0.3f}, {0.0f, 1.0f} },
//		{ {0.3f,-0.9f,-0.25f}, {1.0f, 1.0f} },
//
//		// X-Z��(���)
//		{ {0.25f,-0.9f,-0.3f}, {0.0f, 0.0f} },
//		{ {0.3f,-0.9f,-0.25f}, {1.0f, 0.0f} },
//		{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
//		{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
//		//-------------- X-Z�� --------------
//
//		//-------------- XZ�� --------------
//		// XZ��(�V��)
//		{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
//		{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
//		{ {0.3f, 0.9f,0.25f}, {0.0f, 1.0f} },
//		{ {0.25f,0.9f,0.3f}, {1.0f, 1.0f} },
//
//		// XZ��(�㑤�΂߂̓V�ʑ�)
//		{ {0.3f,0.9f,0.25f}, {0.0f, 0.0f} },
//		{ {0.25f,0.9f,0.3f}, {1.0f, 0.0f} },
//		{ {0.7f,0.7f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,0.7f,0.7f}, {1.0f, 1.0f} },
//
//		// XZ��(�㑤�΂߂̑��ʑ�)
//		{ {0.7f,0.7f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,0.7f,0.7f}, {1.0f, 0.0f} },
//		{ {0.9f,0.3f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// XZ��(�㑤����)
//		{ {0.9f,0.3f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,0.3f,0.9f}, {1.0f, 0.0f} },
//		{ {1.0f,0.0f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,0.0f,1.0f}, {1.0f, 1.0f} },
//
//		// XZ��(��������)
//		{ {1.0f,0.0f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,0.0f,1.0f}, {1.0f, 0.0f} },
//		{ {0.9f,-0.3f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,-0.3f,0.9f}, {1.0f, 1.0f} },
//
//		// XZ��(�����΂߂̑��ʑ�)
//		{ {0.9f,-0.3f,0.5f}, {0.0f, 0.0f} },
//		{ {0.5f,-0.3f,0.9f}, {1.0f, 0.0f} },
//		{ {0.7f,-0.7f,0.5f}, {0.0f, 1.0f} },
//		{ {0.5f,-0.7f,0.7f}, {1.0f, 1.0f} },
//
//		// XZ��(�����΂߂̒�ʑ�)
//		{ {0.7f,-0.7f,0.5f}, {0.0f, 0.0f} },
	//	{ {0.5f,-0.7f,0.7f}, {1.0f, 0.0f} },
	//	{ {0.3f,-0.9f,0.25f}, {0.0f, 1.0f} },
	//	{ {0.25f,-0.9f,0.3f}, {1.0f, 1.0f} },

	//	// XZ��(���)
	//	{ {0.3f,-0.9f,0.25f}, {0.0f, 0.0f} },
	//	{ {0.25f,-0.9f,0.3f}, {1.0f, 0.0f} },
	//	{ {0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
	//	{ {0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
	//	//-------------- XZ�� --------------

	//	//-------------- -X-Z�� --------------
	//	// -X-Z��(�V��)
	//	{ {0.0f, 1.0f,0.0f}, {0.0f, 0.0f} },
	//	{ {0.0f, 1.0f,0.0f}, {1.0f, 0.0f} },
	//	{ {-0.3f, 0.9f,-0.25f}, {0.0f, 1.0f} },
	//	{ {-0.25f,0.9f,-0.3f}, {1.0f, 1.0f} },

	//	// -X-Z��(�㑤�΂߂̓V�ʑ�)
	//	{ {-0.3f,0.9f,-0.25f}, {0.0f, 0.0f} },
	//	{ {-0.25f,0.9f,-0.3f}, {1.0f, 0.0f} },
	//	{ {-0.7f,0.7f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,0.7f,-0.7f}, {1.0f, 1.0f} },

	//	// -X-Z��(�㑤�΂߂̑��ʑ�)
	//	{ {-0.7f,0.7f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,0.7f,-0.7f}, {1.0f, 0.0f} },
	//	{ {-0.9f,0.3f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,0.3f,-0.9f}, {1.0f, 1.0f} },

	//	// -X-Z��(�㑤����)
	//	{ {-0.9f,0.3f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,0.3f,-0.9f}, {1.0f, 0.0f} },
	//	{ {-1.0f,0.0f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,0.0f,-1.0f}, {1.0f, 1.0f} },

	//	// -X-Z��(��������)
	//	{ {-1.0f,0.0f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,0.0f,-1.0f}, {1.0f, 0.0f} },
	//	{ {-0.9f,-0.3f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,-0.3f,-0.9f}, {1.0f, 1.0f} },

	//	// -X-Z��(�����΂߂̑��ʑ�)
	//	{ {-0.9f,-0.3f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,-0.3f,-0.9f}, {1.0f, 0.0f} },
	//	{ {-0.7f,-0.7f,-0.5f}, {0.0f, 1.0f} },
	//	{ {-0.5f,-0.7f,-0.7f}, {1.0f, 1.0f} },

	//	// -X-Z��(�����΂߂̒�ʑ�)
	//	{ {-0.7f,-0.7f,-0.5f}, {0.0f, 0.0f} },
	//	{ {-0.5f,-0.7f,-0.7f}, {1.0f, 0.0f} },
	//	{ {-0.3f,-0.9f,-0.25f}, {0.0f, 1.0f} },
	//	{ {-0.25f,-0.9f,-0.3f}, {1.0f, 1.0f} },

	//	// -X-Z��(���)
	//	{ {-0.3f,-0.9f,-0.25f}, {0.0f, 0.0f} },
	//	{ {-0.25f,-0.9f,-0.3f}, {1.0f, 0.0f} },
	//	{ {-0.0f,-1.0f,0.0f}, {0.0f, 1.0f} },
	//	{ {-0.0f,-1.0f,0.0f}, {1.0f, 1.0f} },
	//	//-------------- -X-Z�� --------------
	//};

	////--- �C���f�b�N�X�̍쐬

	//int idx[] = {
	//	//--------------X��--------------
	//	 0,  1,  2,  1,  3,  2,		// -X��(�V��)
	//	 4,  5,  6,  5,  7,  6,		// -X��(�㑤�΂߂̓V�ʑ�)
	//	 8,  9, 10,  9, 11, 10,		// -X��(�㑤�΂߂̑��ʑ�)
	//	 12, 13, 14, 13, 15, 14,	// -X��(�㑤����)
	//	 16, 17, 18, 17, 19, 18,	// -X��(��������)
	//	 20, 21, 22, 21, 23, 22,	// -X��(�����΂߂̑��ʑ�)
	//	 24, 25, 26, 25, 27, 26,	// -X��(�����΂߂̒�ʑ�)
	//	 28, 29, 30, 29, 31, 30,	// -X��(���)
	//	 32, 33, 34, 33, 35, 34,	//  X��(�V��)
	//	 36, 37, 38, 37, 39, 38,	//  X��(�㑤�΂߂̓V�ʑ�)
	//	 40, 41, 42, 41, 43, 42,	//  X��(�㑤�΂߂̑��ʑ�)
	//	 44, 45, 46, 45, 47, 46,	//  X��(�㑤����)
	//	 48, 49, 50, 49, 51, 50,	//  X��(��������)
	//	 52, 53, 54, 53, 55, 54,	//  X��(�����΂߂̑��ʑ�)
	//	 56, 57, 58, 57, 59, 58,	//  X��(�����΂߂̒�ʑ�)
	//	 60, 61, 62, 61, 63, 62,	//  X��(���)
	//	 //--------------X��--------------

	//	 //--------------Z��--------------
	//	 64, 65, 66, 65, 67, 66,	//  Z��(�V��)
	//	 68, 69, 70, 69, 71, 70,	//  Z��(�㑤�΂߂̓V�ʑ�)
	//	 72, 73, 74, 73, 75, 74,	//  Z��(�㑤�΂߂̑��ʑ�)
	//	 76, 77, 78, 77, 79, 78,	//  Z��(�㑤����)
	//	 80, 81, 82, 81, 83, 82,	//  Z��(��������)
	//	 84, 85, 86, 85, 87, 86,	//  Z��(�����΂߂̑��ʑ�)
	//	 88, 89, 90, 89, 91, 90,	//  Z��(�����΂߂̒�ʑ�)
	//	 92, 93, 94, 93, 95, 94,	//  Z��(���)
	//	 96, 97, 98, 97, 99, 98,	// -Z��(�V��)
	//	 100,101,102,101,103,102,	// -Z��(�㑤�΂߂̓V�ʑ�)
	//	 104,105,106,105,107,106,	// -Z��(�㑤�΂߂̑��ʑ�)
	//	 108,109,110,109,111,110,	// -Z��(�㑤����)
	//	 112,113,114,113,115,114,	// -Z��(��������)
	//	 116,117,118,117,119,118,	// -Z��(�����΂߂̑��ʑ�)
	//	 120,121,122,121,123,122,	// -Z��(�����΂߂̒�ʑ�)
	//	 124,125,126,125,127,126,	// -Z��(���)
	//	 //--------------Z��--------------

	//	 //-------------- -XZ�� --------------
	//	 128,129,130,129,131,130,	// -XZ��(�V��)
	//	 132,133,134,133,135,134,	// -XZ��(�㑤�΂߂̓V�ʑ�)
	//	 136,137,138,137,139,138,	// -XZ��(�㑤�΂߂̑��ʑ�)
	//	 140,141,142,141,143,142,	// -XZ��(�㑤����)
	//	 144,145,146,145,147,146,	// -XZ��(��������)
	//	 148,149,150,149,151,150,	// -XZ��(�����΂߂̑��ʑ�)
	//	 152,153,154,153,155,154,	// -XZ��(�����΂߂̒�ʑ�)
	//	 156,157,158,157,159,158,	// -XZ��(���)
	//	 //-------------- -XZ�� --------------

	//	 //-------------- X-Z�� --------------
	//	 160,161,162,161,163,162,	// X-Z��(�V��)
	//	 164,165,166,165,167,166,	// X-Z��(�㑤�΂߂̓V�ʑ�)
	//	 168,169,170,169,171,170,	// X-Z��(�㑤�΂߂̑��ʑ�)
	//	 172,173,174,173,175,174,	// X-Z��(�㑤����)
	//	 176,177,178,177,179,178,	// X-Z��(��������)
	//	 180,181,182,181,183,182,	// X-Z��(�����΂߂̑��ʑ�)
	//	 184,185,186,185,187,186,	// X-Z��(�����΂߂̒�ʑ�)
	//	 188,189,190,189,191,190,	// X-Z��(���)
	//	 //-------------- X-Z�� --------------

	//	 //-------------- XZ�� --------------
	//	 192,193,194,193,195,194,	// XZ��(�V��)
	//	 196,197,198,197,199,198,	// XZ��(�㑤�΂߂̓V�ʑ�)
	//	 200,201,202,201,203,202,	// XZ��(�㑤�΂߂̑��ʑ�)
	//	 204,205,206,205,207,206,	// XZ��(�㑤����)
	//	 208,209,210,209,211,210,	// XZ��(��������)
	//	 212,213,214,213,215,214,	// XZ��(�����΂߂̑��ʑ�)
	//	 216,217,218,217,219,218,	// XZ��(�����΂߂̒�ʑ�)
	//	 220,221,222,221,223,222,	// XZ��(���)
	//	 //-------------- XZ�� --------------

	//	 //-------------- -X-Z�� --------------
	//	 224,225,126,225,227,226,	// -X-Z��(�V��)
	//	 228,229,230,229,231,230,	// -X-Z��(�㑤�΂߂̓V�ʑ�)
	//	 232,233,234,233,235,234,	// -X-Z��(�㑤�΂߂̑��ʑ�)
	//	 236,237,238,237,239,238,	// -X-Z��(�㑤����)
	//	 240,241,242,241,243,242,	// -X-Z��(��������)
	//	 244,245,246,245,247,246,	// -X-Z��(�����΂߂̑��ʑ�)
	//	 248,249,250,249,251,250,	// -X-Z��(�����΂߂̒�ʑ�)
	//	 252,253,254,253,255,254,	// -X-Z��(���)
	//	 //-------------- -X-Z�� --------------
	//};
//
//	// �o�b�t�@�̍쐬
//	MeshBuffer::Description desc = {};
//	desc.pVtx = vtx;
//	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); �z��̃T�C�Y��Ԃ� //24;	// ���_�̐�
//	desc.vtxSize = sizeof(Vertex); // 20;	// ���_�������̃f�[�^�T�C�Y
//	desc.pIdx = idx;
//	desc.idxCount = _countof(idx);	// �C���f�b�N�X�̐�
//	desc.idxSize = sizeof(int); //4;	// �C���f�b�N�X�������̃f�[�^�T�C�Y
//	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
//	m_pSphere = new MeshBuffer(desc);
//}

/**
*@brief	�I�u�W�F�N�g�̍��W��Ԃ�
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
//	// �I�u�W�F�N�g�̈ʒu (pos)
//	DirectX::XMFLOAT3 pos = { m_pos.x, m_pos.y , m_pos.z };
//
//	// �I�u�W�F�N�g�̉������_ (focus)
//	DirectX::XMFLOAT3 focus = { m_pos.x, m_pos.y * 2.0f, m_pos.z };
//
//	// �����_����J�����ʒu�ւ̃x�N�g�����v�Z
//	DirectX::XMFLOAT3 lookDirection;
//	lookDirection.x = focus.x - pos.x;
//	lookDirection.y = focus.y - pos.y;
//	lookDirection.z = focus.z - pos.z;
//
//	// ���̃x�N�g���𐳋K�� (������1�ɂ���) ���ĉ����x�N�g���𓾂�
//	float length = sqrt(lookDirection.x * lookDirection.x + lookDirection.y * lookDirection.y + lookDirection.z * lookDirection.z);
//	downVector.x = lookDirection.x / length;
//	downVector.y = lookDirection.y / length;
//	downVector.z = lookDirection.z / length;
//
//	return downVector;
//}

/**
*@brief	�I�u�W�F�N�g�̍��W�������̒l�ɐݒ肷��
*@param [in] newObjectPos	�ݒ肷����W
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
*@brief	�萔�o�b�t�@�̃|�C���^�������̒l�ɐݒ肷��
*@param [in] mat	�萔�o�b�t�@�ւ̐擪�A�h���X
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
*@brief	���f���}�l�[�W���[�������o�ɃZ�b�g����
******************************************************
*@param [in] modelManager ���f���}�l�[�W���[�̃|�C���^
******************************************************/
//void Object::SetModelManager(ModelManager * modelManager)
//{
//	m_pModelManager = modelManager;
//}

/*******************************************************
*@brief	�I�u�W�F�N�g�̃��f���L�[�ɉ����ă��f�����擾����
********************************************************/
//void Object::SetModelData()
//{
//	m_pModel = m_pModelManager->FindModel(m_modelKey);
//}

/****************************************************
*@brief	���f���f�[�^�Ɋ�Â��ĕ`����s��
*****************************************************
*@param [in] mat ���W���������ޒ萔�o�b�t�@�̃|�C���^
*@param [in] vs	 �g�����_�V�F�[�_�̃|�C���^
*****************************************************/
void Object::DrawModel(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;
	//---�ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(m_modelRatio *m_oldScale.x, m_modelRatio * m_oldScale.y, m_modelRatio * m_oldScale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_rotate.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_rotate.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_rotate.z)) *
		DirectX::XMMatrixTranslation(m_pos.x + m_BoxMoveX, m_pos.y + m_BoxMoveY, m_pos.z + m_BoxMoveZ);

	world = DirectX::XMMatrixTranspose(world);	// �V�F�[�_�[�ɓn���p�ɓ]�u
	DirectX::XMStoreFloat4x4(&mat[0], world);	// ���[���h�ϊ��s���ݒ�

	//---�ϊ��s��������o�ɐݒ�
	SetWorld(mat[0]);
	SetView(mat[1]);
	SetProjection(mat[2]);

	// �f�v�X�o�b�t�@�L��̃����_�[�^�[�Q�b�g�r���[���쐬
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	// �ϊ��s���GPU�̒萔�o�b�t�@�ɃR�s�[
	vs->WriteBuffer(0, m_WVP);
	// ���f���`��Ŏg�����_�V�F�[�_�[���Z�b�g
	m_pModel->SetVertexShader(vs);
	// ���f���`��
	m_pModel->Draw();

}

/***********************************
*@brief	���f���f�[�^�̃|�C���^��Ԃ�
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

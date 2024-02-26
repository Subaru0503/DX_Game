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
	m_pTexture = new Texture();
	if (FAILED(m_pTexture->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Object Shadow.png", "Error", MB_OK);
	}
}

Object::~Object()
{
	Uninit();
	SAFE_DELETE(m_pTexture);
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

	if (m_pos.y < 0.0f) return;

	DirectX::XMMATRIX Shadowworld = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90.0f)) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, 0.01f, m_pos.z);

	DirectX::XMFLOAT4X4 Shadowmat;
	DirectX::XMStoreFloat4x4(&Shadowmat, DirectX::XMMatrixTranspose(Shadowworld));
	Sprite::SetWorld(Shadowmat);					// ���[���h�s��̐ݒ�
	Sprite::SetView(mat[1]);	// �r���[�s��̐ݒ�
	Sprite::SetProjection(mat[2]);	// �v���W�F�N�V�����s��̐ݒ�
	Sprite::SetSize(DirectX::XMFLOAT2(1.0f, 1.0f));		// �T�C�Y��ݒ�
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture);					// �e�N�X�`����ݒ�
	Sprite::Draw();
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

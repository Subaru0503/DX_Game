//----�C���N���[�h��----
#include "Player.h"
#include "Input.h"
#include "Sprite.h"

//----�萔�E�}�N����`----
#define GRAVITY (0.15f)
#define RADIAN (180.0f / 3.14f)
#define JUMP (1.0f)

Player::Player()	// �R���X�g���N�^
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_oldpos(0.0f, 0.0f, 0.0f)
	, m_size(0.5f, 2.0f, 0.5f)
	, m_pCamera(nullptr)
	, m_pTexture{ nullptr, nullptr }
	, m_fGravity(0.0f)
	, m_Move{ 0.0f, 0.0f, 0.0f }	// �ړ����
	, m_OldMove{ 0.0f, 0.0f, 0.0f }	// �O�̈ړ����
	, m_directRad(0.0f)				//�v���C���[�̌������W�A���p
	, m_directAngle(0.0f)			//�v���C���[�̌����p�x
	, m_nLand(0)					// �W�����v�t���O
	, m_fJump(0.0f)					// �W�����v��
	, m_nEventFlg(true)
{
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/3D���f���f�[�^/�����c�߂߂�/MokotaMememe.pmx", 1.0f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "Player���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/shader/VS_Model.cso")))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "Player�V�F�[�_�[�ǂݍ��ݎ��s", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_pEffect = new Effect();
	m_pMoveEmitter = new MoveEmitter();
	m_pEffect->AddEmitter(m_pMoveEmitter);

	m_pTexture[0] = new Texture();
	m_pTexture[1] = new Texture();
	m_pTexture[2] = new Texture();
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Player Shadow.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Marker.png")))
	{
		MessageBox(NULL, "Player Marker.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/warp.png")))
	{
		MessageBox(NULL, "Player warp.png", "Error", MB_OK);
	}

	m_pTrail = new TrailEffect(this);
	m_pTrail->AddLine(20);
	m_pTrail->AddLine(10);
}

Player::~Player()
{
	delete m_pTrail;
	delete m_pMoveEmitter;
	delete m_pEffect;
	delete m_pVS;
	delete m_pModel;

	for (int i = 0; i < 3; i++)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void Player::Update()
{
	//----���W�ޔ�----
	m_oldpos = m_pos;

	//----�d�͉��Z----
	m_pos.y -= GRAVITY;

	//----�W�����v���Ă���d�͂̕�����----
	if (m_fJump > 0.0f)
	{
		//----�d�͕�����----
		m_fJump -= GRAVITY;

		//----0��菬�����Ȃ��Ă���0�ɖ߂�----
		if (m_fJump < 0.0f)
		{
			m_fJump = 0.0f;	//----0�ɒ���----
		}
	}


	bool isMove = false;
	DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();	// �J�����̍��W
	DirectX::XMFLOAT3 camLook = m_pCamera->GetLook();	// �J�����̒����_
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);

	DirectX::XMVECTOR vFront;	// �J�����̐��ʕ����̃x�N�g��
	vFront = DirectX::XMVectorSubtract(vCamPos, vCamLook);	// ���ʕ����̃x�N�g���v�Z
	vFront = DirectX::XMVector3Normalize(vFront);	// ���K��

	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f));	// 90�x��]
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);
	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();	// 0�ŏ�����

	//const float Speed = 0.1f;
	// �C�x���g�̂Ȃ�����������ł���悤��
	if (!m_nEventFlg)
	{
		//----�v���C���[�ړ�����----
		if (IsKeyPress('W')) { isMove = true; vMove = DirectX::XMVectorSubtract(vMove, vFront); }
		if (IsKeyPress('S')) { isMove = true; vMove = DirectX::XMVectorAdd(vMove, vFront); }
		if (IsKeyPress('D')) { isMove = true; vMove = DirectX::XMVectorSubtract(vMove, vSide); }
		if (IsKeyPress('A')) { isMove = true; vMove = DirectX::XMVectorAdd(vMove, vSide); }
	}

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);	// �ړ��x�N�g���̐��K��
	vMove = DirectX::XMVectorScale(vMove, 0.1f);	// �ړ����x

	DirectX::XMStoreFloat3(&m_Move, vMove);	// XMFLOAT3�ɕϊ�

	//----�n�ʂɂ��ĂăW�����v�{�^���������ꂽ��----
	if (m_nLand && IsKeyTrigger(VK_SPACE))
	{
		m_fJump = JUMP;	// �W�����v��
		m_nLand = 0;	// ���n�t���O����
	}

	m_pos.x += m_Move.x; m_pos.y += m_Move.y + m_fJump; m_pos.z += m_Move.z;	// ���W�̍X�V

	//----�v���C���[�̉�]�p�x���v�Z----
	float rotationAngle;

	// �ړ����Ă���
	if (m_Move.x != 0.0f || m_Move.z != 0.0f)
	{
		// �ړ����������ɉ�]����悤�ɒ���
		rotationAngle = atan2(m_Move.x, m_Move.z);
		// �ړ����ޔ�
		m_OldMove = m_Move;
	}
	// �ړ����ĂȂ�������
	else
	{
		// �O��̕����̂܂�
		rotationAngle = atan2(m_OldMove.x, m_OldMove.z);
	}

	//---�v���C���[�̉�]�s����X�V
	m_directRad = rotationAngle;
	m_directAngle = rotationAngle * RADIAN;  // ���W�A���p����x���ɕϊ�
	m_directRad = DirectX::XMConvertToRadians(m_directAngle);// / RADIAN;
	//----�v���C���[�̉�]�p�x���v�Z----

	// �C�x���g���Ȃ�I��
	if (m_nEventFlg) return;

	m_pEffect->Update();		// �G�t�F�N�g�̍X�V
	m_pEffect->SetPos(m_pos);	// �����ʒu�̐ݒ�
	if (!m_pEffect->IsPlay() && isMove)	// �G�t�F�N�g�̍Đ����~�܂��Ă����Ԃňړ����Ă��邩
	{
		m_pEffect->Play();		// �G�t�F�N�g�̔���
	}

	m_pTrail->Update();

	if (m_pos.y < -20.0f)
	{
		m_pos.y = 0.0f;
	}
}

void Player::Draw()
{
	// �J�������Ȃ���Ώ����͍s��Ȃ�
	if (!m_pCamera) { return; }

	// �s��̌v�Z
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMFLOAT3 centerRotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	//���_
	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *
							  DirectX::XMMatrixRotationX(0.0f) *
							  DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(180.0f)) *
							  DirectX::XMMatrixRotationZ(0.0f) *
							  DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	//---���S�_�̕ϊ�
	DirectX::XMMATRIX centerTranslationMatrix =
		DirectX::XMMatrixTranslation(-centerRotation.x, -centerRotation.y, -centerRotation.z);
	DirectX::XMMATRIX centerRotationMatrix = DirectX::XMMatrixRotationY(m_directRad);  // ������]��K�p
	DirectX::XMMATRIX centerWorldMatrix = centerRotationMatrix * centerTranslationMatrix;

	//---���S�_�𒆐S�Ƀ��f������]
	world = centerWorldMatrix * world;

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();
	
	m_pVS->WriteBuffer(0, mat);
	m_pModel->Draw();

	// �e
	DirectX::XMMATRIX Shadowworld = /*DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) **/
		DirectX::XMMatrixRotationX(-80.0f) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.01f, m_pos.z);

	DirectX::XMFLOAT4X4 Shadowmat;
	DirectX::XMStoreFloat4x4(&Shadowmat, DirectX::XMMatrixTranspose(Shadowworld));
	Sprite::SetWorld(Shadowmat);					// ���[���h�s��̐ݒ�
	Sprite::SetView(m_pCamera->GetViewMatrix());	// �r���[�s��̐ݒ�
	Sprite::SetProjection(m_pCamera->GetProjectionMatrix());	// �v���W�F�N�V�����s��̐ݒ�
	Sprite::SetSize(DirectX::XMFLOAT2(0.5f, 0.5f));		// �T�C�Y��ݒ�
	Sprite::SetTexture(m_pTexture[0]);					// �e�N�X�`����ݒ�
	Sprite::Draw();

	// �C�x���g����������`�悵�Ȃ�
	if (m_nEventFlg) return;

	DirectX::XMFLOAT4X4 inv;	// �t�s��̊i�[��
	inv = m_pCamera->GetViewMatrix();

	// �J�����̍s���GPU�ɓn���ۂɓ]�u����Ă���A�t�s��̌v�Z�̂��߂Ɉ�x���ɖ߂��B
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);

	matInv = DirectX::XMMatrixTranspose(matInv);	// �]�u
	// �ړ������͋t�s��őł������K�v���Ȃ��̂ŁA�t�s��̌v�Z�̂��߂Ɉ�x���ɖ߂��B
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);	// �t�s��̍쐬

	// �G�t�F�N�g
	// Z�\�[�g(������`��)
	DirectX::XMFLOAT4X4 matBill;
	DirectX::XMStoreFloat4x4(&matBill, matInv);

	// marker
	DirectX::XMMATRIX invworld = matInv * DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 2.3f, m_pos.z);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(invworld));
	Sprite::SetWorld(mat[0]);
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	m_pEffect->SetBillboardMatrix(matBill);
	//----�G�t�F�N�g----
	m_pEffect->Draw(
		m_pCamera->GetViewMatrix(),
		m_pCamera->GetProjectionMatrix());


	// �O�Ղ̕\��
	m_pTrail->SetView(m_pCamera->GetViewMatrix());
	m_pTrail->SetProjection(m_pCamera->GetProjectionMatrix());
	m_pTrail->SetTexture(m_pTexture[2]);
	m_pTrail->Draw();
}

void Player::SetCamera(CameraBase * pCamera)
{
	m_pCamera = pCamera;
}

void Player::ResetGravity()	// �d�̓��Z�b�g�֐�
{
	m_fGravity = 0.0f;
}

void Player::ResetJumpFlg()	// �W�����v�t���O�����֐�
{
	m_nLand = 1;
}

void Player::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void Player::SetEventFlg(int event)
{
	m_nEventFlg = event;
}

void Player::SetPosY(float height)			// �ߋ����W�Z�b�g
{
	m_pos.y = height;
}

DirectX::XMFLOAT3 Player::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 Player::GetCenterPos()
{
	DirectX::XMFLOAT3 m_centerpos;
	m_centerpos = m_pos;
	m_centerpos.y += m_size.y / 2.0f;

	return m_centerpos;
}

DirectX::XMFLOAT3 Player::GetSize()
{
	return m_size;
}
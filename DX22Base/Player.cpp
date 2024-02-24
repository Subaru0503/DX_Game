//----�C���N���[�h��----
#include "Player.h"
#include "Input.h"
#include "Sprite.h"
//----�I�u�W�F�N�g----
#include "Object.h"

//----�萔�E�}�N����`----
#define GRAVITY (0.15f)
#define RADIAN (180.0f / 3.14f)
#define JUMP (1.0f)

Player::Player(DirectX::XMFLOAT3 PlayerPos)	// �R���X�g���N�^
	: m_pos(PlayerPos)
	, m_oldpos(PlayerPos)
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
	, m_nPrevItem((int)Object::Kind::NONE)
	, m_nPrevScore(0)
	, m_nLastScore(0)
	, m_nPrevColor((int)Object::Color::NO)
	, m_nScore(0)
	, m_nMinusScore(0)
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
		if (IsKeyPress('W')) { 
			isMove = true; vMove = DirectX::XMVectorSubtract(vMove, vFront); }
		if (IsKeyPress('S')) { 
			isMove = true; vMove = DirectX::XMVectorAdd(vMove, vFront); }
		if (IsKeyPress('D')) { 
			isMove = true; vMove = DirectX::XMVectorSubtract(vMove, vSide); }
		if (IsKeyPress('A')) { 
			isMove = true; vMove = DirectX::XMVectorAdd(vMove, vSide); }
	}

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);	// �ړ��x�N�g���̐��K��
	vMove = DirectX::XMVectorScale(vMove, 0.23f);	// �ړ����x

	DirectX::XMStoreFloat3(&m_Move, vMove);	// XMFLOAT3�ɕϊ�

	//----�n�ʂɂ��ĂăW�����v�{�^���������ꂽ��----
	if (m_nLand && IsKeyTrigger(VK_SPACE))
	{
		m_fJump = JUMP;	// �W�����v��
		m_nLand = 0;	// ���n�t���O����
	}

	m_pos.x += m_Move.x; m_pos.y += m_Move.y + m_fJump; m_pos.z += m_Move.z;	// ���W�̍X�V


	//---�v���C���[�̉�]�p�x���v�Z
	float rotationAngle;

	// �ړ����Ă���
	if (m_Move.x != 0.0f || m_Move.z != 0.0f)
	{
		// �ړ����������ɉ�]����悤�ɒ���
		rotationAngle = atan2(m_Move.x, m_Move.z);
		//ModelRotate();	// �v���C���[���f���̉�]
		// �ړ����ޔ�
		m_OldMove = m_Move;
	}
	else
	{
		// �������Œ�
		rotationAngle = atan2(m_OldMove.x, m_OldMove.z);
	}

	//---�v���C���[�̉�]�s����X�V
	m_directRad = rotationAngle;
	m_directAngle = rotationAngle * RADIAN;  // ���W�A���p����x���ɕϊ�
	m_directRad = DirectX::XMConvertToRadians(m_directAngle);


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

void Player::ModelRotate()	// ���f���̉�]
{
	//----���݂̌����Ă�������v�Z----
	DirectX::XMFLOAT3 currentPos;
	currentPos.x = m_oldpos.x + m_OldMove.x;
	currentPos.y = m_oldpos.y + m_OldMove.y;
	currentPos.z = m_oldpos.z + m_OldMove.z;

	DirectX::XMVECTOR currentDir = DirectX::XMVectorSubtract(
		DirectX::XMLoadFloat3(&currentPos),
		DirectX::XMLoadFloat3(&m_pos)
	);
	//----���݂̕����𐳋K��----
	currentDir = DirectX::XMVector3Normalize(currentDir);


	//----�V���������Ă���������v�Z----
	DirectX::XMFLOAT3 newPos;
	newPos.x = m_pos.x + m_Move.x;
	newPos.y = m_pos.y + m_Move.y;
	newPos.z = m_pos.z + m_Move.z;

	DirectX::XMVECTOR newDir = DirectX::XMVectorSubtract(
		DirectX::XMLoadFloat3(&newPos),
		DirectX::XMLoadFloat3(&m_pos)
	);
	//----���݂̕����𐳋K��----
	newDir = DirectX::XMVector3Normalize(newDir);


	//----���f���̉�]�p�x���v�Z----
	float ModelRotateAngle;
	DirectX::XMStoreFloat(&ModelRotateAngle, DirectX::XMVector3AngleBetweenNormals(
		currentDir,			// ���݂̃v���C���[�̕����x�N�g��
		newDir				// �V�����v���C���[�̕����x�N�g�� 
	));

	//---�v���C���[�̉�]�s����X�V
	//m_directRad = ModelRotateAngle;
	m_directAngle = DirectX::XMConvertToDegrees(ModelRotateAngle);  // ���W�A���p����x���ɕϊ�
	m_directRad = DirectX::XMConvertToRadians(m_directAngle);		// ���W�A���p�ɕϊ�
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

void Player::AddScore(int kind, int color, int add)	// �X�R�A���Z
{
	// �ЂƂڂ̃A�C�e����������
	if (m_nPrevItem == (int)Object::Kind::NONE)
	{
		// �f�[�^������Ă���
		m_nPrevItem = kind;		// ���
		m_nPrevScore = add;		// �X�R�A
		m_nPrevColor = color;	// �F
		return;	// �ȍ~�̏��������Ȃ�
	}
	// ��ނ������Ă�����
	else if (m_nPrevItem == kind)
	{
		m_nScore += add;	// �X�R�A���Z
		m_nLastScore = add;	// �X�R�A�̃f�[�^������Ă���
	}
	// �F�������Ă�����
	else if (m_nPrevColor == color)
	{
		// ���Z����X�R�A���v�Z
		int ScoreAdd;
		ScoreAdd = add / 100.0f * 10;
		if (ScoreAdd >= 50)	// 50�ȏ�Ȃ�
		{
			ScoreAdd = 40;
		}
		m_nScore += ScoreAdd;		// �X�R�A���Z
		m_nLastScore = ScoreAdd;	// �X�R�A�̃f�[�^������Ă���
	}
	// �S�~���E���Ă��܂��Ă�����
	else if(m_nPrevItem == (int)Object::Kind::CAN || kind == (int)Object::Kind::CAN)
	{
		if (m_nPrevItem == kind)	// ��Ƃ��S�~��������Ō��
		{
			m_nScore -= m_nLastScore * add;	// �X�R�A���Z
			m_nMinusScore += m_nLastScore * add;	// �����ꂽ�X�R�A�̃f�[�^������Ă���
		}
		// ������S�~�Ȃ璼�O�Ɏ�������̃X�R�A������
		else if(m_nPrevItem == (int)Object::Kind::CAN)
		{
			m_nScore -= m_nPrevScore;	// �X�R�A���Z
			m_nMinusScore += m_nPrevScore;	// �����ꂽ�X�R�A�̃f�[�^������Ă���
		}
		else
		{
			m_nScore -= add;// �X�R�A���Z
		}
		if (m_nScore < 0)	// �X�R�A��0���Ⴍ�Ȃ��Ă���
		{
			m_nScore = 0;
		}
	}

	// �O�Ɏ�����A�C�e������������
	m_nPrevItem = (int)Object::Kind::NONE;
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

DirectX::XMFLOAT3 Player::GetOldPos()	// �ߋ����W�̎擾
{
	return m_oldpos;
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

int Player::GetScore()		// �X�R�A�擾
{
	return m_nScore;
}

int Player::GetMinusScore()	// �����ꂽ�X�R�A�擾
{
	return m_nMinusScore;
}

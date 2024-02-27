//----�C���N���[�h��----
#include "Tutorial.h"
#include "Input.h"
#include "Sprite.h"
//----�I�u�W�F�N�g----
#include "Object.h"

Tutorial::Tutorial(DirectX::XMFLOAT3 TutorialPos)	// �R���X�g���N�^
	: m_pos(TutorialPos)
	, m_size(2.0f, 2.0f, 2.0f)
	, m_pCamera(nullptr)
	, m_pTexture{ nullptr, nullptr }
	, m_nPrevItem((int)Object::Kind::NONE)
	, m_nResetFlg(false)
{
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Player/Player.fbx", 3.0f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "Tutorial���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/shader/VS_Model.cso")))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "Tutorial�V�F�[�_�[�ǂݍ��ݎ��s", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_pTexture[0] = new Texture();
	m_pTexture[1] = new Texture();
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Tutorial Shadow.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Smoke.png")))
	{
		MessageBox(NULL, "Tutorial Smoke.png", "Error", MB_OK);
	}
}

Tutorial::~Tutorial()
{
	delete m_pVS;
	delete m_pModel;

	for (int i = 0; i < 2; i++)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void Tutorial::Update()
{
	
}

void Tutorial::Draw()
{
	// �J�������Ȃ���Ώ����͍s��Ȃ�
	if (!m_pCamera) { return; }

	// �s��̌v�Z
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMFLOAT3 centerRotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	//���_
	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixRotationX(0.0f) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(180.0f)) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.4f, m_pos.z);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	m_pModel->Draw();

	// �e
	DirectX::XMMATRIX Shadowworld = DirectX::XMMatrixScaling(3.0f, 3.0f, 3.0f) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90.0f)) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, -0.5f, m_pos.z);

	DirectX::XMFLOAT4X4 Shadowmat;
	DirectX::XMStoreFloat4x4(&Shadowmat, DirectX::XMMatrixTranspose(Shadowworld));
	Sprite::SetWorld(Shadowmat);					// ���[���h�s��̐ݒ�
	Sprite::SetView(m_pCamera->GetViewMatrix());	// �r���[�s��̐ݒ�
	Sprite::SetProjection(m_pCamera->GetProjectionMatrix());	// �v���W�F�N�V�����s��̐ݒ�
	Sprite::SetSize(DirectX::XMFLOAT2(1.0f, 1.0f));		// �T�C�Y��ݒ�
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);					// �e�N�X�`����ݒ�
	Sprite::Draw();
}

void Tutorial::SetCamera(CameraBase * pCamera)	//�@�J�����̐ݒ�
{
	m_pCamera = pCamera;
}

void Tutorial::AddScore(int kind, int color, int add)	// �`���[�g���A������
{
	// �ЂƂڂ̃A�C�e����������
	if (m_nPrevItem == (int)Object::Kind::NONE)
	{
		// �f�[�^������Ă���
		m_nPrevItem = kind;		// ���
		// 1�ڂ̃p�l���ɂ͂߂�
		m_pUI->SetUP(DirectX::XMFLOAT3(580.0f, 80.0f, 0.0f), kind, true);
		return;	// �ȍ~�̏��������Ȃ�
	}
	

	// 2�ڂ̃p�l���ɂ͂߂�
	m_pUI->SetUP(DirectX::XMFLOAT3(680.0f, 80.0f, 0.0f), kind, true);
	if (m_nPrevItem == kind)
	{
		// ����UI�Z�b�g
		m_pUI->SetJudge(true, false, false);
	}
	else if (kind == (int)Object::Kind::CAN)
	{
		// ����UI�Z�b�g
		m_pUI->SetJudge(false, false, true);
	}
	else
	{
		// ����UI�Z�b�g
		m_pUI->SetJudge(false, true, false);
	}
	// �O�Ɏ�����A�C�e������������
	m_nPrevItem = (int)Object::Kind::NONE;
	// ���Z�b�g�t���O���グ��
	m_nResetFlg = true;
}

void Tutorial::SetItemUI(ItemUI * ItemUI)	// �A�C�e��UI�Z�b�g
{
	m_pUI = ItemUI;
}

void Tutorial::SetResetFlg(int flg)	// ���Z�b�g�t���O�Z�b�g
{
	m_nResetFlg = flg;
}

DirectX::XMFLOAT3 Tutorial::GetPos()	// ���ݒn�̎擾
{
	return m_pos;
}

DirectX::XMFLOAT3 Tutorial::GetSize()	// �v���C���[�̃T�C�Y�擾
{
	return m_size;
}

int Tutorial::GetResetFlg()	// ���Z�b�g�t���O���Q�b�g
{
	return m_nResetFlg;
}

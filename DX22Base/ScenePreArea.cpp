//=================================================================
//
//	SceneGame.cpp
//	�X�e�[�W�O�֘A
//
//=================================================================

//----�C���N���[�h��----
#include "ScenePreArea.h"
#include "Geometory.h"
#include "CameraPlayer.h"
#include "CameraDebug.h"
#include "CameraEvent.h"
#include "Collision.h"

//----�萔�E�}�N����`----
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)

CScenePreArea::CScenePreArea()
	: m_nMainCamera(CAM_PLAYER)
{
	// �X�e�[�W���W
	m_StagePos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	// �X�e�[�W�T�C�Y
	m_StageSize = DirectX::XMFLOAT3(20.0f, 2.0f, 40.0f);

	// ���f���ǂݍ���
	m_pStageModel = new Model();
	if (!m_pStageModel->Load("Assets/Model/Stage/Stage.fbx", 1.0f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�X�e�[�W���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel->SetVertexShader(m_pVS);
	m_pPlayer->SetEventFlg(false);	// �C�x���g�t���O����
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer);
	m_pCamera[CAM_DEBUG] = new CameraDebug();
	m_pCamera[CAM_EVENT] = nullptr;
	//CameraEvent *pEvent = new CameraEvent();
	m_pPlayer->SetCamera(m_pCamera[CAM_PLAYER]);
	//pEvent->SetEvent(DirectX::XMFLOAT3(0.0f, 1.0f, 6.0f), DirectX::XMFLOAT3(0.0f, 3.0f, 0.0f), 4.0f);
	//m_pCamera[CAM_EVENT] = pEvent;
	m_pField = new Field();
}

CScenePreArea::~CScenePreArea()
{
	SAFE_DELETE(m_pStageModel);
	for (int i = 0; i < MAX_CAMERA; i++)
	{
		if (m_pCamera[i])
		{
			delete m_pCamera[i];
			m_pCamera[i] = nullptr;
		}
	}
	SAFE_DELETE(m_pField);
}

void CScenePreArea::Update(float tick)
{
	if (m_nMainCamera == CAM_EVENT)
	{
		m_pCamera[CAM_EVENT]->Update();
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_nMainCamera]);
		if (!pEvent->IsEvent())
		{
			m_nMainCamera = CAM_PLAYER;
			m_pPlayer->SetCamera(m_pCamera[m_nMainCamera]);
			m_pPlayer->SetEventFlg(false);
		}
	}
	if (IsKeyTrigger('3'))
	{
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[CAM_EVENT]);
		pEvent->SetEvent(DirectX::XMFLOAT3(0.0f, 1.0f, 6.0f), DirectX::XMFLOAT3(0.0f, 3.0f, 0.0f), 4.0f);
		m_nMainCamera = CAM_EVENT;
	}

	// ���C�̍쐬
	//Collision::Ray ray;
	m_pPlayer->Update();
	//ray.start = m_pPlayer->GetPos();
	//ray.start.y += 1.0f;
	//ray.direction = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);

	//// ���ׂẴt�B�[���h�ƃ��C�̓����蔻������s
	//for (int i = 0; i < m_pField->GetDataNum(); i++)
	//{
	//	Collision::Result collision = Collision::CheckRayPlane(ray, m_pField->GetPlaneInfo(i));
	//	if (collision.hit)
	//	{
	//		for (int j = 0; j < 2; j++)
	//		{
	//			Collision::Result triCollision = Collision::CheckPointTriangle(collision.point, m_pField->GetTriangleInfo(i, j));
	//			if (triCollision.hit)
	//			{
	//				// �v���C���[��n�ʂɗ��Ă�(�������̈ړ��ʂ�0�ɂł���Ƃ���)
	//				m_pPlayer->SetPos(collision.point);
	//				m_pPlayer->ResetGravity();	// �d�̓��Z�b�g
	//				m_pPlayer->ResetJumpFlg();	// �W�����v�t���O����
	//			}
	//		}
	//	}
	//}
	
	// ���ɓ������Ă��邩
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_StagePos, m_pPlayer->GetSize(), m_StageSize))
	{
		m_pPlayer->SetPosY(m_StagePos.y + 0.5f);	// ���̏�ɖ߂�
		m_pPlayer->ResetGravity();	// �d�̓��Z�b�g
		m_pPlayer->ResetJumpFlg();	// ���n�t���O�グ
	}

	if (m_nMainCamera != CAM_PLAYER) return;
	m_pCamera[CAM_PLAYER]->Update();
	m_pUI->Update();
}

void CScenePreArea::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	DepthStencil* pDSV = GetDefaultDSV();
	SetRenderTargets(1, &pRTV, pDSV);

	DirectX::XMFLOAT4X4 mat[3];

	mat[1] = m_pCamera[m_nMainCamera]->GetViewMatrix();
	mat[2] = m_pCamera[m_nMainCamera]->GetProjectionMatrix();

	//---Geometory�p�̕ϊ��s���ݒ�
	Geometory::SetWorld(mat[0]);
	Geometory::SetView(mat[1]);
	Geometory::SetProjection(mat[2]);

	// �X�e�[�W���f���`��
	DrawStage(mat, m_pVS);

	//----�v���C���[�̕`��----
	m_pPlayer->Draw();
	//----�t�B�[���h�̕`��----
	//m_pField->Draw();

	// �C�x���g����������`�悵�Ȃ�
	if (m_nMainCamera == CAM_EVENT) return;
	//----UI�`��----
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	m_pUI->Draw();
}

// �X�e�[�W��`�悷��
void CScenePreArea::DrawStage(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;

	//---Geometory�p�̕ϊ��s����v�Z
	world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixRotationX(0.0f) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_StagePos.x, m_StagePos.y, m_StagePos.z);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	//---�ϊ��s���ݒ�
	vs->WriteBuffer(0, mat);
	m_pStageModel->SetVertexShader(vs);
	m_pStageModel->Draw();
}
//=================================================================
//
//	SceneGame.cpp
//	�X�e�[�W�O�֘A
//
//=================================================================

//----�C���N���[�h��----
#include "SceneGame.h"
#include "Geometory.h"
#include "CameraPlayer.h"
#include "CameraDebug.h"
#include "CameraEvent.h"
#include "Collision.h"

//----�萔�E�}�N����`----
#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (720)
#define FRAME (1)
#define TUTORIAL_FRAME (1)

CSceneGame::CSceneGame(CSceneMng* pSceneMng, int Stage, CSoundMng* pSoundMng)
	: CSceneStageBase(pSceneMng, Stage, DirectX::XMFLOAT3(8.0f, 0.0f, 0.0f), pSoundMng)
	, m_fFrameCnt(0.0f)
{
	m_nMainCamera = CAM_EVENT;
	// ���f���ǂݍ���
	// �n��
	m_pStageModel[0] = new Model();
	if (!m_pStageModel[0]->Load("Assets/Model/Stage/fruitsStage.fbx", 1.0f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�X�e�[�W���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// ��
	m_pStageModel[1] = new Model();
	if (!m_pStageModel[1]->Load("Assets/Model/river/river.fbx", 1.0f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�샂�f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[2] = new Model();
	if (!m_pStageModel[2]->Load("Assets/Model/river/river.fbx", 1.0f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�샂�f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// ��
	m_pStageModel[3] = new Model();
	if (!m_pStageModel[3]->Load("Assets/Model/Sky/Sky.fbx", 1.8f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�󃂃f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// �w�i
	m_pStageModel[4] = new Model();
	if (!m_pStageModel[4]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.8f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// �w�i
	m_pStageModel[5] = new Model();
	if (!m_pStageModel[5]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.3f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// �w�i
	m_pStageModel[6] = new Model();
	if (!m_pStageModel[6]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.5f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// ��
	m_pStageModel[7] = new Model();
	if (!m_pStageModel[7]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[8] = new Model();
	if (!m_pStageModel[8]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[9] = new Model();
	if (!m_pStageModel[9]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[10] = new Model();
	if (!m_pStageModel[10]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// �w�i
	m_pStageModel[11] = new Model();
	if (!m_pStageModel[11]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.8f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// �w�i
	m_pStageModel[12] = new Model();
	if (!m_pStageModel[12]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.3f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// �w�i
	m_pStageModel[13] = new Model();
	if (!m_pStageModel[13]->Load("Assets/Model/StageBackGround/BackGround.fbx", 1.5f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	// ��
	m_pStageModel[14] = new Model();
	if (!m_pStageModel[14]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[15] = new Model();
	if (!m_pStageModel[15]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[16] = new Model();
	if (!m_pStageModel[16]->Load("Assets/Model/Rock/Rock.fbx", 1.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}

	m_pStageModel[17] = new Model();
	if (!m_pStageModel[17]->Load("Assets/Model/Rock/Rock.fbx", 2.6f, Model::XFlip))
	{
		//----�G���[���b�Z�[�W�\��----
		MessageBox(NULL, "�w�i���f���ǂݍ��ݎ��s", "Error", MB_OK);
	}
	//m_pPlayer->SetEventFlg(false);	// �C�x���g�t���O����
	m_pCamera[CAM_PLAYER] = new CameraPlayer(m_pPlayer, 90.0f, 40.0f, 15.0f);
	m_pCamera[CAM_DEBUG] = new CameraDebug();
	CameraEvent *pEvent = new CameraEvent(90.0f, 40.0f, 15.0f);
	m_pPlayer->SetCamera(pEvent);
	m_pTutorial->SetCamera(pEvent);
	pEvent->SetEvent(m_pPlayer->GetPos(), DirectX::XMFLOAT3(-10.0f, 0.0f, -3.0f), 1.0f, 9.8f);
	m_pCamera[CAM_EVENT] = pEvent;
}

CSceneGame::~CSceneGame()
{
	for (int i = 0; i < MAX_STADE_MODEL; i++)
	{
		SAFE_DELETE(m_pStageModel[i]);
	}
	for (int i = 0; i < MAX_CAMERA; i++)
	{
		if (m_pCamera[i])
		{
			delete m_pCamera[i];
			m_pCamera[i] = nullptr;
		}
	}
}

void CSceneGame::Update(float tick)
{
	// �o�ߎ��Ԃ��������Ԃ𒴂��Ă�����
	if (m_pTimeUI->GetElapsedTime() >= m_pTimeUI->GetTimeLimit())
	{
		m_nTotalScore = m_pPlayer->GetScore();		// ���v�X�R�A
		m_nMinusScore = m_pPlayer->GetMinusScore();	// �[���v�X�R�A
		m_nFruitsNum = m_pPlayer->GetFruitsNum();	// ���߂��t���[�c�̐�
		m_nCanNum = m_pPlayer->GetCanNum();			// ���߂��J���̐�
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_RESULT, 1);	// ���U���g�V�[����
		return;	// �ȍ~�̃V�[�g���������Ȃ�
	}
	if (m_nMainCamera == CAM_EVENT)
	{
		m_pCamera[CAM_EVENT]->Update();
		CameraEvent* pEvent = reinterpret_cast<CameraEvent*>(m_pCamera[m_nMainCamera]);
		if (pEvent->GetMoveFlg())
		{
			m_pObjectMng->SetMoveFlg(pEvent->GetMoveFlg());
			m_pObjectMng->TutorialUpdate(tick);
			m_pCollision->Update();
			// �J�E���g�������Ă���p�l���̒��̃t���[�c�̕`��t���O�����Z�b�g����
			if (m_fFrameCnt / 60.0f > FRAME)
			{
				// �t���O���Z�b�g
				m_pTutorial->SetResetFlg(false);
				m_pUI->ResetDrawFlg();
				m_pUI->SetJudge(false, false, false);
				m_fFrameCnt = 0.0f;	// �J�E���g���Z�b�g
			}
			// �t���O�������Ă���
			if (m_pTutorial->GetResetFlg())
			{
				m_fFrameCnt++;	// �J�E���g�A�b�v
			}
		}
		if (!pEvent->IsEvent())
		{
			// �t���O���Z�b�g
			m_pTutorial->SetResetFlg(false);
			m_pUI->ResetDrawFlg();
			m_fFrameCnt = 0.0f;	// �J�E���g���Z�b�g
			m_pUI->SetJudge(false, false, false);
			m_pCollision->SetTutorialFlg(false);
			m_nMainCamera = CAM_PLAYER;
			m_pPlayer->SetCamera(m_pCamera[m_nMainCamera]);
			m_pPlayer->SetEventFlg(false);
			m_pObjectMng->SetObject();	// �����I�u�W�F�N�g���Z�b�g
		}

	}

	if (m_nMainCamera != CAM_PLAYER) return;

	// �J�E���g�������Ă���p�l���̒��̃t���[�c�̕`��t���O�����Z�b�g����
	if (m_fFrameCnt / 60.0f > FRAME)
	{
		// �t���O���Z�b�g
		m_pPlayer->SetResetFlg(false);
		m_pUI->ResetDrawFlg();
		m_fFrameCnt = 0.0f;	// �J�E���g���Z�b�g
	}

	m_pPlayer->Update();							// �v���C���[�X�V
	m_pObjectMng->Update(tick);						// �I�u�W�F�N�g�}�l�[�W���[�X�V
	m_pUI->Update();								// �A�C�e��UI�`��
	m_pScoreUI->SetScore(m_pPlayer->GetScore());	// �X�R�A�X�V

	// �G���A�ɓ����蔻��
	m_pCollisionAreaMng->Update();
	m_pCollision->Update();

	m_pCamera[CAM_PLAYER]->Update();
	//----UI----
	m_pTimeUI->Update();	// ���ԍX�V

	// �t���O�������Ă���
	if (m_pPlayer->GetResetFlg())
	{
		m_fFrameCnt++;	// �J�E���g�A�b�v
	}
}

void CSceneGame::Draw()
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

	//----�I�u�W�F�N�g�̕`��----
	m_pObjectMng->Draw(mat);

	// �C�x���g����������`�悵�Ȃ�
	if (m_nMainCamera == CAM_EVENT)
	{
		//----�`���[�g���A���`��----
		m_pTutorial->Draw();
		//----UI�`��----
		pRTV = GetDefaultRTV();
		SetRenderTargets(1, &pRTV, nullptr);
		m_pUI->Draw();		// �A�C�e���`��
		return;
	}
	//----UI�`��----
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//m_pUI->Draw();
	m_pScoreUI->Draw();	// �X�R�A�`��
	m_pUI->Draw();		// �A�C�e���`��
	m_pTimeUI->Draw();	// ���ԕ`��
}

// �X�e�[�W��`�悷��
void CSceneGame::DrawStage(DirectX::XMFLOAT4X4 *mat, VertexShader* vs)
{
	DirectX::XMMATRIX world;

	for (int i = 0; i < MAX_STADE_MODEL; i++)
	{
		switch (i)
		{
		case 0:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.6f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, -1.5f, 18.8f);
			break;
		case 2:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.6f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(0.0f) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, -1.5f, -18.8f);
			break;
		case 3:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
			break;
		case 4:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-21.5f, -2.0f, 0.0f);
			break;
		case 5:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-20.0f, -2.0f, 10.0f);
			break;
		case 6:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-21.0f, -2.0f, -9.0f);
			break;
		case 7:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-20.0f, -0.0f, 18.5f);
			break;
		case 8:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-17.0f, 0.0f, 6.0f);
			break;
		case 9:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-17.0f, 0.0f, -6.0f);
			break;
		case 10:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(-20.0f, 0.0f, -18.5f);
			break;
		case 11:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(21.5f, -2.0f, 0.0f);
			break;
		case 12:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(20.0f, -2.0f, 10.0f);
			break;
		case 13:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(0.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(21.0f, -2.0f, -9.0f);
			break;
		case 14:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(20.0f, -0.0f, 18.5f);
			break;
		case 15:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(17.0f, 0.0f, 6.0f);
			break;
		case 16:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(17.0f, 0.0f, -6.0f);
			break;
		case 17:
			//---Geometory�p�̕ϊ��s����v�Z
			world = DirectX::XMMatrixScaling(1.3f, 1.0f, 1.0f) *
				DirectX::XMMatrixRotationX(0.0f) *
				DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f)) *
				DirectX::XMMatrixRotationZ(0.0f) *
				DirectX::XMMatrixTranslation(20.0f, 0.0f, -18.5f);
			break;
		}

		world = DirectX::XMMatrixTranspose(world);
		DirectX::XMStoreFloat4x4(&mat[0], world);

		//---�ϊ��s���ݒ�
		vs->WriteBuffer(0, mat);
		m_pStageModel[i]->SetVertexShader(vs);
		m_pStageModel[i]->Draw();
	}
}
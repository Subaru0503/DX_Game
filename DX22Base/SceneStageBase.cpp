//=================================================================
//
//	SceneStageBase.cpp
//	�X�e�[�W�V�[���̋��ʕ���
//
//=================================================================

#include "SceneStageBase.h"

CSceneStageBase::CSceneStageBase()
{
	// ----- ���_�V�F�[�_�[�ǂݍ��� -----
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// ----- �f�[�^�쐬 -----
	m_pPlayer = new Player;
	m_pUI = new ItemUI;

}

CSceneStageBase::~CSceneStageBase()
{
	// ----- �f�[�^�����݂�����폜 -----
	SAFE_DELETE(m_pVS);
	SAFE_DELETE(m_pUI);
	SAFE_DELETE(m_pPlayer);

}
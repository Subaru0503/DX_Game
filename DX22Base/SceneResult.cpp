//=================================================================
//
//	SceneResult.cpp
//	�^�C�g���V�[��
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneResult.h"
#include "Input.h"

// ========== �R���X�g���N�^ ==========
CSceneResult::CSceneResult(CSceneMng* pSceneMng, int ResetNo, int StageClear)
	: m_pushEsc(false)
	, m_select(true)
	, m_pSceneMng(pSceneMng)
{

}

// ========== �f�X�g���N�^ ==========
CSceneResult::~CSceneResult()
{

}

// ========== Update�֐� ==========
void CSceneResult::Update()
{

	// =-=-= ���U���g��� =-=-=
	  // ----- �Q�[���X�^�[�g -----
	if (IsKeyTrigger(VK_RETURN)) {
		m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_TITLE, 1);
	}

}

// ========== Draw�֐� ==========
void CSceneResult::Draw()
{

}
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
	: m_pSceneMng(pSceneMng)
{
	m_pResultBackGround = new CResultBackGround();
}

// ========== �f�X�g���N�^ ==========
CSceneResult::~CSceneResult()
{
	SAFE_DELETE(m_pResultBackGround);
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
	RenderTarget* pRTV = GetDefaultRTV();
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//----�w�i�`��----
	m_pResultBackGround->Draw();
}
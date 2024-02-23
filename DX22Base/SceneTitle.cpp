//=================================================================
//
//	SceneTitle.cpp
//	�^�C�g���V�[��
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "SceneTitle.h"
#include "Input.h"

// ========== �R���X�g���N�^ ==========
CSceneTitle::CSceneTitle(CSceneMng* pSceneMng)
	: m_pSceneMng(pSceneMng)
{
	m_pTitleBackGround = new CTitleBackGround();
}

// ========== �f�X�g���N�^ ==========
CSceneTitle::~CSceneTitle()
{
	SAFE_DELETE(m_pTitleBackGround);
}

// ========== Update�֐� ==========
void CSceneTitle::Update()
{

	// =-=-= �^�C�g����� =-=-=
	{	// �I���m�F��ʂ��J���Ă��Ȃ�
	   //if (IsKeyTrigger(VK_ESCAPE))	m_pushEsc = true;		// ESC�Ŋm�F��ʊJ��

	   // ----- �Q�[���X�^�[�g -----
		if (IsKeyTrigger(VK_RETURN)) {
			//m_pSoundMng->playSound(CSoundMng::SystemSE::Tstrat);
			//animestart = true;
			m_pSceneMng->SetNextScene(CSceneMng::SceneKind::SCENE_GAME, 1);
		}
	}

}

// ========== Draw�֐� ==========
void CSceneTitle::Draw()
{
	RenderTarget* pRTV = GetDefaultRTV();
	pRTV = GetDefaultRTV();
	SetRenderTargets(1, &pRTV, nullptr);
	//----�w�i�`��----
	m_pTitleBackGround->Draw();
}
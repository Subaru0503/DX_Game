//=================================================================
//
//	CollisionAreaManager.cpp
//	�G���A����̃}�l�[�W���[
//
//=================================================================

// ========== �C���N���[�h�� ========== 
#include "CollisionAreaManager.h"
#include "SceneManager.h"

// ========== �R���X�g���N�^ ==========
CCollisionAreaMng::CCollisionAreaMng(int stage)
	: m_nNextScene(0)
{
	SetCollision(stage);	// �����蔻��Z�b�g
}

// ========== �f�X�g���N�^ ==========
CCollisionAreaMng::~CCollisionAreaMng()
{
	// ���X�g���̂��ׂẴI�u�W�F�N�g�����
	for (CCollisionArea* pArea : m_areaList) {
		if (pArea != nullptr)
		{
			delete pArea;
		}
	}
	m_areaList.clear();// �S�v�f�폜
}

// �S�ẴG���A������s��
void CCollisionAreaMng::Update()
{
	// =-=-= �e�G���A�Ƃ̓����蔻�� =-=-=
	for (CCollisionArea* pArea : m_areaList) {	// �S�G���A�𔻒�
		// ----- �΁@�v���C���[ -----
		pArea->SetPlayer(m_pPlayer);		// Player���ݒ�
		pArea->Update();					// �����蔻�菈��

		// �V�[����J�ڂ��邩
		if (pArea->GetKind() == CCollisionArea::areaKind::SceneChange
			&& pArea->GetSceneChange())
		{
			m_nNextScene = pArea->GetNextScene();
		}
	}
}

// ========== SetPlayer ==========
// ���@���F
// CPlayer* �v���C���[�̎��̃|�C���^
// �߂�l�F�Ȃ�
// �v���C���[�̎��̂�Ⴄ
// ============================== 
void CCollisionAreaMng::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

// ========== GetAreaList ==========
// ���@���F�Ȃ�
// �߂�l�Flist<CCollisionArea*>*
// �G���A���X�g�̎��̂�n��
// ============================== 
list<CCollisionArea*>* CCollisionAreaMng::GetAreaList()
{
	return &m_areaList;
}

int CCollisionAreaMng::GetNextScene()			// ���̃V�[������Ԃ�
{
	return m_nNextScene;
}

void CCollisionAreaMng::SetCollision(int stage)	// �����蔻��Z�b�g
{
	
	switch (stage)
	{
	case CSceneMng::SceneKind::SCENE_GAME:
		m_areaList.push_back(new CAreaGround(0.0f, -1.0f, 0.0f, 60.0f, 1.0f, 60.0f));	// ��
		//m_areaList.push_back(new CAreaWall(11.0f, 5.0f, 0.0f, 2.0f, 10.0f, 40.0f));		// ������
		//m_areaList.push_back(new CAreaWall(-11.0f, 5.0f, 0.0f, 2.0f, 10.0f, 40.0f));	// ������
		//m_areaList.push_back(new CAreaWall(-9.0f, 5.0f, 18.0f, 0.5f, 10.0f, 12.0f));	// �X�e�[�W1�ʘH�̕�
		//m_areaList.push_back(new CAreaWall(-3.4f, 5.0f, 18.0f, 0.5f, 10.0f, 12.0f));	// �X�e�[�W1�ʘH�̕�
		//m_areaList.push_back(new CAreaWall(0.8f, 5.0f, 11.0f, 8.6f, 10.0f, 2.0f));		// �ʘH��2������̐^�񒆂̕�
		//m_areaList.push_back(new CAreaWall(-9.5f, 5.0f, 11.0f, 0.5f, 10.0f, 2.0f));		// �ʘH��2������̒[�����̕�
		//m_areaList.push_back(new CAreaWall(-6.2f, 5.0f, -11.0f, 7.0f, 10.0f, 2.0f));	// �ʘH��1������̃X�e�[�W1���̕�
		//m_areaList.push_back(new CAreaWall(6.2f, 5.0f, -11.0f, 7.0f, 10.0f, 2.0f));		// �ʘH��1������̃X�e�[�W3���̕�
		break;
	}

}

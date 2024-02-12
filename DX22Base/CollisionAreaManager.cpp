//=================================================================
//
//	CollisionAreaManager.cpp
//	�G���A����̃}�l�[�W���[
//
//=================================================================

// ========== �C���N���[�h�� ========== 
#include "CollisionAreaManager.h"


// ========== �R���X�g���N�^ ==========
CCollisionAreaMng::CCollisionAreaMng()
{
	m_areaList.push_back(new CAreaGround(0.0f, 0.0f, 0.0f, 20.0f, 2.0f, 40.0f));	// ��
	m_areaList.push_back(new CAreaWall(11.0f, 5.0f, 0.0f, 2.0f, 10.0f, 40.0f));		// ������
	m_areaList.push_back(new CAreaWall(-11.0f, 5.0f, 0.0f, 2.0f, 10.0f, 40.0f));	// ������
	m_areaList.push_back(new CAreaWall(0.8f, 5.0f, 11.0f, 8.6f, 10.0f, 2.0f));		// �ʘH��2������̐^�񒆂̕�
	m_areaList.push_back(new CAreaWall(-6.2f, 5.0f, -11.0f, 7.0f, 10.0f, 2.0f));	// �ʘH��1������̃X�e�[�W1���̕�
	m_areaList.push_back(new CAreaWall(6.2f, 5.0f, -11.0f, 7.0f, 10.0f, 2.0f));		// �ʘH��1������̃X�e�[�W3���̕�
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

//=================================================================
//
//	CollisionArea.cpp
//	�G���A����e�֘A
//
//=================================================================

// ========== �C���N���[�h�� ==========
#include "CollisionArea.h"
#include "CollisionAreaManager.h"
#include "Collision.h"


// ========== GetPos ==========
// ���@���F�Ȃ�
// �߂�l�FXMFLOAT3
// ���W��n��
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetPos()
{
	return m_pos;
}

// ========== GetScale ==========
// ���@���F�Ȃ�
// �߂�l�FXMFLOAT3
// �T�C�Y��n��
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetScale()
{
	return m_scale;
}

CCollisionArea::areaKind CCollisionArea::GetKind()
{
	return m_areakind;
}

int CCollisionArea::GetNextScene()							// ���̃V�[������Ԃ�
{
	return m_nNextScene;
}

int CCollisionArea::GetSceneChange()	// �V�[����J�ڂ���t���O
{
	return m_nSceneChangeFlg;
}

// ========== SetPlayer ==========
// ���@���F
// CPlayer* �v���C���[�̎��̃|�C���^
// �߂�l�F�Ȃ�
// �v���C���[�̎��̂����炤
// ==============================
void CCollisionArea::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

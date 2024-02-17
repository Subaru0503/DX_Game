#include "AreaWall.h"
#include "Collision.h"

CAreaWall::CAreaWall(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = wall;
}

// ����������v���C���[�̈ʒu��␳����
void CAreaWall::Update()
{
	// �ǂɓ������Ă��邩
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_pos, m_pPlayer->GetSize(), m_scale))
	{
		DirectX::XMFLOAT3 newPlayerpos = m_pPlayer->GetOldPos();		// �ߋ����W�ɖ߂�
		newPlayerpos.y = m_pPlayer->GetPos().y;							// Y���W�͖߂��Ȃ�
		m_pPlayer->SetPos(newPlayerpos);								// �␳
	}
}
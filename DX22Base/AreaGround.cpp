#include "AreaGround.h"
#include "Collision.h"
#include "CollisionAreaManager.h"

CAreaGround::CAreaGround(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = ground;
}

// ����������v���C���[�̈ʒu��␳����
void CAreaGround::Update()
{
	// ���ɓ������Ă��邩
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_pos, m_pPlayer->GetSize(), m_scale))
	{
		m_pPlayer->SetPosY(m_pos.y + 0.5f);	// ���̏�ɖ߂�
		m_pPlayer->ResetGravity();	// �d�̓��Z�b�g
		m_pPlayer->ResetJumpFlg();	// ���n�t���O�グ
	}
}
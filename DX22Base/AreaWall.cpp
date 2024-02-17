#include "AreaWall.h"
#include "Collision.h"

CAreaWall::CAreaWall(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = wall;
}

// 当たったらプレイヤーの位置を補正する
void CAreaWall::Update()
{
	// 壁に当たっているか
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_pos, m_pPlayer->GetSize(), m_scale))
	{
		DirectX::XMFLOAT3 newPlayerpos = m_pPlayer->GetOldPos();		// 過去座標に戻す
		newPlayerpos.y = m_pPlayer->GetPos().y;							// Y座標は戻さない
		m_pPlayer->SetPos(newPlayerpos);								// 補正
	}
}
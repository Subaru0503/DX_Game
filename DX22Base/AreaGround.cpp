#include "AreaGround.h"
#include "Collision.h"
#include "CollisionAreaManager.h"

CAreaGround::CAreaGround(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = ground;
}

// 当たったらプレイヤーの位置を補正する
void CAreaGround::Update()
{
	// 床に当たっているか
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_pos, m_pPlayer->GetSize(), m_scale))
	{
		m_pPlayer->SetPosY(m_pos.y + 0.5f);	// 床の上に戻す
		m_pPlayer->ResetGravity();	// 重力リセット
		m_pPlayer->ResetJumpFlg();	// 着地フラグ上げ
	}
}
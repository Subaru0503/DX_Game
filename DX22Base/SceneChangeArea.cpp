#include "SceneChangeArea.h"
#include "Collision.h"

CSceneChangeArea::CSceneChangeArea(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int scene)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = SceneChange;	// 次のシーン情報
	m_nNextScene = scene;	// 次のシーン情報
	m_nSceneChangeFlg = 0;	// シーン遷移フラグ
}

// 当たったらプレイヤーの位置を補正する
void CSceneChangeArea::Update()
{
	// 壁に当たっているか
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_pos, m_pPlayer->GetSize(), m_scale))
	{
		m_nSceneChangeFlg = 1;
	}
}
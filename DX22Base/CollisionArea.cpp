//=================================================================
//
//	CollisionArea.cpp
//	エリア判定親関連
//
//=================================================================

// ========== インクルード部 ==========
#include "CollisionArea.h"
#include "CollisionAreaManager.h"
#include "Collision.h"


// ========== GetPos ==========
// 引　数：なし
// 戻り値：XMFLOAT3
// 座標を渡す
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetPos()
{
	return m_pos;
}

// ========== GetScale ==========
// 引　数：なし
// 戻り値：XMFLOAT3
// サイズを渡す
// ==============================
DirectX::XMFLOAT3 CCollisionArea::GetScale()
{
	return m_scale;
}

CCollisionArea::areaKind CCollisionArea::GetKind()
{
	return m_areakind;
}

int CCollisionArea::GetNextScene()							// 次のシーン情報を返す
{
	return m_nNextScene;
}

int CCollisionArea::GetSceneChange()	// シーンを遷移するフラグ
{
	return m_nSceneChangeFlg;
}

// ========== SetPlayer ==========
// 引　数：
// CPlayer* プレイヤーの実体ポインタ
// 戻り値：なし
// プレイヤーの実体をもらう
// ==============================
void CCollisionArea::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}

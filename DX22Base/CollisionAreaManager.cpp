//=================================================================
//
//	CollisionAreaManager.cpp
//	エリア判定のマネージャー
//
//=================================================================

// ========== インクルード部 ========== 
#include "CollisionAreaManager.h"


// ========== コンストラクタ ==========
CCollisionAreaMng::CCollisionAreaMng()
{
	m_areaList.push_back(new CAreaGround(0.0f, 0.0f, 0.0f, 20.0f, 2.0f, 40.0f));	// 床
	m_areaList.push_back(new CAreaWall(11.0f, 5.0f, 0.0f, 2.0f, 10.0f, 40.0f));		// 長い壁
	m_areaList.push_back(new CAreaWall(-11.0f, 5.0f, 0.0f, 2.0f, 10.0f, 40.0f));	// 長い壁
	m_areaList.push_back(new CAreaWall(0.8f, 5.0f, 11.0f, 8.6f, 10.0f, 2.0f));		// 通路が2つある方の真ん中の壁
	m_areaList.push_back(new CAreaWall(-6.2f, 5.0f, -11.0f, 7.0f, 10.0f, 2.0f));	// 通路が1つある方のステージ1側の壁
	m_areaList.push_back(new CAreaWall(6.2f, 5.0f, -11.0f, 7.0f, 10.0f, 2.0f));		// 通路が1つある方のステージ3側の壁
}

// ========== デストラクタ ==========
CCollisionAreaMng::~CCollisionAreaMng()
{
	// リスト内のすべてのオブジェクトを解放
	for (CCollisionArea* pArea : m_areaList) {
		if (pArea != nullptr)
		{
			delete pArea;
		}
	}
	m_areaList.clear();// 全要素削除
}

// 全てのエリア判定を行う
void CCollisionAreaMng::Update()
{
	// =-=-= 各エリアとの当たり判定 =-=-=
	for (CCollisionArea* pArea : m_areaList) {	// 全エリアを判定
		// ----- 対　プレイヤー -----
		pArea->SetPlayer(m_pPlayer);		// Player情報設定
		pArea->Update();					// 当たり判定処理
	}
}

// ========== SetPlayer ==========
// 引　数：
// CPlayer* プレイヤーの実体ポインタ
// 戻り値：なし
// プレイヤーの実体を貰う
// ============================== 
void CCollisionAreaMng::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}

// ========== GetAreaList ==========
// 引　数：なし
// 戻り値：list<CCollisionArea*>*
// エリアリストの実体を渡す
// ============================== 
list<CCollisionArea*>* CCollisionAreaMng::GetAreaList()
{
	return &m_areaList;
}

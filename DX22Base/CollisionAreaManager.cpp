//=================================================================
//
//	CollisionAreaManager.cpp
//	エリア判定のマネージャー
//
//=================================================================

// ========== インクルード部 ========== 
#include "CollisionAreaManager.h"
#include "SceneManager.h"

// ========== コンストラクタ ==========
CCollisionAreaMng::CCollisionAreaMng(int stage)
	: m_nNextScene(0)
{
	SetCollision(stage);	// 当たり判定セット
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

		// シーンを遷移するか
		if (pArea->GetKind() == CCollisionArea::areaKind::SceneChange
			&& pArea->GetSceneChange())
		{
			m_nNextScene = pArea->GetNextScene();
		}
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

int CCollisionAreaMng::GetNextScene()			// 次のシーン情報を返す
{
	return m_nNextScene;
}

void CCollisionAreaMng::SetCollision(int stage)	// 当たり判定セット
{
	
	switch (stage)
	{
	case CSceneMng::SceneKind::SCENE_GAME:
		m_areaList.push_back(new CAreaGround(0.0f, -1.0f, 0.0f, 60.0f, 1.0f, 60.0f));	// 床
		m_areaList.push_back(new CAreaWall(0.0f, 5.0f, -11.5f, 40.0f, 10.0f, 1.0f));	// 横壁
		m_areaList.push_back(new CAreaWall(0.0f, 5.0f, 11.5f, 40.0f, 10.0f, 1.0f));		// 横壁
		m_areaList.push_back(new CAreaWall(16.0f, 5.0f, 0.0f, 1.0f, 10.0f, 40.0f));	// 縦壁
		m_areaList.push_back(new CAreaWall(-16.0f, 5.0f, 0.0f, 1.0f, 10.0f, 40.0f));		// 縦壁
		break;
	}

}

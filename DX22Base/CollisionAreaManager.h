
//----インクルードガード----
#ifndef COLLISION_AREA_MNG
#define COLLISION_AREA_MNG

// ========== インクルード部 ==========
#include "Player.h"
#include "CollisionArea.h"
#include "AreaGround.h"
#include "AreaWall.h"

// --- リスト用 ---
#include <list>
using namespace std;

class CCollisionAreaMng
{
public:
	CCollisionAreaMng();
	~CCollisionAreaMng();
	void Update();

	void SetPlayer(Player* pPlayer);		// プレイヤー実体取得
	//void SetObjList(list<Object*>* pObj);	// オブジェクトリスト実体取得
	list<CCollisionArea*>* GetAreaList();   // AreaListのポインタ渡し

private:
	list<CCollisionArea*> m_areaList;       // 空間判定リスト
	Player* m_pPlayer;						// プレイヤーのポインタ
	//list<Object*>* m_pObjList;				// オブジェクトリストのポインタ
};
#endif

//----インクルードガード----
#ifndef COLLISION_AREA_MNG
#define COLLISION_AREA_MNG

// ========== インクルード部 ==========
#include "Player.h"
#include "CollisionArea.h"
#include "AreaGround.h"
#include "AreaWall.h"
#include "SceneChangeArea.h"

// --- リスト用 ---
#include <list>
using namespace std;

class CCollisionAreaMng
{
public:
	CCollisionAreaMng(int stage);
	~CCollisionAreaMng();
	void Update();

	void SetPlayer(Player* pPlayer);		// プレイヤー実体取得
	//void SetObjList(list<Object*>* pObj);	// オブジェクトリスト実体取得
	list<CCollisionArea*>* GetAreaList();   // AreaListのポインタ渡し
	int GetNextScene();						// 次のシーン情報を返す

private:
	void SetCollision(int stage);					// 当たり判定セット
private:
	list<CCollisionArea*> m_areaList;       // 空間判定リスト
	Player* m_pPlayer;						// プレイヤーのポインタ
	int m_nNextScene;						// 次のシーン
	//list<Object*>* m_pObjList;				// オブジェクトリストのポインタ
};
#endif
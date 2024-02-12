
//----インクルードガード----
#ifndef AREA_GROUND_H
#define AREA_GROUND_H

//----インクルード部----
#include "CollisionArea.h"
class CCollisionAreaMng;

// クラス定義
class CAreaGround :
	public CCollisionArea
{
public:
	CAreaGround(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ);
	~CAreaGround() {}
	void Update();

private:
};

#endif
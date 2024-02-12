
//----インクルードガード----
#ifndef AREA_WALL_H
#define AREA_WALL_H

//----インクルード部----
#include "CollisionArea.h"

// クラス定義
class CAreaWall :
	public CCollisionArea
{
public:
	CAreaWall(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ);
	~CAreaWall() {}
	void Update();

private:
};

#endif
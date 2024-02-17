
//----インクルードガード----
#ifndef SCENE_CHANGE_AREA_H
#define SCENE_CHANGE_AREA_H

//----インクルード部----
#include "CollisionArea.h"

// クラス定義
class CSceneChangeArea :
	public CCollisionArea
{
public:
	CSceneChangeArea(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int scene);
	~CSceneChangeArea() {}
	void Update();

private:
};

#endif
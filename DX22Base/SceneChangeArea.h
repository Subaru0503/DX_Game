
//----�C���N���[�h�K�[�h----
#ifndef SCENE_CHANGE_AREA_H
#define SCENE_CHANGE_AREA_H

//----�C���N���[�h��----
#include "CollisionArea.h"

// �N���X��`
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
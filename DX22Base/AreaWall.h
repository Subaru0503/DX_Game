
//----�C���N���[�h�K�[�h----
#ifndef AREA_WALL_H
#define AREA_WALL_H

//----�C���N���[�h��----
#include "CollisionArea.h"

// �N���X��`
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
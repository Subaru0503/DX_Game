
//----�C���N���[�h�K�[�h----
#ifndef AREA_GROUND_H
#define AREA_GROUND_H

//----�C���N���[�h��----
#include "CollisionArea.h"
class CCollisionAreaMng;

// �N���X��`
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
#ifndef __APPLE_H__
#define __APPLE_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CApple : public Object
{
public:
	CApple(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CApple();

private:
};

#endif // __APPLE_H__
#ifndef __APPLE_H__
#define __APPLE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CApple : public Object
{
public:
	CApple(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CApple();

private:
};

#endif // __APPLE_H__
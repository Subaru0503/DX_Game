#ifndef __LEMON_H__
#define __LEMON_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CLemon : public Object
{
public:
	CLemon(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CLemon();

private:
};

#endif // __LEMON_H__
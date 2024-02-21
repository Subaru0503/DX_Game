#ifndef __BANANA_H__
#define __BANANA_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CBanana : public Object
{
public:
	CBanana(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CBanana();

private:
};

#endif // __BANANA_H__
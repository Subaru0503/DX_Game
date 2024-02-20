#ifndef __WATER_MELON_H__
#define __WATER_MELON_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CWaterMelon : public Object
{
public:
	CWaterMelon(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CWaterMelon();

private:
};

#endif // __WATER_MELON_H__
//----インクルードガード----
#ifndef __MELON_H__
#define __MELON_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CMelon : public Object
{
public:
	CMelon(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CMelon();

private:
};

#endif // __MELON_H__
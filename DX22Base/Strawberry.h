//----インクルードガード----
#ifndef __STRAWBERRY_H__
#define __STRAWBERRY_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CStrawberry : public Object
{
public:
	CStrawberry(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CStrawberry();

private:
};

#endif // __STRAWBERRY_H__
#ifndef __CAN_H__
#define __CAN_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CCan : public Object
{
public:
	CCan(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CCan();

private:
};

#endif // __CAN_H__
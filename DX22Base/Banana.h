#ifndef __BANANA_H__
#define __BANANA_H__

//----�C���N���[�h��----
#include "Object.h"

//----�N���X��`----
class CBanana : public Object
{
public:
	CBanana(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CBanana();

private:
};

#endif // __BANANA_H__
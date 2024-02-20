#ifndef __TREE_H__
#define __TREE_H__

//----インクルード部----
#include "Object.h"

//----クラス定義----
class CTree : public Object
{
public:
	CTree(float posX, float posY, float posZ,
		float sizeX, float sizeY, float sizeZ);
	~CTree();

private:
};

#endif // __TREE_H__
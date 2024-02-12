// CameraDebug.h

//----インクルードガード----
#ifndef __GAMERA_DEBUG_H__
#define __GAMERA_DEBUG_H__
//----インクルード部----
#include "CameraBase.h"
#include "Input.h"

//----クラス定義----
class CameraDebug : public CameraBase
{
public:
	CameraDebug();	// コンストラクタ
	~CameraDebug();	// デストラクタ
	void Update();	// 更新
private:
	float m_radXZ, m_radY;
	float m_radius;
};

#endif	// __GAMERA_DEBUG_H__
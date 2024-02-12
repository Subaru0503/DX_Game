// CamraEvent.h

//----インクルードガード----
#ifndef __CAMERA_EVENT_H__
#define __CAMERA_EVENT_H__
//----インクルード部----
#include <DirectXMath.h>
#include "CameraBase.h"

//----クラス定義----
class CameraEvent : public CameraBase
{
public:
	CameraEvent();		// コンストラクタ
	~CameraEvent();		// デストラクタ

	void Update();		// 更新
	void SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time);

	bool IsEvent();

private:
	DirectX::XMFLOAT3 m_start;	// スタート地点
	DirectX::XMFLOAT3 m_end;	// ゴール地点
	float m_time;				// 現在時間
	float m_totalTime;			// 総時間
};

#endif	// __CAMERA_EVENT_H__
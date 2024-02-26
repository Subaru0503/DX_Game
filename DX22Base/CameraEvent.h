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
	CameraEvent(float radXZ, float radY, float radius);		// コンストラクタ
	~CameraEvent();		// デストラクタ

	void Update();		// 更新
	void SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float Movetime,
				  float totalTime);

	bool IsEvent();
	int GetMoveFlg();	// 移動フラグ

private:
	DirectX::XMFLOAT3 m_start;	// スタート地点
	DirectX::XMFLOAT3 m_end;	// ゴール地点
	DirectX::XMFLOAT3 m_endPos;	// ゴール座標
	float m_time;				// 現在時間
	float m_MoveTime;			// 移動時間
	float m_fTotalTime;			// 総時間
	int m_nMoveFlg;				// 移動完了フラグ
	float m_radXZ, m_radY;
	float m_fRadius;
};

#endif	// __CAMERA_EVENT_H__
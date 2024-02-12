// CamraBase.h

//----インクルードガード----
#ifndef __CAMERA_BASE_H__
#define __CAMERA_BASE_H__
//----インクルード部----
#include <DirectXMath.h>

//----クラス定義----
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Update() = 0;

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();

	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	// ビュー行列の設定に必要な変数
	DirectX::XMFLOAT3 m_oldPos;				// 過去座標
	float m_fovy, m_aspect, m_near, m_far;	// プロジェクション行列の設定に必要な変数
};

#endif	// __CAMERA_BASE_H__
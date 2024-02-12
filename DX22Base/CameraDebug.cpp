// CameraDebug.h
//----インクルード部----
#include "CameraDebug.h"

CameraDebug::CameraDebug()	// コンストラクタ
	: m_radXZ(0.0f)
	, m_radY(0.0f)
	, m_radius(5.0f)
{

}

CameraDebug::~CameraDebug()	// デストラクタ
{

}

void CameraDebug::Update()	// 更新
{
	const float Speed = 0.1f;
	// ←,↑,→,↓,shift,ctrlでカメラの注視点を動かす
	if (IsKeyPress(VK_UP)){	m_look.z += Speed; }
	if (IsKeyPress(VK_DOWN)){ m_look.z -= Speed; }
	if (IsKeyPress(VK_LEFT)){ m_look.x -= Speed; }
	if (IsKeyPress(VK_RIGHT)){ m_look.x += Speed; }
	if (IsKeyPress(VK_SHIFT)){ m_look.y += Speed; }
	if (IsKeyPress(VK_CONTROL)){ m_look.y -= Speed; }

	// W,A,S,D,Q,Eでカメラの位置を動かす
	//if (IsKeyPress('W')) { m_pos.z += Speed; }
	//if (IsKeyPress('S')) { m_pos.z -= Speed; }
	//if (IsKeyPress('A')) { m_pos.x -= Speed; }
	//if (IsKeyPress('D')) { m_pos.x += Speed; }
	//if (IsKeyPress('E')) { m_pos.y += Speed; }
	//if (IsKeyPress('Q')) { m_pos.y -= Speed; }

	// 回転
	if (IsKeyPress('W')) { m_radY += Speed; }
	if (IsKeyPress('S')) { m_radY -= Speed; }
	if (IsKeyPress('D')) { m_radXZ += Speed; }
	if (IsKeyPress('A')) { m_radXZ -= Speed; }

	// 距離
	if (IsKeyPress('Q')) { m_radius -= Speed; }
	if (IsKeyPress('E')) { m_radius += Speed; }

	// 角度と距離、注視点からカメラの位置を計算
	m_pos.x = cos(m_radY) * sin(m_radXZ) * m_radius + m_look.x;
	m_pos.y = sin(m_radY) * m_radius + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * m_radius + m_look.z;
}

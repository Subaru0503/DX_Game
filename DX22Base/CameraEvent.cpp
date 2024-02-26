// CameraEvent.cpp

//----インクルード部----
#include "CameraEvent.h"
#include "EasingFunction.h"

CameraEvent::CameraEvent(float radXZ, float radY, float radius)	// コンストラクタ
	: m_start(0.0f, 0.0f, 0.0f)
	, m_end(0.0f, 0.0f, 0.0f)
	, m_endPos(DirectX::XMFLOAT3(-3.0f, 8.0f, -3.0f))
	, m_time(0.0f)
	, m_MoveTime(0.0f)
	, m_radXZ(DirectX::XMConvertToRadians(radXZ))
	, m_radY(DirectX::XMConvertToRadians(radY))
	, m_nMoveFlg(false)
{
	m_look = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	const float Radius = radius;
	m_fRadius = radius;

	// 角度と距離、注視点からカメラの位置を計算
	m_pos.x = cos(m_radY) * sin(m_radXZ) * Radius + m_look.x;
	m_pos.y = sin(m_radY) * Radius + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * Radius + m_look.z;
}

CameraEvent::~CameraEvent()	// デストラクタ
{
}

void CameraEvent::Update()	// 更新
{
	if (!IsEvent()) return;
	if (!m_nMoveFlg)
	{
		m_look.x = (m_end.x - m_start.x) * EaseOutExpo(m_time / m_MoveTime) + m_start.x;
		m_look.y = (m_end.y - m_start.y) * EaseOutExpo(m_time / m_MoveTime) + m_start.y;
		m_look.z = (m_end.z - m_start.z) * EaseOutExpo(m_time / m_MoveTime) + m_start.z;
		m_pos.x -= 30.0f / 120.0f;
		m_pos.y -= 1.0f / 120.0f;
		m_pos.z -= 6.0f / 120.0f;
	}
	else
	{
		m_look = m_end;
		m_pos = m_endPos;
	}

	m_time += 1.0f / 60.0f;
	if (m_time > m_MoveTime)
	{
		m_nMoveFlg = true;
	}
}

void CameraEvent::SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float Movetime,
						  float totalTime)
{
	m_start = startPos;
	m_end = endPos;
	m_time = 0.0f;
	m_MoveTime = Movetime;
	m_fTotalTime = totalTime;
}

bool CameraEvent::IsEvent()
{
	if (m_time > m_fTotalTime)
	{
		m_pos.x = m_pos.x;
	}
	return m_time < m_fTotalTime;
}

int CameraEvent::GetMoveFlg()	// 移動フラグ
{
	return m_nMoveFlg;
}

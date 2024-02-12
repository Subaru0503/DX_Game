// CameraEvent.cpp

//----インクルード部----
#include "CameraEvent.h"

CameraEvent::CameraEvent()	// コンストラクタ
	: m_start(0.0f, 0.0f, 0.0f)
	, m_end(0.0f, 0.0f, 0.0f)
	, m_time(0.0f)
	, m_totalTime(0.0f)
{
	m_look = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

CameraEvent::~CameraEvent()	// デストラクタ
{
}

void CameraEvent::Update()	// 更新
{
	if (!IsEvent()) return;
	m_look.x = (m_end.x - m_start.x) * (m_time / m_totalTime) + m_start.x;
	m_look.y = (m_end.y - m_start.y) * (m_time / m_totalTime) + m_start.y;
	m_look.z = (m_end.z - m_start.z) * (m_time / m_totalTime) + m_start.z;

	m_pos.x += 0.0f / 120.0f;
	m_pos.y += 2.0f / 120.0f;
	m_pos.z -= 6.0f / 120.0f;

	m_time += 1.0f / 60.0f;
}

void CameraEvent::SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time)
{
	m_pos = startPos;
	m_start = startPos;
	m_end = endPos;
	m_time = 0.0f;
	m_totalTime = time;
}

bool CameraEvent::IsEvent()
{
	if (m_time > m_totalTime)
	{
		m_pos.x = m_pos.x;
	}
	return m_time < m_totalTime;
}

// CameraPlayer.h
//----インクルード部----
#include "CameraPlayer.h"
#include "Input.h"

CameraPlayer::CameraPlayer(Player* pPlayer)	// コンストラクタ
	: m_pPlayer(pPlayer)
	, m_radXZ(DirectX::XMConvertToRadians(0.0f))
	, m_radY(DirectX::XMConvertToRadians(40.0f))
	, m_oldradXZ(DirectX::XMConvertToRadians(0.0f))
	, m_oldradY(DirectX::XMConvertToRadians(40.0f))
{
	m_look = m_pPlayer->GetPos();	// 注視点をプレイヤーの位置にする
	const float Radius = 8.0f;

	// 角度と距離、注視点からカメラの位置を計算
	m_pos.x = cos(m_radY) * sin(m_radXZ) * Radius + m_look.x;
	m_pos.y = sin(m_radY) * Radius + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * Radius + m_look.z;
}

CameraPlayer::~CameraPlayer()	// デストラクタ
{

}

void CameraPlayer::Update()	// 更新
{
	// 値退避
	m_oldradY = m_radY;
	m_oldradXZ = m_radXZ;
	m_oldPos = m_pos;

	m_look = m_pPlayer->GetPos();	// 注視点をプレイヤーの位置にする
	const float Speed = 0.1f;

	// 回転
	if (IsKeyPress(VK_UP)) { m_radY += Speed; }
	if (IsKeyPress(VK_DOWN)) { m_radY -= Speed; }
	if (IsKeyPress(VK_LEFT)) { m_radXZ += Speed; }
	if (IsKeyPress(VK_RIGHT)) { m_radXZ -= Speed; }

	const float Radius = 8.0f;

	// 角度と距離、注視点からカメラの位置を計算
	m_pos.x = cos(m_radY) * sin(m_radXZ) * Radius + m_look.x;
	m_pos.y = sin(m_radY) * Radius + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * Radius + m_look.z;
	if (m_pos.y < 0.5f)
	{
		m_pos.y = m_oldPos.y;
		m_radY = m_oldradY;
	}
}

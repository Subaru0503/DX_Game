// CameraPlayer.h
//----�C���N���[�h��----
#include "CameraPlayer.h"
#include "Input.h"

CameraPlayer::CameraPlayer(Player* pPlayer)	// �R���X�g���N�^
	: m_pPlayer(pPlayer)
	, m_radXZ(DirectX::XMConvertToRadians(0.0f))
	, m_radY(DirectX::XMConvertToRadians(40.0f))
	, m_oldradXZ(DirectX::XMConvertToRadians(0.0f))
	, m_oldradY(DirectX::XMConvertToRadians(40.0f))
{
	m_look = m_pPlayer->GetPos();	// �����_���v���C���[�̈ʒu�ɂ���
	const float Radius = 8.0f;

	// �p�x�Ƌ����A�����_����J�����̈ʒu���v�Z
	m_pos.x = cos(m_radY) * sin(m_radXZ) * Radius + m_look.x;
	m_pos.y = sin(m_radY) * Radius + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * Radius + m_look.z;
}

CameraPlayer::~CameraPlayer()	// �f�X�g���N�^
{

}

void CameraPlayer::Update()	// �X�V
{
	// �l�ޔ�
	m_oldradY = m_radY;
	m_oldradXZ = m_radXZ;
	m_oldPos = m_pos;

	m_look = m_pPlayer->GetPos();	// �����_���v���C���[�̈ʒu�ɂ���
	const float Speed = 0.1f;

	// ��]
	if (IsKeyPress(VK_UP)) { m_radY += Speed; }
	if (IsKeyPress(VK_DOWN)) { m_radY -= Speed; }
	if (IsKeyPress(VK_LEFT)) { m_radXZ += Speed; }
	if (IsKeyPress(VK_RIGHT)) { m_radXZ -= Speed; }

	const float Radius = 8.0f;

	// �p�x�Ƌ����A�����_����J�����̈ʒu���v�Z
	m_pos.x = cos(m_radY) * sin(m_radXZ) * Radius + m_look.x;
	m_pos.y = sin(m_radY) * Radius + m_look.y;
	m_pos.z = cos(m_radY) * cos(m_radXZ) * Radius + m_look.z;
	if (m_pos.y < 0.5f)
	{
		m_pos.y = m_oldPos.y;
		m_radY = m_oldradY;
	}
}

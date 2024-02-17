#include "SceneChangeArea.h"
#include "Collision.h"

CSceneChangeArea::CSceneChangeArea(float posX, float posY, float posZ, float scaleX, float scaleY, float scaleZ, int scene)
{
	m_pos = DirectX::XMFLOAT3(posX, posY, posZ);
	m_scale = DirectX::XMFLOAT3(scaleX, scaleY, scaleZ);
	m_areakind = SceneChange;	// ���̃V�[�����
	m_nNextScene = scene;	// ���̃V�[�����
	m_nSceneChangeFlg = 0;	// �V�[���J�ڃt���O
}

// ����������v���C���[�̈ʒu��␳����
void CSceneChangeArea::Update()
{
	// �ǂɓ������Ă��邩
	if (Collision::AreaCheckCollision(m_pPlayer->GetCenterPos(), m_pos, m_pPlayer->GetSize(), m_scale))
	{
		m_nSceneChangeFlg = 1;
	}
}
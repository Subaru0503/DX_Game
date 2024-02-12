//----�C���N���[�h��----
#include "TrailEffect.h"
#include "Player.h"


TrailEffect::TrailEffect(Player * pPlayer)	// �R���X�g���N�^
	:m_pPlayer(pPlayer)
{
	m_oldPos = m_pPlayer->GetPos();
}

TrailEffect::~TrailEffect()	// �f�X�g���N�^
{
}

void TrailEffect::UpdateControlPoints(LineID id, ControlPoints & controlPoints)
{
	// ���t���[��, �|�����C���̕�������������������
	ControlPoints::iterator it = controlPoints.begin();
	while (it != controlPoints.end())
	{
		it->bold *= 0.85f;	// �|���Z�Ō����Ȃ����炢�̐���_�̕���傫���܂ŏ���������
		++it;
	}

	// �v���C���[���ړ����Ă��邩�m�F
	float distance = 0.0f;
	DirectX::XMFLOAT3 pos = m_pPlayer->GetPos();
	DirectX::XMVECTOR vOld = DirectX::XMLoadFloat3(&m_oldPos);
	DirectX::XMVECTOR vNow = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vDir = DirectX::XMVectorSubtract(vNow, vOld);
	DirectX::XMStoreFloat(&distance, DirectX::XMVector3Length(vDir));	// �ړ���������
	if (distance >= 0.2f/* && id == 1*/)	// �v���C���[���ړ�������
	{
		// ������炷
		for (int i = controlPoints.size() - 1; i > 0; --i)
		{
			controlPoints[i] = controlPoints[i - 1];
		}

		// �擪�ɐV�����f�[�^��ݒ�
		controlPoints[0].pos = pos;
		controlPoints[0].pos.x += id;	// �|�����C���������������炸���悤��
		controlPoints[0].pos.y += 0.01;	// �G�t�F�N�g��Y�l
		controlPoints[0].bold = 0.5f;	// �|�����C���̑傫��(��)

		if(id == 1)
			// �v���C���[�̑O�̈ʒu�̍X�V
			m_oldPos = pos;
	}
	//else if (id == 0)
	//{

	//}
}

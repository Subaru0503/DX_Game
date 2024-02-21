//----�C���N���[�h��----
#include "Collision.h"

//----�I�u�W�F�N�g�Ƃ̓����蔻��----
void Collision::Update()
{
	// =-=-= ������ =-=-=
// ----- �I�u�W�F�N�g�̃|�C���^���X�g���擾 -----
	list<Object*>*  ObjectList = m_pObjMng->GetObjectList();

	//----�����蔻��----
	for (Object* pObj : *ObjectList)	// �S�ẴI�u�W�F�N�g�Ɠ����蔻������
	{
		switch (pObj->GetKind())		// �I�u�W�F�N�g�̎�ނɉ������`�œ����蔻������
		{
			// ----- ��`�@�΁@��` -----
		case Object::NONE:	break;
		case Object::TREE:				// ��

			//---�����蔻������----
			if (InsideCheckPoint(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetSize(), pObj->GetScale()))
			{
				DirectX::XMFLOAT3 newPlayerpos = m_pPlayer->GetOldPos();		// �ߋ����W�ɖ߂�
				newPlayerpos.y = m_pPlayer->GetPos().y;							// Y���W�͖߂��Ȃ�
				m_pPlayer->SetPos(newPlayerpos);								// �␳
			}
			break;
		case Object::APPLE:
		case Object::BANANA:
		case Object::LEMON:
		case Object::WATER_MELON:
		case Object::CAN:

			//---�����蔻������----
			if (InsideCheckPoint(m_pPlayer->GetPos(),
				pObj->GetPos(), m_pPlayer->GetSize(), pObj->GetScale()))
			{
				pObj->SetDelete();	// �폜�t���O�𗧂Ă�
				pObj->SetCreate();	// �����t���O�𗧂Ă�
				m_pPlayer->AddScore(pObj->GetKind(), pObj->GetColor(), pObj->GetScore());	// �X�R�A�̏���
			}
			break;
		}
	}
}

// �ʂƃ��C�̓����蔻��
Collision::Result Collision::CheckRayPlane(Ray ray, Plane plane)
{
	Result result = {};

	// ���C�̏����l
	float rayLength;
	DirectX::XMVECTOR vRayStart = DirectX::XMLoadFloat3(&ray.start);		// ���C�̎n�_
	DirectX::XMVECTOR vRayN		= DirectX::XMLoadFloat3(&ray.direction);	// ���C�̕����x�N�g��
	DirectX::XMVECTOR vRayEnd	= DirectX::XMVectorAdd(vRayStart, vRayN);	// ���C�̏I�_
	DirectX::XMStoreFloat(&rayLength, DirectX::XMVector3Length(vRayN));		// ���C�̒���
	vRayN	= DirectX::XMVector3Normalize(vRayN);	// �����x�N�g���̐��K��

	// �ʂ̏����l
	DirectX::XMVECTOR vPlaneN = DirectX::XMLoadFloat3(&plane.normal);	// �ʂ̖@��
	DirectX::XMVECTOR vPlanePos = DirectX::XMLoadFloat3(&plane.pos);	// �ʏ�̍��W
	vPlaneN = DirectX::XMVector3Normalize(vPlaneN);	// �ʂ̖@���̐��K��

	// 1)���ʂ̍��W���烌�C�̎n�_�܂ł̋���
	float P1;
	DirectX::XMVECTOR vTOStart = DirectX::XMVectorSubtract(vRayStart, vPlanePos);
	DirectX::XMVECTOR PP1 = DirectX::XMVector3Dot(vPlaneN, vTOStart);
	DirectX::XMStoreFloat(&P1, PP1);

	// 2)���ʂ̍��W���烌�C�̏I�_�܂ł̋���
	float P2;
	DirectX::XMVECTOR vTOEnd = DirectX::XMVectorSubtract(vRayEnd, vPlanePos);
	DirectX::XMVECTOR PP2 = DirectX::XMVector3Dot(vPlaneN, vTOEnd);
	DirectX::XMStoreFloat(&P2, PP2);

	// 3)���C���ʂ��ђʂ��Ă��邩
	if (P1 > 0 && P2 < 0)
	{
		result.hit = true;	// �ЂƂ܂��������Ă���Ƃ݂Ȃ�
		float rate = P1 / (P1 + (P2 * -1));
		rayLength = rayLength * rate;
		DirectX::XMStoreFloat3(&result.point, DirectX::XMVectorAdd(
			vRayStart, DirectX::XMVectorScale(vRayN, rayLength)));
	}

	return result;
}

Collision::Result Collision::CheckPointTriangle(DirectX::XMFLOAT3 point, Triangle triangle)
{
	Result result = {false, point};

	// �ӂ̃x�N�g���Ɠ_�Ɍ������x�N�g������O�ς��v�Z
	DirectX::XMVECTOR vCross[3];	// �O�ς̌v�Z���ʊi�[��
	DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point);
	DirectX::XMVECTOR vTriStart = DirectX::XMLoadFloat3(&triangle.p[0]);
	for (int i = 0; i < 3; i++)
	{
		// �e�x�N�g���̌v�Z
		DirectX::XMVECTOR vTriEnd = DirectX::XMLoadFloat3(&triangle.p[(i + 1) % 3]);
		DirectX::XMVECTOR vTriEdge = DirectX::XMVectorSubtract(vTriEnd, vTriStart);	// �ӂ̃x�N�g��
		DirectX::XMVECTOR vToPoint = DirectX::XMVectorSubtract(vPoint, vTriStart);	// �_�Ɍ������x�N�g��

		// �e�O�ς��v�Z
		vCross[i] = DirectX::XMVector3Cross(vTriEdge, vToPoint);
		vCross[i] = DirectX::XMVector3Normalize(vCross[i]);

		// ���̃��[�v�ł́A���݂̏I�_�����̎n�_�ɂȂ�
		vTriStart = vTriEnd;
	}

	// �O�ς̃x�N�g�����m������ς��v�Z
	DirectX::XMVECTOR vDot[3] = { DirectX::XMVector3Dot(vCross[0], vCross[1]), DirectX::XMVector3Dot(vCross[1], vCross[2]),
	DirectX::XMVector3Dot(vCross[2], vCross[0]) };

	float match[3];
	for (int i = 0; i < 3; i++)
	{
		DirectX::XMStoreFloat(&match[i], vCross[i]);
	}

	if (match[0] >= 0 && match[1] >= 0 && match[2] >= 0)
	{
		result.hit = true;	// �O�p�`�����ɓ_���܂܂�Ă���
		result.point = point;
	}
	return result;
}

int Collision::InsideCheckPoint(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2)
{
	Result result = { false };

	DirectX::XMFLOAT3 harfSize1;
	DirectX::XMFLOAT3 harfSize2;
	harfSize1.x = size1.x / 2.0f; harfSize1.y = size1.y / 2.0f; harfSize1.z = size1.z / 2.0f;
	harfSize2.x = size2.x / 2.0f; harfSize2.y = size2.y / 2.0f; harfSize2.z = size2.z / 2.0f;

	if (pos2.x - harfSize2.x < pos1.x + harfSize1.x && pos2.x + harfSize2.x > pos1.x - harfSize1.x)
	{
		if (pos2.y - harfSize2.y < pos1.y + harfSize1.y && pos2.y + harfSize2.y > pos1.y - harfSize1.y)
		{
			if (pos2.z - harfSize2.z < pos1.z + harfSize1.z && pos2.z + harfSize2.z > pos1.z - harfSize1.z)
			{
				result.hit = true;
			}
		}
	}

	return result.hit;
}

int Collision::AreaCheckCollision(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2)
{
	Result result = { false };

	DirectX::XMFLOAT3 harfSize1;
	DirectX::XMFLOAT3 harfSize2;
	harfSize1.x = size1.x / 2.0f; harfSize1.y = size1.y / 2.0f; harfSize1.z = size1.z / 2.0f;
	harfSize2.x = size2.x / 2.0f; harfSize2.y = size2.y / 2.0f; harfSize2.z = size2.z / 2.0f;

	if (pos2.x - harfSize2.x < pos1.x + harfSize1.x && pos2.x + harfSize2.x > pos1.x - harfSize1.x)
	{
		if (pos2.y + harfSize2.y > pos1.y - harfSize1.y)
		{
			if (pos2.z - harfSize2.z < pos1.z + harfSize1.z && pos2.z + harfSize2.z > pos1.z - harfSize1.z)
			{
				result.hit = true;
			}
		}
	}

	return result.hit;
}

// ========== SetPlayer ==========
// ���@���FCPlayer*	�v���C���[�̎��̂̃|�C���^
// �߂�l�F�Ȃ�
// Player����ݒ肷��
// ==============================
void Collision::SetPlayer(Player* player)
{
	m_pPlayer = player;
}

// ========== SetObjectManager ==========
// ���@���FCObjectMng*	�I�u�W�F�N�gMng�̎��̂̃|�C���^
// �߂�l�F�Ȃ�
// ObjectMng����ݒ肷��
// ======================================
void Collision::SetObjectManager(CObjectMng* objMng)
{
	m_pObjMng = objMng;
}
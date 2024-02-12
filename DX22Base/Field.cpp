//----�C���N���[�h��----
#include "Field.h"
#include "Geometory.h"

Field::Field()	// �R���X�g���N�^
{
	Data initData[] = { 
		{DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),DirectX::XMFLOAT3(10.0f, 1.0f, 10.0f),DirectX::XMFLOAT3(1.0f, 1.0f, 0.0f) },
		/*{ DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),DirectX::XMFLOAT3(30.0f, 1.0f, 30.0f),DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f) },*/
	};
	for (int i = 0; i < _countof(initData); i++)
		m_data.push_back(initData[i]);
}

Field::~Field()	// �f�X�g���N�^
{

}

void Field::Draw()	// �`��
{
	for (int i = 0; i < m_data.size(); i++)
	{
		// �e�x�N�g����p��
		DirectX::XMVECTOR vStart = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&m_data[i].normal);
		vStart = DirectX::XMVector3Normalize(vStart);
		vTarget = DirectX::XMVector3Normalize(vTarget);

		// ��̃x�N�g�������]�̎����v�Z (Cross�͂��̂���)
		DirectX::XMVECTOR vCross = DirectX::XMVector3Cross(vStart, vTarget);
		vCross = DirectX::XMVector3Normalize(vCross);

		// ��̃x�N�g�������]�ɕK�v�Ȋp�x���v�Z
		float angle;
		DirectX::XMVECTOR vDot;
		vDot = DirectX::XMVector3Dot(vStart, vTarget);
		DirectX::XMStoreFloat(&angle, vDot);
		angle = acos(angle);

		// �t�B�[���h�\���ɕK�v�ȍs����v�Z
		DirectX::XMMATRIX mSize =
			DirectX::XMMatrixScaling(m_data[i].size.x, m_data[i].size.y, m_data[i].size.z);
		DirectX::XMMATRIX mPos =
			DirectX::XMMatrixTranslation(m_data[i].pos.x, m_data[i].pos.y, m_data[i].pos.z);
		DirectX::XMMATRIX mOffset =
			DirectX::XMMatrixTranslation(0.0f, -m_data[i].size.y * 0.5f, 0.0f);
		DirectX::XMMATRIX mRot = angle > 0.0f ? // �p�x��0�x����vCross�̒l���s����ɂȂ邽��
			DirectX::XMMatrixRotationAxis(vCross, angle) :
			DirectX::XMMatrixIdentity();
		//DirectX::XMMATRIX mAngle =
		//	DirectX::XMMatrixRotationX(m_data[i].angle.x) *
		//	DirectX::XMMatrixRotationY(m_data[i].angle.y) *
		//	DirectX::XMMatrixRotationZ(m_data[i].angle.z);
		DirectX::XMMATRIX mWorld = mSize * mPos * mOffset * mRot/* * mAngle*/;
		mWorld = DirectX::XMMatrixTranspose(mWorld);
		DirectX::XMFLOAT4X4 world;
		DirectX::XMStoreFloat4x4(&world, mWorld);

		// �`��
		Geometory::SetWorld(world);
		Geometory::DrawBox();	
	}
}

// �����蔻��̃f�[�^���擾
Collision::Plane Field::GetPlaneInfo(int index)
{
	Collision::Plane plane;
	plane.normal = m_data[index].normal;
	plane.pos = m_data[index].pos;

	return plane;
}

Collision::Triangle Field::GetTriangleInfo(int index, bool first)
{
	Collision::Triangle triangle;
	Data data = m_data[index];

	// �e�x�N�g����p��
	DirectX::XMVECTOR vStart = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&data.normal);
	vStart = DirectX::XMVector3Normalize(vStart);
	vTarget = DirectX::XMVector3Normalize(vTarget);

	// ��̃x�N�g�������]�̎����v�Z(2�̃x�N�g�����狁�߂��O�ς̃x�N�g���͉�]�̎��Ƃ��ė��p�ł���)
	DirectX::XMVECTOR vCross = DirectX::XMVector3Cross(vStart, vTarget);
	vCross = DirectX::XMVector3Normalize(vCross);

	// ��̃x�N�g�������]�ɕK�v�Ȋp�x���v�Z
	float angle;
	DirectX::XMVECTOR vDot;
	vDot = DirectX::XMVector3Dot(vStart, vTarget);
	DirectX::XMStoreFloat(&angle, vDot);
	angle = acos(angle);

	// �V��4���̒��_��ϊ�����s����v�Z
	DirectX::XMMATRIX mSize =
		DirectX::XMMatrixScaling(data.size.x, data.size.y, data.size.z);
	DirectX::XMMATRIX mPos =
		DirectX::XMMatrixTranslation(data.pos.x, data.pos.y, data.pos.z);
	DirectX::XMMATRIX mOffset =
		DirectX::XMMatrixTranslation(0.0f, -data.size.y * 0.5f, 0.0f);
	DirectX::XMMATRIX mRot = angle > 0.0f ? // �p�x��0�x����vCross�̒l���s����ɂȂ邽��
		DirectX::XMMatrixRotationAxis(vCross, angle) :
		DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX mWorld = mSize * mPos * mOffset * mRot;

	// ���_���s��ŕϊ�(���܂ł�GPU�Ōv�Z���Ă���������A�`��ȊO�ŕϊ���̒��_���K�v�ȏꍇ�A���O�Ōv�Z����)
	DirectX::XMFLOAT3 point[2][3] =	// �O�p�`�̒��_���
	{
		{ {-0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f} },	// �O�p�`����1
		{ {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f,-0.5f}, {-0.5f, 0.5f, -0.5f} },	// �O�p�`����2
	};
	for (int i = 0; i < 3; i++)
	{
		DirectX::XMVECTOR vPoint = DirectX::XMLoadFloat3(&point[first][i]);
		vPoint = DirectX::XMVector3TransformCoord(vPoint, mWorld);	// ���_���s��ŕϊ�
		DirectX::XMStoreFloat3(&triangle.p[i], vPoint);
	}

	return triangle;
}

int Field::GetDataNum()
{
	return m_data.size();
}

DirectX::XMFLOAT3 Field::GetFieldCenterPos(int No)	// �t�B�[���h�̍��W�̎擾
{
	DirectX::XMFLOAT3 m_centerpos;
	m_centerpos = m_data[No].pos;
	m_centerpos.y -= m_data[No].size.y / 2.0f;

	return m_centerpos;
}

DirectX::XMFLOAT3 Field::GetFieldSize(int No)	// �t�B�[���h�̃T�C�Y�擾
{
	return m_data[No].size;
}
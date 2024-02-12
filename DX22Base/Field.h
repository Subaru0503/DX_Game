//----�C���N���[�h�K�[�h----
#ifndef __FIELD_H__
#define __FIELD_H__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Collision.h"
#include <vector>

//----�N���X��`----
class Field
{
public:
	// ������
	Field();	// �R���X�g���N�^
	~Field();	// �f�X�g���N�^

	void Draw();	// �`��

	// �����蔻��̃f�[�^���擾
	Collision::Plane GetPlaneInfo(int index);

	Collision::Triangle GetTriangleInfo(int index, bool first);

	// �������ō쐬�����f�[�^���̎擾
	int GetDataNum();

	// �t�B�[���h�̍��W�̎擾
	DirectX::XMFLOAT3 GetFieldCenterPos(int No);
	// �t�B�[���h�̃T�C�Y�擾
	DirectX::XMFLOAT3 GetFieldSize(int No);
private:
	struct Data
	{
		DirectX::XMFLOAT3 pos;		// �t�B�[���h(�V��)�̈ʒu
		DirectX::XMFLOAT3 size;		// �t�B�[���h�̃T�C�Y
		DirectX::XMFLOAT3 normal;	// �t�B�[���h(�V��)�̖@��
	};
	std::vector<Data> m_data;		// �f�[�^�z��
};

#endif		// __FIELD_H__
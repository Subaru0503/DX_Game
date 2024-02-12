// CamraBase.h

//----�C���N���[�h�K�[�h----
#ifndef __CAMERA_BASE_H__
#define __CAMERA_BASE_H__
//----�C���N���[�h��----
#include <DirectXMath.h>

//----�N���X��`----
class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();
	virtual void Update() = 0;

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();

	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetLook();

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	// �r���[�s��̐ݒ�ɕK�v�ȕϐ�
	DirectX::XMFLOAT3 m_oldPos;				// �ߋ����W
	float m_fovy, m_aspect, m_near, m_far;	// �v���W�F�N�V�����s��̐ݒ�ɕK�v�ȕϐ�
};

#endif	// __CAMERA_BASE_H__
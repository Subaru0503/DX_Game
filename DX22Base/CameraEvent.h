// CamraEvent.h

//----�C���N���[�h�K�[�h----
#ifndef __CAMERA_EVENT_H__
#define __CAMERA_EVENT_H__
//----�C���N���[�h��----
#include <DirectXMath.h>
#include "CameraBase.h"

//----�N���X��`----
class CameraEvent : public CameraBase
{
public:
	CameraEvent();		// �R���X�g���N�^
	~CameraEvent();		// �f�X�g���N�^

	void Update();		// �X�V
	void SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float time);

	bool IsEvent();

private:
	DirectX::XMFLOAT3 m_start;	// �X�^�[�g�n�_
	DirectX::XMFLOAT3 m_end;	// �S�[���n�_
	float m_time;				// ���ݎ���
	float m_totalTime;			// ������
};

#endif	// __CAMERA_EVENT_H__
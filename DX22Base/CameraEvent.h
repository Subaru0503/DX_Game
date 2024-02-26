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
	CameraEvent(float radXZ, float radY, float radius);		// �R���X�g���N�^
	~CameraEvent();		// �f�X�g���N�^

	void Update();		// �X�V
	void SetEvent(DirectX::XMFLOAT3 startPos, DirectX::XMFLOAT3 endPos, float Movetime,
				  float totalTime);

	bool IsEvent();
	int GetMoveFlg();	// �ړ��t���O

private:
	DirectX::XMFLOAT3 m_start;	// �X�^�[�g�n�_
	DirectX::XMFLOAT3 m_end;	// �S�[���n�_
	DirectX::XMFLOAT3 m_endPos;	// �S�[�����W
	float m_time;				// ���ݎ���
	float m_MoveTime;			// �ړ�����
	float m_fTotalTime;			// ������
	int m_nMoveFlg;				// �ړ������t���O
	float m_radXZ, m_radY;
	float m_fRadius;
};

#endif	// __CAMERA_EVENT_H__
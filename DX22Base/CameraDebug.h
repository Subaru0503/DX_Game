// CameraDebug.h

//----�C���N���[�h�K�[�h----
#ifndef __GAMERA_DEBUG_H__
#define __GAMERA_DEBUG_H__
//----�C���N���[�h��----
#include "CameraBase.h"
#include "Input.h"

//----�N���X��`----
class CameraDebug : public CameraBase
{
public:
	CameraDebug();	// �R���X�g���N�^
	~CameraDebug();	// �f�X�g���N�^
	void Update();	// �X�V
private:
	float m_radXZ, m_radY;
	float m_radius;
};

#endif	// __GAMERA_DEBUG_H__
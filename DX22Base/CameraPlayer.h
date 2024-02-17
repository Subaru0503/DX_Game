// CameraPlayer.h

//----�C���N���[�h�K�[�h----
#ifndef __CAMERA_PLAYER_H__
#define __CAMERA_PLAYER_H__
//----�C���N���[�h��----
#include "CameraBase.h"
#include "Player.h"

//----�N���X��`----
class CameraPlayer : public CameraBase
{
public:
	CameraPlayer(Player* pPlayer, float radXZ, float radY, float radius);	// �R���X�g���N�^
	~CameraPlayer();	// �f�X�g���N�^
	void Update();	// �X�V
private:
	Player* m_pPlayer;
	float m_radXZ, m_radY;
	float m_oldradXZ, m_oldradY;	// �l�ޔ�p
	float m_fRadius;
};

#endif		// __CAMERA_PLAYER_H__

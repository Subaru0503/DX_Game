
//----�C���N���[�h�K�[�h----
#ifndef __TRAIL_EFFECT_H__
#define __TRAIL_EFFECT_H__

//----�C���N���[�h��----
#include "Polyline.h"
//#include "Player.h"

class Player;

// �v���C���[�̌��ǂ�������G�t�F�N�g
class TrailEffect : public Polyline
{
public:
	TrailEffect(Player* pPlayer);	// �R���X�g���N�^
	~TrailEffect();					// �f�X�g���N�^

protected:
	// �|�����C���̐���_���X�V
	void UpdateControlPoints(
		LineID id, ControlPoints& controlPoints) final;	// ����_�ƒ��_�܂ł̕��̏�񂪂���

private:
	Player* m_pPlayer;
	DirectX::XMFLOAT3 m_oldPos;
};

#endif		// __TRAIL_EFFECT_H__
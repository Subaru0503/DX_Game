// Move_Emitter.h

//----�C���N���[�h�K�[�h----
#ifndef __MOVE_EMITTER_H__
#define __MOVE_EMITTER_H__

//----�C���N���[�h��----
#include "Effect.h"

//----�N���X��`----
class MoveEmitter : public Emitter
{
public:
	MoveEmitter();	// �R���X�g���N�^
	~MoveEmitter();	// �f�X�g���N�^

protected:
	void Spawn(Particle* particle, const DirectX::XMFLOAT3& rootPos);
};

#endif	// __MOVE_EMITTER_H__
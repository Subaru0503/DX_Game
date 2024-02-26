// MoveEmitter.cpp

//----�C���N���[�h��----
#include "MoveEmitter.h"

MoveEmitter::MoveEmitter()	// �R���X�g���N�^
	: Emitter("Assets/Texture/Smoke.png", { 3, 0.1, 0.1f })	// {�p�[�e�B�N��������, �p�[�e�B�N�������Ԋu, �G�~�b�^�[�̐�������}
{

}

MoveEmitter::~MoveEmitter()	// �f�X�g���N�^
{

}

void MoveEmitter::Spawn(Particle * particle, const DirectX::XMFLOAT3 & rootPos)
{
	particle->pos.value = rootPos;	// �G�t�F�N�g�z�u�ʒu
	particle->pos.value.x += (rand() % 3 - 1) * 0.1f;
	particle->pos.add.y = 0.001f;	// �A�N�Z���̒l�𑝂₷��add�̒l��������
									// add�̒l�𑝂₷��value�̒l��������
	particle->size.value.x = 0.5f;
	particle->size.value.y = 0.5f;
	particle->size.add.x = 0.01f;
	particle->size.add.y = 0.01f;
	particle->alpha.add.x = -0.05f;
	particle->life = 0.9f;			// ��������
}

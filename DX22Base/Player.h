//----�C���N���[�h�K�[�h----
#ifndef __PLAYER_H__
#define __PLAYER_H__

//----�C���N���[�h��----
//#include <DirectXMath.h>
#include "Shader.h"
//#include "MeshBuffer.h"
#include "CameraBase.h"
#include "Model.h"
#include "Texture.h"
#include "MoveEmitter.h"
#include "Effect.h"
#include "TrailEffect.h"

//----�N���X��`----
class Player
{
public:
	Player(DirectX::XMFLOAT3 PlayerPos);	// �R���X�g���N�^
	~Player();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	// ���f���̉�]
	void ModelRotate();

	//�@�J�����̐ݒ�
	void SetCamera(CameraBase* pCamera);

	// �d�̓��Z�b�g
	void ResetGravity();

	// �W�����v�t���O���Z�b�g
	void ResetJumpFlg();

	// ���ݒn�̐ݒ�
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetPosY(float height);				// �����␳
	void SetEventFlg(int event);	// �C�x���g�t���O�ݒ�

	// ���ݒn�̎擾
	DirectX::XMFLOAT3 GetPos();
	// �ߋ����W�̎擾
	DirectX::XMFLOAT3 GetOldPos();
	// �v���C���[�̒��S���W�擾
	DirectX::XMFLOAT3 GetCenterPos();
	// �v���C���[�̃T�C�Y�擾
	DirectX::XMFLOAT3 GetSize();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;		// �J�����̎Q��
	DirectX::XMFLOAT3 m_pos;	// �v���C���[�̈ʒu
	DirectX::XMFLOAT3 m_oldpos;	// �v���C���[�̈ʒu
	DirectX::XMFLOAT3 m_size;	// �v���C���[�̃T�C�Y
	Texture* m_pTexture[3];

	Effect* m_pEffect;
	MoveEmitter* m_pMoveEmitter;

	// �|�����C��
	TrailEffect* m_pTrail;
	float m_fGravity;

	DirectX::XMFLOAT3 m_Move;		// �v�Z�����ړ��x�N�g���̊i�[��
	DirectX::XMFLOAT3 m_OldMove;	// �O�̈ړ����
	float m_directRad, m_directAngle;									//�v���C���[���W�A���p�A�p�x(��)

	int m_nLand;	// �W�����v�t���O
	float m_fJump;	// �W�����v��

	int m_nEventFlg;	// �C�x���g�t���O
};
#endif		// __PLAYER_H__

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
//----UI----
#include "ItemUI.h"
//----�G�t�F�N�g----
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

	// �X�R�A���Z
	void AddScore(int kind, int color, int add);
	// ���ݒn�̐ݒ�
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetPosY(float height);				// �����␳
	void SetEventFlg(int event);	// �C�x���g�t���O�ݒ�
	void SetItemUI(ItemUI* ItemUI);	// �A�C�e��UI�Z�b�g
	void SetResetFlg(int flg);		// ���Z�b�g�t���O�Z�b�g

	// ���ݒn�̎擾
	DirectX::XMFLOAT3 GetPos();
	// �ߋ����W�̎擾
	DirectX::XMFLOAT3 GetOldPos();
	// �v���C���[�̒��S���W�擾
	DirectX::XMFLOAT3 GetCenterPos();
	// �v���C���[�̃T�C�Y�擾
	DirectX::XMFLOAT3 GetSize();
	// �X�R�A�擾
	int GetScore();
	// �����ꂽ�X�R�A�擾
	int GetMinusScore();
	// ���߂��t���[�c�̐��擾
	int GetFruitsNum();
	// ���߂��J���̐��擾
	int GetCanNum();
	// ���Z�b�g�t���O���Q�b�g
	int GetResetFlg();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;		// �J�����̎Q��
	DirectX::XMFLOAT3 m_pos;	// �v���C���[�̈ʒu
	DirectX::XMFLOAT3 m_oldpos;	// �v���C���[�̈ʒu
	DirectX::XMFLOAT3 m_size;	// �v���C���[�̃T�C�Y
	Texture* m_pTexture[3];

	ItemUI* m_pUI;	// UI

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

	int m_nPrevItem;		// �ЂƂڂɎ�ɓ��ꂽ�A�C�e��
	int m_nPrevScore;		// �ЂƂڂɎ�ɓ��ꂽ�A�C�e���̃X�R�A
	int m_nLastScore;		// �Ō�Ɏ�ɓ��ꂽ�A�C�e��(�t���[�c)�̃X�R�A���
	int m_nPrevColor;		// �ЂƂڂɎ�ɓ��ꂽ�A�C�e���̐F
	int m_nScore;			// �X�R�A
	int m_nMinusScore;		// �����ꂽ�X�R�A�̍��v
	int m_nFruitsNum;		// ���߂��t���[�c�̐�
	int m_nCanNum;			// ���߂��J���̐�
	int m_nResetFlg;		// ���Z�b�g���Ăяo���t���O
};
#endif		// __PLAYER_H__

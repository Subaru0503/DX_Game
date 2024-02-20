// Object.h
#ifndef __OBJECT_H__
#define __OBJECT_H__

//=====�C���N���[�h=====
#include <DirectXMath.h>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Model.h"
#include "TrailEffect.h"
#include "Defines.h"
#include "Sprite.h"
#include "Texture.h"
/******************************
*@brief	�I�u�W�F�N�g���N���X
******************************/
class Object
{
public:
	// �I�u�W�F�N�g�̎��
	enum Kind
	{
		NONE = -1,			// ���ݒ�
		// �t���[�c
		APPLE,			// �����S
		WATER_MELON,	// �X�C�J
		MAX_FRUITS,		// �t���[�c�ő吔

		// �I�u�W�F�N�g
		TREE,			// ��
	};
private:
	// ������`�悷��ۂ̒��_���\����
	struct LineVertex
	{
		float pos[3];
		float color[4];
	};
	// �|���S����`�悷��ۂ̒��_���\����
	struct Vertex
	{
		float pos[3];
		float uv[2];
	};
public:
	// �`�揉���ʒu�A�X�P�[���A�A���O���������Ɏ��R���X�g���N�^
	Object(float posX, float posY, float posZ);
	virtual ~Object();					// �f�X�g���N�^

	void Init();				// ����������
	void Uninit();				// �I������
	virtual void Update(float tick);	// �X�V����

	void SetWorld(DirectX::XMFLOAT4X4 world);		// �萔�o�b�t�@�֑���f�[�^�Ƀ��[���h���W�ϊ��s����Z�b�g
	void SetView(DirectX::XMFLOAT4X4 view);			// �萔�o�b�t�@�֑���f�[�^�Ƀr���[���W�ϊ��s����Z�b�g
	void SetProjection(DirectX::XMFLOAT4X4 proj);	// �萔�o�b�t�@�֑���f�[�^�Ƀv���W�F�N�V�������W�ϊ��s����Z�b�g
	void SetBoxMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Box�ړ�����
	void SetSphereMove(float x = 0.0f, float y = 0.0f, float z = 0.0f);		// Sphere�ړ�����

	//void AddLine(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,
		//DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));	// �`�悷�������ǉ����鏈��
	//void DrawLines();	// ������`�悷�鏈��

	int GetKind();					// �I�u�W�F�N�g�̎�ޔԍ���Ԃ�
	DirectX::XMFLOAT3 GetScale();	// �X�P�[����Ԃ�
	bool GetDelete();				// �폜�t���O��Ԃ�
	void SetDelete();				// �폜�t���O�𗧂Ă�
	void SetCreate();				// �����t���O�𗧂Ă�
	int GetCreate();				// �����t���O��Ԃ�
	int GetScore();					// �Q�b�g�����A�C�e���̃X�R�A��Ԃ�
	DirectX::XMFLOAT3 GetAngle();	// ��]�p�x

	//void SetSound(CSoundMng* sound);

private:
	void MakeVS();			// ���_�V�F�[�_�쐬
	void MakePS();			// �s�N�Z���V�F�[�_�쐬
	void MakeLineShader();	// �����p�V�F�[�_�쐬

private:
	//void MakeLine();		// �����̒��_�o�b�t�@�쐬 
	//void MakeBox();			// Box�̒��_�o�b�t�@�쐬
	//void MakeCylinder();	// Cylinder�̒��_�o�b�t�@�쐬
	//void MakeSphere();		// Sphere�̒��_�o�b�t�@�쐬
	//const int MAX_LINE_NUM = 1000;	// shiran
	//const int CIRCLE_DETAIL = 16;	// shiran

private:
	MeshBuffer* m_pBox;			// Box�̒��_�o�b�t�@�ւ̃|�C���^
	MeshBuffer* m_pCylinder;	// Cylinder�̒��_�o�b�t�@�ւ̃|�C���^
	MeshBuffer* m_pSphere;		// Sphere�̒��_�o�b�t�@�ւ̃|�C���^
	MeshBuffer* m_pLines;		// �����̒��_�o�b�t�@�ւ̃|�C���^
	Shader* m_pVS;				// ���_�V�F�[�_�̃|�C���^
	Shader* m_pPS;				// �s�N�Z���V�F�[�_�̃|�C���^
	Shader* m_pLineShader[2];		// �����p�V�F�[�_�̃|�C���^
	DirectX::XMFLOAT4X4 m_WVP[3];	// �萔�o�b�t�@�֏������ރf�[�^�̃|�C���^
	//void* m_pLineVtx;				// shiran
	//int m_lineCnt;					// shiran

public:
	DirectX::XMFLOAT3 GetPos();				// �I�u�W�F�N�g�̍��W��Ԃ�
	DirectX::XMFLOAT3 GetOldPos();			// 1�t���[���O�̍��W��Ԃ�
	//DirectX::XMFLOAT3 GetDownVector();		// �������ւ̃x�N�g����Ԃ�
	void SetPos(DirectX::XMFLOAT3);			// ���W���Z�b�g
	void SetAngle(DirectX::XMFLOAT3 angle);	// ��]���Z�b�g
	void SetScale(DirectX::XMFLOAT3 scale);	// �T�C�Y���Z�b�g
	void SetMat(DirectX::XMFLOAT4X4*);		// �萔�o�b�t�@�|�C���^�w��p
	//void SetVelocity(float);				// �ړ����x���Z�b�g
	void SetDirection(DirectX::XMVECTOR);	// �ړ������x�N�g�����Z�b�g
	void SetPosX(float posx);				// X���W�Z�b�g
	void SetPosY(float posy);				// Y���W�Z�b�g
	void SetPosZ(float posz);				// Z���W�Z�b�g
	//void SetPlayerPosY(float posY);			// �v���C���[Y���W�Z�b�g
	//float GetMass();						// ���ʂ�Ԃ�
	//void SetModelManager(ModelManager* modelManager);	// ���f���}�l�[�W���[�������o�ɃZ�b�g
	//void SetModelData();								// �I�u�W�F�N�g�̎�ނɉ����ă��f���f�[�^���擾 

	virtual void DrawModel(DirectX::XMFLOAT4X4* mat, VertexShader* vs);	// ���f���̕`��
	Model* GetModel();						// ���f���f�[�^�̃|�C���^��Ԃ�
	bool GetDraw();
	void SetDraw(bool draw);
	//std::string GetModelKey();
	//bool IsGetMoney();
	//void SetGetScore(bool getScore);
	void SetPlayerPos(DirectX::XMFLOAT3 playerPos);

protected:
	DirectX::XMFLOAT4X4* m_mat;
	DirectX::XMFLOAT3 m_pos, m_scale, m_rotate;
	float m_PlayerPosY;					// �v���C���[�̍��WY
	DirectX::XMFLOAT3 m_oldPos;
	DirectX::XMFLOAT3 m_oldSize;		// Box�T�C�Y�ޔ�p�ϐ�
	DirectX::XMFLOAT3 m_oldScale;		// �T�C�Y�ޔ�p�ϐ�
	DirectX::XMVECTOR m_moveDirection;	// �ړ������x�N�g��
	float m_velocity;					// ���x
	float m_gravity;					// �d��
	int m_nKind;						// �I�u�W�F�N�g�̎��
	int m_nFruits;						// �t���[�c�t���O
	bool m_bDelete;						// �폜�t���O
	int m_nCreate;						// �����t���O
	int m_nScore;						// �Q�b�g�ł���X�R�A
	float m_mass;						// ����
	bool m_draw;

	Model* m_pModel;				// ���f���f�[�^�i�[�p

	float m_modelRatio;	// ���f���̊g�k��
	int m_noldTime;		// 30�b�o�������v�Z���邽�߂̒l�ޔ�
	int m_nTime;		// ���݂̎���
	//float m_time;				// �T�C���p�^�C�}�[
	//float m_weight;				// �ړ����x�����p
	//float m_radius;				// �ړ��\�͈͂̔��a
	//float m_suctionDis;			// �M�~�b�N�z�����݌��E���W�Ƃ̔䗦
	float m_fallTime;			// ��������
	DirectX::XMFLOAT3 m_playerPos;
	DirectX::XMFLOAT3 m_endPos;	// �ړ�����W

	DirectX::XMFLOAT3 m_shakePos;	// �h��A�N�V�������̍��W���
	//CSoundMng* m_pSoundMng;
	//TrailEffect* m_pTrail;	// �O�ՃG�t�F�N�g
	//bool m_bTrailSet;			// 
	int m_nMaxRatio;
	float m_fRatio;
};

#endif // __OBJECT_H__

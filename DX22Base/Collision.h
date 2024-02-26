//----�C���N���[�h�K�[�h----
#ifndef __COLLISION_H__
#define __COLLISION_H__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Player.h"
#include "ObjectManager.h"
#include "Tutorial.h"

//----�N���X��`----
class Collision
{
public:
	//---- �����蔻����s���e��`��----
	// ��
	struct Plane
	{
		DirectX::XMFLOAT3 normal;	// �ʂ̖@��
		DirectX::XMFLOAT3 pos;		// �ʏ�̍��W
	};

	// ���C
	struct Ray
	{
		DirectX::XMFLOAT3 start;		// ���C�̊J�n�_
		DirectX::XMFLOAT3 direction;	// ���C�̕���
	};

	//----�����蔻��̌���----
	struct Result
	{
		bool hit;					// �����������ǂ���
		DirectX::XMFLOAT3 point;	// �q�b�g�ʒu
	};

	//----�����蔻����s���e��`��----
	struct Triangle
	{
		DirectX::XMFLOAT3 p[3];	// �O�p�`�̒��_���W
	};
public:
	void Update();	// �I�u�W�F�N�g�Ƃ̓����蔻��

	// �ʂƃ��C�̓����蔻��
	static Result CheckRayPlane(Ray ray, Plane plane);

	// �_�̎O�p�`�̓��O����
	static Result CheckPointTriangle(DirectX::XMFLOAT3 point, Triangle triangle);

	// �����ɓ����蔻��
	static int InsideCheckPoint(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2);

	static int AreaCheckCollision(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, DirectX::XMFLOAT3 size1, DirectX::XMFLOAT3 size2);

	void SetPlayer(Player* player);			// Player���ݒ�
	void SetObjectManager(CObjectMng* objMng);	// ObjectMng�ݒ�
	void SetTutorial(Tutorial* tutorial);	// Tutorial���ݒ�
	void SetTutorialFlg(int flg);			// �`���[�g���A���t���O�Z�b�g

private:
	Player* m_pPlayer;							// Player�|�C���^�i�[�p
	CObjectMng* m_pObjMng;						// ObjectMng�|�C���^�i�[�p
	Tutorial* m_pTutorial;						// Tutorial�|�C���^�i�[�p
	int m_nTutorialFlg;							// �`���[�g���A���t���O
};
#endif			// __COLLISION_H__
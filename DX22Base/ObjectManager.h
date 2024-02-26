//----�C���N���[�h�K�[�h----
#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__

//----�C���N���[�h��----
#include <DirectXMath.h>
#include "Defines.h"
//#include "SoundManager.h"
#include "Model.h"
//#include "ModelManager.h"		// ���f���}�l�[�W���[
// ----- �X�e�[�W -----
#include "Tree.h"				// ��
// �t���[�c
#include "Apple.h"				// �����S
#include "Strawberry.h"			// �C�`�S
#include "Banana.h"				// �o�i�i
#include "Lemon.h"				// ������
#include "WaterMelon.h"			// �X�C�J
#include "Melon.h"				// ������
#include "Can.h"				// �󂫊�

// �I�u�W�F�N�g���X�g�p
#include <list>
using namespace std;

// �O���錾
class Player;

//----�N���X��`----
class CObjectMng
{
public:
	CObjectMng();							// �R���X�g���N�^	
	~CObjectMng();							// �f�X�g���N�^

	void TutorialUpdate(float tick);		// �`���[�g���A���X�V
	void Update(float tick);				// �X�V
	void Draw(DirectX::XMFLOAT4X4 *mat);	// �`��

	list<Object*>* GetObjectList();			// �I�u�W�F�N�g���X�g�̃|�C���^��n��

	void SetTutorialFruits();				// �`���[�g���A���p�̃I�u�W�F�N�g���Z�b�g
	void SetObject();						// �����I�u�W�F�N�g�Z�b�g
	void FruitsObjectSet(DirectX::XMFLOAT3 pos);		// �V�����t���[�c�I�u�W�F�N�g����
	void SetTime(int time);					// ���ԃZ�b�g
	void SetPlayer(Player* pPlayer);
	void SetMoveFlg(int flg);				// �ړ������t���O�Z�b�g
private:
	list<Object*> m_ObjectList;				// �I�u�W�F�N�g���X�g

	VertexShader* m_pVS;

	Model* m_pModel;
	Player* m_pPlayer;
	int m_nTime;							// ��������
	int m_nCnt;								// �t���[�c�J�E���g
	int m_nMoveFlg;							// �ړ������t���O
};

#endif
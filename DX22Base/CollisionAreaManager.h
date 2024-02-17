
//----�C���N���[�h�K�[�h----
#ifndef COLLISION_AREA_MNG
#define COLLISION_AREA_MNG

// ========== �C���N���[�h�� ==========
#include "Player.h"
#include "CollisionArea.h"
#include "AreaGround.h"
#include "AreaWall.h"
#include "SceneChangeArea.h"

// --- ���X�g�p ---
#include <list>
using namespace std;

class CCollisionAreaMng
{
public:
	CCollisionAreaMng(int stage);
	~CCollisionAreaMng();
	void Update();

	void SetPlayer(Player* pPlayer);		// �v���C���[���̎擾
	//void SetObjList(list<Object*>* pObj);	// �I�u�W�F�N�g���X�g���̎擾
	list<CCollisionArea*>* GetAreaList();   // AreaList�̃|�C���^�n��
	int GetNextScene();						// ���̃V�[������Ԃ�

private:
	void SetCollision(int stage);					// �����蔻��Z�b�g
private:
	list<CCollisionArea*> m_areaList;       // ��Ԕ��胊�X�g
	Player* m_pPlayer;						// �v���C���[�̃|�C���^
	int m_nNextScene;						// ���̃V�[��
	//list<Object*>* m_pObjList;				// �I�u�W�F�N�g���X�g�̃|�C���^
};
#endif
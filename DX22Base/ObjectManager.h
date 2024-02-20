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
#include "Apple.h"
#include "WaterMelon.h"

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

	void Update(float tick);				// �X�V
	void Draw(DirectX::XMFLOAT4X4 *mat);	// �`��

	list<Object*>* GetObjectList();			// �I�u�W�F�N�g���X�g�̃|�C���^��n��

	//void SetTotalObjNum(int totalObjNum);	// �z�����߂�I�u�W�F�N�g�̑�����ݒ�
	//void ModelSetting();					// �I�u�W�F�N�g�Ƀ��f�����Z�b�g����
	//void SetSuction(Suction* suction);
	//void SetSound(CSoundMng* sound);
	void SetObject();						// �����I�u�W�F�N�g�Z�b�g
	void FruitsObjectSet(float posX, float posZ);		// �t���[�c�I�u�W�F�N�g�Z�b�g
	void SetTime(int time);					// ���ԃZ�b�g
	void SetPlayer(Player* pPlayer);
private:
	list<Object*> m_ObjectList;				// �I�u�W�F�N�g���X�g

	//CSoundMng* m_pSoundMng;
	//ModelManager* m_pModelManager;			// ���f���}�l�[�W���[
	VertexShader* m_pVS;

	Model* m_pModel;
	Player* m_pPlayer;
	int m_nTime;							// ��������
};

#endif
//----�C���N���[�h��----
#include "ObjectManager.h"
#include "Geometory.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

//----�萔�E�}�N����`----
#define MAX_TREE (4)	// �؍ő吔
#define FALL_FRUITS_POSY (7.0f)	// �t���[�c�����ʒu
using namespace std;

CObjectMng::CObjectMng()	// �R���X�g���N�^
	//: m_pModelManager(nullptr)
{
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))	// �V�F�[�_�ǂݍ���
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	SetObject();	// �I�u�W�F�N�g�̃Z�b�g
	// �I�u�W�F�N�g�Ƀ��f�������蓖�Ă�p
	//m_pModelManager = new ModelManager();
}

CObjectMng::~CObjectMng()	// �f�X�g���N�^
{
	// ���X�g���̂��ׂẴI�u�W�F�N�g�����
	for (Object* pObj : m_ObjectList) {
		if (pObj != nullptr)
		{
			//pObj->Uninit();
			delete pObj;
		}
	}
	m_ObjectList.clear();// �S�v�f�폜

	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}

	//if (m_pModelManager)
	//{
	//	delete m_pModelManager;
	//	m_pModelManager = nullptr;
	//}
}

void CObjectMng::Update(float tick)	// �X�V
{
	//--�z�����܂��or�j�󂳂��I�u�W�F�N�g�̏���
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end();)
	{
		Object* pObj = *it;			// �I�u�W�F�N�g�̊֐����Ăяo����悤�ɕϊ�
		(*it)->SetPlayerPos(m_pPlayer->GetPos());	// �v���C���[�̍��W�����I�u�W�F�N�g�ɐݒ�

		if (pObj->GetCreate())	// �����t���O�������Ă���
		{
			FruitsObjectSet(pObj->GetPos());	// �V�����t���[�c���Z�b�g����
		}
		if (pObj->GetDelete()) {	// �폜�t���O�������Ă�����
			delete pObj;					// �����������
			it = m_ObjectList.erase(it);	// ���X�g����폜���ăC�e���[�^���X�V�����̗v�f��
		}
		else {			// �폜���Ȃ��̂�
			++it;		// �C�e���[�^��i�߂�
		}
	}
	int i = 0;
	// �I�u�W�F�N�g�X�V����
	for (Object* pObj : m_ObjectList)
	{
		pObj->Update(tick);
		i++;
	}

}

void CObjectMng::Draw(DirectX::XMFLOAT4X4 *mat)		// �`��
{
	// ���X�g���̃I�u�W�F�N�g�̕`�揈��
	for (Object* pObj : m_ObjectList)
	{
		bool draw = pObj->GetDraw();
		if (pObj->GetModel() != nullptr)
		{
			if (draw)
				pObj->DrawModel(mat, m_pVS);
		}
	}
}

list<Object*>* CObjectMng::GetObjectList()
{
	return &m_ObjectList;
}

//void CObjectMng::SetTotalObjNum(int totalObjNum)
//{
//	m_totalObjNum = totalObjNum;
//}

//void CObjectMng::ModelSetting()
//{
//	for (Object* pObj : m_ObjectList) {
//		pObj->SetModelManager(m_pModelManager);	// ���f���}�l�[�W���[���I�u�W�F�N�g�ɃZ�b�g
//		pObj->SetModelData();					// �I�u�W�F�N�g�Ƀ��f�����Z�b�g
//	}
//}

//void CObjectMng::SetSound(CSoundMng * sound)
//{
//	m_pSoundMng = sound;
//}

void CObjectMng::SetObject()			// �����I�u�W�F�N�g�Z�b�g
{
	DirectX::XMFLOAT3 Deltapos = DirectX::XMFLOAT3(7.0f, 0.0f, -1.0f);		// ���W�ω���
	DirectX::XMFLOAT3 TreePos = DirectX::XMFLOAT3(-10.0f, 6.0f, -5.0f);		// �؍��W
	DirectX::XMFLOAT3 FruitsPos = DirectX::XMFLOAT3(-10.0f, FALL_FRUITS_POSY, -3.0f);	// �t���[�c���W
	DirectX::XMFLOAT3 FruitsSize = DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f);		// �t���[�c�T�C�Y
	// ��
	for (int i = 0; i < MAX_TREE; i++)
	{
		// �ؐ���
		m_ObjectList.push_back(new CTree(TreePos.x, TreePos.y, TreePos.z, 1.0f, 21.0f, 1.0f));
		// ���W�ω�
		TreePos.x += Deltapos.x;
		TreePos.z *= Deltapos.z;
	}

	// ����������
	srand((unsigned int)time(NULL));
	int	random;	// �����i�[�p
	//----�؂̐����ŏ��̃t���[�c��p�ӂ���----
	for (int i = 0; i < MAX_TREE; i++)
	{
		random = (rand() + (int)(FruitsPos.x + FruitsPos.y + FruitsPos.z)) % ((int)Object::Kind::MAX_FALL);

		// ����
		switch (random)
		{
		case Object::Kind::APPLE:	// �����S
			m_ObjectList.push_back(new CApple(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::STRAWBERRY:	// �C�`�S
			m_ObjectList.push_back(new CStrawberry(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::BANANA:	// �o�i�i
			m_ObjectList.push_back(new CBanana(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::LEMON:	// ������
			m_ObjectList.push_back(new CLemon(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::WATER_MELON:		// �X�C�J
			m_ObjectList.push_back(new CWaterMelon(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::MELON:		// ������
			m_ObjectList.push_back(new CMelon(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		default:
			i--;
			continue;
			break;
		}

		// ���W�ω�
		FruitsPos.x += Deltapos.x;
		//FruitsPos.y += Deltapos.y;
		FruitsPos.z *= Deltapos.z;
	}

}

void CObjectMng::FruitsObjectSet(DirectX::XMFLOAT3 pos)		// �V�����t���[�c�I�u�W�F�N�g����
{
	DirectX::XMFLOAT3 FruitsSize = DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f);		// �t���[�c�T�C�Y

	// ����������
	srand((unsigned int)time(NULL));
	int	random;	// �����i�[�p
	random = (rand() + (int)(pos.x + 6.0f + pos.z)) % ((int)Object::Kind::MAX_FALL);

	// ����
	switch (random)
	{
	case Object::Kind::APPLE:	// �����S
		m_ObjectList.push_back(new CApple(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::STRAWBERRY:	// �C�`�S
		m_ObjectList.push_back(new CStrawberry(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::BANANA:	// �o�i�i
		m_ObjectList.push_back(new CBanana(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::LEMON:	// ������
		m_ObjectList.push_back(new CLemon(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::WATER_MELON:		// �X�C�J
		m_ObjectList.push_back(new CWaterMelon(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::MELON:		// ������
		m_ObjectList.push_back(new CMelon(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::CAN:		// �󂫊�
		m_ObjectList.push_back(new CCan(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	}
}

void CObjectMng::SetTime(int time)
{
	m_nTime = time;
}

void CObjectMng::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}
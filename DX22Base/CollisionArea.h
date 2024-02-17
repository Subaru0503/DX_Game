
//----�C���N���[�h�K�[�h----
#ifndef COLLISION_AREA_H
#define COLLISION_AREA_H

// ========== �C���N���[�h�� ==========
#include "Player.h"
#include <DirectXMath.h>
#include "Geometory.h"
class CCollisionAreaMng;
#include <list>

// ========== �N���X ==========
class CCollisionArea
{
public:// �p�����[�^
	enum areaKind {
		ground = 1,
		wall,
		SceneChange,
	};

public:// �֐�
	CCollisionArea() {}
	virtual ~CCollisionArea() {}

	virtual void Update() = 0;
	DirectX::XMFLOAT3 GetPos();					// ���W�n��
	DirectX::XMFLOAT3 GetScale();				// �T�C�Y�n��
	areaKind GetKind();							// ����̎�ޓn��
	int GetNextScene();							// ���̃V�[������Ԃ�
	int GetSceneChange();						// �V�[����J�ڂ���t���O
	void SetPlayer(Player* pPlayer);			// �v���C���[�̍��W�E�T�C�Y���擾
	//void SetObj(Object* pObj);					// �I�u�W�F�N�g���X�g�擾

protected:
	int m_stage;								// ���X�e�[�W��
	DirectX::XMFLOAT3 m_pos, m_scale;			// ���W�E�T�C�Y
	areaKind m_areakind;						// ����̎��
	Player* m_pPlayer;							// �v���C���[���󂯎��p
	//Object* m_pObject;							// �I�u�W�F�N�g�󂯎��p
	int m_height;								// �V�ʂ̍���(�`�i��)
	int m_lowHt;								// ���(�ݒu�ʒu)�̍���(�`�i��)
	int m_nNextScene;							// ���̃V�[�����
	int m_nSceneChangeFlg;						// �V�[���J�ڃt���O
};

#endif // !COLLISION_AREA_H
//=================================================================
//
//	SceneStageBase.h
//	�X�e�[�W�V�[���̋��ʕ���
//
//=================================================================

#ifndef __SCENE_STAGE_BASE_H__
#define __SCENE_STAGE_BASE_H__

// ========== �C���N���[�h�� ==========
// ----- �V�X�e�� -----
#include "SceneManager.h"
#include "Model.h"
#include "Shader.h"
// ----- �I�u�W�F�N�g -----
#include "Player.h"
#include "Collision.h"
#include "CollisionAreaManager.h"
// ----- UI -----
#include "ItemUI.h"

using namespace std;


// ========== �N���X ==========
class CSceneStageBase
{
public:
	CSceneStageBase();
	virtual ~CSceneStageBase();
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

	//virtual void ItemCheck(int* item);			// �A�C�e���g�p�̊m�F�֐�

protected:
	virtual void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs) = 0;	// ���`��

	// �e�Q�[���f�[�^�p
	VertexShader* m_pVS;
	Player* m_pPlayer;
	CCollisionAreaMng* m_pCollisionAreaMng;
	ItemUI* m_pUI;
	//CObjectMng* m_pObjectMng;

	Model* m_pStageModel;		// �X�e�[�W���f��

};

#endif // !__SCENE_STAGE_BASE_H__

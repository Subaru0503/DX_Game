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
#include "ItemUI.h"
#include "Collision.h"

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
	ItemUI* m_pUI;
	//CObjectMng* m_pObjectMng;

	DirectX::XMFLOAT3 m_StagePos;	// �X�e�[�W���W
	DirectX::XMFLOAT3 m_StageSize;	// �X�e�[�W�T�C�Y
	Model* m_pStageModel;		// �X�e�[�W���f��

};

#endif // !__SCENE_STAGE_BASE_H__

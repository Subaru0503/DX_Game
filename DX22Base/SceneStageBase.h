//=================================================================
//
//	SceneStageBase.h
//	ステージシーンの共通部分
//
//=================================================================

#ifndef __SCENE_STAGE_BASE_H__
#define __SCENE_STAGE_BASE_H__

// ========== インクルード部 ==========
// ----- システム -----
#include "SceneManager.h"
#include "CameraBase.h"
#include "Model.h"
#include "Shader.h"
// ----- オブジェクト -----
#include "ObjectManager.h"
//#include "Object.h"
#include "Player.h"
#include "Collision.h"
#include "CollisionAreaManager.h"
// ----- UI -----
#include "ItemUI.h"
#include "ScoreUI.h"
#include "TimeUI.h"

using namespace std;

//----定数・マクロ定義----
#define MAX_STADE_MODEL (3)

// ========== クラス ==========
class CSceneStageBase
{
public:
	enum CameraKind
	{
		CAM_PLAYER,
		CAM_DEBUG,
		CAM_EVENT,
		MAX_CAMERA // カメラ最大数
	};
public:
	CSceneStageBase(CSceneMng* pSceneMng, int Stage, DirectX::XMFLOAT3 PlayerPos);
	virtual ~CSceneStageBase();
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

	//virtual void ItemCheck(int* item);			// アイテム使用の確認関数

protected:
	virtual void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs) = 0;	// 陸描画

	// 各ゲームデータ用
	VertexShader* m_pVS;
	CameraBase* m_pCamera[MAX_CAMERA];
	Player* m_pPlayer;
	CObjectMng* m_pObjectMng;
	CSceneMng* m_pSceneMng;
	CCollisionAreaMng* m_pCollisionAreaMng;
	Collision* m_pCollision;
	ItemUI* m_pUI;
	CScoreUI* m_pScoreUI;
	CTimeUI* m_pTimeUI;

	Model* m_pStageModel[MAX_STADE_MODEL];		// ステージモデル

	int m_nMainCamera;	// 現在のカメラ

};

#endif // !__SCENE_STAGE_BASE_H__

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
#include "Model.h"
#include "Shader.h"
// ----- オブジェクト -----
#include "Player.h"
#include "ItemUI.h"
#include "Collision.h"

using namespace std;


// ========== クラス ==========
class CSceneStageBase
{
public:
	CSceneStageBase();
	virtual ~CSceneStageBase();
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

	//virtual void ItemCheck(int* item);			// アイテム使用の確認関数

protected:
	virtual void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs) = 0;	// 陸描画

	// 各ゲームデータ用
	VertexShader* m_pVS;
	Player* m_pPlayer;
	ItemUI* m_pUI;
	//CObjectMng* m_pObjectMng;

	DirectX::XMFLOAT3 m_StagePos;	// ステージ座標
	DirectX::XMFLOAT3 m_StageSize;	// ステージサイズ
	Model* m_pStageModel;		// ステージモデル

};

#endif // !__SCENE_STAGE_BASE_H__

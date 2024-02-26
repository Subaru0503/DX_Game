
//----インクルードガード----
#ifndef __CSCENE_GAME_H__
#define __CSCENE_GAME_H__

//----インクルード部----
#include "SceneStageBase.h"

class CSceneGame : public CSceneStageBase
{
public:
	CSceneGame(CSceneMng* pSceneMng, int Stage);
	~CSceneGame();
	void Update(float tick);
	void Draw();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 陸描画

private:
	float m_fFrameCnt;	// フレームカウント
};

#endif // __CSCENE_GAME_H__
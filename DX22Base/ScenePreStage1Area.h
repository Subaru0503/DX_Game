
//----インクルードガード----
#ifndef __CSCENE_PRE_STAGE1_AREA_H__
#define __CSCENE_PRE_STAGE1_AREA_H__

//----インクルード部----
#include "SceneStageBase.h"

class CScenePreStage1Area : public CSceneStageBase
{

public:
	CScenePreStage1Area(CSceneMng* pSceneMng, int Stage);
	~CScenePreStage1Area();
	void Update(float tick);
	void Draw();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 陸描画

private:

};

#endif // __CSCENE_PRE_STAGE1_AREA_H__
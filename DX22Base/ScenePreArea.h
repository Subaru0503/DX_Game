
//----�C���N���[�h�K�[�h----
#ifndef __CSCENE_PRE_AREA_H__
#define __CSCENE_PRE_AREA_H__

//----�C���N���[�h��----
#include "SceneStageBase.h"
#include "Field.h"

class CScenePreArea : public CSceneStageBase
{
public:
	CScenePreArea(CSceneMng* pSceneMng, int Stage);
	~CScenePreArea();
	void Update(float tick);
	void Draw();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// ���`��

private:
	//CameraEvent* pEvent;
	Field *m_pField;
};

#endif // __CSCENE_PRE_AREA_H__
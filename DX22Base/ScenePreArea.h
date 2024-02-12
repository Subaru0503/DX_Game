#ifndef __CSCENE_PRE_AREA_H__
#define __CSCENE_PRE_AREA_H__

//----インクルード部----
#include "CameraBase.h"
#include "SceneStageBase.h"
#include "Field.h"

class CScenePreArea : public CSceneStageBase
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
	CScenePreArea();
	~CScenePreArea();
	void Update(float tick);
	void Draw();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// 陸描画

private:
	CameraBase* m_pCamera[MAX_CAMERA];
	//CameraEvent* pEvent;
	Field *m_pField;
	int m_nMainCamera;	// 現在のカメラ
};

#endif // __CSCENE_PRE_AREA_H__
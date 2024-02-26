
//----�C���N���[�h�K�[�h----
#ifndef __CSCENE_GAME_H__
#define __CSCENE_GAME_H__

//----�C���N���[�h��----
#include "SceneStageBase.h"

class CSceneGame : public CSceneStageBase
{
public:
	CSceneGame(CSceneMng* pSceneMng, int Stage);
	~CSceneGame();
	void Update(float tick);
	void Draw();

private:
	void DrawStage(DirectX::XMFLOAT4X4 * mat, VertexShader * vs);	// ���`��

private:
	float m_fFrameCnt;	// �t���[���J�E���g
};

#endif // __CSCENE_GAME_H__
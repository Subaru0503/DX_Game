//=================================================================
//
//	sceneManager.cpp
//	シーン管理
//
//=================================================================

// ========== インクルード部 ==========
#include "SceneManager.h"
#include "SceneTitle.h"
#include "ScenePreArea.h"
//#include "SceneStage2.h"
#include "SceneResult.h"

// ========== 定数・マクロ定義 ==========

// ========== コンストラクタ ==========
CSceneMng::CSceneMng()
	: m_scene(SCENE_TITLE)
	, m_nextScene(SCENE_TITLE)
	, m_GameEnd(false)
	, m_nResetNo(0)
	, m_nClear(0)
{
	m_pTitle = new CSceneTitle(this);
	//m_pStage2 = new SceneStage2(this, 3);
}

// ========== デストラクタ ==========
CSceneMng::~CSceneMng()
{
	// =-=-= シーンに応じたデータ削除 =-=-=
	// 存在していれば削除
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_STAGE1:	SAFE_DELETE(m_pScenePreArea);  break;
	//case SCENE_STAGE2:	SAFE_DELETE(m_pStage2); break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	SAFE_DELETE(m_pResult); break;
	default: break;
	}
}

// ========== 更新 ==========
void CSceneMng::Update(float tick)
{
	//if (!m_pFade->IsPlay()) {	//いろんな処理はフェード処理が終わってから。
	//	if (m_scene != m_nextScene)	SceneSwap();	// シーンチェンジが行われていれば遷移
	//}
	//else {
	//	// フェードに合わせてBGMのボリューム調整(必要になったらここに実装)
	//}

	if (m_scene != m_nextScene)
	{
		SceneSwap();
	}

	// =-=-= シーンに応じた更新 =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Update();			break;
	case SCENE_STAGE1:	m_pScenePreArea->Update(tick); 	break;
	//case SCENE_STAGE2:	m_pStage2->Update(tick);	break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	m_pResult->Update();	break;
	default: break;
	}

	// ----- 各種更新 -----
	//m_pFade->Update();
}

// ========== 描画 ==========
void CSceneMng::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:	m_pTitle->Draw();	break;
	case SCENE_STAGE1:	m_pScenePreArea->Draw();	break;
	//case SCENE_STAGE2:	m_pStage2->Draw(); break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	m_pResult->Draw();	break;
	default: break;
	}
	//m_pFade->Draw();
}

// ========== シーン切り替え設定 ==========
// 引　数：SceneKind 遷移先シーン
// 戻り値：なし
// 指定のシーンを遷移先に設定。
// ======================================
void CSceneMng::SetNextScene(SceneKind scene, int Deth)
{
	//// フェード中は次のシーンを予約しない
	//if (m_pFade->IsPlay())
	//{
	//	return;
	//}

	m_nextScene = scene;	// 次シーン予約

	//// ----- フェード -----
	//switch (m_nextScene)
	//{
	//case SCENE_STAGE1:
	//case SCENE_STAGE2:
	//case SCENE_STAGE3:
	//	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::TIPS);	break;
	//	break;
	//default:
	//	m_pFade->Start(FADE_OUT, FADE_OUT_TIME, Fade::WHITE);	break;
	//	break;
	//}
}

// ========== シーン切り替え ==========
// 引　数：なし
// 戻り値：なし
// 指定のシーンに切り替え、必要情報を引き継ぐ
// ==================================
void CSceneMng::SceneSwap()
{
	//switch (m_scene)	// 遊んだステージの情報を格納
	//{
	//case SCENE_STAGE1:	m_oldPlayStage = SCENE_STAGE1;	break;
	//case SCENE_STAGE2:	m_oldPlayStage = SCENE_STAGE2;	break;
	//case SCENE_STAGE3:	m_oldPlayStage = SCENE_STAGE3;	break;
	//}

	// =-=-= 新しいシーンの読み込み =-=-=
	switch (m_nextScene)
	{
	case SCENE_TITLE:
		m_pTitle = new CSceneTitle(this);	// シーン遷移処理呼び出しのためSceneMng*受け渡し
		break;
	case SCENE_STAGE1: m_pScenePreArea = new CScenePreArea();  break;
	//case SCENE_STAGE2: m_pStage2 = new SceneStage2(this, 3); break;
	case SCENE_STAGE3:
	case SCENE_RESULT:
		m_pResult = new CSceneResult(this, m_nResetNo, m_nClear);
		break;
	}


	// =-=-= 現在のシーン削除 =-=-=
	switch (m_scene)
	{
	case SCENE_TITLE:	SAFE_DELETE(m_pTitle);	break;
	case SCENE_STAGE1:	SAFE_DELETE(m_pScenePreArea); break;
	//case SCENE_STAGE2:	SAFE_DELETE(m_pStage2); break;
	case SCENE_STAGE3:
	case SCENE_RESULT:	SAFE_DELETE(m_pResult);	m_nResetNo = 0; m_nClear = 0; break;
	default: break;
	}

	// ゲームシーンへの遷移でなければフェードイン
	m_scene = m_nextScene;	// シーン情報上書き
}
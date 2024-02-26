//----インクルードガード----
#ifndef __TUTORIAL_H__
#define __TUTORIAL_H__

//----インクルード部----
#include <DirectXMath.h>
#include "Shader.h"
#include "CameraBase.h"
#include "Model.h"
#include "Texture.h"
//----UI----
#include "ItemUI.h"

//----クラス定義----
class Tutorial
{
public:
	Tutorial(DirectX::XMFLOAT3 TutorialPos);	// コンストラクタ
	~Tutorial();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	//　カメラの設定
	void SetCamera(CameraBase* pCamera);
	// チュートリアル処理
	void AddScore(int kind, int color, int add);

	void SetItemUI(ItemUI* ItemUI);	// アイテムUIセット
	void SetResetFlg(int flg);		// リセットフラグセット

	// 現在地の取得
	DirectX::XMFLOAT3 GetPos();
	// プレイヤーのサイズ取得
	DirectX::XMFLOAT3 GetSize();
	// リセットフラグ情報ゲット
	int GetResetFlg();

private:
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;		// カメラの参照
	DirectX::XMFLOAT3 m_pos;	// プレイヤーの位置
	DirectX::XMFLOAT3 m_size;	// プレイヤーのサイズ
	Texture* m_pTexture[2];

	ItemUI* m_pUI;	// UI

	int m_nPrevItem;		// ひとつ目に手に入れたアイテム
	int m_nResetFlg;		// リセットを呼び出すフラグ
};
#endif		// __TUTORIAL_H__

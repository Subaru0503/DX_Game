// Melon.cpp

//=====インクルード=====
#include "Melon.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CMelon::CMelon(float posX, float posY, float posZ,
	float sizeX, float sizeY, float sizeZ)
	: Object(posX, posY, posZ)	// 親クラスのコンストラクタに引数を渡す)
{
	// 基本初期化処理
	Init();

	// 引数からスケール設定
	m_scale = { sizeX, sizeY, sizeZ };

	// 削除フラグ初期化
	m_bDelete = false;

	// オブジェクトの種類の設定
	m_nKind = Object::MELON;

	// フルーツフラグを立てる
	m_nFruits = true;

	// 色の設定
	m_nColor = Object::GREEN;

	// スコア設定
	m_nScore = 550;

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Fruits/Melon/Melon.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Fruits/Melon/Melon.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}

	// 見える向きを変える
	SetAngle(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));

	m_mass = 2.0f;
}

/********************
*@brief デストラクタ
*********************/
CMelon::~CMelon()	// デストラクタ
{
	SAFE_DELETE(m_pModel);
}
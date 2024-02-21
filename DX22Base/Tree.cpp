// Tree.cpp

//=====インクルード=====
#include "Tree.h"

#define BASE_SIZE_X	(1)

/************************************************
*@brief 座標＆スケール設定引数付きコンストラクタ
*************************************************/
CTree::CTree(float posX, float posY, float posZ,
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
	m_nKind = Object::TREE;

	// フルーツフラグを下げる
	m_nFruits = false;

	// 色の設定
	m_nColor = Object::NONE;

	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Tree/Tree.fbx", 1.0f, Model::Flip::XFlip))	// モデルデータ読み込み
	{
		MessageBox(NULL, "”Assets/Model/Tree/Tree.fbx”が読み込めませんでした", "Error", MB_OK);	// エラーメッセージ
	}
}

/********************
*@brief デストラクタ
*********************/
CTree::~CTree()	// デストラクタ
{
	SAFE_DELETE(m_pModel);
}
//----インクルード部----
#include "Tutorial.h"
#include "Input.h"
#include "Sprite.h"
//----オブジェクト----
#include "Object.h"

Tutorial::Tutorial(DirectX::XMFLOAT3 TutorialPos)	// コンストラクタ
	: m_pos(TutorialPos)
	, m_size(2.0f, 2.0f, 2.0f)
	, m_pCamera(nullptr)
	, m_pTexture{ nullptr, nullptr }
	, m_nPrevItem((int)Object::Kind::NONE)
	, m_nResetFlg(false)
{
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/Player/Player.fbx", 3.0f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "Tutorialモデル読み込み失敗", "Error", MB_OK);
	}

	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/shader/VS_Model.cso")))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "Tutorialシェーダー読み込み失敗", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_pTexture[0] = new Texture();
	m_pTexture[1] = new Texture();
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Tutorial Shadow.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Smoke.png")))
	{
		MessageBox(NULL, "Tutorial Smoke.png", "Error", MB_OK);
	}
}

Tutorial::~Tutorial()
{
	delete m_pVS;
	delete m_pModel;

	for (int i = 0; i < 2; i++)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void Tutorial::Update()
{
	
}

void Tutorial::Draw()
{
	// カメラがなければ処理は行わない
	if (!m_pCamera) { return; }

	// 行列の計算
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMFLOAT3 centerRotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	//原点
	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixRotationX(0.0f) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(180.0f)) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.4f, m_pos.z);

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	m_pModel->Draw();

	// 影
	DirectX::XMMATRIX Shadowworld = DirectX::XMMatrixScaling(3.0f, 3.0f, 3.0f) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(90.0f)) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, -0.5f, m_pos.z);

	DirectX::XMFLOAT4X4 Shadowmat;
	DirectX::XMStoreFloat4x4(&Shadowmat, DirectX::XMMatrixTranspose(Shadowworld));
	Sprite::SetWorld(Shadowmat);					// ワールド行列の設定
	Sprite::SetView(m_pCamera->GetViewMatrix());	// ビュー行列の設定
	Sprite::SetProjection(m_pCamera->GetProjectionMatrix());	// プロジェクション行列の設定
	Sprite::SetSize(DirectX::XMFLOAT2(1.0f, 1.0f));		// サイズを設定
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	Sprite::SetTexture(m_pTexture[0]);					// テクスチャを設定
	Sprite::Draw();
}

void Tutorial::SetCamera(CameraBase * pCamera)	//　カメラの設定
{
	m_pCamera = pCamera;
}

void Tutorial::AddScore(int kind, int color, int add)	// チュートリアル処理
{
	// ひとつ目のアイテムだったら
	if (m_nPrevItem == (int)Object::Kind::NONE)
	{
		// データを取っておく
		m_nPrevItem = kind;		// 種類
		// 1個目のパネルにはめる
		m_pUI->SetUP(DirectX::XMFLOAT3(580.0f, 80.0f, 0.0f), kind, true);
		return;	// 以降の処理をしない
	}
	

	// 2個目のパネルにはめる
	m_pUI->SetUP(DirectX::XMFLOAT3(680.0f, 80.0f, 0.0f), kind, true);
	if (m_nPrevItem == kind)
	{
		// 判定UIセット
		m_pUI->SetJudge(true, false, false);
	}
	else if (kind == (int)Object::Kind::CAN)
	{
		// 判定UIセット
		m_pUI->SetJudge(false, false, true);
	}
	else
	{
		// 判定UIセット
		m_pUI->SetJudge(false, true, false);
	}
	// 前に取ったアイテム情報を初期化
	m_nPrevItem = (int)Object::Kind::NONE;
	// リセットフラグを上げる
	m_nResetFlg = true;
}

void Tutorial::SetItemUI(ItemUI * ItemUI)	// アイテムUIセット
{
	m_pUI = ItemUI;
}

void Tutorial::SetResetFlg(int flg)	// リセットフラグセット
{
	m_nResetFlg = flg;
}

DirectX::XMFLOAT3 Tutorial::GetPos()	// 現在地の取得
{
	return m_pos;
}

DirectX::XMFLOAT3 Tutorial::GetSize()	// プレイヤーのサイズ取得
{
	return m_size;
}

int Tutorial::GetResetFlg()	// リセットフラグ情報ゲット
{
	return m_nResetFlg;
}

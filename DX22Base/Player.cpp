//----インクルード部----
#include "Player.h"
#include "Input.h"
#include "Sprite.h"
//----オブジェクト----
#include "Object.h"

//----定数・マクロ定義----
#define GRAVITY (0.15f)
#define RADIAN (180.0f / 3.14f)
#define JUMP (1.0f)

Player::Player(DirectX::XMFLOAT3 PlayerPos)	// コンストラクタ
	: m_pos(PlayerPos)
	, m_oldpos(PlayerPos)
	, m_size(0.5f, 2.0f, 0.5f)
	, m_pCamera(nullptr)
	, m_pTexture{ nullptr, nullptr }
	, m_fGravity(0.0f)
	, m_Move{ 0.0f, 0.0f, 0.0f }	// 移動情報
	, m_OldMove{ 0.0f, 0.0f, 0.0f }	// 前の移動情報
	, m_directRad(0.0f)				//プレイヤーの向きラジアン角
	, m_directAngle(0.0f)			//プレイヤーの向き角度
	, m_nLand(0)					// ジャンプフラグ
	, m_fJump(0.0f)					// ジャンプ量
	, m_nEventFlg(true)
	, m_nPrevItem((int)Object::Kind::NONE)
	, m_nPrevScore(0)
	, m_nLastScore(0)
	, m_nPrevColor((int)Object::Color::NO)
	, m_nScore(0)
	, m_nMinusScore(0)
{
	m_pModel = new Model();
	if (!m_pModel->Load("Assets/Model/3Dモデルデータ/もこ田めめめ/MokotaMememe.pmx", 1.0f, Model::XFlip))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "Playerモデル読み込み失敗", "Error", MB_OK);
	}

	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/shader/VS_Model.cso")))
	{
		//----エラーメッセージ表示----
		MessageBox(NULL, "Playerシェーダー読み込み失敗", "Error", MB_OK);
	}
	m_pModel->SetVertexShader(m_pVS);

	m_pEffect = new Effect();
	m_pMoveEmitter = new MoveEmitter();
	m_pEffect->AddEmitter(m_pMoveEmitter);

	m_pTexture[0] = new Texture();
	m_pTexture[1] = new Texture();
	m_pTexture[2] = new Texture();
	if (FAILED(m_pTexture[0]->Create("Assets/Texture/Shadow.png")))
	{
		MessageBox(NULL, "Player Shadow.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[1]->Create("Assets/Texture/Marker.png")))
	{
		MessageBox(NULL, "Player Marker.png", "Error", MB_OK);
	}
	if (FAILED(m_pTexture[2]->Create("Assets/Texture/warp.png")))
	{
		MessageBox(NULL, "Player warp.png", "Error", MB_OK);
	}

	m_pTrail = new TrailEffect(this);
	m_pTrail->AddLine(20);
	m_pTrail->AddLine(10);
}

Player::~Player()
{
	delete m_pTrail;
	delete m_pMoveEmitter;
	delete m_pEffect;
	delete m_pVS;
	delete m_pModel;

	for (int i = 0; i < 3; i++)
	{
		if (m_pTexture)
		{
			delete m_pTexture[i];
			m_pTexture[i] = nullptr;
		}
	}
}

void Player::Update()
{
	//----座標退避----
	m_oldpos = m_pos;

	//----重力加算----
	m_pos.y -= GRAVITY;

	//----ジャンプしてたら重力の分引く----
	if (m_fJump > 0.0f)
	{
		//----重力分引く----
		m_fJump -= GRAVITY;

		//----0より小さくなってたら0に戻す----
		if (m_fJump < 0.0f)
		{
			m_fJump = 0.0f;	//----0に調整----
		}
	}


	bool isMove = false;
	DirectX::XMFLOAT3 camPos = m_pCamera->GetPos();	// カメラの座標
	DirectX::XMFLOAT3 camLook = m_pCamera->GetLook();	// カメラの注視点
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);

	DirectX::XMVECTOR vFront;	// カメラの正面方向のベクトル
	vFront = DirectX::XMVectorSubtract(vCamPos, vCamLook);	// 正面方向のベクトル計算
	vFront = DirectX::XMVector3Normalize(vFront);	// 正規化

	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f));	// 90度回転
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);
	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();	// 0で初期化

	//const float Speed = 0.1f;
	// イベントのない時だけ操作できるように
	if (!m_nEventFlg)
	{
		//----プレイヤー移動処理----
		if (IsKeyPress('W')) { 
			isMove = true; vMove = DirectX::XMVectorSubtract(vMove, vFront); }
		if (IsKeyPress('S')) { 
			isMove = true; vMove = DirectX::XMVectorAdd(vMove, vFront); }
		if (IsKeyPress('D')) { 
			isMove = true; vMove = DirectX::XMVectorSubtract(vMove, vSide); }
		if (IsKeyPress('A')) { 
			isMove = true; vMove = DirectX::XMVectorAdd(vMove, vSide); }
	}

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);	// 移動ベクトルの正規化
	vMove = DirectX::XMVectorScale(vMove, 0.23f);	// 移動速度

	DirectX::XMStoreFloat3(&m_Move, vMove);	// XMFLOAT3に変換

	//----地面についててジャンプボタンが押されたら----
	if (m_nLand && IsKeyTrigger(VK_SPACE))
	{
		m_fJump = JUMP;	// ジャンプ量
		m_nLand = 0;	// 着地フラグ下げ
	}

	m_pos.x += m_Move.x; m_pos.y += m_Move.y + m_fJump; m_pos.z += m_Move.z;	// 座標の更新


	//---プレイヤーの回転角度を計算
	float rotationAngle;

	// 移動してたら
	if (m_Move.x != 0.0f || m_Move.z != 0.0f)
	{
		// 移動した方向に回転するように調整
		rotationAngle = atan2(m_Move.x, m_Move.z);
		//ModelRotate();	// プレイヤーモデルの回転
		// 移動情報退避
		m_OldMove = m_Move;
	}
	else
	{
		// 向きを固定
		rotationAngle = atan2(m_OldMove.x, m_OldMove.z);
	}

	//---プレイヤーの回転行列を更新
	m_directRad = rotationAngle;
	m_directAngle = rotationAngle * RADIAN;  // ラジアン角から度数に変換
	m_directRad = DirectX::XMConvertToRadians(m_directAngle);


	// イベント中なら終了
	if (m_nEventFlg) return;

	m_pEffect->Update();		// エフェクトの更新
	m_pEffect->SetPos(m_pos);	// 発生位置の設定
	if (!m_pEffect->IsPlay() && isMove)	// エフェクトの再生が止まっている状態で移動しているか
	{
		m_pEffect->Play();		// エフェクトの発生
	}

	m_pTrail->Update();

	if (m_pos.y < -20.0f)
	{
		m_pos.y = 0.0f;
	}
}

void Player::Draw()
{
	// カメラがなければ処理は行わない
	if (!m_pCamera) { return; }

	// 行列の計算
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMFLOAT3 centerRotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	//原点
	DirectX::XMMATRIX world = DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *
							  DirectX::XMMatrixRotationX(0.0f) *
							  DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(180.0f)) *
							  DirectX::XMMatrixRotationZ(0.0f) *
							  DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

	//---中心点の変換
	DirectX::XMMATRIX centerTranslationMatrix =
		DirectX::XMMatrixTranslation(-centerRotation.x, -centerRotation.y, -centerRotation.z);
	DirectX::XMMATRIX centerRotationMatrix = DirectX::XMMatrixRotationY(m_directRad);  // 同じ回転を適用
	DirectX::XMMATRIX centerWorldMatrix = centerRotationMatrix * centerTranslationMatrix;

	//---中心点を中心にモデルを回転
	world = centerWorldMatrix * world;

	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);

	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();
	
	m_pVS->WriteBuffer(0, mat);
	m_pModel->Draw();

	// 影
	DirectX::XMMATRIX Shadowworld = /*DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) **/
		DirectX::XMMatrixRotationX(-80.0f) *
		DirectX::XMMatrixRotationY(0.0f) *
		DirectX::XMMatrixRotationZ(0.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 0.01f, m_pos.z);

	DirectX::XMFLOAT4X4 Shadowmat;
	DirectX::XMStoreFloat4x4(&Shadowmat, DirectX::XMMatrixTranspose(Shadowworld));
	Sprite::SetWorld(Shadowmat);					// ワールド行列の設定
	Sprite::SetView(m_pCamera->GetViewMatrix());	// ビュー行列の設定
	Sprite::SetProjection(m_pCamera->GetProjectionMatrix());	// プロジェクション行列の設定
	Sprite::SetSize(DirectX::XMFLOAT2(0.5f, 0.5f));		// サイズを設定
	Sprite::SetTexture(m_pTexture[0]);					// テクスチャを設定
	Sprite::Draw();

	// イベント中だったら描画しない
	if (m_nEventFlg) return;

	DirectX::XMFLOAT4X4 inv;	// 逆行列の格納先
	inv = m_pCamera->GetViewMatrix();

	// カメラの行列はGPUに渡す際に転置されている、逆行列の計算のために一度元に戻す。
	DirectX::XMMATRIX matInv = DirectX::XMLoadFloat4x4(&inv);

	matInv = DirectX::XMMatrixTranspose(matInv);	// 転置
	// 移動成分は逆行列で打ち消す必要がないので、逆行列の計算のために一度元に戻す。
	DirectX::XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;

	matInv = DirectX::XMLoadFloat4x4(&inv);
	matInv = DirectX::XMMatrixInverse(nullptr, matInv);	// 逆行列の作成

	// エフェクト
	// Zソート(奥から描画)
	DirectX::XMFLOAT4X4 matBill;
	DirectX::XMStoreFloat4x4(&matBill, matInv);

	// marker
	DirectX::XMMATRIX invworld = matInv * DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 2.3f, m_pos.z);

	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(invworld));
	Sprite::SetWorld(mat[0]);
	Sprite::SetTexture(m_pTexture[1]);
	Sprite::Draw();

	m_pEffect->SetBillboardMatrix(matBill);
	//----エフェクト----
	m_pEffect->Draw(
		m_pCamera->GetViewMatrix(),
		m_pCamera->GetProjectionMatrix());


	// 軌跡の表示
	m_pTrail->SetView(m_pCamera->GetViewMatrix());
	m_pTrail->SetProjection(m_pCamera->GetProjectionMatrix());
	m_pTrail->SetTexture(m_pTexture[2]);
	m_pTrail->Draw();
}

void Player::ModelRotate()	// モデルの回転
{
	//----現在の向いてる方向を計算----
	DirectX::XMFLOAT3 currentPos;
	currentPos.x = m_oldpos.x + m_OldMove.x;
	currentPos.y = m_oldpos.y + m_OldMove.y;
	currentPos.z = m_oldpos.z + m_OldMove.z;

	DirectX::XMVECTOR currentDir = DirectX::XMVectorSubtract(
		DirectX::XMLoadFloat3(&currentPos),
		DirectX::XMLoadFloat3(&m_pos)
	);
	//----現在の方向を正規化----
	currentDir = DirectX::XMVector3Normalize(currentDir);


	//----新しく向いている方向を計算----
	DirectX::XMFLOAT3 newPos;
	newPos.x = m_pos.x + m_Move.x;
	newPos.y = m_pos.y + m_Move.y;
	newPos.z = m_pos.z + m_Move.z;

	DirectX::XMVECTOR newDir = DirectX::XMVectorSubtract(
		DirectX::XMLoadFloat3(&newPos),
		DirectX::XMLoadFloat3(&m_pos)
	);
	//----現在の方向を正規化----
	newDir = DirectX::XMVector3Normalize(newDir);


	//----モデルの回転角度を計算----
	float ModelRotateAngle;
	DirectX::XMStoreFloat(&ModelRotateAngle, DirectX::XMVector3AngleBetweenNormals(
		currentDir,			// 現在のプレイヤーの方向ベクトル
		newDir				// 新しいプレイヤーの方向ベクトル 
	));

	//---プレイヤーの回転行列を更新
	//m_directRad = ModelRotateAngle;
	m_directAngle = DirectX::XMConvertToDegrees(ModelRotateAngle);  // ラジアン角から度数に変換
	m_directRad = DirectX::XMConvertToRadians(m_directAngle);		// ラジアン角に変換
}

void Player::SetCamera(CameraBase * pCamera)
{
	m_pCamera = pCamera;
}

void Player::ResetGravity()	// 重力リセット関数
{
	m_fGravity = 0.0f;
}

void Player::ResetJumpFlg()	// ジャンプフラグ下げ関数
{
	m_nLand = 1;
}

void Player::AddScore(int kind, int color, int add)	// スコア加算
{
	// ひとつ目のアイテムだったら
	if (m_nPrevItem == (int)Object::Kind::NONE)
	{
		// データを取っておく
		m_nPrevItem = kind;		// 種類
		m_nPrevScore = add;		// スコア
		m_nPrevColor = color;	// 色
		return;	// 以降の処理をしない
	}
	// 種類が揃っていたら
	else if (m_nPrevItem == kind)
	{
		m_nScore += add;	// スコア加算
		m_nLastScore = add;	// スコアのデータを取っておく
	}
	// 色が揃っていたら
	else if (m_nPrevColor == color)
	{
		// 加算するスコアを計算
		int ScoreAdd;
		ScoreAdd = add / 100.0f * 10;
		if (ScoreAdd >= 50)	// 50以上なら
		{
			ScoreAdd = 40;
		}
		m_nScore += ScoreAdd;		// スコア加算
		m_nLastScore = ScoreAdd;	// スコアのデータを取っておく
	}
	// ゴミを拾ってしまっていたら
	else if(m_nPrevItem == (int)Object::Kind::CAN || kind == (int)Object::Kind::CAN)
	{
		if (m_nPrevItem == kind)	// 二つともゴミだったら最後に
		{
			m_nScore -= m_nLastScore * add;	// スコア減算
			m_nMinusScore += m_nLastScore * add;	// 引かれたスコアのデータを取っておく
		}
		// 一つだけゴミなら直前に取った物のスコア分引く
		else if(m_nPrevItem == (int)Object::Kind::CAN)
		{
			m_nScore -= m_nPrevScore;	// スコア減算
			m_nMinusScore += m_nPrevScore;	// 引かれたスコアのデータを取っておく
		}
		else
		{
			m_nScore -= add;// スコア減算
		}
		if (m_nScore < 0)	// スコアが0より低くなってたら
		{
			m_nScore = 0;
		}
	}

	// 前に取ったアイテム情報を初期化
	m_nPrevItem = (int)Object::Kind::NONE;
}

void Player::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}

void Player::SetEventFlg(int event)
{
	m_nEventFlg = event;
}

void Player::SetPosY(float height)			// 過去座標セット
{
	m_pos.y = height;
}

DirectX::XMFLOAT3 Player::GetPos()
{
	return m_pos;
}

DirectX::XMFLOAT3 Player::GetOldPos()	// 過去座標の取得
{
	return m_oldpos;
}

DirectX::XMFLOAT3 Player::GetCenterPos()
{
	DirectX::XMFLOAT3 m_centerpos;
	m_centerpos = m_pos;
	m_centerpos.y += m_size.y / 2.0f;

	return m_centerpos;
}

DirectX::XMFLOAT3 Player::GetSize()
{
	return m_size;
}

int Player::GetScore()		// スコア取得
{
	return m_nScore;
}

int Player::GetMinusScore()	// 引かれたスコア取得
{
	return m_nMinusScore;
}

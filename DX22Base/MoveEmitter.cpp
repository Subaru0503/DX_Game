// MoveEmitter.cpp

//----インクルード部----
#include "MoveEmitter.h"

MoveEmitter::MoveEmitter()	// コンストラクタ
	: Emitter("Assets/Texture/Smoke.png", { 3, 0.1, 0.1f })	// {パーティクル生成数, パーティクル生成間隔, エミッターの生存時間}
{

}

MoveEmitter::~MoveEmitter()	// デストラクタ
{

}

void MoveEmitter::Spawn(Particle * particle, const DirectX::XMFLOAT3 & rootPos)
{
	particle->pos.value = rootPos;	// エフェクト配置位置
	particle->pos.value.x += (rand() % 3 - 1) * 0.1f;
	particle->pos.add.y = 0.001f;	// アクセルの値を増やすとaddの値が増える
									// addの値を増やすとvalueの値が増える
	particle->size.value.x = 0.5f;
	particle->size.value.y = 0.5f;
	particle->size.add.x = 0.01f;
	particle->size.add.y = 0.01f;
	particle->alpha.add.x = -0.05f;
	particle->life = 0.9f;			// 生存時間
}

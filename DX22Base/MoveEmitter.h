// Move_Emitter.h

//----インクルードガード----
#ifndef __MOVE_EMITTER_H__
#define __MOVE_EMITTER_H__

//----インクルード部----
#include "Effect.h"

//----クラス定義----
class MoveEmitter : public Emitter
{
public:
	MoveEmitter();	// コンストラクタ
	~MoveEmitter();	// デストラクタ

protected:
	void Spawn(Particle* particle, const DirectX::XMFLOAT3& rootPos);
};

#endif	// __MOVE_EMITTER_H__

//----インクルードガード----
#ifndef __TRAIL_EFFECT_H__
#define __TRAIL_EFFECT_H__

//----インクルード部----
#include "Polyline.h"
//#include "Player.h"

class Player;

// プレイヤーの後を追いかけるエフェクト
class TrailEffect : public Polyline
{
public:
	TrailEffect(Player* pPlayer);	// コンストラクタ
	~TrailEffect();					// デストラクタ

protected:
	// ポリラインの制御点を更新
	void UpdateControlPoints(
		LineID id, ControlPoints& controlPoints) final;	// 制御点と頂点までの幅の情報がある

private:
	Player* m_pPlayer;
	DirectX::XMFLOAT3 m_oldPos;
};

#endif		// __TRAIL_EFFECT_H__
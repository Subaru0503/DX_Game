//----インクルード部----
#include "TrailEffect.h"
#include "Player.h"


TrailEffect::TrailEffect(Player * pPlayer)	// コンストラクタ
	:m_pPlayer(pPlayer)
{
	m_oldPos = m_pPlayer->GetPos();
}

TrailEffect::~TrailEffect()	// デストラクタ
{
}

void TrailEffect::UpdateControlPoints(LineID id, ControlPoints & controlPoints)
{
	// 毎フレーム, ポリラインの幅を少しずつ小さくする
	ControlPoints::iterator it = controlPoints.begin();
	while (it != controlPoints.end())
	{
		it->bold *= 0.85f;	// 掛け算で見えないくらいの制御点の幅を大きさまで小さくする
		++it;
	}

	// プレイヤーが移動しているか確認
	float distance = 0.0f;
	DirectX::XMFLOAT3 pos = m_pPlayer->GetPos();
	DirectX::XMVECTOR vOld = DirectX::XMLoadFloat3(&m_oldPos);
	DirectX::XMVECTOR vNow = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vDir = DirectX::XMVectorSubtract(vNow, vOld);
	DirectX::XMStoreFloat(&distance, DirectX::XMVector3Length(vDir));	// 移動した距離
	if (distance >= 0.2f/* && id == 1*/)	// プレイヤーが移動したら
	{
		// 一つずつずらす
		for (int i = controlPoints.size() - 1; i > 0; --i)
		{
			controlPoints[i] = controlPoints[i - 1];
		}

		// 先頭に新しいデータを設定
		controlPoints[0].pos = pos;
		controlPoints[0].pos.x += id;	// ポリラインが複数だったらずれるように
		controlPoints[0].pos.y += 0.01;	// エフェクトのY値
		controlPoints[0].bold = 0.5f;	// ポリラインの大きさ(幅)

		if(id == 1)
			// プレイヤーの前の位置の更新
			m_oldPos = pos;
	}
	//else if (id == 0)
	//{

	//}
}

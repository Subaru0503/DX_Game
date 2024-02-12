// CameraPlayer.h

//----インクルードガード----
#ifndef __CAMERA_PLAYER_H__
#define __CAMERA_PLAYER_H__
//----インクルード部----
#include "CameraBase.h"
#include "Player.h"

//----クラス定義----
class CameraPlayer : public CameraBase
{
public:
	CameraPlayer(Player* pPlayer);	// コンストラクタ
	~CameraPlayer();	// デストラクタ
	void Update();	// 更新
private:
	Player* m_pPlayer;
	float m_radXZ, m_radY;
	float m_oldradXZ, m_oldradY;	// 値退避用
};

#endif		// __CAMERA_PLAYER_H__

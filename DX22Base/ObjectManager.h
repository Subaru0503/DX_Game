//----インクルードガード----
#ifndef __OBJECT_MANAGER__
#define __OBJECT_MANAGER__

//----インクルード部----
#include <DirectXMath.h>
#include "Defines.h"
//#include "SoundManager.h"
#include "Model.h"
//#include "ModelManager.h"		// モデルマネージャー
// ----- ステージ -----
#include "Tree.h"				// 木
// フルーツ
#include "Apple.h"				// リンゴ
#include "Strawberry.h"			// イチゴ
#include "Banana.h"				// バナナ
#include "Lemon.h"				// レモン
#include "WaterMelon.h"			// スイカ
#include "Melon.h"				// メロン
#include "Can.h"				// 空き缶

// オブジェクトリスト用
#include <list>
using namespace std;

// 前方宣言
class Player;

//----クラス定義----
class CObjectMng
{
public:
	CObjectMng();							// コンストラクタ	
	~CObjectMng();							// デストラクタ

	void TutorialUpdate(float tick);		// チュートリアル更新
	void Update(float tick);				// 更新
	void Draw(DirectX::XMFLOAT4X4 *mat);	// 描画

	list<Object*>* GetObjectList();			// オブジェクトリストのポインタを渡す

	void SetTutorialFruits();				// チュートリアル用のオブジェクトをセット
	void SetObject();						// 初期オブジェクトセット
	void FruitsObjectSet(DirectX::XMFLOAT3 pos);		// 新しくフルーツオブジェクト生成
	void SetTime(int time);					// 時間セット
	void SetPlayer(Player* pPlayer);
	void SetMoveFlg(int flg);				// 移動完了フラグセット
private:
	list<Object*> m_ObjectList;				// オブジェクトリスト

	VertexShader* m_pVS;

	Model* m_pModel;
	Player* m_pPlayer;
	int m_nTime;							// 制限時間
	int m_nCnt;								// フルーツカウント
	int m_nMoveFlg;							// 移動完了フラグ
};

#endif
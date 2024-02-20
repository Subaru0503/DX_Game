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
#include "Apple.h"
#include "WaterMelon.h"

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

	void Update(float tick);				// 更新
	void Draw(DirectX::XMFLOAT4X4 *mat);	// 描画

	list<Object*>* GetObjectList();			// オブジェクトリストのポインタを渡す

	//void SetTotalObjNum(int totalObjNum);	// 吸い込めるオブジェクトの総数を設定
	//void ModelSetting();					// オブジェクトにモデルをセットする
	//void SetSuction(Suction* suction);
	//void SetSound(CSoundMng* sound);
	void SetObject();						// 初期オブジェクトセット
	void FruitsObjectSet(float posX, float posZ);		// フルーツオブジェクトセット
	void SetTime(int time);					// 時間セット
	void SetPlayer(Player* pPlayer);
private:
	list<Object*> m_ObjectList;				// オブジェクトリスト

	//CSoundMng* m_pSoundMng;
	//ModelManager* m_pModelManager;			// モデルマネージャー
	VertexShader* m_pVS;

	Model* m_pModel;
	Player* m_pPlayer;
	int m_nTime;							// 制限時間
};

#endif
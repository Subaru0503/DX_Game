//----インクルード部----
#include "ObjectManager.h"
#include "Geometory.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

//----定数・マクロ定義----
#define MAX_TREE (4)	// 木最大数
#define FALL_FRUITS_POSY (7.0f)	// フルーツ落下位置
using namespace std;

CObjectMng::CObjectMng()	// コンストラクタ
	//: m_pModelManager(nullptr)
{
	m_pVS = new VertexShader();
	if (FAILED(m_pVS->Load("Assets/Shader/VS_Model.cso")))	// シェーダ読み込み
	{
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	SetObject();	// オブジェクトのセット
	// オブジェクトにモデルを割り当てる用
	//m_pModelManager = new ModelManager();
}

CObjectMng::~CObjectMng()	// デストラクタ
{
	// リスト内のすべてのオブジェクトを解放
	for (Object* pObj : m_ObjectList) {
		if (pObj != nullptr)
		{
			//pObj->Uninit();
			delete pObj;
		}
	}
	m_ObjectList.clear();// 全要素削除

	if (m_pVS)
	{
		delete m_pVS;
		m_pVS = nullptr;
	}

	//if (m_pModelManager)
	//{
	//	delete m_pModelManager;
	//	m_pModelManager = nullptr;
	//}
}

void CObjectMng::Update(float tick)	// 更新
{
	//--吸い込まれるor破壊されるオブジェクトの処理
	for (auto it = m_ObjectList.begin(); it != m_ObjectList.end();)
	{
		Object* pObj = *it;			// オブジェクトの関数を呼び出せるように変換
		(*it)->SetPlayerPos(m_pPlayer->GetPos());	// プレイヤーの座標情報をオブジェクトに設定

		if (pObj->GetCreate())	// 生成フラグが立っていら
		{
			FruitsObjectSet(pObj->GetPos());	// 新しくフルーツをセットする
		}
		if (pObj->GetDelete()) {	// 削除フラグが立っていたら
			delete pObj;					// メモリを解放
			it = m_ObjectList.erase(it);	// リストから削除してイテレータを更新→次の要素へ
		}
		else {			// 削除しないので
			++it;		// イテレータを進める
		}
	}
	int i = 0;
	// オブジェクト更新処理
	for (Object* pObj : m_ObjectList)
	{
		pObj->Update(tick);
		i++;
	}

}

void CObjectMng::Draw(DirectX::XMFLOAT4X4 *mat)		// 描画
{
	// リスト内のオブジェクトの描画処理
	for (Object* pObj : m_ObjectList)
	{
		bool draw = pObj->GetDraw();
		if (pObj->GetModel() != nullptr)
		{
			if (draw)
				pObj->DrawModel(mat, m_pVS);
		}
	}
}

list<Object*>* CObjectMng::GetObjectList()
{
	return &m_ObjectList;
}

//void CObjectMng::SetTotalObjNum(int totalObjNum)
//{
//	m_totalObjNum = totalObjNum;
//}

//void CObjectMng::ModelSetting()
//{
//	for (Object* pObj : m_ObjectList) {
//		pObj->SetModelManager(m_pModelManager);	// モデルマネージャーをオブジェクトにセット
//		pObj->SetModelData();					// オブジェクトにモデルをセット
//	}
//}

//void CObjectMng::SetSound(CSoundMng * sound)
//{
//	m_pSoundMng = sound;
//}

void CObjectMng::SetObject()			// 初期オブジェクトセット
{
	DirectX::XMFLOAT3 Deltapos = DirectX::XMFLOAT3(7.0f, 0.0f, -1.0f);		// 座標変化量
	DirectX::XMFLOAT3 TreePos = DirectX::XMFLOAT3(-10.0f, 6.0f, -5.0f);		// 木座標
	DirectX::XMFLOAT3 FruitsPos = DirectX::XMFLOAT3(-10.0f, FALL_FRUITS_POSY, -3.0f);	// フルーツ座標
	DirectX::XMFLOAT3 FruitsSize = DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f);		// フルーツサイズ
	// 木
	for (int i = 0; i < MAX_TREE; i++)
	{
		// 木生成
		m_ObjectList.push_back(new CTree(TreePos.x, TreePos.y, TreePos.z, 1.0f, 21.0f, 1.0f));
		// 座標変化
		TreePos.x += Deltapos.x;
		TreePos.z *= Deltapos.z;
	}

	// 乱数初期化
	srand((unsigned int)time(NULL));
	int	random;	// 乱数格納用
	//----木の数分最初のフルーツを用意する----
	for (int i = 0; i < MAX_TREE; i++)
	{
		random = (rand() + (int)(FruitsPos.x + FruitsPos.y + FruitsPos.z)) % ((int)Object::Kind::MAX_FALL);

		// 生成
		switch (random)
		{
		case Object::Kind::APPLE:	// リンゴ
			m_ObjectList.push_back(new CApple(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::STRAWBERRY:	// イチゴ
			m_ObjectList.push_back(new CStrawberry(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::BANANA:	// バナナ
			m_ObjectList.push_back(new CBanana(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::LEMON:	// レモン
			m_ObjectList.push_back(new CLemon(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::WATER_MELON:		// スイカ
			m_ObjectList.push_back(new CWaterMelon(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		case Object::Kind::MELON:		// メロン
			m_ObjectList.push_back(new CMelon(FruitsPos.x, FruitsPos.y, FruitsPos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
			break;
		default:
			i--;
			continue;
			break;
		}

		// 座標変化
		FruitsPos.x += Deltapos.x;
		//FruitsPos.y += Deltapos.y;
		FruitsPos.z *= Deltapos.z;
	}

}

void CObjectMng::FruitsObjectSet(DirectX::XMFLOAT3 pos)		// 新しくフルーツオブジェクト生成
{
	DirectX::XMFLOAT3 FruitsSize = DirectX::XMFLOAT3(2.0f, 2.0f, 2.0f);		// フルーツサイズ

	// 乱数初期化
	srand((unsigned int)time(NULL));
	int	random;	// 乱数格納用
	random = (rand() + (int)(pos.x + 6.0f + pos.z)) % ((int)Object::Kind::MAX_FALL);

	// 生成
	switch (random)
	{
	case Object::Kind::APPLE:	// リンゴ
		m_ObjectList.push_back(new CApple(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::STRAWBERRY:	// イチゴ
		m_ObjectList.push_back(new CStrawberry(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::BANANA:	// バナナ
		m_ObjectList.push_back(new CBanana(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::LEMON:	// レモン
		m_ObjectList.push_back(new CLemon(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::WATER_MELON:		// スイカ
		m_ObjectList.push_back(new CWaterMelon(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::MELON:		// メロン
		m_ObjectList.push_back(new CMelon(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	case Object::Kind::CAN:		// 空き缶
		m_ObjectList.push_back(new CCan(pos.x, FALL_FRUITS_POSY, pos.z, FruitsSize.x, FruitsSize.y, FruitsSize.z));
		break;
	}
}

void CObjectMng::SetTime(int time)
{
	m_nTime = time;
}

void CObjectMng::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}
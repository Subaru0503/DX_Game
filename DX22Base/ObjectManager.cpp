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
			FruitsObjectSet(pObj->GetPos().x, pObj->GetPos().z);	// 新しくフルーツをセットする
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
	DirectX::XMFLOAT3 TreePos = DirectX::XMFLOAT3(-10.0f, 3.0f, -5.0f);		// 木座標
	DirectX::XMFLOAT3 FruitsPos = DirectX::XMFLOAT3(-10.0f, 6.0f, -3.0f);	// フルーツ座標
	// 木
	for (int i = 0; i < MAX_TREE; i++)
	{
		// 木生成
		m_ObjectList.push_back(new CTree(TreePos.x, TreePos.y, TreePos.z, 1.0f, 6.0f, 1.0f));
		// 座標変化
		TreePos.x += Deltapos.x;
		TreePos.z *= Deltapos.z;
	}
	//m_ObjectList.push_back(new CTree(-10.0f, 3.0f, -5.0f, 1.0f, 6.0f, 1.0f));
	//m_ObjectList.push_back(new CTree(-3.0f, 3.0f, 5.0f, 1.0f, 6.0f, 1.0f));
	//m_ObjectList.push_back(new CTree(4.0f, 3.0f, -5.0f, 1.0f, 6.0f, 1.0f));
	//m_ObjectList.push_back(new CTree(11.0f, 3.0f, 5.0f, 1.0f, 6.0f, 1.0f));
	// 乱数初期化
	srand((unsigned int)time(NULL));
	int	random;	// 乱数格納用
	//----木の数分最初のフルーツを用意する----
	for (int i = 0; i < MAX_TREE; i++)
	{
		random = (rand() + (int)(FruitsPos.x + FruitsPos.y + FruitsPos.z)) % ((int)Object::Kind::MAX_FRUITS);

		// 生成
		switch (random)
		{
		case Object::Kind::APPLE:	// リンゴ
			m_ObjectList.push_back(new CApple(FruitsPos.x, FruitsPos.y, FruitsPos.z, 1.0f, 1.0f, 1.0f));
			break;
		case Object::Kind::WATER_MELON:		// スイカ
			m_ObjectList.push_back(new CWaterMelon(FruitsPos.x, FruitsPos.y, FruitsPos.z, 1.0f, 1.0f, 1.0f));
			break;
		}

		// 座標変化
		FruitsPos.x += Deltapos.x;
		FruitsPos.z *= Deltapos.z;
	}

	//m_ObjectList.push_back(new CWaterMelon(-3.0f, 6.0f, 3.0f, 1.0f, 1.0f, 1.0f));
	//m_ObjectList.push_back(new CWaterMelon(3.0f, 6.0f, -3.0f, 1.0f, 1.0f, 1.0f));
	//m_ObjectList.push_back(new CWaterMelon(10.0f, 6.0f, 3.0f, 1.0f, 1.0f, 1.0f));
}

void CObjectMng::FruitsObjectSet(float posX, float posZ)		// フルーツオブジェクトセット
{
	// 乱数初期化
	srand((unsigned int)time(NULL));
	int	random;	// 乱数格納用
	random = rand() % ((int)Object::Kind::MAX_FRUITS);

	// 生成
	switch (random)
	{
	case Object::Kind::APPLE:	// リンゴ
		m_ObjectList.push_back(new CApple(posX, 6.0f, posZ, 1.0f, 1.0f, 1.0f));
		break;
	case Object::Kind::WATER_MELON:		// スイカ
		m_ObjectList.push_back(new CWaterMelon(posX, 6.0f, posZ, 1.0f, 1.0f, 1.0f));
		break;
	}
	// スイカ
	//m_ObjectList.push_back(new CWaterMelon(posX, 6.0f, posZ, 1.0f, 1.0f, 1.0f));
}

void CObjectMng::SetTime(int time)
{
	m_nTime = time;
}

void CObjectMng::SetPlayer(Player * pPlayer)
{
	m_pPlayer = pPlayer;
}
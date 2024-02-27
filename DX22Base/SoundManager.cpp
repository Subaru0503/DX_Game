//=================================================================
//
//	SoundManager.cpp
//	SEを一元管理する
//
//=================================================================

// ========== インクルード部 ==========
#include "SoundManager.h"

// ========== 定数・マクロ定義 ==========
// ----- 定数 -----
#define TITLE_BGM_VOL			(0.8f)	// タイトルBGM
#define GAEM_BGM_VOL			(0.7f)	// ゲームBGM
#define RESULT_BGM_VOL			(0.8f)	// リザルトBGM
#define DECSION_VOL				(0.2f)	// 決定 
#define CANCEL_VOL				(1.0f)	// キャンセル 
#define SELECT_VOL				(1.0f)	// 選択 
#define TSTRAT_VOL				(1.0f)	//ゲーム開始(タイトル)
#define SWAP_VOL				(0.5f)	//ステージチェンジ
#define OP_BGM_VOL				(1.0f)	//オープニング
#define ED_BGM_VOL				(1.0f)	//エンディング
#define GET_FRUITS_SE_VOL		(1.0f)	// フルーツ入手音
#define EXCELLENT_SE_VOL		(0.4f)	// 秀
#define GOOD_SE_VOL		(0.7f)	// 良
#define BAD_SE_VOL		(1.0f)	// 悪

// ----- マクロ -----
#define STR(var) #var   //引数にした変数を変数名を示す文字列として返すマクロ関数

// ========== コンストラクタ ==========
CSoundMng::CSoundMng()
{
	// =-=-= 各BGM読み込み =-=-=
	m_pSoundMap[STR(CSoundMng::BGM::title)] = LoadSound("Assets/BGM/タイトル.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::game)] = LoadSound("Assets/BGM/ゲーム.mp3", true);
	m_pSoundMap[STR(CSoundMng::BGM::result)] = LoadSound("Assets/BGM/リザルト.mp3", true);

	// ---- 入手音 ----
	m_pSoundMap[STR(CSoundMng::GetSE::fruits)] = LoadSound("Assets/SE/入手音/フルーツ入手.mp3");
	m_pSoundMap[STR(CSoundMng::JudgeSE::excellent)] = LoadSound("Assets/SE/ペア組み合わせ/秀.mp3");
	m_pSoundMap[STR(CSoundMng::JudgeSE::good)] = LoadSound("Assets/SE/ペア組み合わせ/良.mp3");
	m_pSoundMap[STR(CSoundMng::JudgeSE::bad)] = LoadSound("Assets/SE/ペア組み合わせ/悪.mp3");

}

// ========== デストラクタ ==========
CSoundMng::~CSoundMng()
{
	// =-=-= 解放 =-=-=
	// ----- 音源map -----
	for (auto it = m_pSoundMap.begin(); it != m_pSoundMap.end();) {	// 全サウンドデータを解放
		//delete it->second->pAudioData;						// サウンドデータを解放 Sound.hがやってくれるので省略
		it = m_pSoundMap.erase(it);								// ポインタを開放
	}

	// ----- スピーカーlist -----
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();) {	// 全スピーカーデータを解放
		if ((*it)) {
			(*it)->m_Speaker->Stop();						// 再生停止(不要？)
			(*it)->m_Speaker->DestroyVoice();				// 音を破棄
			delete (*it);									// 必要？不要？？これ書くと参照エラー出る。	Destroyで動的データ消えてる？
			it = m_pSpeakerList.erase(it);				// ポインタを開放
		}
	}
}


// ========== 再生終了スピーカー破棄 ==========
// 引　数：なし
// 戻り値：なし
// 再生が終わったSEスピーカーを破棄する
// ==========================================
void CSoundMng::DeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// 全てのSEスピーカーをみる
	{
		XAUDIO2_VOICE_STATE state{ 0 };
		(*it)->m_Speaker->GetState(&state);					// 再生状況取得
		if (state.BuffersQueued == 0)						// 再生が終わっていたら破棄
		{
			// ----- スピーカー削除 -----
			(*it)->m_Speaker->Stop();						// 再生停止(不要？)
			(*it)->m_Speaker->DestroyVoice();				// 音を破棄
			delete (*it);									// スピーカー構造体の実体解放
			it = m_pSpeakerList.erase(it);				// ポインタを開放
		}
		else
		{
			it++;								// 次の要素へ
		}
	}
}

// ========== 再生中スピーカー全破棄 ==========
// 引　数：なし
// 戻り値：なし
// 再生中の全てのスピーカーを破棄する
// ==========================================
void CSoundMng::AllDeleteSpeaker()
{
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end();)	// 全てのSEスピーカーをみる
	{
		// ----- スピーカー削除 -----
		(*it)->m_Speaker->Stop();						// 再生停止(不要？)
		(*it)->m_Speaker->DestroyVoice();				// 音を破棄
		delete (*it);									// スピーカー構造体の実体解放
		it = m_pSpeakerList.erase(it);					// ポインタを開放
	}
}

// ========== BGM再生 ==========
// 引　数：
// BGM 鳴らしたいBGM番号
// 戻り値：なし
// 指定のBGMを鳴らす
// =====================================
void CSoundMng::playSound(BGM kind)
{
	switch (kind)
	{
	case CSoundMng::BGM::title:	// タイトルBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::title)]), SpeakerKind::bTitle });
		m_pSpeakerList.back()->m_Speaker->SetVolume(TITLE_BGM_VOL);
		break;
	case CSoundMng::BGM::game:	// ゲームBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::game)]), SpeakerKind::bGame });
		m_pSpeakerList.back()->m_Speaker->SetVolume(GAEM_BGM_VOL);
		break;
	case CSoundMng::BGM::result:	// リザルトBGM
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::BGM::result)]), SpeakerKind::bResult });
		m_pSpeakerList.back()->m_Speaker->SetVolume(RESULT_BGM_VOL);
		break;
	}
}

// ========== システムSE再生 ==========
// 引　数：
// SystemSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のシステムSEを鳴らす
// ===================================
void CSoundMng::playSound(SystemSE kind)
{
	//switch (kind)
	//{
	//case CSoundMng::decision:	// 決定
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::decision)]), SpeakerKind::sDecision });	// スピーカー生成
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(DECSION_VOL);	// ここに小数いれる(たぶん0.0/*最小*/ ~ 1.0/*最大*/)
	//	break;
	//case CSoundMng::cancel:		// キャンセル
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::cancel)]), SpeakerKind::sCancel });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(CANCEL_VOL);
	//	break;
	//case CSoundMng::select:		// 選択
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::select)]), SpeakerKind::sSelect });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(SELECT_VOL);
	//	break;
	//case CSoundMng::Tstrat:		// ゲーム開始
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::Tstrat)]), SpeakerKind::sTStrat });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(TSTRAT_VOL);
	//	break;
	//case CSoundMng::swap:		// ステージチェンジ
	//	m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::SystemSE::swap)]), SpeakerKind::sSwap });
	//	m_pSpeakerList.back()->m_Speaker->SetVolume(SWAP_VOL);
	//	break;
	//}
}

// ========== 入手SE再生 ==========
// 引　数：
// GetSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のシステムSEを鳴らす
// ===================================
void CSoundMng::playSound(GetSE kind)
{
	switch (kind)
	{
	case CSoundMng::fruits:	// フルーツ入手
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::GetSE::fruits)]), SpeakerKind::bFruits });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(GET_FRUITS_SE_VOL);	// ここに小数いれる(たぶん0.0/*最小*/ ~ 1.0/*最大*/)
		break;
	}
}

// ========== 判定SE再生 ==========
// 引　数：
// JudgeSE 鳴らしたいSE番号
// 戻り値：なし
// 指定のシステムSEを鳴らす
// ===================================
void CSoundMng::playSound(JudgeSE kind)
{
	switch (kind)
	{
	case CSoundMng::excellent:	// 秀
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::JudgeSE::excellent)]), SpeakerKind::bExcellent });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(EXCELLENT_SE_VOL);	// ここに小数いれる(たぶん0.0/*最小*/ ~ 1.0/*最大*/)
		break;
	case CSoundMng::good:	// 秀
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::JudgeSE::good)]), SpeakerKind::bGood });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(GOOD_SE_VOL);	// ここに小数いれる(たぶん0.0/*最小*/ ~ 1.0/*最大*/)
		break;
	case CSoundMng::bad:	// 秀
		m_pSpeakerList.push_back(new Speaker{ PlaySound(m_pSoundMap[STR(CSoundMng::JudgeSE::bad)]), SpeakerKind::bBad });	// スピーカー生成
		m_pSpeakerList.back()->m_Speaker->SetVolume(BAD_SE_VOL);	// ここに小数いれる(たぶん0.0/*最小*/ ~ 1.0/*最大*/)
		break;
	}
}

// ========== システムSE再生終了チェック ===============
// 引　数：
// SystemSE 調べたいSE番号
// 戻り値：再生終了(or 再生してない) → true
// 指定のシステムSEが再生終了したかチェック
// ==========================================
//bool CSoundMng::CheckSoundEnd(SystemSE kind)
//{
	//for (Speaker* pSpeaker : m_pSpeakerList)
	//{
	//	switch (kind)
	//	{
	//	case CSoundMng::SystemSE::decision:
	//		if (pSpeaker->m_Kind == sDecision) return false;
	//		break;
	//	case CSoundMng::SystemSE::cancel:
	//		if (pSpeaker->m_Kind == sCancel) return false;
	//		break;
	//	case CSoundMng::SystemSE::select:
	//		if (pSpeaker->m_Kind == sSelect) return false;
	//		break;
	//	case CSoundMng::SystemSE::swap:
	//		if (pSpeaker->m_Kind == sSwap) return false;
	//		break;
	//	}
	//}

	//return true;
//}

//bool CSoundMng::CheckSoundEnd(GetSE kind)
//{
//	for (Speaker* pSpeaker : m_pSpeakerList)
//	{
//		switch (kind)
//		{
//		case CSoundMng::GetSE::fruits:
//			if (pSpeaker->m_Kind == bFruits) return false;
//			break;
//		}
//	}
//
//	return true;
//}


// ========== BGM再生停止 ==========
// 引　数：
// BGM 停止したいBGM番号
// 戻り値：なし
// 指定のBGMの再生を停止し、スピーカーを破棄する
// ==========================================
void CSoundMng::StopSound(BGM kind)
{
	bool flg = false;	// 再生中

	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)	// 全再生中SEの中から指定のSEを探す
	{
		switch (kind)
		{
		case CSoundMng::BGM::title:
			if ((*it)->m_Kind == bTitle) flg = true;
			break;
		case CSoundMng::BGM::game:
			if ((*it)->m_Kind == bGame) flg = true;
			break;
		case CSoundMng::result:
			if ((*it)->m_Kind == bResult) flg = true;
			break;
		}

		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}

void CSoundMng::StopSound(SystemSE kind)
{
	bool flg = false;	// 再生中
	for (auto it = m_pSpeakerList.begin(); it != m_pSpeakerList.end(); it++)
	{
		//switch (kind)
		//{
		//case CSoundMng::SystemSE::Fpon:
		//	if ((*it)->m_Kind == sFpon) flg = true;
		//	break;
		//}
		if (flg)	// 再生中の指定SEを見つけたらそれを破棄
		{
			(*it)->m_Speaker->Stop();
			(*it)->m_Speaker->DestroyVoice();
			delete (*it);
			m_pSpeakerList.erase(it);
			break;
		}
	}
}
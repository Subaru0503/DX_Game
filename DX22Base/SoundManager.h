//=================================================================
//
//	SoundManager.h
//	サウンドを一元管理する
//
//=================================================================

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

// ========== インクルード部 ==========
#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <list>
using namespace std;

// ========== クラス ==========
class CSoundMng
{
public:	// 列挙型 外部呼出し用
	// =-=-= BGM =-=-=
	enum BGM {
		title,
		game,
		result,
	};

	// =-=-= SE =-=-=
	// ----- システム音 -----
	enum SystemSE {
		decision,		// 決定
		cancel,			// キャンセル
		select,			// 選択
		Tstrat,			//ゲーム開始(タイトル)
		swap,			//ステージチェンジ
		Fpon,			//リザルトSE
	};

	// ----- 入手音 -----
	enum GetSE {
		fruits,			// フルーツ
		Can,			// 空き缶
	};

	// ---- 判定音 ----
	enum JudgeSE {
		excellent,
		good,
		bad,
	};
public:	// 関数
	CSoundMng();
	~CSoundMng();
	void DeleteSpeaker();							// 再生終了したSEスピーカーを削除
	void AllDeleteSpeaker();						// 再生中のスピーカーを全削除

	// =-=-= 再生 =-=-=
	// ----- BGM -----
	void playSound(BGM kind);						// BGM

	// ----- SE -----
	void playSound(SystemSE kind);					// システム音
	void playSound(GetSE kind);						// 入手音
	void playSound(JudgeSE kind);					// 判定音

	// =-=-= 再生終了チェック =-=-=
	// ----- BGM -----
	//bool CheckSoundEnd(BGM kind);

	// ----- SE -----
	//bool CheckSoundEnd(SystemSE kind);				// システム指定のSEが再生終了したかチェック
	//bool CheckSoundEnd(GetSE kind);					// 入手指定のSEが再生終了したかチェック

	// =-=-= 再生停止 =-=-=
	// ----- BGM -----
	void StopSound(BGM kind);						// BGM

	// ----- SE -----
	void StopSound(SystemSE kind);				// システム音SE再生停止


private: // 列挙型　内部処理用
	enum SpeakerKind
	{
		//----BGM----
		bTitle,			// タイトル
		bGame,			// ゲーム
		bResult,		// リザルト
		//----SE----
		bFruits,		// フルーツ入手
		bExcellent,		// 秀
		bGood,			// 良
		bBad,			// 悪
	};

	typedef struct		// スピーカー
	{
		IXAudio2SourceVoice*	m_Speaker;		// スピーカー
		SpeakerKind				m_Kind;				// スピーカーの種類
	}Speaker;

private:

	map<string, XAUDIO2_BUFFER*> m_pSoundMap;		// 音源用map
	list<Speaker*> m_pSpeakerList;					// スピーカー用list
};
#endif // !__SOUND_MANAGER_H__
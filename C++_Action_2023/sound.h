
//-===============================================
//-
//-	サウンド処理のヘッダー[sound.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SOUND_H_		// このマクロが定義されなかったら
#define _SOUND_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	構造体定義
//-======================================

typedef struct
{
	char *pFilename;	// ファイル名
	int nCntLoop;		// ループカウント
} SOUNDINFO;

//-======================================
//-	クラス定義
//-======================================

class CSound
{

public:

	// サウンドラベル
	typedef enum
	{
		LABEL_BGM_TITLE = 0,	// タイトルBGM
		LABEL_BGM_GAME,			// ゲームBGM
		LABEL_BGM_RESULT,		// リザルトBGM
		
		LABEL_SE_JUMP,			// ジャンプSE
		LABEL_SE_DOUBLE_JUMP,	// 二段ジャンプSE
		LABEL_SE_KAZEDAMA,		// 風だまSE
		LABEL_SE_GET,			// 取得SE
		LABEL_SE_SHOT,			// 発射SE
		LABEL_SE_JEWEL,			// 宝石SE
		LABEL_MAX,
	}LABEL;

	// サウンドの情報
	SOUNDINFO g_aSoundInfo[LABEL_MAX] =
	{
		{ "Data/BGM/Brave.wav",-1 },			// タイトル
		{ "Data/BGM/LIAR_PARADOX_2.wav",-1 },	// ゲーム
		{ "Data/BGM/MusMus-BGM-116.wav",-1 },	// リザルト
		{ "data/SE/jump.wav", 0 },				// ジャンプ
		{ "data/SE/double_jump.wav", 0 },		// ダブルジャンプ
		{ "data/SE/kazedama.wav", 0 },			// 風だま
		{ "data/SE/get.wav", 0 },				// 取得
		{ "data/SE/shot.wav", 0 },				// 発射
		{ "data/SE/jewel.wav", 0 },				// 宝石
	};

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[LABEL_MAX];						// オーディオデータ
	DWORD m_aSizeAudio[LABEL_MAX];						// オーディオデータサイズ
};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了

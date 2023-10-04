
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
		LABEL_BGM_TITLE = 0,			// タイトル
		LABEL_BGM_GAME,					// ゲーム
		LABEL_BGM_CHAOS_CHARGE_SHOT,	// 闇の攻撃
		LABEL_SE_SHOT_000,				// ショット
		LABEL_SE_NOR_CHARGE_SHOT,		// チャージショット
		LABEL_SE_DAMAGE_ENEMY_000,		// 敵のダメージ音000
		LABEL_SE_DAMAGE_ENEMY_001,		// 敵のダメージ音001
		LABEL_SE_DAMAGE_PLAYER,			// プレイヤーのダメージ音
		LABEL_SE_DIED_ENEMY_000,		// 敵の死亡音000
		LABEL_SE_TLEPORT_000,			// テレポ
		LABEL_SE_EAT_000,				// 食べる音000
		LABEL_MAX,
	}LABEL;

	// サウンドの情報
	SOUNDINFO g_aSoundInfo[LABEL_MAX] =
	{
		{ "Data/BGM/Raijin.wav",-1 },				// タイトル
		{ "Data/BGM/arcman.wav",-1 },				// ゲーム
		{ "Data/BGM/ChaosChargeShot000.wav",-1 },	// 闇の攻撃
		{ "data/SE/Shot000.wav", 0 },				// ショット000
		{ "data/SE/NorChargeShot000.wav", 0 },		// 通常チャージ攻撃
		{ "data/SE/DamageEnemy000.wav", 0 },		// 敵のダメージ音
		{ "data/SE/DamageEnemy001.wav", 0 },		// 敵のダメージ音
		{ "data/SE/DamagePlayer.wav", 0 },			// プレイヤーのダメージ音
		{ "data/SE/DiedEnemy000.wav", 0 },			// 敵のダメージ音
		{ "data/SE/Teleport.wav", 0 },				// テレポ
		{ "data/SE/Eat000.wav", 0 },				// 食べる音000
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

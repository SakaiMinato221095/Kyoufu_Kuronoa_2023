
//-===============================================
//-
//-	ゲームの処理のヘッダー[game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GAME_H_		// このマクロが定義されなかったら
#define _GAME_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "manager.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	前方宣言
//-======================================

class CPlayer;

class CTimer;

class CEditMap;

class CPause;
//-======================================
//-	クラス定義
//-======================================

class CGame : public CScene
{

public:

	typedef enum
	{
		GAME_NONE = 0,	// ゲームの通常状態
		GAME_PAUSE,		// ポーズ状態
		GAME_MAX
	}GAME;

	CGame();
	~CGame();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CPlayer *GetPlayer(void);

	static CPause *GetPause(void);

private:

	static CPlayer *m_pPlayer;				// プレイヤー
	static CTimer *m_pTimer;				// タイマー

	static CEditMap *m_pEditMap;			// マップエディット

	static CPause *m_pPause;				// ポーズ

	GAME m_game;							// ゲーム状態
};

#endif	// 二重インクルード防止の終了

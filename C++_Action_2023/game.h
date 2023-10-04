
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

#include "sys_game_phase.h"

//=======================================
//=	マクロ定義
//=======================================

#define OBJ_2D_NONE_NUM_MAX	(8)		// 効果なし2Dの最大数
#define EFFECT_2D_NUM_MAX	(8)		// 2Dエフェクトの最大数

//-======================================
//-	前方宣言
//-======================================

class CMgrSysObj;

class CManagerObject;

class CStateGame;
class CStateBattle;

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

	static void SetPhase(CSysGamePhase::TYPE type);
	static CSysGamePhase::TYPE GetPhase(void);

	static CSysGamePhase *GetSysGamePhase(void);

	static CMgrSysObj *GetMgrSysObj(void);
	
	static CStateGame *GetStateGame(void);
	static CStateBattle *GetStateBattle(void);

	static CPause *GetPause(void);

private:

	void UpdateSetResult(void);
	void UpdateTimeEndResult(void);

	static CSysGamePhase *m_pSysGamePhase;	// ゲームフェーズのポインタ

	static CMgrSysObj *m_pMgrSysObj;		// システムオブジェクト管理のポインタ

	static CStateGame *m_pStateGame;		// ゲームステータス
	static CStateBattle *m_pStateBattle;	// 戦闘ステータス

	static CPause *m_pPause;				// ポーズ

	GAME m_game;							// ゲーム状態
};

#endif	// 二重インクルード防止の終了

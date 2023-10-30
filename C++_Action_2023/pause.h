
//-===============================================
//-
//-	ポーズの処理のヘッダー[pause.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PAUSE_H_		// このマクロが定義されなかったら
#define _PAUSE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	前方宣言
//-======================================

class CObj2dNone;

//-======================================
//-	クラス定義
//-======================================

class CPause : public CObject
{

public:

	typedef enum
	{
		TYPE_BG = 0,	// 背景
		TYPE_GAME,		// ゲーム
		TYPE_RETRY,		// リトライ
		TYPE_TITLE,		// タイトル
		TYPE_CURSOR,	// カーソル
		TYPE_MAX
	}TYPE;

	typedef enum
	{
		TYPE_SELECT_GAME = 0,	// ゲーム
		TYPE_SELECT_RETRY,		// リトライ
		TYPE_SELECT_TITLE,		// タイトル
		TYPE_SELECT_MAX,
	}TYPE_SELECT;

	CPause();
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause * Create(void);

	static CObj2dNone *GetObj2dNone(int nNum);

	TYPE_SELECT GetTypeSelect(void);

	bool GetOk(void);
private:

	static CObj2dNone *m_apObj2dNone[TYPE_MAX];	// 効果なし2Dオブジェクトのポインタ
	TYPE_SELECT m_typeSelect;					// 現在の選択の種類

	bool m_bOk;

};

#endif	// 二重インクルード防止の終了


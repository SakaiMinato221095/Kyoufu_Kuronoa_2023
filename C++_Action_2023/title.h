
//-===============================================
//-
//-	タイトルの処理のヘッダー[title.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _TITLE_H_		// このマクロが定義されなかったら
#define _TITLE_H_		// 二重インクルード帽子のマクロを定義

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

class CObj2dNone;

//-======================================
//-	クラス定義
//-======================================

class CTitle : public CScene
{

public:

	typedef enum
	{
		TYPE_NONE_2D_LOGO = 0,	// タイトルロゴ
		TYPE_NONE_2D_BUTTON,	// タイトルボタン
		TYPE_NONE_2D_MAX
	}TYPE_NONE_2D;

	CTitle();
	~CTitle();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static CPlayer *m_pPlayer;

	static CObj2dNone *m_apObj2dNone[TYPE_NONE_2D_MAX];
};

#endif	// 二重インクルード防止の終了

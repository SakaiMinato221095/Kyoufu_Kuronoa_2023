
//-===============================================
//-
//-	通常2Dオブジェクト処理のヘッダー[obj_2d_none.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJ_2D_NONE_H_		// このマクロが定義されなかったら
#define _OBJ_2D_NONE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

//-======================================
//-	クラス定義
//-======================================

class CObj2dNone : public CObject2d
{

public:

	// 文字のテクスチャ列挙型
	typedef enum
	{
		TEX_NULL = 0,		// なし
		TEX_TITLE_LOGO,		// タイトルロゴ
		TEX_TITLE_BUTTON,	// タイトルボタン
		//TEX_PAUSE_BG,		// ポーズの背景
		//TEX_PAUSE_GAME,		// ポーズのゲーム
		//TEX_PAUSE_RETRY,	// ポーズのリトライ
		//TEX_PAUSE_TITLE,	// ポーズのタイトル
		//TEX_PAUSE_CURSOR,	// ポーズのカーソル
		TEX_MAX
	}TEX;

	CObj2dNone(int nPriority = 3);
	~CObj2dNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dNone *Create(TEX tex, D3DXVECTOR3 pos,D3DXVECTOR3 size,D3DXCOLOR color);

private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号

};

#endif	// 二重インクルード防止の終了

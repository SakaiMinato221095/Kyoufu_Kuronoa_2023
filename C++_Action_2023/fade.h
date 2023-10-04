
//-===============================================
//-
//-	フェード処理のヘッダー[fade.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FADE_H_		// このマクロが定義されなかったら
#define _FADE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "manager.h"

#include "main.h"
#include "object.h"

#include "data.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CFade
{

public:

	typedef enum
	{
		STATE_NONE = 0,	// 何もしていない状態
		STATE_IN,		// フェードイン状態
		STATE_OUT,		// フェードアウト状態
		STATE_MAX
	}STATE;

	CFade();
	~CFade();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade *CFade::Create(void);

	virtual void SetVtx(void);

	void SetFade(CScene::MODE mode);
	STATE GetFade(void);

	CDataD3DXVECTOR3 m_dataPos;		// 位置
	CDataD3DXVECTOR3 m_dataSize;	// 大きさ
	CDataD3DXCOLOR m_dataColor;		// 色

private:

	void InitSet(
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファを格納
	STATE m_state;								// フェード状態
	CScene::MODE m_mode;						// モードを設定
};

#endif	// 二重インクルード防止の終了

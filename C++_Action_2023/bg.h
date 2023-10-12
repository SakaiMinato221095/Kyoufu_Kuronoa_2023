
//-===============================================
//-
//-	背景処理のヘッダー[bg.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _BG_H_		// このマクロが定義されなかったら
#define _BG_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "main.h"

#include "object2d.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CBg : public CObject2d
{

public:

	// 背景のテクスチャ列挙型
	typedef enum
	{
		TEX_TITLE = 0,		// タイトル
		TEX_RESULT,			// リザルト
		TEX_MAX
	}TEX;

	// テクスチャの頂点値情報
	typedef struct
	{
		D3DXVECTOR2 m_texPos;		// テクスチャの位置
		D3DXVECTOR2 m_texMove;		// テクスチャの移動量
	}VtxTexData;

	CBg(int nPriority = 0);
	~CBg();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg * Create(TEX tex);

	void Set(
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2 texPos = D3DXVECTOR2(0.0f,0.0f), 
		D3DXVECTOR2 texMove = D3DXVECTOR2(0.0f, 0.0f));

private:

	void SetVtx(void);

	void AddTexPos(void);

	void DestTexPos(void);

	VtxTexData m_vtxTexData;				// テクスチャの頂点値情報

	static int m_nTextureNldx[TEX_MAX];		// テクスチャ番号
};

#endif	// 二重インクルード防止の終了

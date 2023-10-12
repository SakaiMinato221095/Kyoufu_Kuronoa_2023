
//-===============================================
//-
//-	構成処理のヘッダー[renderer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _RENDERER_H_		// このマクロが定義されなかったら
#define _RENDERER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CRenderer
{

public:

	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAlphaBlend(bool bUse);
	void SetZTest(bool bUse);
	void SetAlphaTest(bool bUse);

	LPDIRECT3DDEVICE9 GetDevice(void);

private:

	LPDIRECT3D9 m_pD3D;						// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;			// Direct3Dデバイスへのポインタ
};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了
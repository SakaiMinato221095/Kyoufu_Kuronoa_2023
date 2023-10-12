
//-===============================================
//-
//-	テクスチャ管理処理のヘッダー[manager_texture.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MANAGER_TEXTURE_H_		// このマクロが定義されなかったら
#define _MANAGER_TEXTURE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

#define MANAGER_TEXTUTE_MAX	(2048)	// テクスチャの最大数

//-======================================
//-	クラス定義
//-======================================

class CManagerTexture
{

public:

	CManagerTexture();
	~CManagerTexture();

	HRESULT Load(HWND hWnd);
	void Unload(void);

	int Regist(const char *pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nldx);

private:

	LPDIRECT3DTEXTURE9 m_apTexture[MANAGER_TEXTUTE_MAX];	// テクスチャ
	static int m_nNumAll;									// 総数
};

#endif	// 二重インクルード防止の終了

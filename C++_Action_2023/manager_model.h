
//-===============================================
//-
//-	モデル管理処理のヘッダー[manager_model.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MANAGER_MODEL_H_		// このマクロが定義されなかったら
#define _MANAGER_MODEL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

#define MANAGER_MODEL_MAX	(1024)	// モデルの最大数

//-======================================
//-	クラス定義
//-======================================

class CManagerModel
{

public:

	typedef struct
	{
		int *m_nldxTexture;				// テクスチャの番号
		LPDIRECT3DTEXTURE9 *m_pTexture;	// テクスチャのポインタ（動的確保）
		LPD3DXMESH m_pMesh;				// メッシュの情報のポインタ
		LPD3DXBUFFER m_pBuffMat;		// マテリアルのポインタ
		DWORD m_dwNumMat;				// マテリアルの数
	}Model;

	CManagerModel();
	~CManagerModel();

	HRESULT Load(HWND hWnd);
	void Unload(void);

	int Regist(const char *pFilename);
	Model GetAddress(int nldx);

private:

	Model m_model[MANAGER_MODEL_MAX];	// モデル

	static int m_nNumAll;				// 総数
};

#endif	// 二重インクルード防止の終了

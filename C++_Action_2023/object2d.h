
//-===============================================
//-
//-	2Dオブジェクト処理のヘッダー[object2d.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJECT_2D_H_		// このマクロが定義されなかったら
#define _OBJECT_2D_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CObject2d : public CObject
{

public:

	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
	}VtxData;

	CObject2d(int nPriority = 3);
	~CObject2d();

	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(int nTextureNldx);

	static CObject2d *CObject2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	virtual void SetVtx(void);

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

	CObject2d::VtxData GetVtxData(void);
	void SetVtxData(CObject2d::VtxData vtxData);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	VtxData m_vtxData;							// 頂点値情報

	int m_nTextureNldxUse;						// テクスチャの番号

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファを格納
};

//-======================================
//- プロトタイプ宣言
//-======================================

#endif	// 二重インクルード防止の終了

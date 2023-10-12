
//================================================
//=
//= ビルボードオブジェクト処理のヘッター[object_billboard.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_BILLBOARD_H_	// このマクロが定義されなかったら
#define _OBJECT_BILLBOARD_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//=======================================
//=	クラス定義
//=======================================

// ビルボードオブジェクトのクラス
class CObjectBillboard : public CObject
{
public:

	// 頂点値情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
	}VtxData;

	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectBillboard *Create(void);

	void BindTexture(int nTextureNldx);

	void SetVtx(void);

	void SetVtxData(VtxData vtxData);
	VtxData GetVtxData(void);

private:

	VtxData m_vtxData;					// 頂点値情報

	int m_nTextureNldxUse;				// テクスチャの番号

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
};

#endif 
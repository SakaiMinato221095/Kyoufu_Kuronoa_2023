
//================================================
//=
//= 3Dオブジェクト処理のヘッター[object3d.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_3D_H_	//このマクロが定義されなかったら
#define _OBJECT_3D_H_	//二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	クラス定義
//=======================================

class CObject3d : public CObject
{
public:

	// 生成種類
	typedef enum
	{
		TYPE_CREATE_FIELD = 0,
		TYPE_CREATE_WALL,
		TYPE_CREATE_MAX
	}TYPE_CREATE;

	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 size;	// 大きさ
		D3DXCOLOR color;	// 色
	}VtxData;

	CObject3d(int nPriority = 3);;
	~CObject3d();

	HRESULT Init(TYPE_CREATE type,D3DXVECTOR3 pos,D3DXVECTOR3 size ,D3DXVECTOR3 rot ,D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3d *Create(TYPE_CREATE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);

	void BindTexture(int nTextureNldx);

	void SetVtxData(VtxData vtxData);
	VtxData GetVtxData(void);

	virtual void SetVtx(void);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);

	VtxData m_vtxData;					// 頂点値情報

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス

	int m_nTextureNldxUse;				// テクスチャの番号

	TYPE_CREATE m_typeCreate;			// 生成種類
};

#endif	// 二重インクルード防止の終了
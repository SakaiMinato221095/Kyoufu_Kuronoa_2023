
//=======================
//=
//= Xファイルオブジェクト処理のヘッター[object_x.h]
//= Author Sakai Minato
//=
//=======================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _OBJECT_X_H_	// このマクロが定義されなかったら
#define _OBJECT_X_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	クラス定義
//=======================================

// Xファイルオブジェクトのクラス
class CObjectX : public CObject
{
public:

	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 size;	// サイズ
	}VtxData;

	CObjectX(int nPriority = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX *Create(void);

	void BindModel(int nModelNldx, int nModelNum);

	void SetVtxData(VtxData vtxData);
	VtxData GetVtxData(void);

	virtual void SetModel(int nModelNldx);

private:
	
	VtxData m_vtxData;		// 頂点値情報

	int m_nModelNldxUse;	// モデル番号
	
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
};

#endif	// 二重インクルード防止の終了
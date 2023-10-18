
//-===============================================
//-
//- オブジェクトブロック処理のヘッダー[obj_black.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _BLOCK_H_		// このマクロが定義されなかったら
#define _BLOCK_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "objectx_none.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	前方宣言
//=======================================

class CColl;

//-======================================
//-	クラス定義
//-======================================

// ブロックのクラス
class CObjBlock : public CObjectXNone
{

public:

	CObjBlock(int nPriority = 3);
	~CObjBlock();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjBlock * Create(MODEL model,D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void InitSet(void);

	CColl *m_pColl;		// 当たり判定の番号

};

#endif	// 二重インクルード防止の終了

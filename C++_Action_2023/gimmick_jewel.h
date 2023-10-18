
//-===============================================
//-
//-	宝石ギミック処理のヘッダー[gimmick_jewel.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GIMMICK_JEWEL_H_		// このマクロが定義されなかったら
#define _GIMMICK_JEWEL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "gimmick.h"

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

// 宝石ギミックのクラス
class CGimmickJewel : public CGimmick
{

public:

	// 効果の種類
	typedef enum
	{
		TYPE_EFFECT_NONE = 0,	// 効果なし
		TYPE_EFFECT_SPEED_UP,	// 速度上昇
		TYPE_EFFECT_MAX
	}TYPE_EFFECT;

	CGimmickJewel(int nPriority = 3);
	~CGimmickJewel();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGimmickJewel * Create(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void InitSet(TYPE_EFFECT typeEffect);

	void PlayerPlus(void);

	TYPE_EFFECT m_type;	// 効果の種類

	CColl *m_pColl;		// 当たり判定の番号

};

#endif	// 二重インクルード防止の終了
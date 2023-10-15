
//-===============================================
//-
//-	風だまの処理のヘッダー[bullet.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _KAZEDAMA_H_		// このマクロが定義されなかったら
#define _KAZEDAMA_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_billboard.h"

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

class CKazedama : public CObjectBillboard
{

public:

	// テクスチャ
	typedef enum
	{
		TEX_NULL = 0,	// なし
		TEX_MAX
	}TEX;

	// 状態
	typedef enum
	{
		STATE_ACTIVE = 0,	// 活動状態
		STATE_RETURN,		// 帰還状態
		STATE_LOST,			// 消滅状態
		STATE_HIT,			// ヒット状態
		STATE_MAX
	}STATE;
	
	// 向きの種類
	typedef enum
	{
		TYPE_ROT_LEFT = 0,	// 左
		TYPE_ROT_RIGHT,		// 右
		ROT_MAX
	}TYPE_ROT;

	// 情報値
	typedef struct
	{
		D3DXVECTOR3 posParent;	// 親の位置
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 moveAccum;	// 移動の蓄積値
		STATE state;			// 状態
		TYPE_ROT typeRot;		// 向きの種類
	}Data;

	CKazedama(int nPriority = 3);
	~CKazedama();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot);

	static CKazedama * Create(TEX tex);

private:

	void UpdateData(void);
	void UpdateMove(void);

	void Active(void);
	void Return(void);
	void Lost(void);
	void Hit(void);

	static int m_nTextureNldx[TEX_MAX];		// テクスチャの番号

	Data m_data;							// 情報値

	CColl *m_pColl;							// 当たり判定の情報
	
};

#endif	// 二重インクルード防止の終了

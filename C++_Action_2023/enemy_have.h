
//-===============================================
//-
//-	保持敵の処理のヘッダー[enemy_have.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_HAVE_H_		// このマクロが定義されなかったら
#define _ENEMY_HAVE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_x.h"

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

class CEnemyHave : public CObjectX
{

public:

	typedef enum
	{
		MODEL_ALIEN_000 = 0,	// エイリアン_000
		MODEL_MAX
	}MODEL;

	// 状態
	typedef enum
	{
		STATE_OBTAIN = 0,	// 獲得状態
		STATE_WAIT,			// 待機状態
		STATE_SHOT,			// 投げる状態
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
		STATE state;			// 状態

		D3DXVECTOR3 move;		// 移動量
		int nLife;				// 体力
		int nLifeCut;			// 体力カウント
		TYPE_ROT typeRot;		// 向きの種類
	}Data;

	CEnemyHave();
	~CEnemyHave();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemyHave * Create(MODEL model, STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	int GetModel(void);
	void SetModel(int nModelNldx);

	void UpdateObtain(void);
	void UpdateWait(void);
	bool UpdateShot(void);

	void SetShot(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE_ROT typeRot);

private:

	void InitSet(STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	static int m_nModelNldx[MODEL_MAX];		// モデルの番号

	MODEL m_model;							// 自身のモデル

	Data m_data;							// 情報値

	CColl *m_pColl;							// 当たり判定の番号
};

#endif	// 二重インクルード防止の終了
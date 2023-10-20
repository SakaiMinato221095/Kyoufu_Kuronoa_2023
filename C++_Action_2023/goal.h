
//-===============================================
//-
//-	ゴール処理のヘッダー[goal.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _GOAL_H_		// このマクロが定義されなかったら
#define _GOAL_H_		// 二重インクルード帽子のマクロを定義

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

// ギミックのクラス
class CGoal : public CObjectX
{

public:

	// モデルの列挙型
	typedef enum
	{
		MODEL_GOAL_000 = 0,	// ゴール000
		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CGoal(int nPriority = 3);
	~CGoal();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGoal * Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	void InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	MODEL m_model;								// 自身のモデル
	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
	static int m_nModelNldx[MODEL_MAX];			// モデルの番号

	CColl *m_pColl;		// 当たり判定の番号

};

#endif	// 二重インクルード防止の終了


//-===============================================
//-
//-	敵の処理のヘッダー[enemy.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _ENEMY_H_		// このマクロが定義されなかったら
#define _ENEMY_H_		// 二重インクルード帽子のマクロを定義

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

// 敵のクラス
class CEnemy : public CObjectX
{

public:

	typedef enum
	{
		MODEL_ALIEN_000 = 0,			// エイリアン_000
		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL modelType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEnemy *Create(MODEL modelType,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	void InitSet(MODEL modelType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static int m_nModelNldx[MODEL_MAX];			// モデルの番号
	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
	
	MODEL m_model;		// 自身のモデル

	D3DXVECTOR3 m_move;	// 移動量

	CColl *m_pColl;		// 当たり判定の情報

};

#endif	// 二重インクルード防止の終了

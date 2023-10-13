
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

	HRESULT Init(MODEL modelType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos);

	static CEnemy *Create(MODEL modelType);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	static int m_nModelNldx[MODEL_MAX];			// モデルの番号
	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
	
	MODEL m_model;		// 自身のモデル

	D3DXVECTOR3 m_move;	// 移動量

	int m_nCollNldx;	// 当たり判定の番号
};

#endif	// 二重インクルード防止の終了

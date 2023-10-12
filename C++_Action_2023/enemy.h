
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

#include "data.h"

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
		MODEL_TYPE_ALIEN_000 = 0,			// エイリアン_000
		MODEL_TYPE_ALIEN_001,				// エイリアン_001
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL_TYPE modelType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_TYPE_MAX];	// モデルの番号
	static ModelData m_modelData[MODEL_TYPE_MAX];		// モデルの情報

	CDataD3DXVECTOR3 m_dataMove;	// 移動量
	CDataInt m_nDataLife;			// 体力

private:

	MODEL_TYPE m_model;	// 自身のモデル

};

#endif	// 二重インクルード防止の終了

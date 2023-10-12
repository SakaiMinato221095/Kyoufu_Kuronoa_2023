
//-===============================================
//-
//-	効果なしのXファイルオブジェクト処理のヘッダー[objectx_none.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJECT_X_NONE_H_		// このマクロが定義されなかったら
#define _OBJECT_X_NONE_H_		// 二重インクルード帽子のマクロを定義

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

// アイテムのクラス
class CObjectXNone : public CObjectX
{

public:

	// モデルの列挙型
	typedef enum
	{
		MODEL_SAKURA_000,			// 桜
		MODEL_MAX
	}MODEL;

	// モデル情報
	typedef struct
	{
		D3DXVECTOR3 size;	// 大きさ
	}ModelData;

	CObjectXNone(int nPriority = 3);
	~CObjectXNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	void InitSet(MODEL model);

	MODEL m_model;	// 自身のモデル
	static ModelData m_modelData[MODEL_MAX];	// モデルの情報
	static int m_nModelNldx[MODEL_MAX];			// モデルの番号
};

#endif	// 二重インクルード防止の終了


//-===============================================
//-
//-	スカイボックス処理のヘッダー[skybox.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _SKYBOX_H_		// このマクロが定義されなかったら
#define _SKYBOX_H_		// 二重インクルード帽子のマクロを定義

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
class CSkybox : public CObjectX
{

public:

	// モデルの列挙型
	typedef enum
	{
		MODEL_SKYBOX_000 = 0,
		MODEL_MAX
	}MODEL;

	CSkybox(int nPriority = 3);
	~CSkybox();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSkybox * Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static int m_nModelNldx[MODEL_MAX];		// モデルの番号

	MODEL m_model;							// 自身のモデル
};

#endif	// 二重インクルード防止の終了
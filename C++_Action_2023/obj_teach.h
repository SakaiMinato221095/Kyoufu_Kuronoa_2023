
//-===============================================
//-
//-	教えるオブジェクト処理のヘッダー[obj_teach.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _OBJ_TEACH_H_		// このマクロが定義されなかったら
#define _OBJ_TEACH_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object_billboard.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// 教えるオブジェクトのクラス
class CObjTeach : public CObjectBillboard 
{

public:

	// モデルの列挙型
	typedef enum
	{
		TEX_TEACH_MOVE = 0,			// 移動 
		TEX_TEACH_JUMP,				// ジャンプ
		TEX_TEACH_KAZEDAMA,			// 風だま
		TEX_TEACH_DOUBLE_JUMP,		// 二段ジャンプ
		TEX_TEACH_SHOT,				// ショット
		TEX_MAX
	}TEX;

	CObjTeach(int nPriority = 3);
	~CObjTeach();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjTeach *Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

private:

	void InitSet(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	static int m_nTextureNldx[TEX_MAX];		// テクスチャの番号
};

#endif	// 二重インクルード防止の終了


//-===============================================
//-
//-	3D地面処理のヘッダー[wall.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _WALL_H_		// このマクロが定義されなかったら
#define _WALL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object3d.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// アイテムのクラス
class CObj3dWall : public CObject3d
{

public:

	// フィールドのテクスチャの列挙型
	typedef enum
	{
		TEX_NULL = 0,			// テクスチャのなし
		TEX_BLOCKADE_WALL_000,	// 封鎖壁000のテクスチャ
		TEX_DARK_WALL_000,		// 闇壁000のテクスチャ
		TEX_MAX
	}TEX;

	CObj3dWall(int nPriority = 3);
	~CObj3dWall();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj3dWall * Create(TEX tex,D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);

private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャの番号

};

#endif	// 二重インクルード防止の終了
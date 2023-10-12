
//-===============================================
//-
//-	3D地面処理のヘッダー[obj_3d_field.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FIELD_H_		// このマクロが定義されなかったら
#define _FIELD_H_		// 二重インクルード帽子のマクロを定義

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
class CObj3dField : public CObject3d
{

public:

	// フィールドのテクスチャの列挙型
	typedef enum
	{
		TEX_NULL = 0,			// テクスチャのなし
		TEX_WHITE_TILE_000,		// 白い床000のテクスチャ
		TEX_ROAD_000,			// 道路000のテクスチャ
		TEX_ASPHALT_000,		// アスファルト000のテクスチャ
		TEX_GLASS_000,			// 草床000のテクスチャ
		TEX_MAX
	}TEX;

	CObj3dField(int nPriority = 3);;
	~CObj3dField();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj3dField * Create(TEX tex);

	void Set(
		D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,
		D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

private:

	static int m_nTextureNldx[TEX_MAX];		// テクスチャの番号

};

#endif	// 二重インクルード防止の終了

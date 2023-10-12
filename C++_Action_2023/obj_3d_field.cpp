
//-===============================================
//-
//-	地面処理[obj_3d_field.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "obj_3d_field.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 3D地面のテクスチャのコンスト定義
const char *pTextureField[] =
{
	NULL,										// テクスチャなし
	"data\\TEXTURE\\WhiteTile000.jpg",			// フィールドのテクスチャ
	"data\\TEXTURE\\road000.png",				// 道路のテクスチャ
	"data\\TEXTURE\\asphalt000.jpg",			// アスファルトのテクスチャ
	"data\\TEXTURE\\field_glass000.jpg",		// 草床のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CObj3dField::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D地面のコンストラクタ
//-------------------------------------
CObj3dField::CObj3dField(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D地面のデストラクタ
//-------------------------------------
CObj3dField::~CObj3dField()
{

}

//-------------------------------------
//- 3D地面のテクスチャの読み込み
//-------------------------------------
HRESULT CObj3dField::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// テクスチャ管理の有無を判定
	if (pManagerTexture == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureField[nCount]);

		// テクスチャの読み込み成功の有無を確認
		if (m_nTextureNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 3D地面の読み込んだテクスチャの破棄
//-------------------------------------
void CObj3dField::Unload(void)
{

}
//-------------------------------------
//- 3D地面の初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CObj3dField::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 3Dオブジェクトの初期化
	CObject3d::Init(CObject3d::TYPE_CREATE_FIELD);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 3D地面の終了処理
//-------------------------------------
void CObj3dField::Uninit(void)
{
	// 3Dオブジェクトの終了
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D地面の更新処理
//-------------------------------------
void CObj3dField::Update(void)
{
	// 3Dオブジェクトの更新処理
	CObject3d::Update();
}

//-------------------------------------
//- 3D地面の描画処理
//-------------------------------------
void CObj3dField::Draw(void)
{
	// 3Dオブジェクトの描画処理
	CObject3d::Draw();
}

//-------------------------------------
//- 3D地面の生成処理
//-------------------------------------
CObj3dField *CObj3dField::Create(TEX tex)
{
	// フィールドのポインタを宣言
	CObj3dField *pCObj3dField = new CObj3dField(2);

	// 生成の成功の有無を判定
	if (pCObj3dField != NULL)
	{
		// 初期化処理
		if (FAILED(pCObj3dField->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObj3dField == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// フィールドのポインタを返す
	return pCObj3dField;
}

//-------------------------------------
//- 3D地面の設定処理
//-------------------------------------
void CObj3dField::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,D3DXCOLOR color)
{
	// 情報取得（3Dオブジェクト）
	CObject3d::VtxData vtxData = GetVtxData();	// 頂点値情報

	// 情報更新
	vtxData.pos = pos;		// 位置
	vtxData.size = size;	// 大きさ
	vtxData.rot = rot;		// 向き
	vtxData.color = color;	// 色

	// 情報更新（3Dオブジェクト）
	SetVtxData(vtxData);	// 頂点値情報

	// 頂点情報の設定処理
	SetVtx();
}

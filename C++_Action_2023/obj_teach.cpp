
//================================================
//=
//=	教えるオブジェクトの処理[obj_teach.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "obj_teach.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//= コンスト定義
//=======================================

// 教えるテクスチャのコンスト定義
const char *pTextureTeach[] =
{
	"data\\TEXTURE\\Teach\\TeachMove.png",			// 移動
	"data\\TEXTURE\\Teach\\TeachJump.png",			// ジャンプ
	"data\\TEXTURE\\Teach\\TeachKazedama.png",		// 風だまアクション
	"data\\TEXTURE\\Teach\\TeachDoubleJump.png",	// 二段ジャンプ
	"data\\TEXTURE\\Teach\\TeachShot.png",			// 発射
};

//-======================================
//-	静的変数宣言
//-======================================

int CObjTeach::m_nTextureNldx[TEX_MAX] = {};			// テクスチャ

//-------------------------------------
//-	教えるオブジェクトのコンストラクタ
//-------------------------------------
CObjTeach::CObjTeach(int nPriority) : CObjectBillboard(nPriority)
{

}

//-------------------------------------
//-	教えるオブジェクトのデストラクタ
//-------------------------------------
CObjTeach::~CObjTeach()
{

}

//-------------------------------------
//- 教えるオブジェクトのテクスチャの読み込み
//-------------------------------------
HRESULT CObjTeach::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureTeach[nCount]);

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
//- 教えるオブジェクトの読み込んだテクスチャの破棄
//-------------------------------------
void CObjTeach::Unload(void)
{

}

//-------------------------------------
//- 教えるオブジェクトの初期化処理
//-------------------------------------
HRESULT CObjTeach::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 初期設定処理
	InitSet(tex,pos, size, color);

	// ビルボードオブジェクトの初期化
	CObjectBillboard::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 教えるオブジェクトの終了処理
//-------------------------------------
void CObjTeach::Uninit(void)
{
	// ビルボードオブジェクトの終了
	CObjectBillboard::Uninit();
}

//-------------------------------------
//- 教えるオブジェクトの更新処理
//-------------------------------------
void CObjTeach::Update(void)
{
	// ビルボードオブジェクトの更新処理
	CObjectBillboard::Update();
}

//-------------------------------------
//- 教えるオブジェクトの描画処理
//-------------------------------------
void CObjTeach::Draw(void)
{
	// デバイスを取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	// デバイスの情報取得の成功を判定
	if (pRenderer == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// Zテストの設定
	pRenderer->SetZTest(true);

	// アルファテストの設定
	pRenderer->SetAlphaTest(true);

	// 教えるオブジェクトの描画処理
	CObjectBillboard::Draw();

	// Zテストの解除
	pRenderer->SetZTest(false);

	// アルファテストの解除
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- 教えるオブジェクトの生成処理
//-------------------------------------
CObjTeach *CObjTeach::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 教えるオブジェクトの生成
	CObjTeach *pCObjTeach = DBG_NEW CObjTeach(3);

	// 生成の成功の有無を判定
	if (pCObjTeach != NULL)
	{
		// 初期化処理
		if (FAILED(pCObjTeach->Init(tex, pos, size, color)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObjTeach == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 教えるオブジェクトのポインタを返す
	return pCObjTeach;
}

//-------------------------------------
//- 教えるオブジェクトの設定処理
//-------------------------------------
void CObjTeach::InitSet(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 変数を宣言（情報取得）
	CObjectBillboard::VtxData vtxData = GetVtxData();

	vtxData.pos = pos;			// 位置
	vtxData.size = size;		// 大きさ
	vtxData.color = color;		// 色

	// 情報更新
	SetVtxData(vtxData);
}
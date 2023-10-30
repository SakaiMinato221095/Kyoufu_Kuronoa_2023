
//================================================
//=
//=	通常2Dオブジェクト処理[obj_2d_none.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "obj_2d_none.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//= コンスト定義
//=======================================

// 通常オブジェクトテクスチャのコンスト定義
const char *pTextureObj2dNone[] =
{
	NULL,										// なし
	"data\\TEXTURE\\TitleLogo000.png",			// タイトルロゴのテクスチャ
	"data\\TEXTURE\\TitleButton000.png",		// タイトルボタンのテクスチャ
	"data\\TEXTURE\\BgPause.jpg",				// ポーズの背景
	"data\\TEXTURE\\PauseGame.png",				// ポーズのゲーム
	"data\\TEXTURE\\PauseRetryText.png",		// ポーズのリトライ
	"data\\TEXTURE\\PauseQuitText.png",			// ポーズのタイトル
	"data\\TEXTURE\\GameTitleCursor.png",		// ポーズのカーソル
};											   

//=======================================
//=	静的変数宣言
//=======================================

int CObj2dNone::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	通常2Dオブジェクトのコンストラクタ
//-------------------------------------
CObj2dNone::CObj2dNone(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	通常2Dオブジェクトのデストラクタ
//-------------------------------------
CObj2dNone::~CObj2dNone()
{

}

//-------------------------------------
//- 通常2Dオブジェクトの読み込み処理
//-------------------------------------
HRESULT CObj2dNone::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureObj2dNone[nCount]);

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
//- 背景の読み込んだテクスチャの破棄
//-------------------------------------
void CObj2dNone::Unload(void)
{

}

//-------------------------------------
//- 通常2Dオブジェクトの初期化処理
//-------------------------------------
HRESULT CObj2dNone::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 使用テクスチャの設定
	BindTexture(m_nTextureNldx[tex]);

	// 2Dオブジェクトの初期化
	CObject2d::Init(pos,size,color);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 通常2Dオブジェクトの終了処理
//-------------------------------------
void CObj2dNone::Uninit(void)
{
	// 2Dオブジェクトの終了処理
	CObject2d::Uninit();
}

//-------------------------------------
//- 通常2Dオブジェクトの更新処理
//-------------------------------------
void CObj2dNone::Update(void)
{
	// 頂点情報の設定処理
	SetVtx();
}

//-------------------------------------
//- 通常2Dオブジェクトの描画処理
//-------------------------------------
void CObj2dNone::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//-	通常2Dオブジェクトの生成処理
//-------------------------------------
CObj2dNone * CObj2dNone::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 生成
	CObj2dNone *pObj2dNone = DBG_NEW CObj2dNone(7);

	// 生成の成功の有無を判定
	if (pObj2dNone != NULL)
	{
		// 初期化処理
		if (FAILED(pObj2dNone->Init(tex,pos,size,color)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObj2dNone == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 通常2Dオブジェクトのポインタを返す
	return pObj2dNone;
}
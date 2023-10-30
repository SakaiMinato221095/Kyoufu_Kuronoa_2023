
//-===============================================
//-
//-	背景処理[bg.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "bg.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

#include "title.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//= コンスト定義
//=======================================

// 背景テクスチャのコンスト定義
const char *pTextureBg[] =
{
	"data\\TEXTURE\\Title.png",		// タイトルのテクスチャ
	"data\\TEXTURE\\Result.png",	// リザルトのテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CBg::m_nTextureNldx[TEX_MAX] = {};	// テクスチャ

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CBg::CBg(int nPriority) : CObject2d(nPriority)
{
	ZeroMemory(&m_vtxTexData, sizeof(m_vtxTexData));
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CBg::~CBg()
{

}

//-------------------------------------
//- 背景のテクスチャの読み込み
//-------------------------------------
HRESULT CBg::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureBg[nCount]);

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
void CBg::Unload(void)
{

}

//-------------------------------------
//- 背景の初期化処理
//-------------------------------------
HRESULT CBg::Init(TEX tex)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 2Dオブジェクトの初期化
	CObject2d::Init(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	// 頂点情報の設定処理
	SetVtx();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 背景の終了処理
//-------------------------------------
void CBg::Uninit(void)
{
	// 2Dオブジェクトの終了
	CObject2d::Uninit();
}

//-------------------------------------
//- 背景の更新処理
//-------------------------------------
void CBg::Update(void)
{
	// テクスチャ座標の更新処理
	AddTexPos();

	// テクスチャ座標の補正処理
	DestTexPos();

	// 頂点情報の設定処理
	SetVtx();
}

//-------------------------------------
//- 背景の描画処理
//-------------------------------------
void CBg::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//- 背景の生成処理
//-------------------------------------
CBg *CBg::Create(TEX tex)
{
	// 背景のポインタを宣言
	CBg *pCBg = DBG_NEW CBg;

	// 生成の成功の有無を判定
	if (pCBg != NULL)
	{
		// 初期化処理 if(背景の初期化成功の有無を判定)
		if (FAILED(pCBg->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCBg == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 背景のポインタを返す
	return pCBg;
}

//-------------------------------------
//- 背景の設定処理
//-------------------------------------
void CBg::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXCOLOR color, D3DXVECTOR2 texPos, D3DXVECTOR2 texMove)
{
	// 情報代入（頂点値情報）
	CObject2d::VtxData vtxData = GetVtxData();

	vtxData.pos = pos;
	vtxData.size = size;
	vtxData.color = color;

	// 情報更新（頂点値情報）
	SetVtxData(vtxData);

	// 頂点テクスチャ情報
	m_vtxTexData.m_texPos = texPos;
	m_vtxTexData.m_texMove = texMove;
}

//-------------------------------------
//- 背景の頂点情報設定
//-------------------------------------
void CBg::SetVtx(void)
{
	// 情報代入（頂点値情報）
	CObject2d::VtxData vtxData = GetVtxData();

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = vtxData.pos;		// 位置
	D3DXVECTOR3 size = vtxData.size;	// 大きさ
	D3DXCOLOR color = vtxData.color;	// 色

	D3DXVECTOR2 texPos = m_vtxTexData.m_texPos;		// テクスチャ位置
	D3DXVECTOR2 texMove = m_vtxTexData.m_texMove;	// テクスチャ移動量

	// 頂点バッファの取得
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// 頂点バッファ取得成功の有無を判定
	if (vtxBuff == NULL)
	{// 失敗時

		// 頂点情報設定を抜ける
		return;
	}

	// 2D頂点情報のポインタを宣言
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファをロックし、頂点情報のポインタを取得
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	// 頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーを設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// テクスチャの座標を設定
	pVtx[0].tex = D3DXVECTOR2(
		0.0f + texPos.x,
		0.0f + texPos.y);

	pVtx[1].tex = D3DXVECTOR2(
		1.0f + texPos.x,
		0.0f + texPos.y);

	pVtx[2].tex = D3DXVECTOR2(
		0.0f + texPos.x,
		1.0f + texPos.y);

	pVtx[3].tex = D3DXVECTOR2(
		1.0f + texPos.x,
		1.0f + texPos.y);

	// 頂点バッファをアンロックする
	vtxBuff->Unlock();
}

//-------------------------------------
//- 背景のテクスチャ座標の加算処理
//-------------------------------------
void CBg::AddTexPos(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR2 texPos = m_vtxTexData.m_texPos;		// テクスチャ位置
	D3DXVECTOR2 texMove = m_vtxTexData.m_texMove;	// テクスチャ移動量

	// テクスチャ位置に移動量を加算
	texPos += texMove;

	// 情報更新
	m_vtxTexData.m_texPos = texPos;		// テクスチャ位置
	m_vtxTexData.m_texMove = texMove;	// テクスチャ移動量
}

//-------------------------------------
//- 背景のテクスチャ座標の補正
//-------------------------------------
void CBg::DestTexPos(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR2 texPos = m_vtxTexData.m_texPos;		// テクスチャ位置

	// 横のテクスチャ位置の判定
	if (texPos.x > 1.0f)
	{
		// 1.0fを超えた場合0.0fにする
		texPos.x = 0.0f;
	}
	else if (texPos.x < 0.0f)
	{
		// 0.0fを下回った場合1.0fにする
		texPos.x = 1.0f;
	}

	// 縦のテクスチャ位置の判定
	if (texPos.y > 1.0f)
	{
		// 1.0fを超えた場合0.0fにする
		texPos.y = 0.0f;
	}
	else if (texPos.y < 0.0f)
	{
		// 0.0fを下回った場合1.0fにする
		texPos.y = 1.0f;
	}

	// 情報更新
	m_vtxTexData.m_texPos = texPos;		// テクスチャ位置
}
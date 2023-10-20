
//================================================
//=
//=	数字処理[number.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "number.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//= コンスト定義
//=======================================

// 背景テクスチャのコンスト定義
const char *pTextureNumber[] =
{
	"data\\TEXTURE\\number_000.png",	// 数字_000（金色）のテクスチャ
	"data\\TEXTURE\\number_001.png",	// 数字_001（深緑色）のテクスチャ
};

//=======================================
//=	静的変数宣言
//=======================================

int CNumber::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	数字のコンストラクタ
//-------------------------------------
CNumber::CNumber(int nPriority) : CObject2d(nPriority)
{
	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	数字のデストラクタ
//-------------------------------------
CNumber::~CNumber()
{

}

//-------------------------------------
//- 数字の読み込み処理
//-------------------------------------
HRESULT CNumber::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureNumber[nCount]);

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
void CNumber::Unload(void)
{

}

//-------------------------------------
//- 数字の初期化処理
//-------------------------------------
HRESULT CNumber::Init(TEX tex)
{
	// 使用テクスチャの設定
	BindTexture(m_nTextureNldx[tex]);

	// 2Dオブジェクトの初期化
	CObject2d::Init();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 数字の終了処理
//-------------------------------------
void CNumber::Uninit(void)
{
	// 2Dオブジェクトの終了処理
	CObject2d::Uninit();
}

//-------------------------------------
//- 数字の更新処理
//-------------------------------------
void CNumber::Update(void)
{
	// 頂点情報の設定処理
	SetVtx();
}

//-------------------------------------
//- 数字の描画処理
//-------------------------------------
void CNumber::Draw(void)
{
	// 2Dオブジェクトの描画処理
	CObject2d::Draw();
}

//-------------------------------------
//-	数字の生成処理
//-------------------------------------
CNumber *CNumber::Create(TEX tex)
{
	// 数字の生成
	CNumber *pNumber = DBG_NEW CNumber(7);

	// 生成の成功の有無を判定
	if (pNumber != NULL)
	{
		// 初期化処理
		if (FAILED(pNumber->Init(tex)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pNumber == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 数字のポインタを返す
	return pNumber;
}

//-------------------------------------
//- 数字の頂点情報設定
//-------------------------------------
void CNumber::SetVtx(void)
{
	// 変数宣言（情報の取得）
	D3DXVECTOR3 pos = GetVtxData().pos;		// 位置情報
	D3DXVECTOR3 size = GetVtxData().size;	// 大きさ
	D3DXCOLOR color = GetVtxData().color;	// 色

	// 頂点バッファをポインタを宣言
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
	pVtx[0].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 0), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 0), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 1), 1.0f);

	// 頂点バッファをアンロックする
	vtxBuff->Unlock();
}

//-------------------------------------
//- 数字の値情報設定
//-------------------------------------
void CNumber::SetData(Data data)
{
	m_data = data;
}

//-------------------------------------
//- 数字の値情報設定
//-------------------------------------
CNumber::Data CNumber::GetData(void)
{
	return m_data;
}


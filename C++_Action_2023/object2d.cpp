
//-===============================================
//-
//-	2Dオブジェクト処理[object2d.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "object2d.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CObject2d::CObject2d(int nPriority) : CObject(nPriority)
{
	// 値をクリア
	ZeroMemory(&m_vtxData, sizeof(m_vtxData));

	m_nTextureNldxUse = 0;
	m_pVtxBuff = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CObject2d::~CObject2d()
{

}

//-------------------------------------
//- 2Dオブジェクトの初期化処理
//-------------------------------------
HRESULT CObject2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// 初期設定処理
	InitSet(pos,size,color);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファ生成成功の有無を判定
	if (m_pVtxBuff == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;

	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 2Dオブジェクトの終了処理
//-------------------------------------
void CObject2d::Uninit(void)
{
	// 頂点バッファの有無を判定
	if (m_pVtxBuff != NULL)
	{
		// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- 2Dオブジェクトの更新処理
//-------------------------------------
void CObject2d::Update(void)
{
	// 2Dオブジェクトの頂点情報設定
	SetVtx();
}

//-------------------------------------
//- 2Dオブジェクトの描画処理
//-------------------------------------
void CObject2d::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 描画処理を抜ける
		return;
	}
	
	// テクスチャ管理の取得
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// テクスチャ管理の情報取得の成功を判定
	if (pManagerTexture == NULL)
	{// 失敗時

		// 描画処理を抜ける
		return;
	}

	// 頂点情報の描画
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(
			0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(
			0,
			pManagerTexture->GetAddress(m_nTextureNldxUse));

		// 2Dオブジェクトの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			0,								//描画する最初の頂点インデックス
			2);								//プリミティブの（ポリゴン）数
	}
}

//-------------------------------------
//- 2Dオブジェクトのテクスチャ割当
//-------------------------------------
void CObject2d::BindTexture(int nTextureNldx)
{
	// テクスチャの番号割当
	m_nTextureNldxUse = nTextureNldx;
}

//-------------------------------------
//- 2Dオブジェクトの生成処理
//-------------------------------------
CObject2d * CObject2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 2Dオブジェクトの生成
	CObject2d *pObject2d = DBG_NEW CObject2d(3);

	// 生成の成功の有無を判定
	if (pObject2d != NULL)
	{
		// 初期化処理
		if (FAILED(pObject2d->Init(pos,size,color)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObject2d == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// オブジェクトの頂点情報設定
	pObject2d->SetVtx();

	// 2Dオブジェクトのポインタを返す
	return pObject2d;
}

//-------------------------------------
//- 2Dオブジェクトの頂点情報設定
//-------------------------------------
void CObject2d::SetVtx(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_vtxData.pos;	// 位置
	D3DXVECTOR3 size = m_vtxData.size;	// 大きさ
	D3DCOLOR color = m_vtxData.color;	// 色

	// 2D頂点情報のポインタを宣言
	VERTEX_2D *pVtx = NULL;

	// 頂点バッファをロックし、頂点情報のポインタを取得
	m_pVtxBuff->Lock(
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// 情報更新
	m_vtxData.pos = pos;		// 位置
	m_vtxData.size = size;		// 大きさ
	m_vtxData.color = color;	// 色
}

//-------------------------------------
//- 2Dオブジェクトの頂点バッファ取得
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 CObject2d::GetVtxBuff(void)
{
	// 頂点バッファを返す
	return m_pVtxBuff;
}

//-------------------------------------
//- 2Dオブジェクトの頂点値情報取得処理
//-------------------------------------
CObject2d::VtxData CObject2d::GetVtxData(void)
{
	// 頂点値情報
	return m_vtxData;
}

//-------------------------------------
//- 2Dオブジェクトの頂点値情報設定処理
//-------------------------------------
void CObject2d::SetVtxData(CObject2d::VtxData vtxData)
{
	m_vtxData = vtxData;
}

//-------------------------------------
//- 2Dオブジェクトの初期設定処理
//-------------------------------------
void CObject2d::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_vtxData.pos = pos;
	m_vtxData.size = size;
	m_vtxData.color = color;
}

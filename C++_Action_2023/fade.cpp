
//-===============================================
//-
//-	フェード処理[fade.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "fade.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	マクロ定義
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CFade::CFade()
{
	// 値をクリア
	m_pVtxBuff = NULL;
	m_state = STATE_NONE;
	m_mode = CScene::MODE(0);
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CFade::~CFade()
{

}

//-------------------------------------
//- フェードの初期化処理
//-------------------------------------
HRESULT CFade::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

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

	// 初期設定処理
	InitSet();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- フェードの終了処理
//-------------------------------------
void CFade::Uninit(void)
{
	// 頂点バッファの有無を判定
	if (m_pVtxBuff != NULL)
	{
		// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//-------------------------------------
//- フェードの更新処理
//-------------------------------------
void CFade::Update(void)
{
	// 変数宣言（情報取得）
	D3DXCOLOR color = m_dataColor.Get();		// 色

	if (m_state == STATE_OUT)
	{// フェードアウト状態

		// 透明度を加算
		color.a += 0.049f;

		// 透明度の判定
		if (color.a >= 1.0f)
		{
			// 透明度の設定
			color.a = 1.0f;

			// フェード状態に変更
			m_state = STATE_IN;

			// モードを設定
			CManager::SetMode(m_mode);
		}
	}
	else if (m_state == STATE_IN)
	{// フェードイン状態

	 // 透明度を減算
		color.a -= 0.049f;

		// 透明度の判定
		if (color.a <= 0.0f)
		{
			// 透明度の設定
			color.a = 0.0f;

			// 何もしない状態に変更
			m_state = STATE_NONE;
		}
	}

	// 情報更新
	m_dataColor.Set(color);		// 色

	// フェードの頂点情報設定
	SetVtx();
}

//-------------------------------------
//- フェードの描画処理
//-------------------------------------
void CFade::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
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
			NULL);

		// フェードの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			//プリミティブの種類
			0,								//描画する最初の頂点インデックス
			2);								//プリミティブの（ポリゴン）数
	}
}

//-------------------------------------
//- フェードの生成処理
//-------------------------------------
CFade *CFade::Create(void)
{
	// フェードの生成
	CFade *pFade = DBG_NEW CFade;

	// 生成の成功の有無を判定
	if (pFade != NULL)
	{
		// 初期化処理
		if (FAILED(pFade->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pFade == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 頂点情報設定
	pFade->SetVtx();

	// フェードのポインタを返す
	return pFade;
}

//-------------------------------------
//- フェードの頂点情報設定
//-------------------------------------
void CFade::SetVtx(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_dataPos.Get();		// 位置
	D3DXVECTOR3 size = m_dataSize.Get();	// 大きさ
	D3DXCOLOR color = m_dataColor.Get();	// 色

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
	m_dataPos.Set(pos);			// 位置
	m_dataSize.Set(size);		// 大きさ
	m_dataColor.Set(color);		// 色
}

//-------------------------------------
//- フェードの頂点情報設定
//-------------------------------------
void CFade::SetFade(CScene::MODE mode)
{
	// モードを設定
	m_mode = mode;

	// フェードの状態を設定
	m_state = STATE_OUT;
}

//-------------------------------------
//- フェードの状態の取得処理
//-------------------------------------
CFade::STATE CFade::GetFade(void)
{
	return m_state;
}

//-------------------------------------
//- フェードの初期設定処理
//-------------------------------------
void CFade::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataColor.Set(color);
}
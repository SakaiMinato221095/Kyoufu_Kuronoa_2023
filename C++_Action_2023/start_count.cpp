
//================================================
//=
//=	スタートカウントの処理[start_count.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "start_count.h"

#include "renderer.h"
#include "game.h"

#include "manager_texture.h"

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	タイマーのコンストラクタ
//-------------------------------------
CStartCount::CStartCount()
{
	// 値のクリア
	m_pNumber = NULL;

	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	タイマーのデストラクタ
//-------------------------------------
CStartCount::~CStartCount()
{

}

//-------------------------------------
//- タイマーの初期化処理
//-------------------------------------
HRESULT CStartCount::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// タイマーの数字設定
	if (m_pNumber == NULL)
	{
		// 数字の生成処理
		m_pNumber = CNumber::Create(CNumber::TEX_DARK_GREEN_001);

		// 数字の生成成功の有無を判定
		if (m_pNumber == NULL)
		{
			// 「なし」を返す
			return E_FAIL;
		}
	}

	// 初期設定
	InitSet(pos, size, color);

	// 全更新停止処理
	CObject::SetIsUpdateAll(false);
		
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイマーの終了処理
//-------------------------------------
void CStartCount::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		// 数字の初期化
		m_pNumber->Uninit();
		m_pNumber = NULL;
	}

	// 全更新停止処理
	CObject::SetIsUpdateAll(true);
}

//-------------------------------------
//- タイマーの更新処理
//-------------------------------------
void CStartCount::Update(void)
{
	if (m_pNumber != NULL)
	{
		// 数字の更新処理
		m_pNumber->Update();
	}

	if (m_data.nTimerCount < m_data.nTime)
	{
		// カウントを進める
		m_data.nTimerCount++;

		NumberTex();

		if (m_data.nTimerCount >= m_data.nTime)
		{
			// 終了処理
			Uninit();
		}
	}
}

//-------------------------------------
//- タイマーの描画処理
//-------------------------------------
void CStartCount::Draw(void)
{

}

//-------------------------------------
//- タイマーの生成処理
//-------------------------------------
CStartCount * CStartCount::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// タイマーの生成
	CStartCount *pTimer = DBG_NEW CStartCount;

	// 生成の成功の有無を判定
	if (pTimer != NULL)
	{
		// 初期化処理
		if (FAILED(pTimer->Init(pos, size, color)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pTimer == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// パーティクルのポインタを返す
	return pTimer;
}

//-------------------------------------
//- タイマーの位置情報の設定
//-------------------------------------
void CStartCount::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// カウント値
	m_data.nTime = STOP_COUNT;

	// 数字の有無を判定
	if (m_pNumber != NULL)
	{
		// 頂点値情報
		CObject2d::VtxData vtxData = m_pNumber->GetVtxData();

		// 数字の位置情報を代入
		vtxData.pos = pos;
		vtxData.size = size;
		vtxData.color = color;

		// 情報更新（頂点値情報）
		m_pNumber->SetVtxData(vtxData);
	}

	// 数字設定
	NumberTex();
}

//-------------------------------------
//-	タイマーの桁ごとテクスチャの設定処理
//-------------------------------------
void CStartCount::NumberTex(void)
{
	// 変数宣言
	int aTexU = 0;	// 各桁の数字を格納

	// 変数宣言（値情報）
	CNumber::Data data = m_pNumber->GetData();

	int nDig = (m_data.nTime - m_data.nTimerCount) / 60;

	// 数字を設定
	data.nDigits = nDig + 1;

	// タイマーの更新処理
	m_pNumber->SetData(data);
}

//-------------------------------------
//- タイマーの値設定処理
//-------------------------------------
void CStartCount::SetData(CStartCount::Data data)
{
	m_data = data;
}

//-------------------------------------
//- タイマーの値取得処理
//-------------------------------------
CStartCount::Data CStartCount::GetData(void)
{
	return m_data;
}

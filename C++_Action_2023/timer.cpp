
//================================================
//=
//=	タイマー処理[timer.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "timer.h"

#include "renderer.h"
#include "game.h"

#include "manager_texture.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	タイマーのコンストラクタ
//-------------------------------------
CTimer::CTimer()
{
	// 値のクリア
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}

	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	タイマーのデストラクタ
//-------------------------------------
CTimer::~CTimer()
{

}

//-------------------------------------
//- タイマーの初期化処理
//-------------------------------------
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// タイマーの数字設定
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			// 数字の生成処理
			m_apNumber[nCount] = CNumber::Create(CNumber::TEX_DARK_GREEN_001);

			// 数字の生成成功の有無を判定
			if (m_apNumber[nCount] == NULL)
			{
				// 「なし」を返す
				return E_FAIL;
			}
		}
	}

	// 初期設定
	InitSet(pos, interval, between, size, color);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイマーの終了処理
//-------------------------------------
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// 数字の初期化
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//- タイマーの更新処理
//-------------------------------------
void CTimer::Update(void)
{
	// 加算処理
	Elapsed();

	// テクスチャの桁ごと設定処理
	NumberTex();
}

//-------------------------------------
//- タイマーの描画処理
//-------------------------------------
void CTimer::Draw(void)
{

}

//-------------------------------------
//- タイマーの生成処理
//-------------------------------------
CTimer * CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// タイマーの生成
	CTimer *pTimer = DBG_NEW CTimer;

	// 生成の成功の有無を判定
	if (pTimer != NULL)
	{
		// 初期化処理
		if (FAILED(pTimer->Init(pos,interval,between,size,color)))
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
//- タイマーの数字ポインタ初期化処理
//-------------------------------------
void CTimer::NullAllNumber(void)
{
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nCount] != NULL)
		{
			// 数字のポインタ初期化処理
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	タイマーの桁ごとテクスチャの設定処理
//-------------------------------------
void CTimer::NumberTex(void)
{
	// 変数宣言
	int aTexU[DIG_NUM_MAX];	// 各桁の数字を格納

	int nMinutes = (m_data.nTime / 60);
	int nSeconds = (m_data.nTime % 60);
	int nMillSeco = (int)((m_data.nTimerCount % 60) * 1.67f);

	// 桁ごとの数値を代入
	aTexU[0] = ((nMinutes % 100) / 10);
	aTexU[1] = ((nMinutes % 10));

	aTexU[2] = ((nSeconds % 100) / 10);
	aTexU[3] = (nSeconds % 10);

	aTexU[4] = ((nMillSeco % 100) / 10);
	//aTexU[5] = (nMillSeco % 10);

	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		// 変数宣言（値情報）
		CNumber::Data data = m_apNumber[nCount]->GetData();

		// 数字を設定
		data.nDigits = aTexU[nCount];

		// タイマーの更新処理
		m_apNumber[nCount]->SetData(data);
	}
}

//-------------------------------------
//-	タイマーの時間経過処理
//-------------------------------------
void CTimer::Elapsed(void)
{
	// カウンターを加算
	m_data.nTimerCount++;

	// カウンターの判定
	if (m_data.nTimerCount % 60 == 0)
	{// 60フレームに一回

		// 時間を加算
		m_data.nTime++;
	}
}

//-------------------------------------
//- タイマーの位置情報の設定
//-------------------------------------
void CTimer::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 情報代入
	m_data.pos = pos;
	m_data.interval = interval;
	m_data.between = between;

	// 変数宣言
	int nDigMax = 0;	// 桁数カウント
	int nDigCarr = 0;	// 桁数の繰り上げカウント

	for (int nCount = 0; nCount < DIG_MINU_NUM_MAX; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nDigMax] != NULL)
		{
			// 数字の位置を算出
			D3DXVECTOR3 numPos = D3DXVECTOR3(
				pos.x + (interval.x * nDigMax),
				pos.y + (interval.y * nDigMax),
				pos.z + (interval.z * nDigMax));

			// 頂点値情報
			CObject2d::VtxData vtxData = m_apNumber[nDigMax]->GetVtxData();

			// 数字の位置情報を代入
			vtxData.pos = numPos;
			vtxData.size = size;
			vtxData.color = color;

			// 情報更新（頂点値情報）
			m_apNumber[nDigMax]->SetVtxData(vtxData);
		}

		// 桁カウントを加算
		nDigMax++;
	}

	// 桁数繰り上げカウントの加算
	nDigCarr++;

	for (int nCount = 0; nCount < DIG_SECO_NUM_MAX; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nDigMax] != NULL)
		{
			// 数字の位置を算出
			D3DXVECTOR3 numPos = D3DXVECTOR3(
				(pos.x + (between.x * nDigCarr)) + (interval.x * nDigMax),
				(pos.y + (between.y * nDigCarr)) + (interval.y * nDigMax),
				(pos.z + (between.z * nDigCarr)) + (interval.z * nDigMax));

			// 頂点値情報
			CObject2d::VtxData vtxData = m_apNumber[nDigMax]->GetVtxData();

			// 数字の位置情報を代入
			vtxData.pos = numPos;
			vtxData.size = size;
			vtxData.color = color;

			// 情報更新（頂点値情報）
			m_apNumber[nDigMax]->SetVtxData(vtxData);
		}

		// 桁カウントを加算
		nDigMax++;
	}

	// 桁数繰り上げカウントの加算
	nDigCarr++;

	for (int nCount = 0; nCount < DIG_MILL_NUM_MAX; nCount++)
	{
		// 数字の有無を判定
		if (m_apNumber[nDigMax] != NULL)
		{
			// 数字の位置を算出
			D3DXVECTOR3 numPos = D3DXVECTOR3(
				(pos.x + (between.x * nDigCarr)) + (interval.x * nDigMax),
				(pos.y + (between.y * nDigCarr)) + (interval.y * nDigMax),
				(pos.z + (between.z * nDigCarr)) + (interval.z * nDigMax));

			// 頂点値情報
			CObject2d::VtxData vtxData = m_apNumber[nDigMax]->GetVtxData();

			// 数字の位置情報を代入
			vtxData.pos = numPos;
			vtxData.size = size;
			vtxData.color = color;

			// 情報更新（頂点値情報）
			m_apNumber[nDigMax]->SetVtxData(vtxData);
		}

		// 桁カウントを加算
		nDigMax++;
	}
}

//-------------------------------------
//- タイマーの値設定処理
//-------------------------------------
void CTimer::SetData(CTimer::Data data)
{
	m_data = data;
}

//-------------------------------------
//- タイマーの値取得処理
//-------------------------------------
CTimer::Data CTimer::GetData(void)
{
	return m_data;
}

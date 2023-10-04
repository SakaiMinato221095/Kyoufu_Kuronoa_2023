
//-===============================================
//-
//-	オブジェクト処理[object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "manager.h"
#include "debugproc.h"

#include "Input.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

CObject *CObject::m_apObject[OBJECT_PRIORITY_MAX][OBJECT_NUM_MAX] = {};
int CObject::m_nNumAll = 0;
CDataBool CObject::m_bDataStopAllUpdate = {};

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CObject::CObject(int nPriority)
{
	// ポインタを設定
	for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
	{
		if (m_apObject[nPriority][nCountObj] == NULL)
		{
			// 自分のポインタを代入
			m_apObject[nPriority][nCountObj] = this;

			// 自分のアドレス番号を設定
			m_nID = nCountObj;

			// 自分の優先順位を設定
			m_nPriority = nPriority;

			// オブジェクトの総数を加算
			m_nNumAll++;

			break;
		}
	}

	// 値をクリア
	m_type = TYPE_NONE;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CObject::~CObject()
{
}

//-------------------------------------
//-	全開放処理
//-------------------------------------
void CObject::ReleaseAll(void)
{
	// 全オブジェクトポインタを開放
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// 終了処理
				m_apObject[nCountPrio][nCountObj]->Uninit();
			}
		}
	}
}

//-------------------------------------
//-	全更新処理
//-------------------------------------
void CObject::UpdateAll(void)
{
	// キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 情報取得
	bool m_bStopAllUpdate = m_bDataStopAllUpdate.Get();	// 全更新停止の有無

	// 仮の遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_P) != NULL)
	{
		m_bStopAllUpdate = m_bStopAllUpdate ? false : true;
	}

	if (m_bStopAllUpdate == false)
	{
		// 全オブジェクトポインタの情報を更新
		for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
		{
			for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
			{
				if (m_apObject[nCountPrio][nCountObj] != NULL)
				{
					// 更新処理
					m_apObject[nCountPrio][nCountObj]->Update();
				}
			}
		}
	}

	// 情報更新
	m_bDataStopAllUpdate.Set(m_bStopAllUpdate);

	// デバック表示
	Debug();
}

//-------------------------------------
//-	全描画処理
//-------------------------------------
void CObject::DrawAll(void)
{
	// 全オブジェクトポインタの情報を描画
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// 後回し描画の有無
				if (m_apObject[nCountPrio][nCountObj]->m_bDataAfterDraw.Get() == false)
				{
					// 描画処理
					m_apObject[nCountPrio][nCountObj]->Draw();
				}
			}
		}
	}

	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// 後回し描画の有無
				if (m_apObject[nCountPrio][nCountObj]->m_bDataAfterDraw.Get() == true)
				{
					// 描画処理
					m_apObject[nCountPrio][nCountObj]->Draw();

					// 後回し描画のなくす
					m_apObject[nCountPrio][nCountObj]->m_bDataAfterDraw.Set(false);
				}
			}
		}
	}
}

//-------------------------------------
//-	種類の設定処理
//-------------------------------------
void CObject::SetType(TYPE type)
{
	// 種類を設定
	m_type = type;
}

//-------------------------------------
//-	種類の取得処理
//-------------------------------------
CObject::TYPE CObject::GetType(void)
{
	// 種類を返す
	return m_type;
}

//-------------------------------------
//-	オブジェクトの取得処理
//-------------------------------------
CObject * CObject::GetObject(int nPriority, int nldx)
{
	// 種類を返す
	return m_apObject[nPriority][nldx];
}

//-------------------------------------
//-	2Dオブジェクトの取得処理
//-------------------------------------
CObject2d *CObject::GetObject2d(void)
{
	// なしを返す
	return NULL;
}

//-------------------------------------
//-	多重背景の取得処理
//-------------------------------------
CBgMulti *CObject::GetBgMulti(void)
{
	// なしを返す
	return NULL;
}

//-------------------------------------
//-	開放処理
//-------------------------------------
void CObject::Release(void)
{
	// IDを代入
	int nID = m_nID;
	int nPrio = m_nPriority;

	// オブジェクトの破棄
	if (m_apObject[m_nID] != NULL)
	{
		// オブジェクトの開放
		delete m_apObject[nPrio][nID];
		m_apObject[nPrio][nID] = NULL;

		// オブジェクトの総数を減算
		m_nNumAll--;
	}
}

//-------------------------------------
//- プレイヤーのデバック表示
//-------------------------------------
void CObject::Debug(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("オブジェクト総数\n");
	pDebugProc->Print("%d", m_nNumAll);
	pDebugProc->Print("\n");
}

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
bool CObject::m_bIsUpdateAll = true;

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

	m_bIsUpdate = true;
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 全オブジェクトポインタの情報を更新
	if (m_bIsUpdateAll == true)
	{
		for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
		{
			for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
			{
				if (m_apObject[nCountPrio][nCountObj] != NULL)
				{
					if (m_apObject[nCountPrio][nCountObj]->m_bIsUpdate == true)
					{
						if (m_apObject[nCountPrio][nCountObj]->m_bIsUpdate == false)
						{
							int ndata = 0;
							ndata = 1;
						}

						// 更新処理
						m_apObject[nCountPrio][nCountObj]->Update();
					}
				}
			}
		}
	}

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
				// 描画処理
				m_apObject[nCountPrio][nCountObj]->Draw();
			}
		}
	}
}

//-------------------------------------
//- オブジェクトの更新の有無
//-------------------------------------
void CObject::IsUpdateStop(bool bIsUpdate)
{
	m_bIsUpdate = bIsUpdate;
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
//-	全更新の有無の取得処理
//-------------------------------------
bool CObject::GetIsUpdateAll(void)
{
	return m_bIsUpdateAll;
}

//-------------------------------------
//-	全更新の有無の設定処理
//-------------------------------------
void CObject::SetIsUpdateAll(bool bIsUpdateAll)
{
	m_bIsUpdateAll = bIsUpdateAll;
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
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

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
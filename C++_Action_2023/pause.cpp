
//================================================
//=
//=	ポーズ画面処理[pause.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "main.h"

#include "pause.h"

#include "manager.h"
#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "obj_2d_none.h"

//=======================================
//=	マクロ定義
//=======================================

#define WINDOW_POS_X		(SCREEN_WIDTH * 0.5f)	//ポーズの枠の位置(X)
#define WINDOW_POS_Y		(SCREEN_HEIGHT * 0.5f)	//ポーズの枠の位置(Y)
#define WINDOW_SIZE_X		(300.0f)				//ポーズの枠のサイズ(X)
#define WINDOW_SIZE_Y		(200.0f)				//ポーズの枠のサイズ(Y)
#define MENU_POS_X			(SCREEN_WIDTH * 0.5f)	//ポーズメニューの最初の開始位置（X)
#define MENU_POS_Y			(230.0f)				//ポーズメニューの最初の開始位置（Y）	
#define MENU_SIZE_X			(200.0f)				//ポーズメニューの大きさ（X）
#define MENU_SIZE_Y			(60.0f)					//ポーズメニューの大きさ（Y）
#define MENU_INTERVAL_Y		(130.0f)				//ポーズメニューの間隔（Y）

//=======================================
//=	静的変数宣言
//=======================================

CObj2dNone *CPause::m_apObj2dNone[TYPE_MAX] = {};

//-------------------------------------
//-	ポーズのコンストラクタ
//-------------------------------------
CPause::CPause()
{
	m_typeSelect = (TYPE_SELECT)0;
}

//-------------------------------------
//-	ポーズのデストラクタ
//-------------------------------------
CPause::~CPause()
{

}

//-------------------------------------
//- ポーズの初期化処理
//-------------------------------------
HRESULT CPause::Init(void)
{
	// オブジェクト管理の有無を判定
	if (m_apObj2dNone[TYPE_BG] == NULL)
	{
		// オブジェクト管理の生成
		m_apObj2dNone[TYPE_BG] = CObj2dNone::Create(
			CObj2dNone::TEX_PAUSE_BG,
			D3DXVECTOR3(WINDOW_POS_X, WINDOW_POS_Y, 0.0f),
			D3DXVECTOR3(WINDOW_SIZE_X, WINDOW_SIZE_Y, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// オブジェクト管理の初期化処理
		if (m_apObj2dNone[TYPE_BG] == NULL)
		{// 失敗時

			// 初期化を抜ける
			return E_FAIL;
		}
	}
	else
	{// ゴミが入っているとき

		// 初期化を抜ける
		return E_FAIL;
	}

	for (int nCutPause = TYPE_GAME; nCutPause < TYPE_TITLE + 1; nCutPause++)
	{
		// オブジェクト管理の有無を判定
		if (m_apObj2dNone[nCutPause] == NULL)
		{
			if (nCutPause == TYPE_GAME)
			{
				// オブジェクト管理の生成
				m_apObj2dNone[nCutPause] = CObj2dNone::Create(
					CObj2dNone::TEX_PAUSE_GAME,
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
			}
			else if (nCutPause == TYPE_RETRY)
			{
				// オブジェクト管理の生成
				m_apObj2dNone[nCutPause] = CObj2dNone::Create(
					CObj2dNone::TEX_PAUSE_RETRY,
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCutPause == TYPE_TITLE)
			{
				// オブジェクト管理の生成
				m_apObj2dNone[nCutPause] = CObj2dNone::Create(
					CObj2dNone::TEX_PAUSE_TITLE,
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			// オブジェクト管理の初期化処理
			if (m_apObj2dNone[nCutPause] == NULL)
			{// 失敗時

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 初期化を抜ける
			return E_FAIL;
		}
	}

	// オブジェクト管理の有無を判定
	if (m_apObj2dNone[TYPE_CURSOR] == NULL)
	{
		// オブジェクト管理の生成
		m_apObj2dNone[TYPE_CURSOR] = CObj2dNone::Create(
			CObj2dNone::TEX_PAUSE_CURSOR,
			D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y, 0.0f),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// オブジェクト管理の初期化処理
		if (m_apObj2dNone[TYPE_CURSOR] == NULL)
		{// 失敗時

			// 初期化を抜ける
			return E_FAIL;
		}

	}
	else
	{// ゴミが入っているとき

		// 初期化を抜ける
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ポーズの終了処理
//-------------------------------------
void CPause::Uninit(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apObj2dNone[nCount] != NULL)
		{
			// 効果なし2Dオブジェクトの開放処理
			m_apObj2dNone[nCount]->Uninit();
			m_apObj2dNone[nCount] = NULL;
		}
	}

	// 自分自身の開放処理
	Release();
}

//-------------------------------------
//- ポーズの更新処理
//-------------------------------------
void CPause::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		if (m_apObj2dNone[nCutPause] != NULL)
		{
			// 2Dの更新処理
			m_apObj2dNone[nCutPause]->Update();
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_W) != NULL)
	{
		// 種類を加算
		m_typeSelect = (TYPE_SELECT)(m_typeSelect - 1);

		if (m_typeSelect < 0)
		{
			m_typeSelect = TYPE_SELECT_TITLE;
		}

		CObject2d::VtxData vtxData = m_apObj2dNone[TYPE_CURSOR]->GetVtxData();

		vtxData.pos = D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect), 0.0f);

		m_apObj2dNone[TYPE_CURSOR]->SetVtxData(vtxData);

	}
	else if (pInputKeyboard->GetTrigger(DIK_S) != NULL)
	{
		// 種類を加算
		m_typeSelect = (TYPE_SELECT)(m_typeSelect + 1);

		if (m_typeSelect > TYPE_SELECT_TITLE)
		{
			m_typeSelect = (TYPE_SELECT)0;
		}

		CObject2d::VtxData vtxData = m_apObj2dNone[TYPE_CURSOR]->GetVtxData();

		vtxData.pos = D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect), 0.0f);

		m_apObj2dNone[TYPE_CURSOR]->SetVtxData(vtxData);
	}
	
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL)
	{
		m_bOk = true;
	}
}

//-------------------------------------
//- ポーズの描画処理
//-------------------------------------
void CPause::Draw(void)
{

}

//-------------------------------------
//- ポーズの生成処理
//-------------------------------------
CPause *CPause::Create(void)
{
	// ポーズの生成
	CPause *pCPause = DBG_NEW CPause;

	// 生成の成功の有無を判定
	if (pCPause != NULL)
	{
		// 初期化処理
		if (FAILED(pCPause->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPause == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポーズのポインタを返す
	return pCPause;
}

//-------------------------------------
//-	効果なし2dオブジェクトの情報を取得
//-------------------------------------
CObj2dNone * CPause::GetObj2dNone(int nNum)
{
	return m_apObj2dNone[nNum];
}

//-------------------------------------
//-	ポーズ選択の情報を取得
//-------------------------------------
CPause::TYPE_SELECT CPause::GetTypeSelect(void)
{
	return m_typeSelect;
}

bool CPause::GetOk(void)
{
	return m_bOk;
}

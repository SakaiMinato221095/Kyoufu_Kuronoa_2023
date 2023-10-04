
//================================================
//=
//=	ゲーム画面処理[game.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "game.h"

#include "fade.h"

#include "input.h"
#include "sound.h"

#include "time_stop.h"

#include "sys_game_phase.h"
#include "timer.h"

#include "pause.h"

#include "mgr_sys_obj.h"

#include "manager_object.h"

#include "state_game.h"
#include "state_battle.h"
#include "state_mode.h"

#include "ui_mission.h"
#include "ui_start_text.h"

#include "file_garbage.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CSysGamePhase *CGame::m_pSysGamePhase = NULL;

CMgrSysObj *CGame::m_pMgrSysObj = NULL;

CStateGame *CGame::m_pStateGame = NULL;
CStateBattle *CGame::m_pStateBattle = NULL;

CPause *CGame::m_pPause = NULL;

//-------------------------------------
//-	ゲーム画面のコンストラクタ
//-------------------------------------
CGame::CGame()
{
	m_game = (GAME)0;
}

//-------------------------------------
//-	ゲーム画面のデストラクタ
//-------------------------------------
CGame::~CGame()
{

}

//-------------------------------------
//- ゲーム画面の初期化処理
//-------------------------------------
HRESULT CGame::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// システムオブジェクト管理の生成処理
	{
		// システムオブジェクト管理の有無を判定
		if (m_pMgrSysObj == NULL)
		{
			// システムオブジェクト管理の生成
			m_pMgrSysObj = DBG_NEW CMgrSysObj;

			// システムオブジェクト管理の初期化処理
			if (FAILED(m_pMgrSysObj->Init(hInstance, hWnd, bWindow)))
			{// 失敗時

			 // 失敗メッセージ
				MessageBox(hWnd, "システムオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

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

	// 戦闘ステータスの設定処理
	{
		// 戦闘ステータスの有無を判定
		if (m_pStateBattle == NULL)
		{
			// 戦闘ステータスの生成
			m_pStateBattle = CStateBattle::Create();

			// 戦闘ステータスの初期化処理
			if (m_pStateBattle == NULL)
			{// 失敗時

			 // 失敗メッセージ
				MessageBox(hWnd, "戦闘ステータスの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 失敗メッセージ
			MessageBox(hWnd, "戦闘ステータスの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// ゲームステータスの設定処理
	{
		// ゲームステータスの有無を判定
		if (m_pStateGame == NULL)
		{
			// ゲームステータスの生成
			m_pStateGame = CStateGame::Create();

			// ゲームステータスの初期化処理
			if (m_pStateGame == NULL)
			{// 失敗時

			 // 失敗メッセージ
				MessageBox(hWnd, "ゲームステータスの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 失敗メッセージ
			MessageBox(hWnd, "ゲームステータスの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 初期フェーズ（探索フェーズ）の設定処理
	{
		// 初期フェーズ（探索フェーズ）の有無を判定
		if (m_pSysGamePhase == NULL)
		{
			// 初期フェーズ（探索フェーズ）の生成
			m_pSysGamePhase = CSysGamePhase::Create(CSysGamePhase::TYPE_SEARCH, hInstance, hWnd, bWindow);

			// 初期フェーズ（探索フェーズ）の初期化処理
			if (m_pSysGamePhase == NULL)
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "フェーズの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "フェーズの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// 発射音SEの再生
	pSound->Play(CSound::LABEL_BGM_GAME);

	// 情報更新（時間管理）
	m_pMgrSysObj->GetTimer()->m_nDataTime.Set(GAME_TIME);	// 時間

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲーム画面の終了処理
//-------------------------------------
void CGame::Uninit(void)
{
	// システムオブジェクト管理の破棄
	if (m_pMgrSysObj != NULL)
	{
		// システムオブジェクト管理の終了処理
		m_pMgrSysObj->Uninit();

		// システムオブジェクト管理の開放処理
		delete m_pMgrSysObj;
		m_pMgrSysObj = NULL;
	}

	// フェーズの有無を判定
	if (m_pSysGamePhase != NULL)
	{
		// フェーズの終了処理
		m_pSysGamePhase->Uninit();

		// フェーズの開放処理
		delete m_pSysGamePhase;
		m_pSysGamePhase = NULL;
	}

	// 戦闘ステータスの破棄
	if (m_pStateBattle != NULL)
	{
		// 戦闘ステータスの終了処理
		m_pStateBattle->Uninit();

		// 戦闘ステータスの開放処理
		delete m_pStateBattle;
		m_pStateBattle = NULL;
	}

	// ゲームステータスの破棄
	if (m_pStateGame != NULL)
	{
		// ゲームステータスの終了処理
		m_pStateGame->Uninit();

		// ゲームステータスの開放処理
		delete m_pStateGame;
		m_pStateGame = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();

	// ゴミの復活処理
	CFileGarbage::ObjRecall();
}

//-------------------------------------
//- ゲーム画面の更新処理
//-------------------------------------
void CGame::Update(void)
{
	// キーボードの情報取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	// モードステータスの情報取得
	CStateMode *pStateMode = CManager::GetStateMode();;

	// モードステータスの情報取得の成功を判定
	if (pStateMode == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 情報取得（オブジェクト）
	bool bStopAllUpdate = CObject::m_bDataStopAllUpdate.Get();	// 全更新停止

	// 仮の遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_P) != NULL)
	{
		if (m_game == GAME_NONE)
		{
			//m_pPause = CPause::Create();

			// 全更新停止
			bStopAllUpdate = true;

			// ポーズ状態
			m_game = GAME_PAUSE;
		}
		else if (m_game == GAME_PAUSE)
		{
			if (m_pPause != NULL)
			{
				m_pPause->Uninit();
				m_pPause = NULL;
			}

			// 全更新停止を解除
			bStopAllUpdate = false;

			// ゲーム状態
			m_game = GAME_NONE;
		}
	}

	if (m_game == GAME_NONE)
	{
		// リザルトの設定更新処理
		UpdateSetResult();

		// リザルトのタイムエンド処理
		UpdateTimeEndResult();

		// システムオブジェクト管理の有無を判定
		if (m_pStateBattle != NULL)
		{
			// 戦闘ステータスの更新処理
			m_pStateBattle->Update();
		}

		// システムオブジェクト管理の有無を判定
		if (m_pMgrSysObj != NULL)
		{
			// システムオブジェクト管理の更新処理
			m_pMgrSysObj->Update();
		}

		// ゲームフェーズの有無を判定
		if (m_pSysGamePhase != NULL)
		{
			// ゲームフェーズの更新処理
			m_pSysGamePhase->Update();
		}
	}
	else if (m_game == GAME_PAUSE)
	{
		if (m_pPause != NULL)
		{
			// ポーズの更新処理
			m_pPause->Update();

			if (m_pPause->m_bDataOk.Get() == true)
			{
				switch (m_pPause->GetTypeSelect())
				{
				case CPause::TYPE_SELECT_GAME:

					break;

				case CPause::TYPE_SELECT_RETRY:

					// ゲームモード
					CManager::GetFade()->SetFade(CScene::MODE_GAME);

					break;

				case CPause::TYPE_SELECT_TITLE:

					// ゲームモード
					CManager::GetFade()->SetFade(CScene::MODE_TITEL);

					break;
				}

				// ポーズの開放処理
				m_pPause->Uninit();
				m_pPause = NULL;
			}

			// 全更新停止を解除
			bStopAllUpdate = false;

			// ゲーム状態
			m_game = GAME_NONE;
			
		}
	}

	// 情報更新
	CObject::m_bDataStopAllUpdate.Set(bStopAllUpdate);	// 全更新停止

#if _DEBUG

	// 仮の遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL)
	{
		if (m_game == GAME_PAUSE)
		{
			m_pPause->Uninit();
			m_pPause = NULL;

			// 全更新停止を解除
			bStopAllUpdate = false;

			// 情報更新
			CObject::m_bDataStopAllUpdate.Set(bStopAllUpdate);	// 全更新停止

			
			// ゲーム状態
			m_game = GAME_NONE;
		}

		// 通常リザルトに設定
		pStateMode->SetResultState(CStateMode::RESULT_STATE_END);

		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
#endif

}

//-------------------------------------
//- ゲーム画面の描画処理
//-------------------------------------
void CGame::Draw(void)
{

}

//-------------------------------------
//- フェーズの設定処理
//-------------------------------------
void CGame::SetPhase(CSysGamePhase::TYPE type)
{
	if (m_pSysGamePhase != NULL)
	{
		// 現在のモードを破棄
		m_pSysGamePhase->Uninit();

		// 現在のモードの開放処理
		delete m_pSysGamePhase;
		m_pSysGamePhase = NULL;
	}

	// 設定したモードを生成
	m_pSysGamePhase = m_pSysGamePhase->Create(type);
}

//-------------------------------------
//- フェーズの取得処理
//-------------------------------------
CSysGamePhase::TYPE CGame::GetPhase(void)
{
	// フェーズ状態を返す
	return m_pSysGamePhase->GetType();
}

//-------------------------------------
//- ゲームフェイズの情報を取得
//-------------------------------------
CSysGamePhase * CGame::GetSysGamePhase(void)
{
	// ゲームフェイズを返す
	return m_pSysGamePhase;
}

//-------------------------------------
//- システムオブジェクト管理の情報を取得
//-------------------------------------
CMgrSysObj * CGame::GetMgrSysObj(void)
{
	// システムオブジェクトのポインタを返す
	return m_pMgrSysObj;
}

//-------------------------------------
//-	ゲームステータスの情報を取得
//-------------------------------------
CStateGame * CGame::GetStateGame(void)
{
	return m_pStateGame;
}

//-------------------------------------
//-	戦闘ステータスの情報を取得
//-------------------------------------
CStateBattle * CGame::GetStateBattle(void)
{
	return m_pStateBattle;
}

//-------------------------------------
//-	ポーズの情報を取得
//-------------------------------------
CPause * CGame::GetPause(void)
{
	return m_pPause;
}

//-------------------------------------
//-	ゲームのリザルト設定更新処理
//-------------------------------------
void CGame::UpdateSetResult(void)
{
	// モードステータスの情報取得
	CStateMode *pStateMode = CManager::GetStateMode();;

	// モードステータスの情報取得の成功を判定
	if (pStateMode == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	CStateGame::END_STATE endState = m_pStateGame->GetEndState();	// 終了状態

	// ゲームの終了状態を判定
	if (endState != CStateGame::END_STATE_NONE)
	{
		switch (endState)
		{
		case CStateGame::END_STATE_BOSS:

			// 勝利リザルトに設定
			pStateMode->SetResultState(CStateMode::RESULT_STATE_WIN);

			break;

		case CStateGame::END_STATE_TIME:

			// 通常リザルトに設定
			pStateMode->SetResultState(CStateMode::RESULT_STATE_END);

			break;

		case CStateGame::END_STATE_DIED:

			// 敗北リザルトに設定
			pStateMode->SetResultState(CStateMode::RESULT_STATE_LOOSE);

			break;
		}

		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//-	ゲームのリザルト設定更新処理
//-------------------------------------
void CGame::UpdateTimeEndResult(void)
{
	// モードステータスの情報取得
	CStateMode *pStateMode = CManager::GetStateMode();;

	// モードステータスの情報取得の成功を判定
	if (pStateMode == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 時間の情報取得
	CTimer *pTimer = CMgrSysObj::GetTimer();

	// 時間の情報取得の成功を判定
	if (pTimer == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 時間の判定（0秒のとき）
	if (pTimer->m_nDataTime.Get() == 0)
	{
		// 通常リザルトに設定
		pStateMode->SetResultState(CStateMode::RESULT_STATE_END);

		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
}
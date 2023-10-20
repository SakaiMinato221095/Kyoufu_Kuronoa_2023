
//================================================
//=
//=	管理処理[manager.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "manager.h"
#include "renderer.h"

#include "fade.h"

#include "title.h"
#include "game.h"
#include "result.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

#include "manager_texture.h"
#include "manager_model.h"

#include "camera.h"
#include "light.h"

#include "mgr_coll.h"

#include "csv_stage.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CManager *CManager::m_pManager = NULL;

//-------------------------------------------------------------------------
//- シーン
//-------------------------------------------------------------------------

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CScene::CScene()
{
	m_mode = CScene::MODE(0);
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CScene::~CScene()
{

}

//-------------------------------------
//- シーンの初期化処理
//-------------------------------------
HRESULT CScene::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- シーンの終了処理
//-------------------------------------
void CScene::Uninit(void)
{

}

//-------------------------------------
//- シーンの更新処理
//-------------------------------------
void CScene::Update(void)
{

}

//-------------------------------------
//- シーンの描画処理
//-------------------------------------
void CScene::Draw(void)
{

}

//-------------------------------------
//- シーンの生成処理
//-------------------------------------
CScene *CScene::Create(MODE mode, HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// 変数宣言
	CScene *pScene = NULL;

	// 指定されたモードの生成
	switch (mode)
	{
	case MODE::MODE_TITEL:
		
		pScene = DBG_NEW CTitle;

		break;

	case MODE::MODE_GAME:

		pScene = DBG_NEW CGame;

		break;

	case MODE::MODE_RESULT:

		pScene = DBG_NEW CResult;

		break;
	}

	// 生成の成功の有無を判定
	if (pScene != NULL)
	{
		// モード設定処理
		pScene->SetMode(mode);
		
		// 初期化処理
		if (FAILED(pScene->Init(hInstance, hWnd, bWindow)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pScene == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// シーンの情報を返す
	return pScene;
}

//-------------------------------------
//- シーンの設定処理
//-------------------------------------
void CScene::SetMode(MODE mode)
{
	// モード代入
	m_mode = mode;
}

//-------------------------------------
//- シーンの取得処理
//-------------------------------------
CScene::MODE CScene::GetMode(void)
{
	// モードを返す
	return m_mode;
}

//-------------------------------------------------------------------------
//- 管理
//-------------------------------------------------------------------------

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CManager::CManager()
{
	m_pScene = NULL;
	m_pFade = NULL;

	m_pRenderer = NULL;

	m_pInputKeyboard = NULL;
	m_pXInput = NULL;
	m_pSound = NULL;
	m_pDbugProc = NULL;

	m_pManagerTexture = NULL;
	m_pManagerModel = NULL;

	m_pCamera = NULL;
	m_pLight = NULL;

	m_pMgrColl = NULL;

	m_pCsvStage = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CManager::~CManager()
{

}

//-------------------------------------
//- 管理の初期化処理
//-------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// キーボード
	{
		// キーボードの有無を判定
		if (m_pInputKeyboard == NULL)
		{
			// キーボードの生成
			m_pInputKeyboard = DBG_NEW CInputKeyboard;

			// キーボードの初期化処理
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "キーボードの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "キーボードの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// X入力
	{
		// X入力の有無を判定
		if (m_pXInput == NULL)
		{
			// X入力の生成
			m_pXInput = CXInput::Create(hInstance, hWnd);

			// X入力の初期化処理
			if (m_pXInput == NULL)
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "X入力の生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "X入力の初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// サウンド
	{
		// サウンド有無を判定
		if (m_pSound == NULL)
		{
			// サウンド生成
			m_pSound = DBG_NEW CSound;

			// サウンド初期化処理
			if (FAILED(m_pSound->Init(hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "サウンドの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "サウンドの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// レンダラー
	{
		// レンダラーの有無を判定
		if (m_pRenderer == NULL)
		{
			// レンダラーの生成
			m_pRenderer = DBG_NEW CRenderer;

			// レンダラーの初期化処理
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "レンダラーの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "レンダラーの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// フェード
	{
		// フェードの有無を判定
		if (m_pFade == NULL)
		{
			// フェードの生成
			m_pFade = CFade::Create();

			// フェードの生成成功の有無を判定
			if (m_pFade == NULL)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "フェードの生成", "初期処理失敗！", MB_ICONWARNING);

				// 生成処理を抜ける
				return E_FAIL;
			}
		}
	}

	// デバックプロック
	{
		// デバックプロック有無を判定
		if (m_pDbugProc == NULL)
		{
			// デバックプロック生成
			m_pDbugProc = DBG_NEW CDebugProc;

			// デバックプロック初期化処理
			m_pDbugProc->Init();
		}
	}

	// テクスチャ管理
	{
		// テクスチャ管理の有無を判定
		if (m_pManagerTexture == NULL)
		{
			// テクスチャ管理の生成
			m_pManagerTexture = DBG_NEW CManagerTexture;

			// テクスチャ管理の初期化処理
			if (FAILED(m_pManagerTexture->Load(hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "テクスチャ管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "テクスチャ管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// モデル管理
	{
		// モデル管理の有無を判定
		if (m_pManagerModel == NULL)
		{
			// モデル管理の生成
			m_pManagerModel = DBG_NEW CManagerModel;

			// モデル管理の初期化処理
			if (FAILED(m_pManagerModel->Load(hWnd)))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "モデル管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "モデル管理の読み込み", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// カメラ
	{
		// カメラの有無を判定
		if (m_pCamera == NULL)
		{
			// カメラの生成
			m_pCamera = DBG_NEW CCamera;

			// カメラの初期化処理
			if (FAILED(m_pCamera->Init()))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "カメラの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "カメラの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// ライト
	{
		// ライトの有無を判定
		if (m_pLight == NULL)
		{
			// ライトの生成
			m_pLight = DBG_NEW CLight;

			// ライトの初期化処理
			if (FAILED(m_pLight->Init()))
			{// 失敗時

				// 失敗メッセージ
				MessageBox(hWnd, "ライトの生成", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

		 // 失敗メッセージ
			MessageBox(hWnd, "ライトの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// 当たり判定管理
	{
		// 当たり判定管理の有無を判定
		if (m_pMgrColl == NULL)
		{
			// 当たり判定管理の生成
			m_pMgrColl = CMgrColl::Create();

			// 当たり判定管理の有無を判定
			if (m_pMgrColl == NULL)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "当たり判定管理の初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "当たり判定管理の初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// シーン
	{
		// シーンの有無を判定
		if (m_pScene == NULL)
		{
			// シーンの生成
			m_pScene = CScene::Create(CScene::MODE_TITEL, hInstance,hWnd,bWindow);

			// シーンの有無を判定
			if (m_pScene == NULL)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "シーンの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "シーンの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}


	// シーン
	{
		// シーンの有無を判定
		if (m_pCsvStage == NULL)
		{
			// シーンの生成
			m_pCsvStage = CCsvStage::Create();

			// シーンの有無を判定
			if (m_pCsvStage == NULL)
			{
				// 失敗メッセージ
				MessageBox(hWnd, "CSVステージの初期化", "初期処理失敗！", MB_ICONWARNING);

				// 初期化を抜ける
				return E_FAIL;
			}
		}
		else
		{// ゴミが入っているとき

			// 失敗メッセージ
			MessageBox(hWnd, "CSVステージの初期化", "初期処理失敗！", MB_ICONWARNING);

			// 初期化を抜ける
			return E_FAIL;
		}
	}

	// ステージCSVの処理
	if (m_pCsvStage != NULL)
	{
		// CSVステージのロード処理
		m_pCsvStage->Load(CCsvStage::CSV_STAGE_000);
	}
	
	// 音の設定
	if (m_pSound != NULL)
	{
		// BGMを流す
		//m_pSound->Play(CSound::LABEL_BGM_GAME_000);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 管理の終了処理
//-------------------------------------
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの終了処理
		m_pInputKeyboard->Uninit();

		// キーボードの開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// X入力の破棄
	if (m_pXInput != NULL)
	{
		// X入力の終了処理
		m_pXInput->Uninit();

		// X入力の開放
		delete m_pXInput;
		m_pXInput = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// サウンドの開放
		delete m_pSound;
		m_pSound = NULL;
	}

	// デバックプロックの破棄
	if (m_pDbugProc != NULL)
	{
		// デバックプロックの終了処理
		m_pDbugProc->Uninit();

		// デバックプロックの開放
		delete m_pDbugProc;
		m_pDbugProc = NULL;
	}

	// テクスチャ管理の破棄
	if (m_pManagerTexture != NULL)
	{
		// テクスチャ管理の終了処理
		m_pManagerTexture->Unload();

		// テクスチャ管理の開放
		delete m_pManagerTexture;
		m_pManagerTexture = NULL;
	}

	// モデル管理の破棄
	if (m_pManagerModel != NULL)
	{
		// モデル管理の終了処理
		m_pManagerModel->Unload();

		// モデル管理の開放
		delete m_pManagerModel;
		m_pManagerModel = NULL;
	}

	// カメラの有無を判定
	if (m_pCamera != NULL)
	{
		// カメラの終了処理
		m_pCamera->Uninit();

		// カメラの開放処理
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ライトの有無を判定
	if (m_pLight != NULL)
	{
		// ライトの終了処理
		m_pLight->Uninit();

		// ライトの開放処理
		delete m_pLight;
		m_pLight = NULL;
	}

	// 当たり判定管理の破棄
	if (m_pMgrColl != NULL)
	{
		// 当たり判定管理の終了処理
		m_pMgrColl->Uninit();

		// 当たり判定管理の開放処理
		delete m_pMgrColl;
		m_pMgrColl = NULL;
	}

	// CSVステージの破棄
	if (m_pCsvStage != NULL)
	{
		// CSVステージの終了処理
		m_pCsvStage->Uninit();

		// CSVステージの開放処理
		delete m_pCsvStage;
		m_pCsvStage = NULL;
	}

	// シーンの破棄
	if (m_pScene != NULL)
	{
		// シーンの終了処理
		m_pScene->Uninit();

		// シーンの開放処理
		delete m_pScene;
		m_pScene = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();

	// フェードの破棄
	if (m_pFade != NULL)
	{
		// フェードの終了処理
		m_pFade->Uninit();

		// フェードの開放処理
		delete m_pFade;
		m_pFade = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();

		// レンダラーの開放処理
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//-------------------------------------
//- 管理の更新処理
//-------------------------------------
void CManager::Update(void)
{
	// キーボードの有無を判定
	if (m_pInputKeyboard != NULL)
	{
		// キーボードの更新処理
		m_pInputKeyboard->Update();
	}

	// X入力の有無を判定
	if (m_pXInput != NULL)
	{
		// X入力の更新処理
		m_pXInput->Update();
	}

	// カメラの有無を判定
	if (m_pCamera != NULL)
	{
		// カメラの更新処理
		m_pCamera->Update();
	}

	// ライトの有無を判定
	if (m_pLight != NULL)
	{
		// ライトの更新処理
		m_pLight->Update();
	}

	// 当たり判定管理の有無を判定
	if (m_pMgrColl != NULL)
	{
		// 当たり判定管理の更新処理
		m_pMgrColl->Update();
	}

	// デバックプロックの有無を判定
	if (m_pDbugProc != NULL)
	{
		// デバックプロックの更新処理
		m_pDbugProc->Update();
	}

	// レンダラーの有無を判定
	if (m_pRenderer != NULL)
	{
		// レンダラーの更新処理
		m_pRenderer->Update();
	}


	// フェードの有無を判定
	if (m_pFade != NULL)
	{
		// フェードの更新処理
		m_pFade->Update();
	}

	// フェードの有無を判定
	if (m_pFade->GetFade() == CFade::STATE_NONE)
	{
		// シーンの有無を判定
		if (m_pScene != NULL)
		{
			// シーンの更新処理
			m_pScene->Update();
		}
	}

}

//-------------------------------------
//- 管理の描画処理
//-------------------------------------
void CManager::Draw(void)
{
	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// デバック表示
	Debug();

	// カメラの有無を判定
	if (pCamera != NULL)
	{
		// カメラの設定
		pCamera->SetCamera();
	}

	// 当たり判定管理の有無を判定
	if (m_pMgrColl != NULL)
	{
		// 当たり判定管理の設定
		m_pMgrColl->Draw();
	}

	// レンダラーの有無を判定
	if (m_pRenderer != NULL)
	{
		// レンダラーの描画処理
		m_pRenderer->Draw();
	}
}

//-------------------------------------
//- ゲーム状態の設定処理
//-------------------------------------
void CManager::SetMode(CScene::MODE mode)
{
	// サウンドの全停止
	m_pSound->Stop();

	if (m_pScene != NULL)
	{
		// 現在のモードを破棄
		m_pScene->Uninit();

		// 現在のモードの開放処理
		delete m_pScene;
		m_pScene = NULL;
	}

	// 設定したモードを生成
	m_pScene = m_pScene->Create(mode);
}

//-------------------------------------
//- ゲーム状態の取得処理
//-------------------------------------
CScene::MODE CManager::GetMode(void)
{
	// ゲーム状態を返す
	return m_pScene->GetMode();
}

//-------------------------------------
//- フェードの取得処理
//-------------------------------------
CFade *CManager::GetFade(void)
{
	// フェードのポインタを返す
	return m_pFade;
}

//-------------------------------------
//- レンダラーの情報を取得
//-------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	// レンダラーのポインタを返す
	return m_pRenderer;
}

//-------------------------------------
//-	キーボードの情報を取得
//-------------------------------------
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	// キーボードのポインタを返す
	return m_pInputKeyboard;
}

//-------------------------------------
//-	X入力の情報を取得
//-------------------------------------
CXInput * CManager::GetXInput(void)
{
	return m_pXInput;
}

//-------------------------------------
//-	サウンドの情報を取得
//-------------------------------------
CSound *CManager::GetSound(void)
{
	// キーボードのポインタを返す
	return m_pSound;
}

//-------------------------------------
//-	デバックプロックの情報を取得
//-------------------------------------
CDebugProc * CManager::GetDbugProc(void)
{
	// デバックプロックを返す
	return m_pDbugProc;
}

//-------------------------------------
//-	テクスチャ管理の情報を取得
//-------------------------------------
CManagerTexture *CManager::GetManagerTexture(void)
{
	// テクスチャ管理を返す
	return m_pManagerTexture;
}

//-------------------------------------
//-	モデル管理の情報を取得
//-------------------------------------
CManagerModel *CManager::GetManagerModel(void)
{
	return m_pManagerModel;
}

//-------------------------------------
//-	カメラの情報を取得
//-------------------------------------
CCamera *CManager::GetCamera(void)
{
	// キーボードのポインタを返す
	return m_pCamera;
}

//-------------------------------------
//-	ライトの情報を取得
//-------------------------------------
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

//-------------------------------------
//- 当たり判定管理の情報を取得
//-------------------------------------
CMgrColl * CManager::GetMgrColl(void)
{
	return m_pMgrColl;
}

//-------------------------------------
//- 管理のステージCSVを取得処理
//-------------------------------------
CCsvStage * CManager::GetCsvStage(void)
{
	return m_pCsvStage;
}

//-------------------------------------
//- 管理のポインタ設定処理
//-------------------------------------
CManager * CManager::GetInstance()
{
	if (m_pManager == NULL)
	{
		// 管理の生成
		return m_pManager = new CManager;
	}
	else
	{
		// 現在の管理を返す
		return m_pManager;
	}
}

//-------------------------------------
//- マネージャーのデバック表示
//-------------------------------------
void CManager::Debug(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");

	if (GetMode() == CScene::MODE_TITEL)
	{
		pDebugProc->Print("ゲーム状態 : タイトル");
	}
	else if (GetMode() == CScene::MODE_GAME)
	{
		pDebugProc->Print("ゲーム状態 : ゲーム");
	}
	else if (GetMode() == CScene::MODE_RESULT)
	{
		pDebugProc->Print("ゲーム状態 : リザルト");
	}

	pDebugProc->Print("\n");
}

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

#include "manager.h"

#include "fade.h"

#include "input.h"
#include "xinput.h"
#include "sound.h"

#include "camera.h"

#include "player.h"

#include "obj_3d_field.h"
#include "obj_3d_wall.h"
#include "objectx_none.h"

#include "obj_block.h"

#include "skybox.h"

#include "csv_stage.h"

#include "timer.h"

#include "obj_teach.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CPlayer *CGame::m_pPlayer = NULL;
CTimer *CGame::m_pTimer = NULL;

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
	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 位置
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),	// 向き
		CModel::MODEL_TYPE_PLAYER_AONOA,			// モデル
		CMotion::MOTION_TYPE_PLAYER_AONOA);			// モーション

	// プレイヤーの初期化処理
	if (m_pPlayer == NULL)
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "プレイヤーの初期化", "初期処理失敗！", MB_ICONWARNING);

		// 初期化を抜ける
		return E_FAIL;
	}

	// カメラ位置の設定処理
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != NULL)
	{
		pCamera->SetMode(CCamera::MODE_FOLLOWING);
	}

	for (int nCutColu = 0; nCutColu < 16; nCutColu++)
	{
		for (int nCutLine = 0; nCutLine < 64; nCutLine++)
		{
			// フィールドの生成
			CObj3dField::Create(
				CObj3dField::TEX_GLASS_000,
				D3DXVECTOR3(-15000.0f + (1000.0f * nCutLine), 0.0f, 10000.0f - (1000.0f * nCutColu)),
				D3DXVECTOR3(500.0f, 0.0f, 500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	for (int nCount = 0; nCount < 32; nCount++)
	{
		CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			D3DXVECTOR3(-1000.0f, 100.0f * nCount, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			D3DXVECTOR3(9400.0f, 100.0f * nCount, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// スカイボックスの生成
	CSkybox::Create(
		CSkybox::MODEL_SKYBOX_000,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 時間の生成
	m_pTimer = CTimer::Create(
		D3DXVECTOR3(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.075f, 0.0f),
		D3DXVECTOR3(60.0f, 0.0f, 0.0f),
		D3DXVECTOR3(40.0f, 0.0f, 0.0f),
		D3DXVECTOR3(30.0f, 40.0f, 0.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	// 教えるオブジェクトの生成処理
	CObjTeach::Create(
		CObjTeach::TEX_TEACH_MOVE,
		D3DXVECTOR3(200.0f, 600.0f, 500.0f),
		D3DXVECTOR3(400.0f, 200.0f, 50.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CCsvStage *pCsvStage = CManager::GetInstance()->GetCsvStage();

	if (pCsvStage != NULL)
	{
		// CSVステージの設置
		pCsvStage->SetObj();
	}


	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲーム画面の終了処理
//-------------------------------------
void CGame::Uninit(void)
{
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	if (m_pTimer != NULL)
	{
		// 時間管理の終了処理
		m_pTimer->Uninit();

		// 時間管理の開放処理
		delete m_pTimer;
		m_pTimer = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- ゲーム画面の更新処理
//-------------------------------------
void CGame::Update(void)
{
	// キーボードの情報取得
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

	if (m_pTimer != NULL)
	{
		// 時間の更新処理
		m_pTimer->Update();
	}

	// 遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL )
	{
		// ゲームモード
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//- ゲーム画面の描画処理
//-------------------------------------
void CGame::Draw(void)
{

}

//-------------------------------------
//- ゲーム画面のプレイヤーの取得処理
//-------------------------------------
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

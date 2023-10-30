
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

#include "edit_map.h"
#include "file_map.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CPlayer *CGame::m_pPlayer = NULL;
CTimer *CGame::m_pTimer = NULL;
CEditMap *CGame::m_pEditMap = NULL;

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
	// カメラ位置の設定処理
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera == NULL)
	{
		return E_FAIL;
	}

	CFileMap *pFileMap = CManager::GetInstance()->GetFileMap();

	if (pFileMap == NULL)
	{
		return E_FAIL;
	}

	// カメラの設定処理
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	// マップのロード処理
	pFileMap->Load(CFileMap::TEXT_NORMAL);

	// スカイボックスの生成
	CSkybox::Create(
		CSkybox::MODEL_SKYBOX_000,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	if (m_pTimer == NULL)
	{
		// 時間の生成
		m_pTimer = CTimer::Create(
			D3DXVECTOR3(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.075f, 0.0f),
			D3DXVECTOR3(60.0f, 0.0f, 0.0f),
			D3DXVECTOR3(40.0f, 0.0f, 0.0f),
			D3DXVECTOR3(30.0f, 40.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_pPlayer == NULL)
	{
		// プレイヤーの生成
		m_pPlayer = CPlayer::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 位置
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),	// 向き
			CModel::MODEL_TYPE_PLAYER_AONOA,			// モデル
			CMotion::MOTION_TYPE_PLAYER_AONOA);			// モーション
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

	if (m_pEditMap != NULL)
	{
		// マップエディタの終了処理
		m_pEditMap->Uninit();

		// マップエディタの開放処理
		delete m_pEditMap;
		m_pEditMap = NULL;
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

	if (m_pEditMap == NULL)
	{
		if (m_pTimer != NULL)
		{
			// 時間の更新処理
			m_pTimer->Update();
		}

		// 遷移ボタン（えんたー）
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			// ゲームモード
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);

			return;
		}

		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{
			// エディットモードの生成処理
			m_pEditMap = CEditMap::Create();

			if (m_pPlayer != NULL)
			{
				// プレイヤーの更新停止
				m_pPlayer->IsUpdateStop(false);
			}
		}
	}
	else
	{
		// 更新処理
		m_pEditMap->Update();

		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{
			// 終了処理
			m_pEditMap->Uninit();

			// 開放処理
			delete m_pEditMap;
			m_pEditMap = NULL;

			if (m_pPlayer != NULL)
			{
				// プレイヤーの更新停止
				m_pPlayer->IsUpdateStop(true);
			}
		}
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

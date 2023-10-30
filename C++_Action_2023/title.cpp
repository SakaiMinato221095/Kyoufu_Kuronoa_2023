
//================================================
//=
//=	タイトル画面処理[title.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "title.h"

#include "camera.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "file_map.h"

#include "player.h"

#include "skybox.h"
#include "obj_3d_field.h"

#include "obj_2d_none.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CPlayer *CTitle::m_pPlayer = {};
CObj2dNone *CTitle::m_apObj2dNone[TYPE_NONE_2D_MAX] = {};

//-------------------------------------
//-	タイトルのコンストラクタ
//-------------------------------------
CTitle::CTitle()
{

}

//-------------------------------------
//-	タイトルのデストラクタ
//-------------------------------------
CTitle::~CTitle()
{

}

//-------------------------------------
//- タイトルの初期化処理
//-------------------------------------
HRESULT CTitle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
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
	pCamera->SetMode(CCamera::MODE_TITLE);

	// マップのロード処理
	pFileMap->Load(CFileMap::TEXT_TITLE);

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

	if (m_pPlayer == NULL)
	{
		// プレイヤーの生成
		m_pPlayer = CPlayer::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 位置
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),	// 向き
			CModel::MODEL_TYPE_PLAYER_AONOA,			// モデル
			CMotion::MOTION_TYPE_PLAYER_AONOA);			// モーション
	}

	// オブジェクト管理の生成
	m_apObj2dNone[TYPE_NONE_2D_LOGO] = CObj2dNone::Create(
		CObj2dNone::TEX_TITLE_LOGO,
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(300.0f, 150.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// オブジェクト管理の初期化処理
	if (m_apObj2dNone[TYPE_NONE_2D_LOGO] == NULL)
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "効果なし2Dオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

		// 初期化を抜ける
		return E_FAIL;
	}

	// オブジェクト管理の有無を判定
	if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
	{
		// オブジェクト管理の生成
		m_apObj2dNone[TYPE_NONE_2D_BUTTON] = CObj2dNone::Create(
			CObj2dNone::TEX_TITLE_BUTTON,
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f),
			D3DXVECTOR3(200.0f, 100.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// オブジェクト管理の初期化処理
		if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
		{// 失敗時

			// 失敗メッセージ
			MessageBox(hWnd, "効果なし2Dオブジェクトの生成", "初期処理失敗！", MB_ICONWARNING);

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
//- タイトルの終了処理
//-------------------------------------
void CTitle::Uninit(void)
{
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}
	for (int nCount = 0; nCount < TYPE_NONE_2D_MAX; nCount++)
	{
		m_apObj2dNone[nCount] = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- タイトルの更新処理
//-------------------------------------
void CTitle::Update(void)
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

	// 遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL || 
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// ゲームモード
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- タイトルの描画処理
//-------------------------------------
void CTitle::Draw(void)
{

}

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
#include "xinput.h"
#include "sound.h"

#include "player.h"
#include "player_battle.h"

#include "obj_3d_field.h"
#include "objectx_none.h"

#include "enemy.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

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
	// 戦闘ステータスの生成
	CPlayer *pPlayer = CPlayerBattle::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 位置
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),	// 向き
		CModel::MODEL_TYPE_PLAYER,					// モデル
		CMotion::MOTION_TYPE_PLAYER);				// モーション

	// 戦闘ステータスの初期化処理
	if (pPlayer == NULL)
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "戦闘プレイヤーの初期化", "初期処理失敗！", MB_ICONWARNING);

		// 初期化を抜ける
		return E_FAIL;
	}

	CObj3dField *pObj3dField = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

	pObj3dField->Set(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(5000.0f, 0.0f, 5000.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CEnemy *pEnemy = CEnemy::Create(CEnemy::MODEL_ALIEN_000);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ゲーム画面の終了処理
//-------------------------------------
void CGame::Uninit(void)
{
	// オブジェクトの全開放処理
	CObject::ReleaseAll();
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

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{
		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//- ゲーム画面の描画処理
//-------------------------------------
void CGame::Draw(void)
{

}

//-------------------------------------
//-	ポーズの情報を取得
//-------------------------------------
CPause * CGame::GetPause(void)
{
	return m_pPause;
}
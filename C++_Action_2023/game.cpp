
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

#include "obj_3d_field.h"
#include "objectx_none.h"

#include "enemy.h"

#include "gimmick_jewel.h"
#include "obj_block.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CPlayer *CGame::m_pPlayer = NULL;

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
	m_pPlayer = CPlayer::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// 位置
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),	// 向き
		CModel::MODEL_TYPE_PLAYER,					// モデル
		CMotion::MOTION_TYPE_PLAYER);				// モーション

	// 戦闘ステータスの初期化処理
	if (m_pPlayer == NULL)
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

	CEnemy *pEnemy1 = CEnemy::Create(CEnemy::MODEL_ALIEN_000);
	pEnemy1->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CEnemy *pEnemy2 = CEnemy::Create(CEnemy::MODEL_ALIEN_000);
	pEnemy2->Set(D3DXVECTOR3(300.0f, 0.0f, 0.0f));

	CEnemy *pEnemy3 = CEnemy::Create(CEnemy::MODEL_ALIEN_000);
	pEnemy3->Set(D3DXVECTOR3(600.0f, 0.0f, 0.0f));

	CGimmick *pGimmick = CGimmickJewel::Create(
		CGimmick::MODEL_JEWEL_000,
		CGimmickJewel::TYPE_EFFECT_SPEED_UP,
		D3DXVECTOR3(100.0f, 200.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectXNone *pBlock = CObjBlock::Create(
		CObjectXNone::MODEL_BLOCK_000,
		D3DXVECTOR3(-300.0f, 200.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	// 遷移ボタン（えんたー）
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
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

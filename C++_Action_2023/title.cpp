
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

#include "bg.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CBg *CTitle::m_pBg = {};

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
	// 背景の有無を判定
	if (m_pBg == NULL)
	{
		// 背景の生成処理
		m_pBg = CBg::Create(CBg::TEX_TITLE);

		// 背景の有無を判定
		if (m_pBg == NULL)
		{
			// 失敗を返す
			return E_FAIL;
		}

		// 背景の設定
		m_pBg->Set();
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- タイトルの終了処理
//-------------------------------------
void CTitle::Uninit(void)
{
	// 背景の初期化
	if(m_pBg != NULL)
	{
		m_pBg = NULL;
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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// ゲームモード
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- タイトルの描画処理
//-------------------------------------
void CTitle::Draw(void)
{

}

//-------------------------------------
//-	タイトルの背景の情報を取得
//-------------------------------------
CBg * CTitle::GetBg(void)
{
	return m_pBg;
}
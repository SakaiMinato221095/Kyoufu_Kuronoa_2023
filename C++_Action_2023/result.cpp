
//================================================
//=
//=	リザルト画面処理[result.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "result.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"

#include "manager.h"

#include "bg.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

CBg *CResult::m_pBg = NULL;			// 背景のポインタ

//-------------------------------------
//-	リザルトのコンストラクタ
//-------------------------------------
CResult::CResult()
{

}

//-------------------------------------
//-	リザルトのデストラクタ
//-------------------------------------
CResult::~CResult()
{

}

//-------------------------------------
//- リザルトの初期化処理
//-------------------------------------
HRESULT CResult::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// サウンドのポインタを宣言
	CSound *pSound = CManager::GetInstance()->GetSound();

	// サウンドの情報取得の成功を判定
	if (pSound == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// 背景の有無を判定
	if (m_pBg == NULL)
	{
		// 背景の生成処理
		m_pBg = CBg::Create(CBg::TEX_RESULT);

		// 背景の有無を判定
		if (m_pBg == NULL)
		{
			// 失敗を返す
			return E_FAIL;
		}

		// 背景の設定
		m_pBg->Set();
	}

	// タイトルの再生
	pSound->Play(CSound::LABEL_BGM_RESULT);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- リザルトの終了処理
//-------------------------------------
void CResult::Uninit(void)
{
	if (m_pBg != NULL)
	{
		m_pBg = NULL;
	}

	// オブジェクトの全開放処理
	CObject::ReleaseAll();
}

//-------------------------------------
//- リザルトの更新処理
//-------------------------------------
void CResult::Update(void)
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
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITEL);
	}

}

//-------------------------------------
//- リザルトの描画処理
//-------------------------------------
void CResult::Draw(void)
{

}

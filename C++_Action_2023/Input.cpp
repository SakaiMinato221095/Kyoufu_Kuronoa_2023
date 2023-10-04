
//================================================
//=
//= 入力の処理[Input.h]
//= Author Sakai Minato
//=
//================================================

#include "Input.h"

//-======================================
//-	静的変数宣言
//-======================================

LPDIRECTINPUT8 CInput::m_pInput = NULL;		// 入力処理のオブジェクトをクリア

//=====================================
//= 入力のコンストラクタ
//=====================================
CInput::CInput()
{
	// 値をクリア
	m_pDevice = NULL;
}

//=====================================
//= 入力のデストラクタ
//=====================================
CInput::~CInput()
{
}

//=====================================
//= 入力の初期化処理
//=====================================
HRESULT CInput::Init(HINSTANCE hInstanse, HWND hWnd)
{
	// 入力オブジェクトの有無を判定
	if (m_pInput == NULL)
	{
		// 入力オブジェクトの生成
		if (FAILED(DirectInput8Create(hInstanse, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{// 失敗時

			// 初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//=====================================
//= 入力の終了処理
//=====================================
void CInput::Uninit(void)
{
	// 入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		// アクセス権を破棄
		m_pDevice->Unacquire();	

		// 入力デバイスの開放処理
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// 入力オブジェクトの破棄
	if (m_pInput != NULL)
	{
		// 入力オブジェクトの開放処理
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=====================================
//= キーボードのコンストラクタ
//=====================================
CInputKeyboard::CInputKeyboard()
{
	// 値をクリア
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyState[nCount] = 0;
		m_aKeyStateTrigger[nCount] = 0;
		m_aKeyStateRelease[nCount] = 0;
	}
}

//=====================================
//= キーボードのデストラクタ
//=====================================
CInputKeyboard::~CInputKeyboard()
{
}

//=====================================
//= キーボードの初期化処理
//=====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstanse, HWND hWnd)
{
	// 入力の初期化処理
	if (FAILED(CInput::Init(hInstanse,hWnd)))
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// キーボードの入力デバイスを生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// キーボードのデータファーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// キーボードのアクセス権を獲得
	m_pDevice->Acquire();

	// 成功を返す
	return S_OK;
}

//=====================================
//= キーボードの終了処理
//=====================================
void CInputKeyboard::Uninit(void)
{
	// 入力の終了処理
	CInput::Uninit();
}

//=====================================
//= キーボードの更新処理
//=====================================
void CInputKeyboard::Update(void)
{
	// 変数宣言
	BYTE aKeyState[NUM_KEY_MAX];		// キーボードの入力情報

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
		{
			m_aKeyStateTrigger[nCount] = (m_aKeyState[nCount] ^ aKeyState[nCount]) & aKeyState[nCount];		// キーボードのトリガー情報

			m_aKeyStateRelease[nCount] = (aKeyState[nCount] ^ m_aKeyState[nCount]) & m_aKeyState[nCount];	// キーボードのリリース情報

			m_aKeyState[nCount] = aKeyState[nCount];														// キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();	// キーボードのアクセス権を獲得
	}
}

//=====================================
//= キーボードのブレスの情報を取得
//=====================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
//= キーボードのトリガーの情報を取得
//=====================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================
//= キーボードのリリースの情報を取得
//=====================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//================================================
//=
//= X入力の処理[xinput.h]
//= Author Sakai Minato
//=
//================================================

#include "xinput.h"

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//- X入力のコンストラクタ
//-------------------------------------
CXInput::CXInput()
{
	// 値をクリア
	ZeroMemory(&m_gamepad, sizeof(XINPUT_GAMEPAD));
	ZeroMemory(&m_gamepadOld, sizeof(XINPUT_GAMEPAD));

	ZeroMemory(&m_aStickRight, sizeof(m_aStickRight[CXInput::TYPE_STICK_MAX]));
	ZeroMemory(&m_aStickLeft, sizeof(m_aStickLeft[CXInput::TYPE_STICK_MAX]));
	ZeroMemory(&m_aStickRightOld, sizeof(m_aStickRightOld[CXInput::TYPE_STICK_MAX]));
	ZeroMemory(&m_aStickLeftOld, sizeof(m_aStickLeftOld[CXInput::TYPE_STICK_MAX]));

	m_bTriggerRight = false;
	m_bTriggerLeft = false;
	m_bTriggerRightOld = false;
	m_bTriggerLeftOld = false;
}

//-------------------------------------
//- X入力のデストラクタ
//-------------------------------------
CXInput::~CXInput()
{
}

//-------------------------------------
//- X入力の初期化処理
//-------------------------------------
HRESULT CXInput::Init(HINSTANCE hInstanse, HWND hWnd)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- X入力の終了処理
//-------------------------------------
void CXInput::Uninit(void)
{
	XInputEnable(false); // BOOL enable
}

//-------------------------------------
//- X入力の更新処理
//-------------------------------------
void CXInput::Update(void)
{
	// 変数宣言
	XINPUT_STATE state;							// ゲームパッドの状態を取得
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// ゲームパッドの状態を判定
	if (XInputGetState(0,&state) == ERROR_SUCCESS)
	{
		// 前回の入力情報を上書き
		m_gamepadOld = m_gamepad;

		memcpy(&m_aStickRightOld,m_aStickRight,sizeof(m_aStickRight[TYPE_STICK_MAX]));
		memcpy(&m_aStickLeftOld,m_aStickLeft,sizeof(m_aStickLeft[TYPE_STICK_MAX]));

		m_bTriggerRightOld = m_bTriggerRight;
		m_bTriggerLeftOld = m_bTriggerLeft;

		// 入力情報を代入
		m_gamepad = state.Gamepad;

		// 各入力の情報を代入
		UpdateTrigger();
		UpdateStick();
	}
	else
	{
		return;
	}
}

//-------------------------------------
//- X入力の生成処理
//-------------------------------------
CXInput *CXInput::Create(HINSTANCE hInstance, HWND hWnd)
{
	// X入力のポインタを宣言
	CXInput *pCXinput = DBG_NEW CXInput;

	// 生成の成功の有無を判定
	if (pCXinput != NULL)
	{
		// 初期化処理
		if (FAILED(pCXinput->Init(hInstance,hWnd)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCXinput == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// X入力のポインタを返す
	return pCXinput;
}

//-------------------------------------
//- X入力のプレス情報の取得処理
//-------------------------------------
bool CXInput::GetPress(int nKey, TYPE_INPUT type)
{
	switch (type)
	{
	case TYPE_INPUT_BUTTON:

		return(m_gamepad.wButtons & nKey) ? true : false;

		break;

	case TYPE_INPUT_TRIGGER_R:

		return(m_bTriggerRight);

		break;

	case TYPE_INPUT_TRIGGER_L:

		return(m_bTriggerLeft);

		break;

	case TYPE_INPUT_STICK_R:

		return(m_aStickRight[nKey]);

		break;

	case TYPE_INPUT_STICK_L:

		return(m_aStickLeft[nKey]);

		break;
	}

	return false;
}

//-------------------------------------
//- X入力のトリガー情報の取得処理
//-------------------------------------
bool CXInput::GetTrigger(int nKey, TYPE_INPUT type)
{
	switch (type)
	{
	case TYPE_INPUT_BUTTON:
	
		return(
			m_gamepad.wButtons & nKey &&
			m_gamepad.wButtons != m_gamepadOld.wButtons) ? true : false;

		break;


	case TYPE_INPUT_TRIGGER_R:

		return(m_bTriggerRight && m_bTriggerRightOld) ? true : false;

		break;

	case TYPE_INPUT_TRIGGER_L:

		return(m_bTriggerLeft && m_bTriggerLeftOld) ? true : false;

		break;

	case TYPE_INPUT_STICK_R:

		return(m_aStickRight[nKey] && m_aStickRightOld[nKey]) ? true : false;

		break;

	case TYPE_INPUT_STICK_L:

		return(m_aStickLeft[nKey] && m_aStickLeftOld[nKey]) ? true : false;

		break;
	}

	return false;
}

//-------------------------------------
//- X入力のトリガーの更新処理
//-------------------------------------
void CXInput::UpdateTrigger(void)
{
	// 右トリガーの判定
	if (m_gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_bTriggerRight = true;
	}

	// 左トリガーの判定
	if (m_gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_bTriggerLeft = true;
	}
}

//-------------------------------------
//- X入力のスティックの更新処理
//-------------------------------------
void CXInput::UpdateStick(void)
{
	//// 右スティック
	// スティックの上が押された
	if (m_gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_UP] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_UP] = false;
	}

	// スティックの下が押された
	if (m_gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_DOWN] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_DOWN] = false;
	}

	// スティックの左が押された
	if (m_gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_LEFT] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_LEFT] = false;
	}

	// スティックの右が押された
	if (m_gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_RIGHT] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_RIGHT] = false;
	}

	//// 左スティック
	// スティックの上が押された
	if (m_gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_UP] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_UP] = false;
	}

	// スティックの下が押された
	if (m_gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_DOWN] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_DOWN] = false;
	}

	// スティックの左が押された
	if (m_gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_LEFT] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_LEFT] = false;
	}

	// スティックの右が押された
	if (m_gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_RIGHT] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_RIGHT] = false;
	}
}
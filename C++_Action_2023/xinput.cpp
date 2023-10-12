
//================================================
//=
//= X���͂̏���[xinput.h]
//= Author Sakai Minato
//=
//================================================

#include "xinput.h"

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//- X���͂̃R���X�g���N�^
//-------------------------------------
CXInput::CXInput()
{
	// �l���N���A
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
//- X���͂̃f�X�g���N�^
//-------------------------------------
CXInput::~CXInput()
{
}

//-------------------------------------
//- X���͂̏���������
//-------------------------------------
HRESULT CXInput::Init(HINSTANCE hInstanse, HWND hWnd)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- X���͂̏I������
//-------------------------------------
void CXInput::Uninit(void)
{
	XInputEnable(false); // BOOL enable
}

//-------------------------------------
//- X���͂̍X�V����
//-------------------------------------
void CXInput::Update(void)
{
	// �ϐ��錾
	XINPUT_STATE state;							// �Q�[���p�b�h�̏�Ԃ��擾
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// �Q�[���p�b�h�̏�Ԃ𔻒�
	if (XInputGetState(0,&state) == ERROR_SUCCESS)
	{
		// �O��̓��͏����㏑��
		m_gamepadOld = m_gamepad;

		memcpy(&m_aStickRightOld,m_aStickRight,sizeof(m_aStickRight[TYPE_STICK_MAX]));
		memcpy(&m_aStickLeftOld,m_aStickLeft,sizeof(m_aStickLeft[TYPE_STICK_MAX]));

		m_bTriggerRightOld = m_bTriggerRight;
		m_bTriggerLeftOld = m_bTriggerLeft;

		// ���͏�����
		m_gamepad = state.Gamepad;

		// �e���͂̏�����
		UpdateTrigger();
		UpdateStick();
	}
	else
	{
		return;
	}
}

//-------------------------------------
//- X���͂̐�������
//-------------------------------------
CXInput *CXInput::Create(HINSTANCE hInstance, HWND hWnd)
{
	// X���͂̃|�C���^��錾
	CXInput *pCXinput = DBG_NEW CXInput;

	// �����̐����̗L���𔻒�
	if (pCXinput != NULL)
	{
		// ����������
		if (FAILED(pCXinput->Init(hInstance,hWnd)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCXinput == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// X���͂̃|�C���^��Ԃ�
	return pCXinput;
}

//-------------------------------------
//- X���͂̃v���X���̎擾����
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
//- X���͂̃g���K�[���̎擾����
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
//- X���͂̃g���K�[�̍X�V����
//-------------------------------------
void CXInput::UpdateTrigger(void)
{
	// �E�g���K�[�̔���
	if (m_gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_bTriggerRight = true;
	}

	// ���g���K�[�̔���
	if (m_gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		m_bTriggerLeft = true;
	}
}

//-------------------------------------
//- X���͂̃X�e�B�b�N�̍X�V����
//-------------------------------------
void CXInput::UpdateStick(void)
{
	//// �E�X�e�B�b�N
	// �X�e�B�b�N�̏オ�����ꂽ
	if (m_gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_UP] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_UP] = false;
	}

	// �X�e�B�b�N�̉��������ꂽ
	if (m_gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_DOWN] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_DOWN] = false;
	}

	// �X�e�B�b�N�̍��������ꂽ
	if (m_gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_LEFT] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_LEFT] = false;
	}

	// �X�e�B�b�N�̉E�������ꂽ
	if (m_gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		m_aStickRight[TYPE_STICK_RIGHT] = true;
	}
	else
	{
		m_aStickRight[TYPE_STICK_RIGHT] = false;
	}

	//// ���X�e�B�b�N
	// �X�e�B�b�N�̏オ�����ꂽ
	if (m_gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_UP] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_UP] = false;
	}

	// �X�e�B�b�N�̉��������ꂽ
	if (m_gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_DOWN] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_DOWN] = false;
	}

	// �X�e�B�b�N�̍��������ꂽ
	if (m_gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_LEFT] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_LEFT] = false;
	}

	// �X�e�B�b�N�̉E�������ꂽ
	if (m_gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_aStickLeft[TYPE_STICK_RIGHT] = true;
	}
	else
	{
		m_aStickLeft[TYPE_STICK_RIGHT] = false;
	}
}
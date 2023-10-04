
//================================================
//=
//= ���͂̏���[Input.h]
//= Author Sakai Minato
//=
//================================================

#include "Input.h"

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

LPDIRECTINPUT8 CInput::m_pInput = NULL;		// ���͏����̃I�u�W�F�N�g���N���A

//=====================================
//= ���͂̃R���X�g���N�^
//=====================================
CInput::CInput()
{
	// �l���N���A
	m_pDevice = NULL;
}

//=====================================
//= ���͂̃f�X�g���N�^
//=====================================
CInput::~CInput()
{
}

//=====================================
//= ���͂̏���������
//=====================================
HRESULT CInput::Init(HINSTANCE hInstanse, HWND hWnd)
{
	// ���̓I�u�W�F�N�g�̗L���𔻒�
	if (m_pInput == NULL)
	{
		// ���̓I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstanse, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{// ���s��

			// �����������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//=====================================
//= ���͂̏I������
//=====================================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		// �A�N�Z�X����j��
		m_pDevice->Unacquire();	

		// ���̓f�o�C�X�̊J������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// ���̓I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		// ���̓I�u�W�F�N�g�̊J������
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=====================================
//= �L�[�{�[�h�̃R���X�g���N�^
//=====================================
CInputKeyboard::CInputKeyboard()
{
	// �l���N���A
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		m_aKeyState[nCount] = 0;
		m_aKeyStateTrigger[nCount] = 0;
		m_aKeyStateRelease[nCount] = 0;
	}
}

//=====================================
//= �L�[�{�[�h�̃f�X�g���N�^
//=====================================
CInputKeyboard::~CInputKeyboard()
{
}

//=====================================
//= �L�[�{�[�h�̏���������
//=====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstanse, HWND hWnd)
{
	// ���͂̏���������
	if (FAILED(CInput::Init(hInstanse,hWnd)))
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �L�[�{�[�h�̓��̓f�o�C�X�𐶐�
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �L�[�{�[�h�̃f�[�^�t�@�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	// ������Ԃ�
	return S_OK;
}

//=====================================
//= �L�[�{�[�h�̏I������
//=====================================
void CInputKeyboard::Uninit(void)
{
	// ���͂̏I������
	CInput::Uninit();
}

//=====================================
//= �L�[�{�[�h�̍X�V����
//=====================================
void CInputKeyboard::Update(void)
{
	// �ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
		{
			m_aKeyStateTrigger[nCount] = (m_aKeyState[nCount] ^ aKeyState[nCount]) & aKeyState[nCount];		// �L�[�{�[�h�̃g���K�[���

			m_aKeyStateRelease[nCount] = (aKeyState[nCount] ^ m_aKeyState[nCount]) & m_aKeyState[nCount];	// �L�[�{�[�h�̃����[�X���

			m_aKeyState[nCount] = aKeyState[nCount];														// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();	// �L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//=====================================
//= �L�[�{�[�h�̃u���X�̏����擾
//=====================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//=====================================
//= �L�[�{�[�h�̃g���K�[�̏����擾
//=====================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=====================================
//= �L�[�{�[�h�̃����[�X�̏����擾
//=====================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
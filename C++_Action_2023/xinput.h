
//-===============================================
//-
//- X���͏����̃w�b�_�[[xinput.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _X_INPUT_H_	//���̃}�N������`����Ȃ�������
#define _X_INPUT_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// ���͏����̃N���X
class CXInput
{
public:

	// ���͎��
	typedef enum
	{
		TYPE_INPUT_BUTTON = 0,	// �{�^��
		TYPE_INPUT_TRIGGER_R,	// �E�g���K�[
		TYPE_INPUT_TRIGGER_L,	// ���g���K�[
		TYPE_INPUT_STICK_R,		// �E�X�e�B�b�N
		TYPE_INPUT_STICK_L,		// ���X�e�B�b�N
		TYPE_INPUT_MAX
	}TYPE_INPUT;

	// �X�e�B�b�N����
	typedef enum
	{
		TYPE_STICK_NONE = 0,	// �����Ȃ�
		TYPE_STICK_UP,			// �����
		TYPE_STICK_DOWN,		// ������
		TYPE_STICK_LEFT,		// ������
		TYPE_STICK_RIGHT,		// �E����
		TYPE_STICK_MAX,
	}TYPE_STICK;

	CXInput();
	~CXInput();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	static CXInput *Create(HINSTANCE hInstance, HWND hWnd);

	bool GetPress(int nKey, TYPE_INPUT type);
	bool GetTrigger(int nKey, TYPE_INPUT type);

protected:

	void UpdateTrigger(void);
	void UpdateStick(void);

	static LPDIRECTINPUT8 m_pInput;			// ���͏����̃I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 m_pDevice;			// ���͏����̃f�o�C�X

	XINPUT_GAMEPAD m_gamepad;				// �Q�[���p�b�h�̓��͏��
	XINPUT_GAMEPAD m_gamepadOld;			// �O��̃Q�[���p�b�h�̓��͏��

	bool m_aStickRight[TYPE_STICK_MAX];		// �E�X�e�B�b�N�����̗L�� 
	bool m_aStickLeft[TYPE_STICK_MAX];		// ���X�e�B�b�N�����̗L��

	bool m_aStickRightOld[TYPE_STICK_MAX];	// �O��̉E�X�e�B�b�N�����̗L�� 
	bool m_aStickLeftOld[TYPE_STICK_MAX];	// �O��̍��X�e�B�b�N�����̗L��

	bool m_bTriggerRight;					// �E�g���K�[�̗L�� 
	bool m_bTriggerLeft;					// ���g���K�[�̗L��

	bool m_bTriggerRightOld;				// �O��̉E�g���K�[�̗L�� 
	bool m_bTriggerLeftOld;					// �O��̍��g���K�[�̗L��
};

#endif

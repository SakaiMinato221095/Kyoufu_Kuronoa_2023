
//-===============================================
//-
//- ���͏����̃w�b�_�[[input.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _INPUT_H_	//���̃}�N������`����Ȃ�������
#define _INPUT_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

//-======================================
//-	�}�N����`
//-======================================

#define NUM_KEY_MAX		(256)	// �L�[�̍ő吔

//-======================================
//-	�N���X��`
//-======================================

// ���͏����̃N���X
class CInput
{
public:

	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:

	static LPDIRECTINPUT8 m_pInput;		// ���͏����̃I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 m_pDevice;		// ���͏����̃f�o�C�X

};

// �L�[�{�[�h�̓��͏����i���͏����̎q�N���X�j
class CInputKeyboard : public CInput
{
public:

	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];					// �L�[�{�[�h�̃u���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// �L�[�{�[�h�̃g���K�[���
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			// �L�[�{�[�h�̃����[�X���

};

#endif 
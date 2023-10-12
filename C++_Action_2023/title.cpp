
//================================================
//=
//=	�^�C�g����ʏ���[title.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "title.h"

#include "camera.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "bg.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CBg *CTitle::m_pBg = {};

//-------------------------------------
//-	�^�C�g���̃R���X�g���N�^
//-------------------------------------
CTitle::CTitle()
{

}

//-------------------------------------
//-	�^�C�g���̃f�X�g���N�^
//-------------------------------------
CTitle::~CTitle()
{

}

//-------------------------------------
//- �^�C�g���̏���������
//-------------------------------------
HRESULT CTitle::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �w�i�̗L���𔻒�
	if (m_pBg == NULL)
	{
		// �w�i�̐�������
		m_pBg = CBg::Create(CBg::TEX_TITLE);

		// �w�i�̗L���𔻒�
		if (m_pBg == NULL)
		{
			// ���s��Ԃ�
			return E_FAIL;
		}

		// �w�i�̐ݒ�
		m_pBg->Set();
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�g���̏I������
//-------------------------------------
void CTitle::Uninit(void)
{
	// �w�i�̏�����
	if(m_pBg != NULL)
	{
		m_pBg = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- �^�C�g���̍X�V����
//-------------------------------------
void CTitle::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// �J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL || 
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- �^�C�g���̕`�揈��
//-------------------------------------
void CTitle::Draw(void)
{

}

//-------------------------------------
//-	�^�C�g���̔w�i�̏����擾
//-------------------------------------
CBg * CTitle::GetBg(void)
{
	return m_pBg;
}
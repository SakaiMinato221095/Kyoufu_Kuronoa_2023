
//================================================
//=
//=	���U���g��ʏ���[result.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "result.h"

#include "fade.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"

#include "manager.h"

#include "bg.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CBg *CResult::m_pBg = NULL;			// �w�i�̃|�C���^

//-------------------------------------
//-	���U���g�̃R���X�g���N�^
//-------------------------------------
CResult::CResult()
{

}

//-------------------------------------
//-	���U���g�̃f�X�g���N�^
//-------------------------------------
CResult::~CResult()
{

}

//-------------------------------------
//- ���U���g�̏���������
//-------------------------------------
HRESULT CResult::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetInstance()->GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// �w�i�̗L���𔻒�
	if (m_pBg == NULL)
	{
		// �w�i�̐�������
		m_pBg = CBg::Create(CBg::TEX_RESULT);

		// �w�i�̗L���𔻒�
		if (m_pBg == NULL)
		{
			// ���s��Ԃ�
			return E_FAIL;
		}

		// �w�i�̐ݒ�
		m_pBg->Set();
	}

	// �^�C�g���̍Đ�
	pSound->Play(CSound::LABEL_BGM_RESULT);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- ���U���g�̏I������
//-------------------------------------
void CResult::Uninit(void)
{
	if (m_pBg != NULL)
	{
		m_pBg = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- ���U���g�̍X�V����
//-------------------------------------
void CResult::Update(void)
{
	// �L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	// X���͂̃|�C���^��錾
	CXInput *pXInput = CManager::GetInstance()->GetXInput();

	// X���͂̏��擾�̐����𔻒�
	if (pXInput == NULL)
	{
		// �����𔲂���
		return;
	}

	// �J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{
		// �Q�[�����[�h
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_TITEL);
	}

}

//-------------------------------------
//- ���U���g�̕`�揈��
//-------------------------------------
void CResult::Draw(void)
{

}

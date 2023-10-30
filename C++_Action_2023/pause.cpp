
//================================================
//=
//=	�|�[�Y��ʏ���[pause.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "main.h"

#include "pause.h"

#include "manager.h"
#include "fade.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"

#include "obj_2d_none.h"

//=======================================
//=	�}�N����`
//=======================================

#define WINDOW_POS_X		(SCREEN_WIDTH * 0.5f)	//�|�[�Y�̘g�̈ʒu(X)
#define WINDOW_POS_Y		(SCREEN_HEIGHT * 0.5f)	//�|�[�Y�̘g�̈ʒu(Y)
#define WINDOW_SIZE_X		(300.0f)				//�|�[�Y�̘g�̃T�C�Y(X)
#define WINDOW_SIZE_Y		(200.0f)				//�|�[�Y�̘g�̃T�C�Y(Y)
#define MENU_POS_X			(SCREEN_WIDTH * 0.5f)	//�|�[�Y���j���[�̍ŏ��̊J�n�ʒu�iX)
#define MENU_POS_Y			(230.0f)				//�|�[�Y���j���[�̍ŏ��̊J�n�ʒu�iY�j	
#define MENU_SIZE_X			(200.0f)				//�|�[�Y���j���[�̑傫���iX�j
#define MENU_SIZE_Y			(60.0f)					//�|�[�Y���j���[�̑傫���iY�j
#define MENU_INTERVAL_Y		(130.0f)				//�|�[�Y���j���[�̊Ԋu�iY�j

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CObj2dNone *CPause::m_apObj2dNone[TYPE_MAX] = {};

//-------------------------------------
//-	�|�[�Y�̃R���X�g���N�^
//-------------------------------------
CPause::CPause()
{
	m_typeSelect = (TYPE_SELECT)0;
}

//-------------------------------------
//-	�|�[�Y�̃f�X�g���N�^
//-------------------------------------
CPause::~CPause()
{

}

//-------------------------------------
//- �|�[�Y�̏���������
//-------------------------------------
HRESULT CPause::Init(void)
{
	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_apObj2dNone[TYPE_BG] == NULL)
	{
		// �I�u�W�F�N�g�Ǘ��̐���
		m_apObj2dNone[TYPE_BG] = CObj2dNone::Create(
			CObj2dNone::TEX_PAUSE_BG,
			D3DXVECTOR3(WINDOW_POS_X, WINDOW_POS_Y, 0.0f),
			D3DXVECTOR3(WINDOW_SIZE_X, WINDOW_SIZE_Y, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �I�u�W�F�N�g�Ǘ��̏���������
		if (m_apObj2dNone[TYPE_BG] == NULL)
		{// ���s��

			// �������𔲂���
			return E_FAIL;
		}
	}
	else
	{// �S�~�������Ă���Ƃ�

		// �������𔲂���
		return E_FAIL;
	}

	for (int nCutPause = TYPE_GAME; nCutPause < TYPE_TITLE + 1; nCutPause++)
	{
		// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_apObj2dNone[nCutPause] == NULL)
		{
			if (nCutPause == TYPE_GAME)
			{
				// �I�u�W�F�N�g�Ǘ��̐���
				m_apObj2dNone[nCutPause] = CObj2dNone::Create(
					CObj2dNone::TEX_PAUSE_GAME,
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
			}
			else if (nCutPause == TYPE_RETRY)
			{
				// �I�u�W�F�N�g�Ǘ��̐���
				m_apObj2dNone[nCutPause] = CObj2dNone::Create(
					CObj2dNone::TEX_PAUSE_RETRY,
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCutPause == TYPE_TITLE)
			{
				// �I�u�W�F�N�g�Ǘ��̐���
				m_apObj2dNone[nCutPause] = CObj2dNone::Create(
					CObj2dNone::TEX_PAUSE_TITLE,
					D3DXVECTOR3(MENU_POS_X, MENU_POS_Y + (MENU_INTERVAL_Y * (nCutPause - 1)), 0.0f),
					D3DXVECTOR3(MENU_SIZE_X, MENU_SIZE_Y, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}

			// �I�u�W�F�N�g�Ǘ��̏���������
			if (m_apObj2dNone[nCutPause] == NULL)
			{// ���s��

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // �������𔲂���
			return E_FAIL;
		}
	}

	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_apObj2dNone[TYPE_CURSOR] == NULL)
	{
		// �I�u�W�F�N�g�Ǘ��̐���
		m_apObj2dNone[TYPE_CURSOR] = CObj2dNone::Create(
			CObj2dNone::TEX_PAUSE_CURSOR,
			D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y, 0.0f),
			D3DXVECTOR3(30.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �I�u�W�F�N�g�Ǘ��̏���������
		if (m_apObj2dNone[TYPE_CURSOR] == NULL)
		{// ���s��

			// �������𔲂���
			return E_FAIL;
		}

	}
	else
	{// �S�~�������Ă���Ƃ�

		// �������𔲂���
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �|�[�Y�̏I������
//-------------------------------------
void CPause::Uninit(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apObj2dNone[nCount] != NULL)
		{
			// ���ʂȂ�2D�I�u�W�F�N�g�̊J������
			m_apObj2dNone[nCount]->Uninit();
			m_apObj2dNone[nCount] = NULL;
		}
	}

	// �������g�̊J������
	Release();
}

//-------------------------------------
//- �|�[�Y�̍X�V����
//-------------------------------------
void CPause::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
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

	for (int nCutPause = 0; nCutPause < TYPE_MAX; nCutPause++)
	{
		if (m_apObj2dNone[nCutPause] != NULL)
		{
			// 2D�̍X�V����
			m_apObj2dNone[nCutPause]->Update();
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_W) != NULL)
	{
		// ��ނ����Z
		m_typeSelect = (TYPE_SELECT)(m_typeSelect - 1);

		if (m_typeSelect < 0)
		{
			m_typeSelect = TYPE_SELECT_TITLE;
		}

		CObject2d::VtxData vtxData = m_apObj2dNone[TYPE_CURSOR]->GetVtxData();

		vtxData.pos = D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect), 0.0f);

		m_apObj2dNone[TYPE_CURSOR]->SetVtxData(vtxData);

	}
	else if (pInputKeyboard->GetTrigger(DIK_S) != NULL)
	{
		// ��ނ����Z
		m_typeSelect = (TYPE_SELECT)(m_typeSelect + 1);

		if (m_typeSelect > TYPE_SELECT_TITLE)
		{
			m_typeSelect = (TYPE_SELECT)0;
		}

		CObject2d::VtxData vtxData = m_apObj2dNone[TYPE_CURSOR]->GetVtxData();

		vtxData.pos = D3DXVECTOR3(MENU_POS_X - 250.0f, MENU_POS_Y + (MENU_INTERVAL_Y * m_typeSelect), 0.0f);

		m_apObj2dNone[TYPE_CURSOR]->SetVtxData(vtxData);
	}
	
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL)
	{
		m_bOk = true;
	}
}

//-------------------------------------
//- �|�[�Y�̕`�揈��
//-------------------------------------
void CPause::Draw(void)
{

}

//-------------------------------------
//- �|�[�Y�̐�������
//-------------------------------------
CPause *CPause::Create(void)
{
	// �|�[�Y�̐���
	CPause *pCPause = DBG_NEW CPause;

	// �����̐����̗L���𔻒�
	if (pCPause != NULL)
	{
		// ����������
		if (FAILED(pCPause->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPause == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�[�Y�̃|�C���^��Ԃ�
	return pCPause;
}

//-------------------------------------
//-	���ʂȂ�2d�I�u�W�F�N�g�̏����擾
//-------------------------------------
CObj2dNone * CPause::GetObj2dNone(int nNum)
{
	return m_apObj2dNone[nNum];
}

//-------------------------------------
//-	�|�[�Y�I���̏����擾
//-------------------------------------
CPause::TYPE_SELECT CPause::GetTypeSelect(void)
{
	return m_typeSelect;
}

bool CPause::GetOk(void)
{
	return m_bOk;
}

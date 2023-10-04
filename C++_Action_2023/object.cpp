
//-===============================================
//-
//-	�I�u�W�F�N�g����[object.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "manager.h"
#include "debugproc.h"

#include "Input.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CObject *CObject::m_apObject[OBJECT_PRIORITY_MAX][OBJECT_NUM_MAX] = {};
int CObject::m_nNumAll = 0;
CDataBool CObject::m_bDataStopAllUpdate = {};

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CObject::CObject(int nPriority)
{
	// �|�C���^��ݒ�
	for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
	{
		if (m_apObject[nPriority][nCountObj] == NULL)
		{
			// �����̃|�C���^����
			m_apObject[nPriority][nCountObj] = this;

			// �����̃A�h���X�ԍ���ݒ�
			m_nID = nCountObj;

			// �����̗D�揇�ʂ�ݒ�
			m_nPriority = nPriority;

			// �I�u�W�F�N�g�̑��������Z
			m_nNumAll++;

			break;
		}
	}

	// �l���N���A
	m_type = TYPE_NONE;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CObject::~CObject()
{
}

//-------------------------------------
//-	�S�J������
//-------------------------------------
void CObject::ReleaseAll(void)
{
	// �S�I�u�W�F�N�g�|�C���^���J��
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// �I������
				m_apObject[nCountPrio][nCountObj]->Uninit();
			}
		}
	}
}

//-------------------------------------
//-	�S�X�V����
//-------------------------------------
void CObject::UpdateAll(void)
{
	// �L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// ���擾
	bool m_bStopAllUpdate = m_bDataStopAllUpdate.Get();	// �S�X�V��~�̗L��

	// ���̑J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_P) != NULL)
	{
		m_bStopAllUpdate = m_bStopAllUpdate ? false : true;
	}

	if (m_bStopAllUpdate == false)
	{
		// �S�I�u�W�F�N�g�|�C���^�̏����X�V
		for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
		{
			for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
			{
				if (m_apObject[nCountPrio][nCountObj] != NULL)
				{
					// �X�V����
					m_apObject[nCountPrio][nCountObj]->Update();
				}
			}
		}
	}

	// ���X�V
	m_bDataStopAllUpdate.Set(m_bStopAllUpdate);

	// �f�o�b�N�\��
	Debug();
}

//-------------------------------------
//-	�S�`�揈��
//-------------------------------------
void CObject::DrawAll(void)
{
	// �S�I�u�W�F�N�g�|�C���^�̏���`��
	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// ��񂵕`��̗L��
				if (m_apObject[nCountPrio][nCountObj]->m_bDataAfterDraw.Get() == false)
				{
					// �`�揈��
					m_apObject[nCountPrio][nCountObj]->Draw();
				}
			}
		}
	}

	for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
	{
		for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
		{
			if (m_apObject[nCountPrio][nCountObj] != NULL)
			{
				// ��񂵕`��̗L��
				if (m_apObject[nCountPrio][nCountObj]->m_bDataAfterDraw.Get() == true)
				{
					// �`�揈��
					m_apObject[nCountPrio][nCountObj]->Draw();

					// ��񂵕`��̂Ȃ���
					m_apObject[nCountPrio][nCountObj]->m_bDataAfterDraw.Set(false);
				}
			}
		}
	}
}

//-------------------------------------
//-	��ނ̐ݒ菈��
//-------------------------------------
void CObject::SetType(TYPE type)
{
	// ��ނ�ݒ�
	m_type = type;
}

//-------------------------------------
//-	��ނ̎擾����
//-------------------------------------
CObject::TYPE CObject::GetType(void)
{
	// ��ނ�Ԃ�
	return m_type;
}

//-------------------------------------
//-	�I�u�W�F�N�g�̎擾����
//-------------------------------------
CObject * CObject::GetObject(int nPriority, int nldx)
{
	// ��ނ�Ԃ�
	return m_apObject[nPriority][nldx];
}

//-------------------------------------
//-	2D�I�u�W�F�N�g�̎擾����
//-------------------------------------
CObject2d *CObject::GetObject2d(void)
{
	// �Ȃ���Ԃ�
	return NULL;
}

//-------------------------------------
//-	���d�w�i�̎擾����
//-------------------------------------
CBgMulti *CObject::GetBgMulti(void)
{
	// �Ȃ���Ԃ�
	return NULL;
}

//-------------------------------------
//-	�J������
//-------------------------------------
void CObject::Release(void)
{
	// ID����
	int nID = m_nID;
	int nPrio = m_nPriority;

	// �I�u�W�F�N�g�̔j��
	if (m_apObject[m_nID] != NULL)
	{
		// �I�u�W�F�N�g�̊J��
		delete m_apObject[nPrio][nID];
		m_apObject[nPrio][nID] = NULL;

		// �I�u�W�F�N�g�̑��������Z
		m_nNumAll--;
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CObject::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�I�u�W�F�N�g����\n");
	pDebugProc->Print("%d", m_nNumAll);
	pDebugProc->Print("\n");
}
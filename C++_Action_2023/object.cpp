
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
bool CObject::m_bIsUpdateAll = true;

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

	m_bIsUpdate = true;
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// �S�I�u�W�F�N�g�|�C���^�̏����X�V
	if (m_bIsUpdateAll == true)
	{
		for (int nCountPrio = 0; nCountPrio < OBJECT_PRIORITY_MAX; nCountPrio++)
		{
			for (int nCountObj = 0; nCountObj < OBJECT_NUM_MAX; nCountObj++)
			{
				if (m_apObject[nCountPrio][nCountObj] != NULL)
				{
					if (m_apObject[nCountPrio][nCountObj]->m_bIsUpdate == true)
					{
						if (m_apObject[nCountPrio][nCountObj]->m_bIsUpdate == false)
						{
							int ndata = 0;
							ndata = 1;
						}

						// �X�V����
						m_apObject[nCountPrio][nCountObj]->Update();
					}
				}
			}
		}
	}

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
				// �`�揈��
				m_apObject[nCountPrio][nCountObj]->Draw();
			}
		}
	}
}

//-------------------------------------
//- �I�u�W�F�N�g�̍X�V�̗L��
//-------------------------------------
void CObject::IsUpdateStop(bool bIsUpdate)
{
	m_bIsUpdate = bIsUpdate;
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
//-	�S�X�V�̗L���̎擾����
//-------------------------------------
bool CObject::GetIsUpdateAll(void)
{
	return m_bIsUpdateAll;
}

//-------------------------------------
//-	�S�X�V�̗L���̐ݒ菈��
//-------------------------------------
void CObject::SetIsUpdateAll(bool bIsUpdateAll)
{
	m_bIsUpdateAll = bIsUpdateAll;
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
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

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
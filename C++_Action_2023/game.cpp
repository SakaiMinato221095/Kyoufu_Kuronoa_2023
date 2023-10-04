
//================================================
//=
//=	�Q�[����ʏ���[game.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "game.h"

#include "fade.h"

#include "input.h"
#include "sound.h"

#include "time_stop.h"

#include "sys_game_phase.h"
#include "timer.h"

#include "pause.h"

#include "mgr_sys_obj.h"

#include "manager_object.h"

#include "state_game.h"
#include "state_battle.h"
#include "state_mode.h"

#include "ui_mission.h"
#include "ui_start_text.h"

#include "file_garbage.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CSysGamePhase *CGame::m_pSysGamePhase = NULL;

CMgrSysObj *CGame::m_pMgrSysObj = NULL;

CStateGame *CGame::m_pStateGame = NULL;
CStateBattle *CGame::m_pStateBattle = NULL;

CPause *CGame::m_pPause = NULL;

//-------------------------------------
//-	�Q�[����ʂ̃R���X�g���N�^
//-------------------------------------
CGame::CGame()
{
	m_game = (GAME)0;
}

//-------------------------------------
//-	�Q�[����ʂ̃f�X�g���N�^
//-------------------------------------
CGame::~CGame()
{

}

//-------------------------------------
//- �Q�[����ʂ̏���������
//-------------------------------------
HRESULT CGame::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̐�������
	{
		// �V�X�e���I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_pMgrSysObj == NULL)
		{
			// �V�X�e���I�u�W�F�N�g�Ǘ��̐���
			m_pMgrSysObj = DBG_NEW CMgrSysObj;

			// �V�X�e���I�u�W�F�N�g�Ǘ��̏���������
			if (FAILED(m_pMgrSysObj->Init(hInstance, hWnd, bWindow)))
			{// ���s��

			 // ���s���b�Z�[�W
				MessageBox(hWnd, "�V�X�e���I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

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

	// �퓬�X�e�[�^�X�̐ݒ菈��
	{
		// �퓬�X�e�[�^�X�̗L���𔻒�
		if (m_pStateBattle == NULL)
		{
			// �퓬�X�e�[�^�X�̐���
			m_pStateBattle = CStateBattle::Create();

			// �퓬�X�e�[�^�X�̏���������
			if (m_pStateBattle == NULL)
			{// ���s��

			 // ���s���b�Z�[�W
				MessageBox(hWnd, "�퓬�X�e�[�^�X�̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "�퓬�X�e�[�^�X�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �Q�[���X�e�[�^�X�̐ݒ菈��
	{
		// �Q�[���X�e�[�^�X�̗L���𔻒�
		if (m_pStateGame == NULL)
		{
			// �Q�[���X�e�[�^�X�̐���
			m_pStateGame = CStateGame::Create();

			// �Q�[���X�e�[�^�X�̏���������
			if (m_pStateGame == NULL)
			{// ���s��

			 // ���s���b�Z�[�W
				MessageBox(hWnd, "�Q�[���X�e�[�^�X�̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "�Q�[���X�e�[�^�X�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �����t�F�[�Y�i�T���t�F�[�Y�j�̐ݒ菈��
	{
		// �����t�F�[�Y�i�T���t�F�[�Y�j�̗L���𔻒�
		if (m_pSysGamePhase == NULL)
		{
			// �����t�F�[�Y�i�T���t�F�[�Y�j�̐���
			m_pSysGamePhase = CSysGamePhase::Create(CSysGamePhase::TYPE_SEARCH, hInstance, hWnd, bWindow);

			// �����t�F�[�Y�i�T���t�F�[�Y�j�̏���������
			if (m_pSysGamePhase == NULL)
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�t�F�[�Y�̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�t�F�[�Y�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �T�E���h�̃|�C���^��錾
	CSound *pSound = CManager::GetSound();

	// �T�E���h�̏��擾�̐����𔻒�
	if (pSound == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���ˉ�SE�̍Đ�
	pSound->Play(CSound::LABEL_BGM_GAME);

	// ���X�V�i���ԊǗ��j
	m_pMgrSysObj->GetTimer()->m_nDataTime.Set(GAME_TIME);	// ����

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[����ʂ̏I������
//-------------------------------------
void CGame::Uninit(void)
{
	// �V�X�e���I�u�W�F�N�g�Ǘ��̔j��
	if (m_pMgrSysObj != NULL)
	{
		// �V�X�e���I�u�W�F�N�g�Ǘ��̏I������
		m_pMgrSysObj->Uninit();

		// �V�X�e���I�u�W�F�N�g�Ǘ��̊J������
		delete m_pMgrSysObj;
		m_pMgrSysObj = NULL;
	}

	// �t�F�[�Y�̗L���𔻒�
	if (m_pSysGamePhase != NULL)
	{
		// �t�F�[�Y�̏I������
		m_pSysGamePhase->Uninit();

		// �t�F�[�Y�̊J������
		delete m_pSysGamePhase;
		m_pSysGamePhase = NULL;
	}

	// �퓬�X�e�[�^�X�̔j��
	if (m_pStateBattle != NULL)
	{
		// �퓬�X�e�[�^�X�̏I������
		m_pStateBattle->Uninit();

		// �퓬�X�e�[�^�X�̊J������
		delete m_pStateBattle;
		m_pStateBattle = NULL;
	}

	// �Q�[���X�e�[�^�X�̔j��
	if (m_pStateGame != NULL)
	{
		// �Q�[���X�e�[�^�X�̏I������
		m_pStateGame->Uninit();

		// �Q�[���X�e�[�^�X�̊J������
		delete m_pStateGame;
		m_pStateGame = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();

	// �S�~�̕�������
	CFileGarbage::ObjRecall();
}

//-------------------------------------
//- �Q�[����ʂ̍X�V����
//-------------------------------------
void CGame::Update(void)
{
	// �L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// ���ԊǗ��̏����擾
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// ���ԊǗ��擾�̗L���𔻒�
	if (pManagerTime == NULL)
	{
		// �����𔲂���
		return;
	}

	// ���[�h�X�e�[�^�X�̏��擾
	CStateMode *pStateMode = CManager::GetStateMode();;

	// ���[�h�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateMode == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// ���擾�i�I�u�W�F�N�g�j
	bool bStopAllUpdate = CObject::m_bDataStopAllUpdate.Get();	// �S�X�V��~

	// ���̑J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_P) != NULL)
	{
		if (m_game == GAME_NONE)
		{
			//m_pPause = CPause::Create();

			// �S�X�V��~
			bStopAllUpdate = true;

			// �|�[�Y���
			m_game = GAME_PAUSE;
		}
		else if (m_game == GAME_PAUSE)
		{
			if (m_pPause != NULL)
			{
				m_pPause->Uninit();
				m_pPause = NULL;
			}

			// �S�X�V��~������
			bStopAllUpdate = false;

			// �Q�[�����
			m_game = GAME_NONE;
		}
	}

	if (m_game == GAME_NONE)
	{
		// ���U���g�̐ݒ�X�V����
		UpdateSetResult();

		// ���U���g�̃^�C���G���h����
		UpdateTimeEndResult();

		// �V�X�e���I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_pStateBattle != NULL)
		{
			// �퓬�X�e�[�^�X�̍X�V����
			m_pStateBattle->Update();
		}

		// �V�X�e���I�u�W�F�N�g�Ǘ��̗L���𔻒�
		if (m_pMgrSysObj != NULL)
		{
			// �V�X�e���I�u�W�F�N�g�Ǘ��̍X�V����
			m_pMgrSysObj->Update();
		}

		// �Q�[���t�F�[�Y�̗L���𔻒�
		if (m_pSysGamePhase != NULL)
		{
			// �Q�[���t�F�[�Y�̍X�V����
			m_pSysGamePhase->Update();
		}
	}
	else if (m_game == GAME_PAUSE)
	{
		if (m_pPause != NULL)
		{
			// �|�[�Y�̍X�V����
			m_pPause->Update();

			if (m_pPause->m_bDataOk.Get() == true)
			{
				switch (m_pPause->GetTypeSelect())
				{
				case CPause::TYPE_SELECT_GAME:

					break;

				case CPause::TYPE_SELECT_RETRY:

					// �Q�[�����[�h
					CManager::GetFade()->SetFade(CScene::MODE_GAME);

					break;

				case CPause::TYPE_SELECT_TITLE:

					// �Q�[�����[�h
					CManager::GetFade()->SetFade(CScene::MODE_TITEL);

					break;
				}

				// �|�[�Y�̊J������
				m_pPause->Uninit();
				m_pPause = NULL;
			}

			// �S�X�V��~������
			bStopAllUpdate = false;

			// �Q�[�����
			m_game = GAME_NONE;
			
		}
	}

	// ���X�V
	CObject::m_bDataStopAllUpdate.Set(bStopAllUpdate);	// �S�X�V��~

#if _DEBUG

	// ���̑J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL)
	{
		if (m_game == GAME_PAUSE)
		{
			m_pPause->Uninit();
			m_pPause = NULL;

			// �S�X�V��~������
			bStopAllUpdate = false;

			// ���X�V
			CObject::m_bDataStopAllUpdate.Set(bStopAllUpdate);	// �S�X�V��~

			
			// �Q�[�����
			m_game = GAME_NONE;
		}

		// �ʏ탊�U���g�ɐݒ�
		pStateMode->SetResultState(CStateMode::RESULT_STATE_END);

		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
#endif

}

//-------------------------------------
//- �Q�[����ʂ̕`�揈��
//-------------------------------------
void CGame::Draw(void)
{

}

//-------------------------------------
//- �t�F�[�Y�̐ݒ菈��
//-------------------------------------
void CGame::SetPhase(CSysGamePhase::TYPE type)
{
	if (m_pSysGamePhase != NULL)
	{
		// ���݂̃��[�h��j��
		m_pSysGamePhase->Uninit();

		// ���݂̃��[�h�̊J������
		delete m_pSysGamePhase;
		m_pSysGamePhase = NULL;
	}

	// �ݒ肵�����[�h�𐶐�
	m_pSysGamePhase = m_pSysGamePhase->Create(type);
}

//-------------------------------------
//- �t�F�[�Y�̎擾����
//-------------------------------------
CSysGamePhase::TYPE CGame::GetPhase(void)
{
	// �t�F�[�Y��Ԃ�Ԃ�
	return m_pSysGamePhase->GetType();
}

//-------------------------------------
//- �Q�[���t�F�C�Y�̏����擾
//-------------------------------------
CSysGamePhase * CGame::GetSysGamePhase(void)
{
	// �Q�[���t�F�C�Y��Ԃ�
	return m_pSysGamePhase;
}

//-------------------------------------
//- �V�X�e���I�u�W�F�N�g�Ǘ��̏����擾
//-------------------------------------
CMgrSysObj * CGame::GetMgrSysObj(void)
{
	// �V�X�e���I�u�W�F�N�g�̃|�C���^��Ԃ�
	return m_pMgrSysObj;
}

//-------------------------------------
//-	�Q�[���X�e�[�^�X�̏����擾
//-------------------------------------
CStateGame * CGame::GetStateGame(void)
{
	return m_pStateGame;
}

//-------------------------------------
//-	�퓬�X�e�[�^�X�̏����擾
//-------------------------------------
CStateBattle * CGame::GetStateBattle(void)
{
	return m_pStateBattle;
}

//-------------------------------------
//-	�|�[�Y�̏����擾
//-------------------------------------
CPause * CGame::GetPause(void)
{
	return m_pPause;
}

//-------------------------------------
//-	�Q�[���̃��U���g�ݒ�X�V����
//-------------------------------------
void CGame::UpdateSetResult(void)
{
	// ���[�h�X�e�[�^�X�̏��擾
	CStateMode *pStateMode = CManager::GetStateMode();;

	// ���[�h�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateMode == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	CStateGame::END_STATE endState = m_pStateGame->GetEndState();	// �I�����

	// �Q�[���̏I����Ԃ𔻒�
	if (endState != CStateGame::END_STATE_NONE)
	{
		switch (endState)
		{
		case CStateGame::END_STATE_BOSS:

			// �������U���g�ɐݒ�
			pStateMode->SetResultState(CStateMode::RESULT_STATE_WIN);

			break;

		case CStateGame::END_STATE_TIME:

			// �ʏ탊�U���g�ɐݒ�
			pStateMode->SetResultState(CStateMode::RESULT_STATE_END);

			break;

		case CStateGame::END_STATE_DIED:

			// �s�k���U���g�ɐݒ�
			pStateMode->SetResultState(CStateMode::RESULT_STATE_LOOSE);

			break;
		}

		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//-	�Q�[���̃��U���g�ݒ�X�V����
//-------------------------------------
void CGame::UpdateTimeEndResult(void)
{
	// ���[�h�X�e�[�^�X�̏��擾
	CStateMode *pStateMode = CManager::GetStateMode();;

	// ���[�h�X�e�[�^�X�̏��擾�̐����𔻒�
	if (pStateMode == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// ���Ԃ̏��擾
	CTimer *pTimer = CMgrSysObj::GetTimer();

	// ���Ԃ̏��擾�̐����𔻒�
	if (pTimer == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// ���Ԃ̔���i0�b�̂Ƃ��j
	if (pTimer->m_nDataTime.Get() == 0)
	{
		// �ʏ탊�U���g�ɐݒ�
		pStateMode->SetResultState(CStateMode::RESULT_STATE_END);

		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
}
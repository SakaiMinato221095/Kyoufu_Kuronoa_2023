
//================================================
//=
//=	�Ǘ�����[manager.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "manager.h"
#include "renderer.h"

#include "fade.h"

#include "title.h"
#include "game.h"
#include "result.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

#include "manager_texture.h"
#include "manager_model.h"

#include "camera.h"
#include "light.h"

#include "mgr_coll.h"

#include "csv_stage.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CManager *CManager::m_pManager = NULL;

//-------------------------------------------------------------------------
//- �V�[��
//-------------------------------------------------------------------------

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CScene::CScene()
{
	m_mode = CScene::MODE(0);
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CScene::~CScene()
{

}

//-------------------------------------
//- �V�[���̏���������
//-------------------------------------
HRESULT CScene::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �V�[���̏I������
//-------------------------------------
void CScene::Uninit(void)
{

}

//-------------------------------------
//- �V�[���̍X�V����
//-------------------------------------
void CScene::Update(void)
{

}

//-------------------------------------
//- �V�[���̕`�揈��
//-------------------------------------
void CScene::Draw(void)
{

}

//-------------------------------------
//- �V�[���̐�������
//-------------------------------------
CScene *CScene::Create(MODE mode, HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �ϐ��錾
	CScene *pScene = NULL;

	// �w�肳�ꂽ���[�h�̐���
	switch (mode)
	{
	case MODE::MODE_TITEL:
		
		pScene = DBG_NEW CTitle;

		break;

	case MODE::MODE_GAME:

		pScene = DBG_NEW CGame;

		break;

	case MODE::MODE_RESULT:

		pScene = DBG_NEW CResult;

		break;
	}

	// �����̐����̗L���𔻒�
	if (pScene != NULL)
	{
		// ���[�h�ݒ菈��
		pScene->SetMode(mode);
		
		// ����������
		if (FAILED(pScene->Init(hInstance, hWnd, bWindow)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pScene == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �V�[���̏���Ԃ�
	return pScene;
}

//-------------------------------------
//- �V�[���̐ݒ菈��
//-------------------------------------
void CScene::SetMode(MODE mode)
{
	// ���[�h���
	m_mode = mode;
}

//-------------------------------------
//- �V�[���̎擾����
//-------------------------------------
CScene::MODE CScene::GetMode(void)
{
	// ���[�h��Ԃ�
	return m_mode;
}

//-------------------------------------------------------------------------
//- �Ǘ�
//-------------------------------------------------------------------------

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CManager::CManager()
{
	m_pScene = NULL;
	m_pFade = NULL;

	m_pRenderer = NULL;

	m_pInputKeyboard = NULL;
	m_pXInput = NULL;
	m_pSound = NULL;
	m_pDbugProc = NULL;

	m_pManagerTexture = NULL;
	m_pManagerModel = NULL;

	m_pCamera = NULL;
	m_pLight = NULL;

	m_pMgrColl = NULL;

	m_pCsvStage = NULL;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CManager::~CManager()
{

}

//-------------------------------------
//- �Ǘ��̏���������
//-------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �L�[�{�[�h
	{
		// �L�[�{�[�h�̗L���𔻒�
		if (m_pInputKeyboard == NULL)
		{
			// �L�[�{�[�h�̐���
			m_pInputKeyboard = DBG_NEW CInputKeyboard;

			// �L�[�{�[�h�̏���������
			if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�L�[�{�[�h�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�L�[�{�[�h�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// X����
	{
		// X���̗͂L���𔻒�
		if (m_pXInput == NULL)
		{
			// X���͂̐���
			m_pXInput = CXInput::Create(hInstance, hWnd);

			// X���͂̏���������
			if (m_pXInput == NULL)
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "X���͂̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "X���͂̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �T�E���h
	{
		// �T�E���h�L���𔻒�
		if (m_pSound == NULL)
		{
			// �T�E���h����
			m_pSound = DBG_NEW CSound;

			// �T�E���h����������
			if (FAILED(m_pSound->Init(hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�T�E���h�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�T�E���h�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �����_���[
	{
		// �����_���[�̗L���𔻒�
		if (m_pRenderer == NULL)
		{
			// �����_���[�̐���
			m_pRenderer = DBG_NEW CRenderer;

			// �����_���[�̏���������
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�����_���[�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�����_���[�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �t�F�[�h
	{
		// �t�F�[�h�̗L���𔻒�
		if (m_pFade == NULL)
		{
			// �t�F�[�h�̐���
			m_pFade = CFade::Create();

			// �t�F�[�h�̐��������̗L���𔻒�
			if (m_pFade == NULL)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "�t�F�[�h�̐���", "�����������s�I", MB_ICONWARNING);

				// ���������𔲂���
				return E_FAIL;
			}
		}
	}

	// �f�o�b�N�v���b�N
	{
		// �f�o�b�N�v���b�N�L���𔻒�
		if (m_pDbugProc == NULL)
		{
			// �f�o�b�N�v���b�N����
			m_pDbugProc = DBG_NEW CDebugProc;

			// �f�o�b�N�v���b�N����������
			m_pDbugProc->Init();
		}
	}

	// �e�N�X�`���Ǘ�
	{
		// �e�N�X�`���Ǘ��̗L���𔻒�
		if (m_pManagerTexture == NULL)
		{
			// �e�N�X�`���Ǘ��̐���
			m_pManagerTexture = DBG_NEW CManagerTexture;

			// �e�N�X�`���Ǘ��̏���������
			if (FAILED(m_pManagerTexture->Load(hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�e�N�X�`���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�e�N�X�`���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ���f���Ǘ�
	{
		// ���f���Ǘ��̗L���𔻒�
		if (m_pManagerModel == NULL)
		{
			// ���f���Ǘ��̐���
			m_pManagerModel = DBG_NEW CManagerModel;

			// ���f���Ǘ��̏���������
			if (FAILED(m_pManagerModel->Load(hWnd)))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "���f���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "���f���Ǘ��̓ǂݍ���", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �J����
	{
		// �J�����̗L���𔻒�
		if (m_pCamera == NULL)
		{
			// �J�����̐���
			m_pCamera = DBG_NEW CCamera;

			// �J�����̏���������
			if (FAILED(m_pCamera->Init()))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "�J�����̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�J�����̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// ���C�g
	{
		// ���C�g�̗L���𔻒�
		if (m_pLight == NULL)
		{
			// ���C�g�̐���
			m_pLight = DBG_NEW CLight;

			// ���C�g�̏���������
			if (FAILED(m_pLight->Init()))
			{// ���s��

				// ���s���b�Z�[�W
				MessageBox(hWnd, "���C�g�̐���", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

		 // ���s���b�Z�[�W
			MessageBox(hWnd, "���C�g�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �����蔻��Ǘ�
	{
		// �����蔻��Ǘ��̗L���𔻒�
		if (m_pMgrColl == NULL)
		{
			// �����蔻��Ǘ��̐���
			m_pMgrColl = CMgrColl::Create();

			// �����蔻��Ǘ��̗L���𔻒�
			if (m_pMgrColl == NULL)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "�����蔻��Ǘ��̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�����蔻��Ǘ��̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �V�[��
	{
		// �V�[���̗L���𔻒�
		if (m_pScene == NULL)
		{
			// �V�[���̐���
			m_pScene = CScene::Create(CScene::MODE_TITEL, hInstance,hWnd,bWindow);

			// �V�[���̗L���𔻒�
			if (m_pScene == NULL)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "�V�[���̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�V�[���̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}


	// �V�[��
	{
		// �V�[���̗L���𔻒�
		if (m_pCsvStage == NULL)
		{
			// �V�[���̐���
			m_pCsvStage = CCsvStage::Create();

			// �V�[���̗L���𔻒�
			if (m_pCsvStage == NULL)
			{
				// ���s���b�Z�[�W
				MessageBox(hWnd, "CSV�X�e�[�W�̏�����", "�����������s�I", MB_ICONWARNING);

				// �������𔲂���
				return E_FAIL;
			}
		}
		else
		{// �S�~�������Ă���Ƃ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "CSV�X�e�[�W�̏�����", "�����������s�I", MB_ICONWARNING);

			// �������𔲂���
			return E_FAIL;
		}
	}

	// �X�e�[�WCSV�̏���
	if (m_pCsvStage != NULL)
	{
		// CSV�X�e�[�W�̃��[�h����
		m_pCsvStage->Load(CCsvStage::CSV_STAGE_000);
	}
	
	// ���̐ݒ�
	if (m_pSound != NULL)
	{
		// BGM�𗬂�
		//m_pSound->Play(CSound::LABEL_BGM_GAME_000);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Ǘ��̏I������
//-------------------------------------
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();

		// �L�[�{�[�h�̊J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// X���͂̔j��
	if (m_pXInput != NULL)
	{
		// X���͂̏I������
		m_pXInput->Uninit();

		// X���͂̊J��
		delete m_pXInput;
		m_pXInput = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();

		// �T�E���h�̊J��
		delete m_pSound;
		m_pSound = NULL;
	}

	// �f�o�b�N�v���b�N�̔j��
	if (m_pDbugProc != NULL)
	{
		// �f�o�b�N�v���b�N�̏I������
		m_pDbugProc->Uninit();

		// �f�o�b�N�v���b�N�̊J��
		delete m_pDbugProc;
		m_pDbugProc = NULL;
	}

	// �e�N�X�`���Ǘ��̔j��
	if (m_pManagerTexture != NULL)
	{
		// �e�N�X�`���Ǘ��̏I������
		m_pManagerTexture->Unload();

		// �e�N�X�`���Ǘ��̊J��
		delete m_pManagerTexture;
		m_pManagerTexture = NULL;
	}

	// ���f���Ǘ��̔j��
	if (m_pManagerModel != NULL)
	{
		// ���f���Ǘ��̏I������
		m_pManagerModel->Unload();

		// ���f���Ǘ��̊J��
		delete m_pManagerModel;
		m_pManagerModel = NULL;
	}

	// �J�����̗L���𔻒�
	if (m_pCamera != NULL)
	{
		// �J�����̏I������
		m_pCamera->Uninit();

		// �J�����̊J������
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g�̗L���𔻒�
	if (m_pLight != NULL)
	{
		// ���C�g�̏I������
		m_pLight->Uninit();

		// ���C�g�̊J������
		delete m_pLight;
		m_pLight = NULL;
	}

	// �����蔻��Ǘ��̔j��
	if (m_pMgrColl != NULL)
	{
		// �����蔻��Ǘ��̏I������
		m_pMgrColl->Uninit();

		// �����蔻��Ǘ��̊J������
		delete m_pMgrColl;
		m_pMgrColl = NULL;
	}

	// CSV�X�e�[�W�̔j��
	if (m_pCsvStage != NULL)
	{
		// CSV�X�e�[�W�̏I������
		m_pCsvStage->Uninit();

		// CSV�X�e�[�W�̊J������
		delete m_pCsvStage;
		m_pCsvStage = NULL;
	}

	// �V�[���̔j��
	if (m_pScene != NULL)
	{
		// �V�[���̏I������
		m_pScene->Uninit();

		// �V�[���̊J������
		delete m_pScene;
		m_pScene = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();

	// �t�F�[�h�̔j��
	if (m_pFade != NULL)
	{
		// �t�F�[�h�̏I������
		m_pFade->Uninit();

		// �t�F�[�h�̊J������
		delete m_pFade;
		m_pFade = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();

		// �����_���[�̊J������
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//-------------------------------------
//- �Ǘ��̍X�V����
//-------------------------------------
void CManager::Update(void)
{
	// �L�[�{�[�h�̗L���𔻒�
	if (m_pInputKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V����
		m_pInputKeyboard->Update();
	}

	// X���̗͂L���𔻒�
	if (m_pXInput != NULL)
	{
		// X���͂̍X�V����
		m_pXInput->Update();
	}

	// �J�����̗L���𔻒�
	if (m_pCamera != NULL)
	{
		// �J�����̍X�V����
		m_pCamera->Update();
	}

	// ���C�g�̗L���𔻒�
	if (m_pLight != NULL)
	{
		// ���C�g�̍X�V����
		m_pLight->Update();
	}

	// �����蔻��Ǘ��̗L���𔻒�
	if (m_pMgrColl != NULL)
	{
		// �����蔻��Ǘ��̍X�V����
		m_pMgrColl->Update();
	}

	// �f�o�b�N�v���b�N�̗L���𔻒�
	if (m_pDbugProc != NULL)
	{
		// �f�o�b�N�v���b�N�̍X�V����
		m_pDbugProc->Update();
	}

	// �����_���[�̗L���𔻒�
	if (m_pRenderer != NULL)
	{
		// �����_���[�̍X�V����
		m_pRenderer->Update();
	}


	// �t�F�[�h�̗L���𔻒�
	if (m_pFade != NULL)
	{
		// �t�F�[�h�̍X�V����
		m_pFade->Update();
	}

	// �t�F�[�h�̗L���𔻒�
	if (m_pFade->GetFade() == CFade::STATE_NONE)
	{
		// �V�[���̗L���𔻒�
		if (m_pScene != NULL)
		{
			// �V�[���̍X�V����
			m_pScene->Update();
		}
	}

}

//-------------------------------------
//- �Ǘ��̕`�揈��
//-------------------------------------
void CManager::Draw(void)
{
	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �f�o�b�N�\��
	Debug();

	// �J�����̗L���𔻒�
	if (pCamera != NULL)
	{
		// �J�����̐ݒ�
		pCamera->SetCamera();
	}

	// �����蔻��Ǘ��̗L���𔻒�
	if (m_pMgrColl != NULL)
	{
		// �����蔻��Ǘ��̐ݒ�
		m_pMgrColl->Draw();
	}

	// �����_���[�̗L���𔻒�
	if (m_pRenderer != NULL)
	{
		// �����_���[�̕`�揈��
		m_pRenderer->Draw();
	}
}

//-------------------------------------
//- �Q�[����Ԃ̐ݒ菈��
//-------------------------------------
void CManager::SetMode(CScene::MODE mode)
{
	// �T�E���h�̑S��~
	m_pSound->Stop();

	if (m_pScene != NULL)
	{
		// ���݂̃��[�h��j��
		m_pScene->Uninit();

		// ���݂̃��[�h�̊J������
		delete m_pScene;
		m_pScene = NULL;
	}

	// �ݒ肵�����[�h�𐶐�
	m_pScene = m_pScene->Create(mode);
}

//-------------------------------------
//- �Q�[����Ԃ̎擾����
//-------------------------------------
CScene::MODE CManager::GetMode(void)
{
	// �Q�[����Ԃ�Ԃ�
	return m_pScene->GetMode();
}

//-------------------------------------
//- �t�F�[�h�̎擾����
//-------------------------------------
CFade *CManager::GetFade(void)
{
	// �t�F�[�h�̃|�C���^��Ԃ�
	return m_pFade;
}

//-------------------------------------
//- �����_���[�̏����擾
//-------------------------------------
CRenderer *CManager::GetRenderer(void)
{
	// �����_���[�̃|�C���^��Ԃ�
	return m_pRenderer;
}

//-------------------------------------
//-	�L�[�{�[�h�̏����擾
//-------------------------------------
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pInputKeyboard;
}

//-------------------------------------
//-	X���͂̏����擾
//-------------------------------------
CXInput * CManager::GetXInput(void)
{
	return m_pXInput;
}

//-------------------------------------
//-	�T�E���h�̏����擾
//-------------------------------------
CSound *CManager::GetSound(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pSound;
}

//-------------------------------------
//-	�f�o�b�N�v���b�N�̏����擾
//-------------------------------------
CDebugProc * CManager::GetDbugProc(void)
{
	// �f�o�b�N�v���b�N��Ԃ�
	return m_pDbugProc;
}

//-------------------------------------
//-	�e�N�X�`���Ǘ��̏����擾
//-------------------------------------
CManagerTexture *CManager::GetManagerTexture(void)
{
	// �e�N�X�`���Ǘ���Ԃ�
	return m_pManagerTexture;
}

//-------------------------------------
//-	���f���Ǘ��̏����擾
//-------------------------------------
CManagerModel *CManager::GetManagerModel(void)
{
	return m_pManagerModel;
}

//-------------------------------------
//-	�J�����̏����擾
//-------------------------------------
CCamera *CManager::GetCamera(void)
{
	// �L�[�{�[�h�̃|�C���^��Ԃ�
	return m_pCamera;
}

//-------------------------------------
//-	���C�g�̏����擾
//-------------------------------------
CLight * CManager::GetLight(void)
{
	return m_pLight;
}

//-------------------------------------
//- �����蔻��Ǘ��̏����擾
//-------------------------------------
CMgrColl * CManager::GetMgrColl(void)
{
	return m_pMgrColl;
}

//-------------------------------------
//- �Ǘ��̃X�e�[�WCSV���擾����
//-------------------------------------
CCsvStage * CManager::GetCsvStage(void)
{
	return m_pCsvStage;
}

//-------------------------------------
//- �Ǘ��̃|�C���^�ݒ菈��
//-------------------------------------
CManager * CManager::GetInstance()
{
	if (m_pManager == NULL)
	{
		// �Ǘ��̐���
		return m_pManager = new CManager;
	}
	else
	{
		// ���݂̊Ǘ���Ԃ�
		return m_pManager;
	}
}

//-------------------------------------
//- �}�l�[�W���[�̃f�o�b�N�\��
//-------------------------------------
void CManager::Debug(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");

	if (GetMode() == CScene::MODE_TITEL)
	{
		pDebugProc->Print("�Q�[����� : �^�C�g��");
	}
	else if (GetMode() == CScene::MODE_GAME)
	{
		pDebugProc->Print("�Q�[����� : �Q�[��");
	}
	else if (GetMode() == CScene::MODE_RESULT)
	{
		pDebugProc->Print("�Q�[����� : ���U���g");
	}

	pDebugProc->Print("\n");
}
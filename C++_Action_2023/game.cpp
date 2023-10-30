
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

#include "manager.h"

#include "fade.h"

#include "input.h"
#include "xinput.h"
#include "sound.h"

#include "camera.h"

#include "player.h"

#include "obj_3d_field.h"
#include "obj_3d_wall.h"
#include "objectx_none.h"

#include "obj_block.h"

#include "skybox.h"

#include "csv_stage.h"

#include "timer.h"

#include "edit_map.h"
#include "file_map.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CPlayer *CGame::m_pPlayer = NULL;
CTimer *CGame::m_pTimer = NULL;
CEditMap *CGame::m_pEditMap = NULL;

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
	// �J�����ʒu�̐ݒ菈��
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera == NULL)
	{
		return E_FAIL;
	}

	CFileMap *pFileMap = CManager::GetInstance()->GetFileMap();

	if (pFileMap == NULL)
	{
		return E_FAIL;
	}

	// �J�����̐ݒ菈��
	pCamera->SetMode(CCamera::MODE_FOLLOWING);

	// �}�b�v�̃��[�h����
	pFileMap->Load(CFileMap::TEXT_NORMAL);

	// �X�J�C�{�b�N�X�̐���
	CSkybox::Create(
		CSkybox::MODEL_SKYBOX_000,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	for (int nCutColu = 0; nCutColu < 16; nCutColu++)
	{
		for (int nCutLine = 0; nCutLine < 64; nCutLine++)
		{
			// �t�B�[���h�̐���
			CObj3dField::Create(
				CObj3dField::TEX_GLASS_000,
				D3DXVECTOR3(-15000.0f + (1000.0f * nCutLine), 0.0f, 10000.0f - (1000.0f * nCutColu)),
				D3DXVECTOR3(500.0f, 0.0f, 500.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	if (m_pTimer == NULL)
	{
		// ���Ԃ̐���
		m_pTimer = CTimer::Create(
			D3DXVECTOR3(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.075f, 0.0f),
			D3DXVECTOR3(60.0f, 0.0f, 0.0f),
			D3DXVECTOR3(40.0f, 0.0f, 0.0f),
			D3DXVECTOR3(30.0f, 40.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_pPlayer == NULL)
	{
		// �v���C���[�̐���
		m_pPlayer = CPlayer::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// �ʒu
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),	// ����
			CModel::MODEL_TYPE_PLAYER_AONOA,			// ���f��
			CMotion::MOTION_TYPE_PLAYER_AONOA);			// ���[�V����
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[����ʂ̏I������
//-------------------------------------
void CGame::Uninit(void)
{
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	if (m_pTimer != NULL)
	{
		// ���ԊǗ��̏I������
		m_pTimer->Uninit();

		// ���ԊǗ��̊J������
		delete m_pTimer;
		m_pTimer = NULL;
	}

	if (m_pEditMap != NULL)
	{
		// �}�b�v�G�f�B�^�̏I������
		m_pEditMap->Uninit();

		// �}�b�v�G�f�B�^�̊J������
		delete m_pEditMap;
		m_pEditMap = NULL;
	}

	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
}

//-------------------------------------
//- �Q�[����ʂ̍X�V����
//-------------------------------------
void CGame::Update(void)
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

	if (m_pEditMap == NULL)
	{
		if (m_pTimer != NULL)
		{
			// ���Ԃ̍X�V����
			m_pTimer->Update();
		}

		// �J�ڃ{�^���i���񂽁[�j
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			// �Q�[�����[�h
			CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);

			return;
		}

		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{
			// �G�f�B�b�g���[�h�̐�������
			m_pEditMap = CEditMap::Create();

			if (m_pPlayer != NULL)
			{
				// �v���C���[�̍X�V��~
				m_pPlayer->IsUpdateStop(false);
			}
		}
	}
	else
	{
		// �X�V����
		m_pEditMap->Update();

		if (pInputKeyboard->GetTrigger(DIK_F1) == true)
		{
			// �I������
			m_pEditMap->Uninit();

			// �J������
			delete m_pEditMap;
			m_pEditMap = NULL;

			if (m_pPlayer != NULL)
			{
				// �v���C���[�̍X�V��~
				m_pPlayer->IsUpdateStop(true);
			}
		}
	}
}

//-------------------------------------
//- �Q�[����ʂ̕`�揈��
//-------------------------------------
void CGame::Draw(void)
{

}

//-------------------------------------
//- �Q�[����ʂ̃v���C���[�̎擾����
//-------------------------------------
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

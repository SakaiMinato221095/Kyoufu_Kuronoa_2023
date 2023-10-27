
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

#include "obj_teach.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CPlayer *CGame::m_pPlayer = NULL;
CTimer *CGame::m_pTimer = NULL;

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
	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// �ʒu
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),	// ����
		CModel::MODEL_TYPE_PLAYER_AONOA,			// ���f��
		CMotion::MOTION_TYPE_PLAYER_AONOA);			// ���[�V����

	// �v���C���[�̏���������
	if (m_pPlayer == NULL)
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�v���C���[�̏�����", "�����������s�I", MB_ICONWARNING);

		// �������𔲂���
		return E_FAIL;
	}

	// �J�����ʒu�̐ݒ菈��
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != NULL)
	{
		pCamera->SetMode(CCamera::MODE_FOLLOWING);
	}

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

	for (int nCount = 0; nCount < 32; nCount++)
	{
		CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			D3DXVECTOR3(-1000.0f, 100.0f * nCount, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			D3DXVECTOR3(9400.0f, 100.0f * nCount, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// �X�J�C�{�b�N�X�̐���
	CSkybox::Create(
		CSkybox::MODEL_SKYBOX_000,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// ���Ԃ̐���
	m_pTimer = CTimer::Create(
		D3DXVECTOR3(SCREEN_WIDTH * 0.04f, SCREEN_HEIGHT * 0.075f, 0.0f),
		D3DXVECTOR3(60.0f, 0.0f, 0.0f),
		D3DXVECTOR3(40.0f, 0.0f, 0.0f),
		D3DXVECTOR3(30.0f, 40.0f, 0.0f),
		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	// ������I�u�W�F�N�g�̐�������
	CObjTeach::Create(
		CObjTeach::TEX_TEACH_MOVE,
		D3DXVECTOR3(200.0f, 600.0f, 500.0f),
		D3DXVECTOR3(400.0f, 200.0f, 50.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CCsvStage *pCsvStage = CManager::GetInstance()->GetCsvStage();

	if (pCsvStage != NULL)
	{
		// CSV�X�e�[�W�̐ݒu
		pCsvStage->SetObj();
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

	if (m_pTimer != NULL)
	{
		// ���Ԃ̍X�V����
		m_pTimer->Update();
	}

	// �J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL )
	{
		// �Q�[�����[�h
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
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

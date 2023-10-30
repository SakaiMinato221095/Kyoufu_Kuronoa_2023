
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

#include "file_map.h"

#include "player.h"

#include "skybox.h"
#include "obj_3d_field.h"

#include "obj_2d_none.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CPlayer *CTitle::m_pPlayer = {};
CObj2dNone *CTitle::m_apObj2dNone[TYPE_NONE_2D_MAX] = {};

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
	pCamera->SetMode(CCamera::MODE_TITLE);

	// �}�b�v�̃��[�h����
	pFileMap->Load(CFileMap::TEXT_TITLE);

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

	if (m_pPlayer == NULL)
	{
		// �v���C���[�̐���
		m_pPlayer = CPlayer::Create(
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// �ʒu
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),	// ����
			CModel::MODEL_TYPE_PLAYER_AONOA,			// ���f��
			CMotion::MOTION_TYPE_PLAYER_AONOA);			// ���[�V����
	}

	// �I�u�W�F�N�g�Ǘ��̐���
	m_apObj2dNone[TYPE_NONE_2D_LOGO] = CObj2dNone::Create(
		CObj2dNone::TEX_TITLE_LOGO,
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f),
		D3DXVECTOR3(300.0f, 150.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// �I�u�W�F�N�g�Ǘ��̏���������
	if (m_apObj2dNone[TYPE_NONE_2D_LOGO] == NULL)
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "���ʂȂ�2D�I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

		// �������𔲂���
		return E_FAIL;
	}

	// �I�u�W�F�N�g�Ǘ��̗L���𔻒�
	if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
	{
		// �I�u�W�F�N�g�Ǘ��̐���
		m_apObj2dNone[TYPE_NONE_2D_BUTTON] = CObj2dNone::Create(
			CObj2dNone::TEX_TITLE_BUTTON,
			D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f),
			D3DXVECTOR3(200.0f, 100.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		// �I�u�W�F�N�g�Ǘ��̏���������
		if (m_apObj2dNone[TYPE_NONE_2D_BUTTON] == NULL)
		{// ���s��

			// ���s���b�Z�[�W
			MessageBox(hWnd, "���ʂȂ�2D�I�u�W�F�N�g�̐���", "�����������s�I", MB_ICONWARNING);

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
//- �^�C�g���̏I������
//-------------------------------------
void CTitle::Uninit(void)
{
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}
	for (int nCount = 0; nCount < TYPE_NONE_2D_MAX; nCount++)
	{
		m_apObj2dNone[nCount] = NULL;
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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A,CXInput::TYPE_INPUT_BUTTON))
	{
		// �Q�[�����[�h
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//-------------------------------------
//- �^�C�g���̕`�揈��
//-------------------------------------
void CTitle::Draw(void)
{

}
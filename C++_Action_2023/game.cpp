
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
#include "xinput.h"
#include "sound.h"

#include "player.h"
#include "player_battle.h"

#include "obj_3d_field.h"
#include "objectx_none.h"

#include "enemy.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

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
	// �퓬�X�e�[�^�X�̐���
	CPlayer *pPlayer = CPlayerBattle::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// �ʒu
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),	// ����
		CModel::MODEL_TYPE_PLAYER,					// ���f��
		CMotion::MOTION_TYPE_PLAYER);				// ���[�V����

	// �퓬�X�e�[�^�X�̏���������
	if (pPlayer == NULL)
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�퓬�v���C���[�̏�����", "�����������s�I", MB_ICONWARNING);

		// �������𔲂���
		return E_FAIL;
	}

	CObj3dField *pObj3dField = CObj3dField::Create(CObj3dField::TEX_ROAD_000);

	pObj3dField->Set(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(5000.0f, 0.0f, 5000.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CEnemy *pEnemy = CEnemy::Create(CEnemy::MODEL_ALIEN_000);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �Q�[����ʂ̏I������
//-------------------------------------
void CGame::Uninit(void)
{
	// �I�u�W�F�N�g�̑S�J������
	CObject::ReleaseAll();
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
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
	{
		// �Q�[�����[�h
		CManager::GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//- �Q�[����ʂ̕`�揈��
//-------------------------------------
void CGame::Draw(void)
{

}

//-------------------------------------
//-	�|�[�Y�̏����擾
//-------------------------------------
CPause * CGame::GetPause(void)
{
	return m_pPause;
}
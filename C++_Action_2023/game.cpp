
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

#include "obj_3d_field.h"
#include "objectx_none.h"

#include "enemy.h"

#include "gimmick_jewel.h"
#include "obj_block.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CPlayer *CGame::m_pPlayer = NULL;

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
	m_pPlayer = CPlayer::Create(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),				// �ʒu
		D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f),	// ����
		CModel::MODEL_TYPE_PLAYER,					// ���f��
		CMotion::MOTION_TYPE_PLAYER);				// ���[�V����

	// �퓬�X�e�[�^�X�̏���������
	if (m_pPlayer == NULL)
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

	CEnemy *pEnemy1 = CEnemy::Create(CEnemy::MODEL_ALIEN_000);
	pEnemy1->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CEnemy *pEnemy2 = CEnemy::Create(CEnemy::MODEL_ALIEN_000);
	pEnemy2->Set(D3DXVECTOR3(300.0f, 0.0f, 0.0f));

	CEnemy *pEnemy3 = CEnemy::Create(CEnemy::MODEL_ALIEN_000);
	pEnemy3->Set(D3DXVECTOR3(600.0f, 0.0f, 0.0f));

	CGimmick *pGimmick = CGimmickJewel::Create(
		CGimmick::MODEL_JEWEL_000,
		CGimmickJewel::TYPE_EFFECT_SPEED_UP,
		D3DXVECTOR3(100.0f, 200.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CObjectXNone *pBlock = CObjBlock::Create(
		CObjectXNone::MODEL_BLOCK_000,
		D3DXVECTOR3(-300.0f, 200.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f));

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

	// �J�ڃ{�^���i���񂽁[�j
	if (pInputKeyboard->GetTrigger(DIK_RETURN) != NULL ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON))
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

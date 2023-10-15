
//-===============================================
//-
//-	�v���C���[����[player.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "camera.h"

#include "coll.h"

#include "kazedama.h"
#include "enemy_have.h"

//-======================================
//-	�}�N����`
//-======================================

#define PLAYER_SPEED	(4.0f)	//�v���C���[�̑��x

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPlayer::CPlayer()
{
	// �l���N���A
	ZeroMemory(&m_data, sizeof(m_data));

	m_bJump = false;
	m_bHave = false;

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));

	m_pColl = NULL;

	ZeroMemory(m_apModel, sizeof(m_apModel));

	m_nNumModel = 0;

	m_pMotion = NULL;

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPlayer::~CPlayer()
{

}

//-------------------------------------
//- �v���C���[�̏���������
//-------------------------------------
HRESULT CPlayer::Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// ���f���̃p�[�c�����擾
	m_nNumModel = CModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		// �K�w�\��X�I�u�W�F�N�g�̗L���𔻒�
		if (m_apModel[nCount] == NULL)
		{
			// �K�w�\��X�I�u�W�F�N�g�̐���
			m_apModel[nCount] = CModel::Create(modelType, nCount);

			// �K�w�\��X�I�u�W�F�N�g�̐ݒ�
			m_apModel[nCount]->SetParent(m_apModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// ���[�V�����̐���
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		// �t�@�C����ǂݍ���
		m_pMotion->SetFile(motionType);

		// ���f���̐ݒ�
		m_pMotion->SetModel(m_apModel, 0);

		// �ҋ@���[�V������ݒ�
		m_pMotion->Set(0);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �v���C���[�̏I������
//-------------------------------------
void CPlayer::Uninit(void)
{
	// ���f���̏I������
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		if (m_apModel[nCount] != NULL)
		{
			// ���f���̊J������
			m_apModel[nCount]->Uninit();

			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	// ���[�V�����̏I������
	if (m_pMotion != NULL)
	{
		// ���[�V�����̊J��
		m_pMotion->Uninit();

		delete m_pMotion;
		m_pMotion = NULL;
	}

	// ���g�̃|�C���^��������
	m_pInstance = NULL;

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �v���C���[�̍X�V����
//-------------------------------------
void CPlayer::Update(void)
{
	// �O��̈ʒu���X�V
	m_data.posOld = m_data.pos;

	// �ړ��̓��͏���
	InputMove();

	// �W�����v�̓��͏���
	InputJump();

	// �A�N�V�����̓��͏���
	InputAction();

	// �����̍X�V����
	UpdateRot();

	// �ʒu���̍X�V����
	UpdatePos();

	// �f�o�b�N�\��
	DebugPlayer();
}

//-------------------------------------
//- �v���C���[�̕`�揈��
//-------------------------------------
void CPlayer::Draw(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_data.pos;	// �ʒu���
	D3DXVECTOR3 rot = m_data.rot;	// �������

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// �p�[�c���̕`�揈��
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Draw();
	}
}

//-------------------------------------
//- �v���C���[�̃��[�V�������擾����
//-------------------------------------
void CPlayer::Hit(int nDamage)
{

}

//-------------------------------------
//- �v���C���[�̃��[�V�������擾����
//-------------------------------------
CMotion *CPlayer::GetMotion(void)
{
	// ���[�V������Ԃ�
	return m_pMotion;
}

//-------------------------------------
//- �v���C���[�̃��f���̏��擾
//-------------------------------------
CModel *CPlayer::GetModel(int nNumParts)
{
	return m_apModel[nNumParts];
}

//-------------------------------------
//- �v���C���[�̒l�ݒ菈��
//-------------------------------------
void CPlayer::SetData(Data data)
{
	m_data = data;
}

//-------------------------------------
//- �v���C���[�̒l�擾����
//-------------------------------------
CPlayer::Data CPlayer::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- �v���C���[�̏�����Ԃ̐ݒ菈��
//-------------------------------------
void CPlayer::SetHave(bool bHave)
{
	m_bHave = bHave;
}

//-------------------------------------
//- �v���C���[�̃C���X�^���X�擾����
//-------------------------------------
CPlayer * CPlayer::GetInstance(void)
{
	return m_pInstance;
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::UpdatePos(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_data.pos;	// �ʒu
	D3DXVECTOR3 move = m_data.move;	// �ړ���

	// �d�͂̏���
	move.y -= 1.0f;

	// �ʒu���Ɉړ��ʂ����Z
	pos += move;

	// �ړ��ʂ�����
	move.x += (0.0f - move.x) * 0.3f;
	move.z += (0.0f - move.z) * 0.3f;

	//�c���̏���
	if (pos.y <= 0.0f)
	{
		m_bJump = false;
		pos.y = 0.0f;
	}

	// ���X�V
	m_data.pos = pos;
	m_data.move = move;
}

//-------------------------------------
//- �v���C���[�̌�������
//-------------------------------------
void CPlayer::UpdateRot(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_data.rot;			// ����
	D3DXVECTOR3 rotDest = m_data.rotDest;	// �ړI�̌���

	// �ړI�̌����̕␳
	if (rotDest.y > D3DX_PI)
	{
		rotDest.y += -D3DX_PI * 2;
	}
	else if (rotDest.y < -D3DX_PI)
	{
		rotDest.y += D3DX_PI * 2;
	}

	// �����̌������Z�o
	float rotDiff = rotDest.y - rot.y;

	// �����̌�����␳
	if (rotDiff > D3DX_PI)
	{
		rotDiff += -D3DX_PI * 2;
	}
	else if (rotDiff < -D3DX_PI)
	{
		rotDiff += D3DX_PI * 2;
	}

	//�ړ������i�p�x�j�̕␳
	rot.y += rotDiff * 0.15f;

	// �����̕␳
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	// ���X�V
	m_data.rot = rot;			// ����
	m_data.rotDest = rotDest;	// �ړI�̌���
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::InputMove(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;			// �ړ��ʂ��擾
	D3DXVECTOR3 rotDest = m_data.rotDest;	// �ړI�̉�]�ʂ��擾

	// �J�����̏����擾
	CCamera *pCamera = CManager::GetCamera();

	// �J�����̌������擾
	D3DXVECTOR3 rotCamera = pCamera->GetData().rot;

	if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//A�L�[�������ꂽ�Ƃ�

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//D�L�[�������ꂽ�Ƃ�

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;

		rotDest.y = -(D3DX_PI * 0.5f) + rotCamera.y;
	}

	// ���X�V
	m_data.move = move;			// �ړ���
	m_data.rotDest = rotDest;	// �ړI�̌���

}

//-------------------------------------
//- �v���C���[�̃W�����v���͏���
//-------------------------------------
void CPlayer::InputJump(void)
{
	if (m_bJump == false)
	{
		// �ʏ�W�����v����
		InputNormalJump();
	}
	else if (m_bJump == true && m_bHave == true)
	{
		// ��i�W�����v
		InputDoubleJump();
	}
}

//-------------------------------------
//- �v���C���[�̒ʏ�W�����v���͏���
//-------------------------------------
void CPlayer::InputNormalJump(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;			// �ړ��ʂ��擾

	// ���͏����iSPACE�L�[ / A�{�^���j
	if (pInputKeyboard->GetTrigger(DIK_SPACE) != NULL && m_bJump == false ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) && m_bJump == false)
	{
		// �W�����v��ԂɕύX
		m_bJump = true;

		// �W�����v�ʂ�ݒ�
		move.y = 20.0f;
	}

	// ���X�V
	m_data.move = move;			// �ړ���
}

//-------------------------------------
//- �v���C���[�̓�i�W�����v���͏���
//-------------------------------------
void CPlayer::InputDoubleJump(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;			// �ړ��ʂ��擾

	if (pInputKeyboard->GetTrigger(DIK_SPACE) != NULL && m_bJump == true && m_bHave == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) && m_bJump == true && m_bHave == true)
	{
		// �ێ���Ԃ�����
		m_bHave = false;

		// �ێ��G�̗L���𔻒�
		if (CEnemyHave::GetInstance() != NULL)
		{
			// �ێ��G�̏I������
			CEnemyHave::GetInstance()->Uninit();
		}

		// �W�����v�ʂ�ݒ�
		move.y = 30.0f;
	}

	// ���X�V
	m_data.move = move;			// �ړ���
}

//-------------------------------------
//- �v���C���[�̃A�N�V�������͏���
//-------------------------------------
void CPlayer::InputAction(void)
{
	// ������Ԃ̗L���𔻒�
	if (m_bHave == true)
	{
		// ���˓��͏���
		InputShot();
	}
	else
	{
		// �����ܓ��͏���
		InputKazedama();
	}
}

//-------------------------------------
//- �v���C���[�̕����ܓ��͏���
//-------------------------------------
void CPlayer::InputKazedama(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �����܂̃|�C���^�̗L���𔻒�
	if (CKazedama::GetInstance() == NULL)
	{
		// ���͏����iJ�L�[ / B�{�^���j
		if (pInputKeyboard->GetTrigger(DIK_J) != NULL ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON))
		{
			// ���擾
			D3DXVECTOR3 pos = m_data.pos;
			D3DXVECTOR3 rot = m_data.rot;

			// �ϐ��錾
			D3DXVECTOR3 posBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
			posBody.x = m_apModel[0]->GetMtxWorld()._41;
			posBody.y = m_apModel[0]->GetMtxWorld()._42;
			posBody.z = m_apModel[0]->GetMtxWorld()._43;

			// �����܂̐�������
			CKazedama *pKazedama = CKazedama::Create(CKazedama::TEX_NULL);

			if (rot.y >= 0.0f && rot.y <= D3DX_PI)
			{
				// �����܂̐ݒ菈��
				pKazedama->Set(
					posBody,
					D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					D3DXVECTOR3(-20.0f, 0.0f, 0.0f),
					CKazedama::TYPE_ROT_LEFT);
			}
			else if (rot.y <= 0.0f && rot.y <= D3DX_PI)
			{
				// �����܂̐ݒ菈��
				pKazedama->Set(
					posBody,
					D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					D3DXVECTOR3(20.0f, 0.0f, 0.0f),
					CKazedama::TYPE_ROT_RIGHT);
			}
		}
	}
}

//-------------------------------------
//- �v���C���[�̔��˓��͏���
//-------------------------------------
void CPlayer::InputShot(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	CEnemyHave *pEnemyHave = CEnemyHave::GetInstance();

	// �����܂̃|�C���^�̗L���𔻒�
	if (pEnemyHave != NULL)
	{
		// ���͏����iJ�L�[ / B�{�^���j
		if (pInputKeyboard->GetTrigger(DIK_J) != NULL ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON))
		{
			// �ێ���Ԃ�����
			m_bHave = false;

			// ���擾
			D3DXVECTOR3 pos = m_data.pos;
			D3DXVECTOR3 rot = m_data.rot;

			// �ϐ��錾
			D3DXVECTOR3 posBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
			posBody.x = m_apModel[0]->GetMtxWorld()._41;
			posBody.y = m_apModel[0]->GetMtxWorld()._42;
			posBody.z = m_apModel[0]->GetMtxWorld()._43;

			if (rot.y >= 0.0f && rot.y <= D3DX_PI)
			{
				pEnemyHave->SetShot(
					posBody,
					D3DXVECTOR3(-30.0f,0.0f,0.0f),
					60,
					CEnemyHave::TYPE_ROT_LEFT);
			}
			else if (rot.y <= 0.0f && rot.y <= D3DX_PI)
			{
				pEnemyHave->SetShot(
					posBody,
					D3DXVECTOR3(30.0f, 0.0f, 0.0f),
					60,
					CEnemyHave::TYPE_ROT_RIGHT);
			}
		}
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// �f�o�b�N�v���b�N�擾�̗L���𔻒�
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("�v���C���[�̈ʒu");
	pDebugProc->Print("\n");
	pDebugProc->Print("%f,%f,%f",m_data.pos.x, m_data.pos.y, m_data.pos.z);
	pDebugProc->Print("\n");
	pDebugProc->Print("�v���C���[�̏����� %d",m_bHave);
	pDebugProc->Print("\n");
}
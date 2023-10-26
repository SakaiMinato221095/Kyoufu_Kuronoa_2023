
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

#define PLAYER_SPEED		(4.0f)	// �v���C���[�̑��x
#define PLAYER_JUMP			(30.0f)	// �v���C���[�̃W�����v��
#define PLAYER_DOUBLE_JUMP	(35.0f)	// �v���C���[�̓�i�W�����v��

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
	m_bLanding = false;
	m_bHave = false;

	m_pKazedama = NULL;
	m_pEnemyHave = NULL;

	m_stateType = STATE_TYPE(0);
	m_stateTypeNew = m_stateType;

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));

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
HRESULT CPlayer::Init(D3DXVECTOR3 pos , D3DXVECTOR3 rot,CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// �퓬�v���C���[�̐ݒ菈��
	InitSet(pos, rot);

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
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();

		// �����蔻��̊J������
		delete m_pColl;
		m_pColl = NULL;
	}

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

	// �ǉ����̍X�V����
	UpdatePlusData();

	if (m_bHave == false)
	{
		// �ʏ탂�[�V�����̍X�V����
		UpdateMotionNone();
	}
	else
	{
		// �G�ێ����[�V�����̍X�V����
		UpdateMotionHave();
	}

	// �����܂̍X�V����
	UpdateKazedama();

	// �G�ێ��̍X�V����
	UpdateEnemyHave();
	
	//�c���̏���
	if (m_data.pos.y <= 0.0f)
	{
		m_bJump = false;

		if (m_bLanding == false)
		{
			m_bLanding = true;
		}
		 
		m_data.pos.y = 0.0f;
		m_data.move.y = 0.0f;
	}

	// �����蔻��̏��X�V����
	m_pColl->UpdateData(
		m_data.pos,
		m_data.posOld,
		m_data.size);

	// �v���C���[�̓����蔻��
	if (m_pColl->Hit(CMgrColl::TAG_BLOCK, CMgrColl::STATE_HIT_NONE) == true)
	{
		bool bHitSxisX = m_pColl->GetData().abHitSxis[CColl::TYPE_SXIS_X];
		bool bHitSxisY = m_pColl->GetData().abHitSxis[CColl::TYPE_SXIS_Y];

		if (bHitSxisX == true)
		{
			// �ړ��ʂ��Ȃ���
			m_data.move.x = 0.0f;

			// �v���C���[��X���W�ړ����~
			m_data.pos.x = m_pColl->GetData().pos.x;
		}

		if (bHitSxisY == true)
		{
			// �ړ��ʂ��Ȃ���
			m_data.move.y = 0.0f;

			// �v���C���[��Y���W�ړ����~
			m_data.pos.y = m_pColl->GetData().pos.y;

			// �W�����v���g�p��
			m_bJump = false;

			if (m_bLanding == false)
			{
				m_bLanding = true;
			}
		}
	}

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
//- �v���C���[�̐�������
//-------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �v���C���[�̃|�C���^��錾
	CPlayer *pPlayer = new CPlayer;

	// �����̐����̗L���𔻒�
	if (pPlayer != NULL)
	{
		// ����������
		if (FAILED(pPlayer->Init(pos, rot, modelType, motionType, STATE_TYPE_MAX)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pPlayer == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
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
//- �v���C���[�̋����ݒ菈��
//-------------------------------------
void CPlayer::SetPlus(float fRate,int nTime)
{
	m_data.plus.speedRate = fRate;
	m_data.plus.sppedPlusTime = nTime;
}

//-------------------------------------
//- �v���C���[�̏����ݒ菈��
//-------------------------------------
void CPlayer::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_data.pos = pos;
	m_data.rot = rot;
	m_data.size = D3DXVECTOR3(50.0f, 100.0f, 50.0f);

	// �����蔻��ݒ�
	m_pColl = CColl::Create(
		CMgrColl::TAG_PLAYER,
		m_data.pos,
		m_data.size);

	// ����^�O�̐ݒ菈��
	m_pColl->SetTagTgt(CMgrColl::TAG_BLOCK, CMgrColl::TYPE_RECTANGLE_SIDE, true);

	m_data.plus.speedRate = 1.0f;
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
//- �v���C���[�̒ǉ��f�[�^�̍X�V����
//-------------------------------------
void CPlayer::UpdatePlusData(void)
{
	if (m_data.plus.sppedPlusTime != 0)
	{
		m_data.plus.sppedPlusTime--;
		
		if (m_data.plus.sppedPlusTime <= 0)
		{
			m_data.plus.speedRate = 1.0f;
		}
	}	
}

//-------------------------------------
//- �ʏ��ԃv���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayer::UpdateMotionNone(void)
{
	// �ϐ��錾�i���擾�j
	CMotion *pMotion = GetMotion();		// ���[�V����
	D3DXVECTOR3 move = GetData().move;	// �ړ���

	// ��Ԃ𔻒�
	if (m_stateTypeNew == STATE_TYPE_NEUTRAL ||
		m_stateTypeNew == STATE_TYPE_MOVE )
	{
		// �ړ��ʂŏ�Ԃ�ύX
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			// �ړ���ԂɕύX
			m_stateTypeNew = STATE_TYPE_MOVE;
		}
		else
		{
			// �ҋ@��Ԃ̕ύX
			m_stateTypeNew = STATE_TYPE_NEUTRAL;
		}
	}

	if (m_stateTypeNew == STATE_TYPE_JUMP || 
		m_stateTypeNew == STATE_TYPE_DOUBLEJUMP)
	{
		if (m_data.move.y <= 0.0f)
		{
			m_stateTypeNew = STATE_TYPE_LANDING;
		}
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih() == true)
	{
		// ���[�V�����̍X�V
		pMotion->Update();
	}
	else
	{
		// �ҋ@��Ԃ�ݒ�
		m_stateTypeNew = STATE_TYPE_NEUTRAL;
	}

	// ���[�V�����̐ݒ菈��
	if (m_stateType != m_stateTypeNew)
	{
		// ���݂̃��[�V�����̐ݒ�
		pMotion->Set(m_stateTypeNew);

		// ��Ԃ̍X�V
		m_stateType = m_stateTypeNew;
	}
}

//-------------------------------------
//- �G�ێ���ԃv���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayer::UpdateMotionHave(void)
{
	// �ϐ��錾�i���擾�j
	CMotion *pMotion = GetMotion();		// ���[�V����
	D3DXVECTOR3 move = GetData().move;	// �ړ���

	// ��Ԃ𔻒�
	if (m_stateTypeNew == STATE_TYPE_HAVE_NEUTRAL ||
		m_stateTypeNew == STATE_TYPE_HAVE_MOVE)
	{
		// �ړ��ʂŏ�Ԃ�ύX
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			// �ړ���ԂɕύX
			m_stateTypeNew = STATE_TYPE_HAVE_MOVE;
		}
		else
		{
			// �ҋ@��Ԃ̕ύX
			m_stateTypeNew = STATE_TYPE_HAVE_NEUTRAL;
		}
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih() == true)
	{
		// ���[�V�����̍X�V
		pMotion->Update();
	}
	else
	{
		// �ҋ@��Ԃ�ݒ�
		m_stateTypeNew = STATE_TYPE_HAVE_NEUTRAL;
	}

	// ���[�V�����̐ݒ菈��
	if (m_stateType != m_stateTypeNew)
	{
		// ���݂̃��[�V�����̐ݒ�
		pMotion->Set(m_stateTypeNew);

		// ��Ԃ̍X�V
		m_stateType = m_stateTypeNew;
	}
}

//-------------------------------------
//- �v���C���[�̕����܍X�V����
//-------------------------------------
void CPlayer::UpdateKazedama(void)
{
	if (m_pKazedama != NULL)
	{
		// �ϐ��錾
		D3DXVECTOR3 posBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �e�̈ʒu�����i�ԍ��x�^�ł�[15]�ԁj
		posBody.x = m_apModel[0]->GetMtxWorld()._41;
		posBody.y = m_apModel[0]->GetMtxWorld()._42;
		posBody.z = m_apModel[0]->GetMtxWorld()._43;

		// �e�̈ʒu��ݒ�
		m_pKazedama->SetParent(posBody);

		// �����܂̏�Ԃ��擾
		CKazedama::STATE state = m_pKazedama->GetData().state;

		if (state == CKazedama::STATE_FAIL)
		{
			// ���s���̏��ŏ���
			m_pKazedama->LostFail();

			// �����܂̏�����
			m_pKazedama = NULL;
		}
		else if (state == CKazedama::STATE_SUCCE)
		{
			// �������̏��ŏ���
			m_pKazedama->LostSucce();

			// �����܂̏�����
			m_pKazedama = NULL;

			// �����󋵂��X�V
			m_bHave = true;

			// ��Ԃ�ێ���ԂɕύX
			m_stateTypeNew = STATE_TYPE_HAVE_NEUTRAL;

			if (m_pEnemyHave == NULL)
			{
				// �ێ��G�̐�������
				m_pEnemyHave = CEnemyHave::Create(
					CEnemyHave::MODEL_ALIEN_000,
					CEnemyHave::STATE_WAIT,
					D3DXVECTOR3(m_data.pos.x,m_data.pos.y + 200.0f,m_data.pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(50.0f, 50.0f, 50.0f));
			}
		}
	}
}

//-------------------------------------
//- �v���C���[�̕ێ��G�X�V����
//-------------------------------------
void CPlayer::UpdateEnemyHave(void)
{
	if (m_pEnemyHave != NULL)
	{
		// ���擾
		CEnemyHave::VtxData vtxData = m_pEnemyHave->GetVtxData();

		// �ʒu�𕗂��܂̈ʒu�ɕύX
		vtxData.pos = D3DXVECTOR3(m_data.pos.x, m_data.pos.y + 200.0f, m_data.pos.z);

		// ���X�V
		m_pEnemyHave->SetVtxData(vtxData);
	}
}

//-------------------------------------
//- �v���C���[�̈ړ�����
//-------------------------------------
void CPlayer::InputMove(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;					// �ړ��ʂ��擾
	D3DXVECTOR3 rotDest = m_data.rotDest;			// �ړI�̉�]�ʂ��擾
	float speedRate = m_data.plus.speedRate;		// ���x�̔{��

	D3DXVECTOR3 speed = D3DXVECTOR3(PLAYER_SPEED, 0.0f, PLAYER_SPEED);
	speed *= speedRate;

	// �J�����̏����擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	// �J�����̌������擾
	D3DXVECTOR3 rotCamera = pCamera->GetData().rot;

	if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//A�L�[�������ꂽ�Ƃ�

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * speed.x;
		//move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * speed.z;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//D�L�[�������ꂽ�Ƃ�

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * speed.x;
		//move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * speed.z;

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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;			// �ړ��ʂ��擾

	// ���͏����iSPACE�L�[ / A�{�^���j
	if (pInputKeyboard->GetTrigger(DIK_SPACE) != NULL && m_bJump == false ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) && m_bJump == false)
	{
		// �W�����v��ԂɕύX
		m_bJump = true;

		// �W�����v�ʂ�ݒ�
		move.y = PLAYER_JUMP;

		if (m_bHave == false)
		{
			// ��Ԃ��W�����v�ɕύX
			m_stateTypeNew = STATE_TYPE_JUMP;
		}
		else
		{
			// ��Ԃ��W�����v�ɕύX
			m_stateTypeNew = STATE_TYPE_HAVE_JUMP;
		}
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �ϐ��錾
	D3DXVECTOR3 move = m_data.move;			// �ړ��ʂ��擾

	if (pInputKeyboard->GetTrigger(DIK_SPACE) != NULL && m_bJump == true && m_bHave == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) && m_bJump == true && m_bHave == true)
	{
		// �ێ���Ԃ�����
		m_bHave = false;

		// ��Ԃ�G������ԂɕύX
		m_stateTypeNew = STATE_TYPE_DOUBLEJUMP;

		// �ێ��G�̗L���𔻒�
		if (m_pEnemyHave != NULL)
		{
			// �ێ��G�̏I������
			m_pEnemyHave->Uninit();
			m_pEnemyHave = NULL;
		}

		// �W�����v�ʂ�ݒ�
		move.y = PLAYER_DOUBLE_JUMP;
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	if (m_pKazedama == NULL)
	{
		// ���͏����iJ�L�[ / B�{�^���j
		if (pInputKeyboard->GetTrigger(DIK_J) != NULL ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON))
		{
			// ��Ԃ𕗂��܂ɕύX
			m_stateTypeNew = STATE_TYPE_KAZEDAMA;

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
				// �����܂̐�������
				m_pKazedama = CKazedama::Create(
					CKazedama::TEX_KAZEDAMA,
					posBody,
					D3DXVECTOR3(50.0f, 50.0f, 50.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					D3DXVECTOR3(-20.0f, 0.0f, 0.0f),
					CKazedama::TYPE_ROT_LEFT);
;
			}
			else if (rot.y <= 0.0f && rot.y <= D3DX_PI)
			{
				// �����܂̐�������
				m_pKazedama = CKazedama::Create(
					CKazedama::TEX_KAZEDAMA,
					posBody,
					D3DXVECTOR3(50.0f, 50.0f, 50.0f),
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �ړ������𔲂���
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

	// �����܂̃|�C���^�̗L���𔻒�
	if (m_pEnemyHave != NULL)
	{
		// ���͏����iJ�L�[ / B�{�^���j
		if (pInputKeyboard->GetTrigger(DIK_J) != NULL ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON))
		{
			// �ێ���Ԃ�����
			m_bHave = false;

			// ��Ԃ�G������ԂɕύX
			m_stateTypeNew = STATE_TYPE_THROW;

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
				// �ێ��G�𔭎�
				m_pEnemyHave->SetShot(
					posBody,
					D3DXVECTOR3(-30.0f,0.0f,0.0f),
					60,
					CEnemyHave::TYPE_ROT_LEFT);
			}
			else if (rot.y <= 0.0f && rot.y <= D3DX_PI)
			{
				// �ێ��G�𔭎�
				m_pEnemyHave->SetShot(
					posBody,
					D3DXVECTOR3(30.0f, 0.0f, 0.0f),
					60,
					CEnemyHave::TYPE_ROT_RIGHT);
			}

			// �ێ��G�̃|�C���^��������
			m_pEnemyHave = NULL;
		}
	}
}

//-------------------------------------
//- �v���C���[�̃f�o�b�N�\��
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// �f�o�b�N�v���b�N�̎擾
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDbugProc();

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
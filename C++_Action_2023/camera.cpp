
//================================================
//=
//= �J�����̏���[camera.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "camera.h"

#include "main.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "manager_object.h"
#include "sys_game_phase.h"

#include "input.h"

#include "time_stop.h"

#include "player_search.h"
#include "player_battle.h"
#include "player_shop.h"

#include "objectx_none.h"
#include "event_object.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�J�����̃R���X�g���N�^
//-------------------------------------
CCamera::CCamera()
{
	ZeroMemory(m_mtxProjectien, sizeof(D3DXMATRIX));
	ZeroMemory(m_mtxView, sizeof(D3DXMATRIX));

	m_mode = MODE_FOLLOWING;
}

//-------------------------------------
//-	�J�����̃f�X�g���N�^
//-------------------------------------
CCamera::~CCamera()
{
}

//-------------------------------------
//-	�J�����̏���������
//-------------------------------------
HRESULT CCamera::Init(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = m_dataPosR.Get();	// �����_
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����
	float fLength = m_fDataLength.Get();	// �J�����Ƃ̒���
	D3DXVECTOR3 vecU = m_dataVecU.Get();	// ������̃x�N�g��

	// �O���[�o���ϐ��̏�����
	{
		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 500.0f, 500.0f);	// ���_
		posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		// �����_
		fLength = (700.0f);							// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������̃x�N�g��

		// ���X�V
		m_dataPosV.Set(posV);			// ���_
		m_dataPosR.Set(posR);			// �����_
		m_fDataLength.Set(fLength);		// �J�����Ƃ̒���
		m_dataRot.Set(rot);				// ����
		m_dataVecU.Set(vecU);			// ������̃x�N�g��

		m_dataPosVDest.Set(posV);		// �ړI�̎��_
		m_dataPosRDest.Set(posR);		// �ړI�̒����_
		m_dataRotDest.Set(rot);			// �ړI�̌���
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�J�����̏I������
//-------------------------------------
void CCamera::Uninit(void)
{

}

//-------------------------------------
//-	�J�����̍X�V����
//-------------------------------------
void CCamera::Update(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// �J�����̃��[�h
		switch (m_mode)
		{
		case MODE_NORMAL:

			// �J�����̈ړ�����
			UpdateOperation();

			break;

		case MODE_FOLLOWING:

			// �J�����̒ǔ�����
			UpdateFollowing();

			// �J�����̌����ǔ�����
			UpdateRot();

			// ���͂̔���iF2�L�[�j
			if (pInputKeyboard->GetTrigger(DIK_F2) == true)
			{
				// �V���b�v���_�ɕύX
				SetMode(MODE_SHOP);
			}

			break;

		case MODE_SHOP:

			// ���͂̔���iF2�L�[�j
			if (pInputKeyboard->GetTrigger(DIK_F2) == true)
			{
				// �V���b�v���_�ɕύX
				SetMode(MODE_FOLLOWING);
			}

			break;
		}
	}
	else if (CManager::GetMode() == CScene::MODE_TITEL)
	{
		// �^�C�g���̍X�V����
		UpdateTitle();
	}


	// �J�����̓����蔻��
	Collision();
}

//-------------------------------------
//-	�J�����̑��쏈��
//-------------------------------------
void CCamera::UpdateOperation(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = m_dataPosR.Get();	// �����_
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����
	float fLength = m_fDataLength.Get();	// �J�����Ƃ̋���

	// �L�[�{�[�h�̃|�C���^��錾
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

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{//���̈ړ�[A�L�[�������ꂽ�Ƃ�]

		posV.x -= 2.0f;
		posR.x -= 2.0f;

	}
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{//�E�̈ړ�[D�L�[�������ꂽ�Ƃ�]

		posV.x += 2.0f;
		posR.x += 2.0f;

	}
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{//�E�̈ړ�[W�L�[�������ꂽ�Ƃ�]

		posV.z += 2.0f;
		posR.z += 2.0f;

	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{//�E�̈ړ�[S�L�[�������ꂽ�Ƃ�]

		posV.z -= 2.0f;
		posR.z -= 2.0f;

	}

	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{//[Q�L�[�������ꂽ�Ƃ�]

		rot.y -= 0.05f;

		//�����_�̈ʒu���X�V
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;
	}

	if (pInputKeyboard->GetPress(DIK_E) == true)
	{//[E�L�[�������ꂽ�Ƃ�]

		rot.y += 0.05f;

		//�����_�̈ʒu���X�V
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;

	}

	if (pInputKeyboard->GetPress(DIK_Y) == true)
	{
		rot.y -= 0.05f;

		//�����_�̈ʒu���X�V
		posV.x = posR.x + sinf(rot.y) * -fLength;
		posV.z = posR.z + cosf(rot.y) * -fLength;
	}
	if (pInputKeyboard->GetPress(DIK_T) == true)
	{//[E�L�[�������ꂽ�Ƃ�]

		rot.y += 0.05f;

		//�����_�̈ʒu���X�V
		posV.x = posR.x + sinf(rot.y) * -fLength;
		posV.z = posR.z + cosf(rot.y) * -fLength;
	}

	if (pInputKeyboard->GetPress(DIK_RETURN) == true)
	{//[�G���^�[�L�[�������ꂽ�Ƃ�]

		posV = D3DXVECTOR3(0.0f, 50.0f, -200.0f);
		posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�����_�̈ʒu���X�V
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;

		posV.x = posR.x + sinf(rot.y) * -fLength;
		posV.z = posR.z + cosf(rot.y) * -fLength;
	}

	//�p�x�̏C��
	if (rot.y > D3DX_PI)
	{
		rot.y = (-D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = (D3DX_PI);
	}

	// ���X�V
	m_dataPosV.Set(posV);		// ���_
	m_dataPosR.Set(posR);		// �����_
	m_dataRot.Set(rot);			// �J�����̌���
	m_fDataLength.Set(fLength);	// �J�����Ƃ̋���
}

//-------------------------------------
//-	�J�����̒ǔ�����
//-------------------------------------
void CCamera::UpdateFollowing(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();			// ���_
	D3DXVECTOR3 posVDest = m_dataPosVDest.Get();	// �ړI�̎��_
	D3DXVECTOR3 posR = m_dataPosR.Get();			// �����_
	D3DXVECTOR3 posRDest = m_dataPosRDest.Get();	// �ړI�̒����_
	D3DXVECTOR3 rot = m_dataRot.Get();				// ����
	float fLength = m_fDataLength.Get();			// �J�����Ƃ̋���

	// �v���C���[�̏����擾
	CPlayer *pPlayer = CSysGamePhase::GetPlayer();

	// �v���C���[�̏��擾�̐����𔻒�
	if (pPlayer == NULL)
	{// ���s��

		// �ǔ������𔲂���
		return;
	}

	// �ϐ��錾�i�v���C���[�̏��擾�j
	D3DXVECTOR3 playerPos = pPlayer->m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 playerRot = pPlayer->m_dataRot.Get();		// ����

	//�����_�ƃv���C���[�̋���
	D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(
		sinf(playerRot.y) * -50.0f,
		0.0f,
		cosf(playerRot.y) * -50.0f);

	//���_�̈ʒu���X�V
	posV.x = posR.x + sinf(rot.y) * -fLength;
	posV.z = posR.z + cosf(rot.y) * -fLength;

	//�ړI�̎��_�̈ʒu
	posVDest.x = playerPos.x + (sinf(rot.y) * -fLength) + cameraPlayer.x;
	posVDest.z = playerPos.z + (cosf(rot.y) * -fLength) + cameraPlayer.z;

	//�ړI�̒����_�̈ʒu
	posRDest.x = playerPos.x + cameraPlayer.x;
	posRDest.z = playerPos.z + cameraPlayer.z;

	//���_�̕␳
	posV.x += (posVDest.x - posV.x) * 0.1f;
	posV.z += (posVDest.z - posV.z) * 0.1f;

	//�����_�̕␳
	posR.x += (posRDest.x - posR.x) * 0.1f;
	posR.z += (posRDest.z - posR.z) * 0.1f;

	// ���X�V
	m_dataPosV.Set(posV);			// ���_
	m_dataPosVDest.Set(posVDest);	// �ړI�̎��_
	m_dataPosR.Set(posR);			// �����_
	m_dataPosRDest.Set(posRDest);	// �ړI�̒����_
	m_fDataLength.Set(fLength);		// �J�����Ƃ̋���
}

//-------------------------------------
//-	�J�����̌����ǔ�����
//-------------------------------------
void CCamera::UpdateRot(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_dataRot.Get();				// ����
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();		// �ړI�̌���

	// �v���C���[�̏����擾
	CPlayer *pPlayer = CSysGamePhase::GetPlayer();

	// �v���C���[�̏��擾�̐����𔻒�
	if (pPlayer == NULL)
	{// ���s��

		// �ǔ������𔲂���
		return;
	}

	// �ϐ��錾�i�v���C���[�̏��擾�j
	D3DXVECTOR3 playerRot = pPlayer->m_dataRot.Get();		// ����
	
	//if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	//{
	//	// �ړI�̎��_���X�V
	//	rotDest.y = (playerRot.y - D3DX_PI);
	//}


	//if (pInputKeyboard->GetPress(DIK_Q) == true)
	//{//[Q�L�[�������ꂽ�Ƃ�]

	//	rotDest.y -= 0.015f;
	//	rot = rotDest;
	//}

	//if (pInputKeyboard->GetPress(DIK_E) == true)
	//{//[E�L�[�������ꂽ�Ƃ�]

	//	rotDest.y += 0.015f;
	//	rot = rotDest;
	//}

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

	// �p�x�̈ړ�
	rot.y += rotDiff * 0.02f;

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
	m_dataRot.Set(rot);			// ����
	m_dataRotDest.Set(rotDest);	// �ړI�̌���
}

//-------------------------------------
//-	�^�C�g���J�����̍X�V����
//-------------------------------------
void CCamera::UpdateTitle(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_dataRot.Get();				// ����
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();		// �ړI�̌���
	D3DXVECTOR3 posV = m_dataPosV.Get();			// ���_
	D3DXVECTOR3 posVDest = m_dataPosVDest.Get();	// �ړI�̎��_
	D3DXVECTOR3 posR = m_dataPosR.Get();			// �����_
	D3DXVECTOR3 posRDest = m_dataPosRDest.Get();	// �ړI�̒����_
	float fLength = m_fDataLength.Get();			// �J�����Ƃ̋���

	// �J�����̉�]
	rotDest.y += 0.002f;

	//�p�x�̏C��
	if (rot.y > D3DX_PI)
	{
		rot.y = -D3DX_PI;
		rotDest.y = -D3DX_PI + (rotDest.y - D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = D3DX_PI;
		rotDest.y = D3DX_PI + (rotDest.y + D3DX_PI);
	}

	//���_�̈ʒu���X�V
	posV.x = posR.x + sinf(rot.y) * -fLength;
	posV.z = posR.z + cosf(rot.y) * -fLength;

	//�ړI�̎��_�̈ʒu
	posVDest.x = 0.0f + (sinf(rot.y) * -fLength) + 0.0f;
	posVDest.z = 0.0f + (cosf(rot.y) * -fLength) + 0.0f;

	//�ړI�̒����_�̈ʒu
	posRDest.x = 0.0f + 0.0f;
	posRDest.z = 0.0f + 0.0f;

	//���_�̕␳
	posV.x += (posVDest.x - posV.x) * 0.3f;
	posV.z += (posVDest.z - posV.z) * 0.3f;

	//�����_�̕␳
	posR.x += (posRDest.x - posR.x) * 0.3f;
	posR.z += (posRDest.z - posR.z) * 0.3f;

	//�p�x�̕␳
	rot.y += (rotDest.y - rot.y) * 0.3f;

	// ���X�V
	m_dataRot.Set(rot);				// ����
	m_dataRotDest.Set(rotDest);		// �ړI�̌���
	m_dataPosV.Set(posV);			// ���_
	m_dataPosVDest.Set(posVDest);	// �ړI�̎��_
	m_dataPosR.Set(posR);			// �����_
	m_dataPosRDest.Set(posRDest);	// �ړI�̒����_
	m_fDataLength.Set(fLength);		// �J�����Ƃ̋���
}

//-------------------------------------
//-	�J�����̐ݒ菈��
//-------------------------------------
void CCamera::SetCamera(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = m_dataPosR.Get();	// �����_
	D3DXVECTOR3 vecU = m_dataVecU.Get();	// ������̃x�N�g��

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	// �v���W�F�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjectien);

	// �v���W�F�V�����}�g���b�N�X�𐶐��i��{�J�����j
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjectien,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		40000.0f);

	//// �v���W�F�V�����}�g���b�N�X�𐶐��i���s���e�j
	//D3DXMatrixOrthoLH(
	//	&m_mtxProjectien,
	//	(float)SCREEN_WIDTH,
	//	(float)SCREEN_HEIGHT,
	//	10.0f,
	//	1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_PROJECTION,
		&m_mtxProjectien);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);
		
	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&posV,		// ���_
		&posR,		// �����_
		&vecU);		// ������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_VIEW,
		&m_mtxView);

	// ���X�V
	m_dataPosV.Set(posV);	// ���_
	m_dataPosR.Set(posR);	// �����_
	m_dataVecU.Set(vecU);	// ������̃x�N�g��
}

//-------------------------------------
//-	�J�����̊e���[�h�̐ݒ菈��
//-------------------------------------
void CCamera::SetMode(CCamera::MODE mode)
{
	// ���[�h�̐ݒ�
	m_mode = mode;

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_
	D3DXVECTOR3 posR = m_dataPosR.Get();	// �����_
	D3DXVECTOR3 rot = m_dataRot.Get();		// ����
	float fLength = m_fDataLength.Get();	// �J�����Ƃ̒���

	switch (m_mode)
	{
	case MODE_NORMAL:

		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 1250.0f, -500.0f);		// ���_
		posR = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// �����_
		fLength = 1250.0f;								// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����

		break;

	case MODE_FOLLOWING:

		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 500.0f, 500.0f);	// ���_
		posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		// �����_
		fLength = 700.0f;							// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����

		break;

	case MODE_SHOP:

		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 1250.0f, -500.0f);		// ���_
		posR = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// �����_
		fLength = 1250.0f;								// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����

		break;

	case MODE_TITLE:

		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 3000.0f, -5000.0f);	// ���_
		posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �����_
		fLength = 12500.0f;								// �J�����Ƃ̒���
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����

		break;
	}

	// ���X�V
	m_dataPosR.Set(posR);					// ���_
	m_dataPosV.Set(posV);					// �����_
	m_fDataLength.Set(fLength);				// �J�����Ƃ̒���
	m_dataRot.Set(rot);						// ����

	// �ړI�̏��̍X�V
	m_dataPosVDest.Set(m_dataPosV.Get());	// �ړI�̎��_
	m_dataPosRDest.Set(m_dataPosR.Get());	// �ړI�̒����_
	m_dataRotDest.Set(m_dataRot.Get());		// �ړI�̌���
}

//-------------------------------------
//-	�J�����̓����蔻��
//-------------------------------------
void CCamera::Collision(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_dataPosV.Get();	// ���_

	for (int nCutObjectNone = 0; nCutObjectNone < OBJECTX_NONE_NUM_MAX; nCutObjectNone++)
	{
		// ���ʂȂ��I�u�W�F�N�g�̏����擾
		CObjectXNone *pObjectNone = CManagerObject::GetObjectNone(nCutObjectNone);

		// ���ʂȂ��I�u�W�F�N�g�̗L���𔻒�
		if (pObjectNone != NULL)
		{
			// �ϐ��錾�i���ʂȂ��I�u�W�F�N�g�̏��擾�j
			D3DXVECTOR3 objectNonePos = pObjectNone->m_dataPos.Get();	// �ʒu
			D3DXVECTOR3 objectNoneSize = pObjectNone->m_dataSize.Get();	// �傫��

			// ��`�̓����蔻��
			if (posV.x + 200.0f >= objectNonePos.x - objectNoneSize.x &&
				posV.x - 200.0f <= objectNonePos.x + objectNoneSize.x &&
				posV.z + 400.0f >= objectNonePos.z - objectNoneSize.z &&
				posV.z - 400.0f <= objectNonePos.z + objectNoneSize.z)
			{
				// �I�u�W�F�N�g�̕`����O��
				pObjectNone->SetDrawRemove();

				// ��񂵕`��
				pObjectNone->m_bDataAfterDraw.Set(true);
			}
		}
	}

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// �C�x���g�I�u�W�F�N�g�̏����擾
		CEventObject *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// �C�x���g�I�u�W�F�N�g�̗L���𔻒�
		if (pEventObject != NULL)
		{
			// �ϐ��錾�i�C�x���g�I�u�W�F�N�g�̏��擾�j
			D3DXVECTOR3 eventObjectPos = pEventObject->m_dataPos.Get();		// �ʒu
			D3DXVECTOR3 eventObjectSize = pEventObject->m_dataSize.Get();	// �傫��

			// ��`�̓����蔻��
			if (posV.x + 200.0f >= eventObjectPos.x - eventObjectSize.x &&
				posV.x - 200.0f <= eventObjectPos.x + eventObjectSize.x &&
				posV.z + 400.0f >= eventObjectPos.z - eventObjectSize.z &&
				posV.z - 400.0f <= eventObjectPos.z + eventObjectSize.z)
			{
				// �I�u�W�F�N�g�̕`����O��
				pEventObject->SetDrawRemove();

				// ��񂵕`��
				pEventObject->m_bDataAfterDraw.Set(true);
			}
		}
	}
}



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

#include "input.h"

#include "player.h"

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
	ZeroMemory(&m_data, sizeof(m_data));
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
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 vecU = m_data.vecU;		// ������̃x�N�g��
	D3DXVECTOR3 rot = m_data.rot;		// ����
	float fLength = m_data.fLength;		// �J�����Ƃ̒���
	
	// �O���[�o���ϐ��̏�����
	{
		// ���ݒ�
		posV = D3DXVECTOR3(0.0f, 400.0f, 1500.0f);	// ���_
		posR = D3DXVECTOR3(0.0f, 300.0f, 0.0f);		// �����_
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������̃x�N�g��
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		fLength = 1500.0f;							// �J�����Ƃ̒���

		// ���X�V
		m_data.posV = posV;			// ���_
		m_data.posVDest = posV;		// �ړI�̎��_
		m_data.posR = posR;			// �����_
		m_data.posRDest = posR;		// �ړI�̒����_
		m_data.vecU = vecU;			// ������̃x�N�g��
		m_data.rot = rot;			// ����
		m_data.rotDest = rot;		// �ړI�̌���
		m_data.fLength = fLength;	// �J�����Ƃ̒���
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
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
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

			break;
		}
	}
	else if (CManager::GetInstance()->GetMode() == CScene::MODE_TITEL)
	{
		// �^�C�g���̍X�V����
		UpdateTitle();
	}
}

//-------------------------------------
//-	�J�����̑��쏈��
//-------------------------------------
void CCamera::UpdateOperation(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 rot = m_data.rot;		// ����
	float fLength = m_data.fLength;		// �J�����Ƃ̋���

	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{//���̈ړ�[A�L�[�������ꂽ�Ƃ�]

		posV.x -= 100.0f;
		posR.x -= 100.0f;

	}
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{//�E�̈ړ�[D�L�[�������ꂽ�Ƃ�]

		posV.x += 100.0f;
		posR.x += 100.0f;

	}
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{//�E�̈ړ�[W�L�[�������ꂽ�Ƃ�]

		posV.z += 100.0f;
		posR.z += 100.0f;

	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{//�E�̈ړ�[S�L�[�������ꂽ�Ƃ�]

		posV.z -= 100.0f;
		posR.z -= 100.0f;

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
	m_data.posV = posV;			// ���_
	m_data.posR = posR;			// �����_
	m_data.rot = rot;			// ����
	m_data.fLength = fLength;	// �J�����Ƃ̋���
}

//-------------------------------------
//-	�J�����̒ǔ�����
//-------------------------------------
void CCamera::UpdateFollowing(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV =	m_data.posV;			// ���_
	D3DXVECTOR3 posVDest = m_data.posVDest;		// �ړI�̎��_
	float fLength = m_data.fLength;				// �J�����Ƃ̋���

	// �v���C���[�̏����擾
	D3DXVECTOR3 posR = m_data.posR;				// �����_
	D3DXVECTOR3 posRDest = m_data.posRDest;		// �ړI�̒����_
	D3DXVECTOR3 rot = m_data.rot;				// ����

	// �v���C���[�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	// �v���C���[�̏��擾�̐����𔻒�
	if (pPlayer == NULL)
	{// ���s��

		// �ǔ������𔲂���
		return;
	}

	// �ϐ��錾�i�v���C���[�̏��擾�j
	D3DXVECTOR3 playerPos = pPlayer->GetData().pos;		// �ʒu
	D3DXVECTOR3 playerRot = pPlayer->GetData().rot;		// ����

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
	posV.y = playerPos.y + 200.0f;

	//�����_�̕␳
	posR.x += (posRDest.x - posR.x) * 0.1f;
	posR.z += (posRDest.z - posR.z) * 0.1f;
	posR.y = playerPos.y + 200.0f;

	// ���X�V
	m_data.posV = posV;				// ���_
	m_data.posVDest = posVDest;		// �ړI�̎��_
	m_data.posR = posR;				// �����_
	m_data.posRDest = posRDest;		// �ړI�̒����_
	m_data.rot = rot;				// ����
	m_data.fLength = fLength;		// �J�����Ƃ̋���
}

//-------------------------------------
//-	�J�����̌����ǔ�����
//-------------------------------------
void CCamera::UpdateRot(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 rot = m_data.rot;				// ����
	D3DXVECTOR3 rotDest = m_data.rotDest;		// �ړI�̌���

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
	m_data.rot = rot;			// ����
	m_data.rotDest = rotDest;	// �ړI�̌���
}

//-------------------------------------
//-	�^�C�g���J�����̍X�V����
//-------------------------------------
void CCamera::UpdateTitle(void)
{
	//// �ϐ��錾�i���擾�j
	//D3DXVECTOR3 posV = m_data.posV;				// ���_
	//D3DXVECTOR3 posVDest = m_data.posVDest;		// �ړI�̎��_
	//D3DXVECTOR3 posR = m_data.posR;				// �����_
	//D3DXVECTOR3 posRDest = m_data.posRDest;		// �ړI�̒����_
	//D3DXVECTOR3 rot = m_data.rot;				// ����
	//D3DXVECTOR3 rotDest = m_data.rotDest;		// �ړI�̌���
	//float fLength = m_data.fLength;				// �J�����Ƃ̋���

	//// �J�����̉�]
	//rotDest.y += 0.002f;

	////�p�x�̏C��
	//if (rot.y > D3DX_PI)
	//{
	//	rot.y = -D3DX_PI;
	//	rotDest.y = -D3DX_PI + (rotDest.y - D3DX_PI);
	//}
	//else if (rot.y < -D3DX_PI)
	//{
	//	rot.y = D3DX_PI;
	//	rotDest.y = D3DX_PI + (rotDest.y + D3DX_PI);
	//}

	////���_�̈ʒu���X�V
	//posV.x = posR.x + sinf(rot.y) * -fLength;
	//posV.z = posR.z + cosf(rot.y) * -fLength;

	////�ړI�̎��_�̈ʒu
	//posVDest.x = 0.0f + (sinf(rot.y) * -fLength) + 0.0f;
	//posVDest.z = 0.0f + (cosf(rot.y) * -fLength) + 0.0f;

	////�ړI�̒����_�̈ʒu
	//posRDest.x = 0.0f + 0.0f;
	//posRDest.z = 0.0f + 0.0f;

	////���_�̕␳
	//posV.x += (posVDest.x - posV.x) * 0.3f;
	//posV.z += (posVDest.z - posV.z) * 0.3f;

	////�����_�̕␳
	//posR.x += (posRDest.x - posR.x) * 0.3f;
	//posR.z += (posRDest.z - posR.z) * 0.3f;

	////�p�x�̕␳
	//rot.y += (rotDest.y - rot.y) * 0.3f;

	//// ���X�V
	//m_data.posV = posV;			// ���_
	//m_data.posVDest = posV;		// �ړI�̎��_
	//m_data.posR = posR;			// �����_
	//m_data.posRDest = posR;		// �ړI�̒����_
	//m_data.rot = rot;			// ����
	//m_data.rotDest = rot;		// �ړI�̌���
	//m_data.fLength = fLength;	// �J�����Ƃ̒���
}

//-------------------------------------
//-	�J�����̐ݒ菈��
//-------------------------------------
void CCamera::SetCamera(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 vecU = m_data.vecU;		// ������̃x�N�g��

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
	//	40000.0f);

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
	m_data.posV = posV;			// ���_
	m_data.posR = posR;			// �����_
	m_data.vecU = vecU;			// ������̃x�N�g��
}

//-------------------------------------
//-	�J�����̊e���[�h�̐ݒ菈��
//-------------------------------------
void CCamera::SetMode(CCamera::MODE mode)
{
	// ���[�h�̐ݒ�
	m_mode = mode;

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 posV = m_data.posV;		// ���_
	D3DXVECTOR3 posR = m_data.posR;		// �����_
	D3DXVECTOR3 vecU = m_data.vecU;		// ������̃x�N�g��
	D3DXVECTOR3 rot = m_data.rot;		// ����
	float fLength = m_data.fLength;		// �J�����Ƃ̒���

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
		posV = D3DXVECTOR3(0.0f, 500.0f, 1500.0f);	// ���_
		posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������̃x�N�g��
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
		fLength = 1500.0f;							// �J�����Ƃ̒���

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
	m_data.posV = posV;			// ���_
	m_data.posVDest = posV;		// �ړI�̎��_
	m_data.posR = posR;			// �����_
	m_data.posRDest = posR;		// �ړI�̒����_
	m_data.vecU = vecU;			// ������̃x�N�g��
	m_data.rot = rot;			// ����
	m_data.rotDest = rot;		// �ړI�̌���
	m_data.fLength = fLength;	// �J�����Ƃ̒���
}

//-------------------------------------
//-	�J�����̒l�̎擾����
//-------------------------------------
CCamera::Data CCamera::GetData(void)
{
	return m_data;
}

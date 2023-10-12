
//================================================
//=
//= �r���{�[�h�I�u�W�F�N�g�̏���[object_bullet.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "object_billboard.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̃R���X�g���N�^
//------------------------------------
CObjectBillboard::CObjectBillboard(int nPriority) : CObject(nPriority)
{
	// �l���N���A
	ZeroMemory(&m_vtxData, sizeof(m_vtxData));
	m_nTextureNldxUse = 0;

	m_pVtxBuff = NULL;
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̃f�X�g���N�^
//------------------------------------
CObjectBillboard::~CObjectBillboard()
{
}

//------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̏���������
//------------------------------------
HRESULT CObjectBillboard::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�̐��������̗L�����m�F
	if (m_pVtxBuff == NULL)
	{
		// ���s���ɏ����������𔲂���
		return E_FAIL;
	}

	// ���_����ݒ�
	SetVtx();

	// �����̕Ԃ�
	return S_OK;
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectBillboard::Uninit(void)
{
	// ���_�o�b�t�@�̗L���𔻒�
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�̊J������
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectBillboard::Update(void)
{
	// ���_����ݒ�
	SetVtx();
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectBillboard::Draw(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_vtxData.pos;	// �ʒu

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return;
	}

	// �e�N�X�`���Ǘ��̎擾
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// �e�N�X�`���Ǘ��̏��擾�̐����𔻒�
	if (pManagerTexture == NULL)
	{// ���s��

		// �`�揈���𔲂���
		return;
	}

	// �ϐ��錾
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		// �r���[�}�g���b�N�X�̎擾�p

	//���C�e�B���O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X���擾
	pDevice->GetTransform(
		D3DTS_VIEW,
		&mtxView);
	
	// �|���S�����J�����̈ʒu�Ɍ�����ύX
	D3DXMatrixInverse(
		&m_mtxWorld,
		NULL,
		&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		pManagerTexture->GetAddress(m_nTextureNldxUse));

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		2);						// �v���~�e�B�u�́i�|���S���j��

	//���C�e�B���O��ON�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//-------------------------------------
//-	�r���{�[�h�I�u�W�F�N�g�̐�������
//-------------------------------------
CObjectBillboard * CObjectBillboard::Create(void)
{
	// 3D�I�u�W�F�N�g�̃|�C���^��錾
	CObjectBillboard *pObjectBillboard = NULL;

	// ����
	pObjectBillboard = DBG_NEW CObjectBillboard;

	// �����̐����̗L���𔻒�
	if (pObjectBillboard != NULL)
	{
		// ����������
		if (FAILED(pObjectBillboard->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObjectBillboard == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// 3D�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObjectBillboard;
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̃e�N�X�`������
//-------------------------------------
void CObjectBillboard::BindTexture(int nTextureNldx)
{
	// �e�N�X�`���̔ԍ�����
	m_nTextureNldxUse = nTextureNldx;
}

//-------------------------------------
//- �r���{�[�h�I�u�W�F�N�g�̒��_���ݒ�
//-------------------------------------
void CObjectBillboard::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 size = m_vtxData.size;		// �傫��
	D3DXCOLOR color = m_vtxData.color;		// �F

	// 3D���_���̃|�C���^��錾
	VERTEX_3D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	//���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x,  size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+size.x,  size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, -size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+size.x, -size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[��ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//�e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------
//- �v���C���[�̒l�ݒ菈��
//-------------------------------------
void CObjectBillboard::SetVtxData(CObjectBillboard::VtxData vtxData)
{
	m_vtxData = vtxData;
}

//-------------------------------------
//- �v���C���[�̒l�擾����
//-------------------------------------
CObjectBillboard::VtxData CObjectBillboard::GetVtxData(void)
{
	return m_vtxData;
}
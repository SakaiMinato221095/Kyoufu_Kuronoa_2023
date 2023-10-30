
//-===============================================
//-
//-	2D�I�u�W�F�N�g����[object2d.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CObject2d::CObject2d(int nPriority) : CObject(nPriority)
{
	// �l���N���A
	ZeroMemory(&m_vtxData, sizeof(m_vtxData));

	m_nTextureNldxUse = 0;
	m_pVtxBuff = NULL;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CObject2d::~CObject2d()
{

}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CObject2d::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �����ݒ菈��
	InitSet(pos,size,color);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@���������̗L���𔻒�
	if (m_pVtxBuff == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;

	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̏I������
//-------------------------------------
void CObject2d::Uninit(void)
{
	// ���_�o�b�t�@�̗L���𔻒�
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObject2d::Update(void)
{
	// 2D�I�u�W�F�N�g�̒��_���ݒ�
	SetVtx();
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObject2d::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �`�揈���𔲂���
		return;
	}
	
	// �e�N�X�`���Ǘ��̎擾
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// �e�N�X�`���Ǘ��̏��擾�̐����𔻒�
	if (pManagerTexture == NULL)
	{// ���s��

		// �`�揈���𔲂���
		return;
	}

	// ���_���̕`��
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(
			0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(
			0,
			pManagerTexture->GetAddress(m_nTextureNldxUse));

		// 2D�I�u�W�F�N�g�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			0,								//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);								//�v���~�e�B�u�́i�|���S���j��
	}
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̃e�N�X�`������
//-------------------------------------
void CObject2d::BindTexture(int nTextureNldx)
{
	// �e�N�X�`���̔ԍ�����
	m_nTextureNldxUse = nTextureNldx;
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̐�������
//-------------------------------------
CObject2d * CObject2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// 2D�I�u�W�F�N�g�̐���
	CObject2d *pObject2d = DBG_NEW CObject2d(3);

	// �����̐����̗L���𔻒�
	if (pObject2d != NULL)
	{
		// ����������
		if (FAILED(pObject2d->Init(pos,size,color)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObject2d == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �I�u�W�F�N�g�̒��_���ݒ�
	pObject2d->SetVtx();

	// 2D�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObject2d;
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̒��_���ݒ�
//-------------------------------------
void CObject2d::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_vtxData.pos;	// �ʒu
	D3DXVECTOR3 size = m_vtxData.size;	// �傫��
	D3DCOLOR color = m_vtxData.color;	// �F

	// 2D���_���̃|�C���^��錾
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	// ���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[��ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// �e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// ���X�V
	m_vtxData.pos = pos;		// �ʒu
	m_vtxData.size = size;		// �傫��
	m_vtxData.color = color;	// �F
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̒��_�o�b�t�@�擾
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 CObject2d::GetVtxBuff(void)
{
	// ���_�o�b�t�@��Ԃ�
	return m_pVtxBuff;
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̒��_�l���擾����
//-------------------------------------
CObject2d::VtxData CObject2d::GetVtxData(void)
{
	// ���_�l���
	return m_vtxData;
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̒��_�l���ݒ菈��
//-------------------------------------
void CObject2d::SetVtxData(CObject2d::VtxData vtxData)
{
	m_vtxData = vtxData;
}

//-------------------------------------
//- 2D�I�u�W�F�N�g�̏����ݒ菈��
//-------------------------------------
void CObject2d::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_vtxData.pos = pos;
	m_vtxData.size = size;
	m_vtxData.color = color;
}

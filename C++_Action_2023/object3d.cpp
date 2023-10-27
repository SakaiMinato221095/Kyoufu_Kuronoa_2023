
//================================================
//=
//=	3D�I�u�W�F�N�g����[object3d.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "object3d.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//-------------------------------------
//-	3D�I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObject3d::CObject3d(int nPriority) : CObject(nPriority)
{
	// �l���N���A
	m_pVtxBuff = NULL;
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
	ZeroMemory(&m_vtxData, sizeof(m_vtxData));

	m_nTextureNldxUse = 0;
	m_typeCreate = TYPE_CREATE(0);
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObject3d::~CObject3d()
{
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̏�����
//-------------------------------------
HRESULT CObject3d::Init(TYPE_CREATE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����̗L���𔻒�
	if (m_pVtxBuff == NULL)
	{
		// �������𔲂���
		return E_FAIL;
	}

	// ������ނ�ݒ�
	m_typeCreate = type;

	// �����ݒ�
	InitSet(pos,size,rot,color);

	// ���_�o�b�t�@�ݒ�
	SetVtx();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̏I������
//-------------------------------------
void CObject3d::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObject3d::Update(void)
{
	// ���_���ݒ菈��
	SetVtx();
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObject3d::Draw(void)
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

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_vtxData.pos;	// �ʒu���
	D3DXVECTOR3 rot = m_vtxData.rot;	// �������

	//�ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		pManagerTexture->GetAddress(m_nTextureNldxUse));

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`�悷��ŏ��̒��_�C���f�b�N�X
		2);						// �v���~�e�B�u�́i�|���S���j��

}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̐�������
//-------------------------------------
CObject3d * CObject3d::Create(TYPE_CREATE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	// 3D�I�u�W�F�N�g�̐���
	CObject3d *pObject3d = new CObject3d;

	// �����̐����̗L���𔻒�
	if (pObject3d != NULL)
	{
		// ����������
		if (FAILED(pObject3d->Init(type,pos,size,rot,color)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObject3d == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// 3D�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObject3d;
}

//-------------------------------------
//- 3D�I�u�W�F�N�g�̃e�N�X�`������
//-------------------------------------
void CObject3d::BindTexture(int nTextureNldx)
{
	// �e�N�X�`���̔ԍ�����
	m_nTextureNldxUse = nTextureNldx;
}

//-------------------------------------
//- 3D�I�u�W�F�N�g�̒��_�l���̐ݒ菈��
//-------------------------------------
void CObject3d::SetVtxData(VtxData vtxData)
{
	m_vtxData = vtxData;
}

//-------------------------------------
//- 3D�I�u�W�F�N�g�̒��_�l���̎擾����
//-------------------------------------
CObject3d::VtxData CObject3d::GetVtxData(void)
{
	return m_vtxData;
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̒��_���ݒ菈��
//-------------------------------------
void CObject3d::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 size = m_vtxData.size;	// �T�C�Y
	D3DXCOLOR color = m_vtxData.color;	// �F

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// 3D���_���̃|�C���^��錾
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	switch (m_typeCreate)
	{
	case TYPE_CREATE_FIELD:

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-size.x, 0.0f,  size.z);
		pVtx[1].pos = D3DXVECTOR3( size.x, 0.0f,  size.z);
		pVtx[2].pos = D3DXVECTOR3(-size.x, 0.0f, -size.z);
		pVtx[3].pos = D3DXVECTOR3( size.x, 0.0f, -size.z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		break;

	case TYPE_CREATE_WALL:

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-size.x, size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( size.x, size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-size.x,-size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( size.x,-size.y, 0.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		break;
	}

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

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//-------------------------------------
//-	3D�I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CObject3d::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	m_vtxData.pos = pos;
	m_vtxData.size = size;
	m_vtxData.rot = rot;
	m_vtxData.color = color;
}
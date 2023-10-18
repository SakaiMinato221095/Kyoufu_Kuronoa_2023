
//================================================
//=
//= X�t�@�C���I�u�W�F�N�g����[object_x.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "object_x.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//=======================================
//=	�R���X�g��`
//=======================================

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	// �l���N���A
	m_nModelNldxUse = -1;

	ZeroMemory(&m_vtxData, sizeof(m_vtxData));

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectX::~CObjectX()
{
}

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CObjectX::Init()
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectX::Uninit(void)
{
	// �������g�̃|�C���^�̊J��
	Release();
}

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectX::Update(void)
{

}

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectX::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return;
	}

	// ���f���Ǘ��̎擾
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̏��擾�̐����𔻒�
	if (pManagerModel == NULL)
	{// ���s��

		// �`�揈���𔲂���
		return;
	}

	// ���f�������擾
	CManagerModel::Model model = pManagerModel->GetAddress(m_nModelNldxUse);

	// ���f���̗L���𔻒�
	if (model.m_pMesh == NULL)
	{
		// �`�揈���𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_vtxData.pos;	// �ʒu���
	D3DXVECTOR3 rot = m_vtxData.rot;	// �������

	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;				// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���ւ̃|�C���^

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

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);
	
	// �}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)model.m_pBuffMat->GetBufferPointer();

	// �}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)model.m_dwNumMat; nCutMat++)
	{
		// �ꎞ�I�ȐF�̕ۊǏꏊ
		D3DXCOLOR tempColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		// ���̐F��ۊ�
		tempColor = pMat[nCutMat].MatD3D.Diffuse;

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		// �e�N�X�`���̐ݒ�i���j
		pDevice->SetTexture(0, model.m_pTexture[nCutMat]);

		// X�t�@�C���I�u�W�F�N�g�i�p�[�c�j�̕`��
		model.m_pMesh->DrawSubset(nCutMat);
	}

	// �ۑ����Ă����}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//-------------------------------------
//-	X�t�@�C���I�u�W�F�N�g�̐�������
//-------------------------------------
CObjectX *CObjectX::Create(void)
{
	// X�t�@�C���I�u�W�F�N�g�̃|�C���^��錾
	CObjectX *pObjectX = NULL;

	// ����
	pObjectX = DBG_NEW CObjectX;

	// �����̐����̗L���𔻒�
	if (pObjectX != NULL)
	{
		// ����������
		if (FAILED(pObjectX->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObjectX == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// X�t�@�C���I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObjectX;
}

//-------------------------------------
//- X�t�@�C���I�u�W�F�N�g�̃e�N�X�`������
//-------------------------------------
void CObjectX::BindModel(int nModelNldx, int nModelNum)
{
	// �e�N�X�`���̔ԍ�����
	m_nModelNldxUse = nModelNldx;

	// ���f���̐ݒ�
	SetModel(nModelNum);
}

//-------------------------------------
//- X�t�@�C���I�u�W�F�N�g�̒��_�l���̐ݒ菈��
//-------------------------------------
void CObjectX::SetVtxData(VtxData vtxData)
{
	m_vtxData = vtxData;
}

//-------------------------------------
//- X�t�@�C���I�u�W�F�N�g�̒��_�l���̎擾����
//-------------------------------------
CObjectX::VtxData CObjectX::GetVtxData(void)
{
	return m_vtxData;
}

//-------------------------------------
//- X�t�@�C���I�u�W�F�N�g�̃��f���̐ݒ�i���z�֐��j
//-------------------------------------
void CObjectX::SetModel(int nModelNldx)
{
	// ���s
}

//-===============================================
//-
//-	���ʂȂ��I�u�W�F�N�g�̏���[object_none.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "objectx_none.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// ���ʂȂ��I�u�W�F�N�g�̃��f���̃R���X�g��`
const char *pModelObjectXNone[] =
{
	"data\\MODEL\\None\\Block_000.x",			// �u���b�N
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CObjectXNone::ModelData CObjectXNone::m_modelData[MODEL_MAX] = {};	// ���f�����
int CObjectXNone::m_nModelNldx[MODEL_MAX] = {};						// ���f���̔ԍ�

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjectXNone::CObjectXNone(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	���ʂȂ��I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjectXNone::~CObjectXNone()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CObjectXNone::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// ���f���ݒ�
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// ���f���ԍ����擾
		int nModelNldx = m_nModelNldx[nCount];

		// ���f���ԍ��̎擾�i���f���̊����j
		nModelNldx = pManagerModel->Regist(pModelObjectXNone[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nModelNldx[nCount] = nModelNldx;
	}

	m_modelData[MODEL_BLOCK_000].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CObjectXNone::Unload(void)
{

}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObjectXNone::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nModelNldx[model];

	// ���ʂȂ��I�u�W�F�N�g�̃��f������
	BindModel(nModelNldx,model);

	// �����ݒ菈��
	InitSet(model,pos,rot);

	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjectXNone::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjectXNone::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjectXNone::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CObjectXNone * CObjectXNone::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��錾
	CObjectXNone *pCObjectXNone = DBG_NEW CObjectXNone(4);

	// �����̐����̗L���𔻒�
	if (pCObjectXNone != NULL)
	{
		// ����������
		if (FAILED(pCObjectXNone->Init(model,pos,rot)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObjectXNone == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ���ʂȂ��I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pCObjectXNone;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CObjectXNone::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CObjectXNone::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CObjectXNone::SetModelData(int nNum, CObjectXNone::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CObjectXNone::ModelData CObjectXNone::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- ���ʂȂ��I�u�W�F�N�g�̏����ݒ菈��
//-------------------------------------
void CObjectXNone::InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = m_modelData[model].size;

	SetVtxData(vtxData);
}
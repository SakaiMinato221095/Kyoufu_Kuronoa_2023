
//-===============================================
//-
//-	�G�̏���[enemy.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "file_data_emy_nor.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �G�̃��f���̃R���X�g��`
const char *pModelEnemy[] =
{
	"data\\MODEL\\alien000.x",			// �G�C���A��000
	"data\\MODEL\\alien001.x",			// �G�C���A��001
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CDataInt CEnemy::m_nDataModelNldx[MODEL_TYPE_MAX] = {};			// ���f���̔ԍ�

CEnemy::ModelData CEnemy::m_modelData[MODEL_TYPE_MAX] = {};		// ���f�����

//-------------------------------------
//-	�G�̃R���X�g���N�^
//-------------------------------------
CEnemy::CEnemy()
{

}

//-------------------------------------
//-	�G�̃f�X�g���N�^
//-------------------------------------
CEnemy::~CEnemy()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CEnemy::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < MODEL_TYPE_MAX; nCount++)
	{
		// ���f���ԍ����擾
		int nModelNldx = m_nDataModelNldx[nCount].Get();

		// ���f���ԍ��̎擾�i���f���̊����j
		nModelNldx = pManagerModel->Regist(pModelEnemy[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// �ʏ�G�̏��̓ǂݍ���
	CFileDataEmyNor::Load();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CEnemy::Unload(void)
{

}

//-------------------------------------
//- �G�̏���������
//-------------------------------------
HRESULT CEnemy::Init(MODEL_TYPE modelType)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nDataModelNldx[modelType].Get();

	// ���ʂȂ��I�u�W�F�N�g�̃��f������
	BindModel(nModelNldx, modelType);

	// �f�[�^�ݒ�
	m_dataSize.Set(m_modelData[modelType].size);

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
//- �G�̏I������
//-------------------------------------
void CEnemy::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �G�̍X�V����
//-------------------------------------
void CEnemy::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �G�̕`�揈��
//-------------------------------------
void CEnemy::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//-	�G�̃��f���̐ݒ菈��
//-------------------------------------
int CEnemy::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	�G�̃��f���̐ݒ菈��
//-------------------------------------
void CEnemy::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL_TYPE)nModelNldx;
}

//-------------------------------------
//-	�G�̃��f���̏��̐ݒ菈��
//-------------------------------------
void CEnemy::SetModelData(int nNum, CEnemy::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	�G�̃��f���̏��̎擾����
//-------------------------------------
CEnemy::ModelData CEnemy::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}
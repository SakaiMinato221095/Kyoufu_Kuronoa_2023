
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

#include "collision.h"

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
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CEnemy::m_nModelNldx[MODEL_MAX] = {};			// ���f���̔ԍ�

CEnemy::ModelData CEnemy::m_modelData[MODEL_MAX] = {};	// ���f�����

//-------------------------------------
//-	�G�̃R���X�g���N�^
//-------------------------------------
CEnemy::CEnemy()
{
	m_model = MODEL(0);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCollNldx = -1;
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

	// ���f���ݒ�
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// ���f���ԍ����擾
		int nModelNldx = m_nModelNldx[nCount];

		// ���f���ԍ��̎擾�i���f���̊����j
		nModelNldx = pManagerModel->Regist(pModelEnemy[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nModelNldx[nCount] = nModelNldx;
	}

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
HRESULT CEnemy::Init(MODEL modelType)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// �����蔻��̃|�C���^�擾
	CCollision *pCollision = CManager::GetCollision();

	// �����蔻��̗L���𔻒�
	if (pCollision == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nModelNldx[modelType];

	// ���ʂȂ��I�u�W�F�N�g�̃��f������
	BindModel(nModelNldx, modelType);

	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ���_�l�����擾
	VtxData vtxData = GetVtxData();

	// �T�C�Y��ݒ�
	vtxData.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// ���_�l�����X�V
	SetVtxData(vtxData);

	// �����蔻��ݒ�
	m_nCollNldx = pCollision->SetColl(
		CCollision::TAG_ENEMY,
		CCollision::TYPE_RECTANGLE,
		CObjectX::GetVtxData().pos,
		CObjectX::GetVtxData().size,
		this);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̏I������
//-------------------------------------
void CEnemy::Uninit(void)
{
	// �����蔻��̃|�C���^�擾
	CCollision *pCollision = CManager::GetCollision();

	// �����蔻��̗L���𔻒�
	if (pCollision == NULL)
	{
		// �����𔲂���
		return;
	}

	// �����蔻��̏I������
	pCollision->UninitColl(m_nCollNldx);

	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �G�̍X�V����
//-------------------------------------
void CEnemy::Update(void)
{
	// �����蔻��̃|�C���^�擾
	CCollision *pCollision = CManager::GetCollision();

	// �����蔻��̗L���𔻒�
	if (pCollision == NULL)
	{
		// �����𔲂���
		return;
	}

	// �����蔻��ʒu�̍X�V����
	pCollision->UpdateData(
		m_nCollNldx,
		CObjectX::GetVtxData().pos,
		CObjectX::GetVtxData().size);

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
//- �G�̕`�揈��
//-------------------------------------
void CEnemy::Set(D3DXVECTOR3 pos)
{
	VtxData vtxData = GetVtxData();

	vtxData.pos = pos;

	SetVtxData(vtxData);
}

//-------------------------------------
//- �ʏ�G�̐�������
//-------------------------------------
CEnemy *CEnemy::Create(MODEL modelType)
{
	// �ʏ�G�̐���
	CEnemy *pEnemy = DBG_NEW CEnemy;

	// �����̐����̗L���𔻒�
	if (pEnemy != NULL)
	{
		// ����������
		if (FAILED(pEnemy->Init(modelType)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pEnemy == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�G�̃|�C���^��Ԃ�
	return pEnemy;
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
	m_model = (MODEL)nModelNldx;
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
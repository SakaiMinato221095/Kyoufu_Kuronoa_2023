
//-===============================================
//-
//-	�M�~�b�N�̏���[gimmick.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "gimmick.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �M�~�b�N�̃��f���̃R���X�g��`
const char *pModelGimmick[] =
{
	"data\\MODEL\\Gimmick\\Jewel.x",			// ���
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CGimmick::ModelData CGimmick::m_modelData[MODEL_MAX] = {};	// ���f�����
int CGimmick::m_nModelNldx[MODEL_MAX] = {};						// ���f���̔ԍ�

//-------------------------------------
//-	�M�~�b�N�̃R���X�g���N�^
//-------------------------------------
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	�M�~�b�N�̃f�X�g���N�^
//-------------------------------------
CGimmick::~CGimmick()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CGimmick::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGimmick[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nModelNldx[nCount] = nModelNldx;
	}

	m_modelData[MODEL_JEWEL_000].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CGimmick::Unload(void)
{

}

//-------------------------------------
//- �M�~�b�N�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CGimmick::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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

	// �M�~�b�N�̃��f������
	BindModel(nModelNldx, model);

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
//- �M�~�b�N�̏I������
//-------------------------------------
void CGimmick::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �M�~�b�N�̍X�V����
//-------------------------------------
void CGimmick::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �M�~�b�N�̕`�揈��
//-------------------------------------
void CGimmick::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �M�~�b�N�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CGimmick * CGimmick::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �M�~�b�N�̃|�C���^��錾
	CGimmick *pCGimmick = DBG_NEW CGimmick(4);

	// �����̐����̗L���𔻒�
	if (pCGimmick != NULL)
	{
		// ����������
		if (FAILED(pCGimmick->Init(model,pos,rot)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCGimmick == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �M�~�b�N�̃|�C���^��Ԃ�
	return pCGimmick;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CGimmick::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CGimmick::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CGimmick::SetModelData(int nNum, CGimmick::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CGimmick::ModelData CGimmick::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- �M�~�b�N�̏����ݒ菈��
//-------------------------------------
void CGimmick::InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = m_modelData[model].size;

	SetVtxData(vtxData);
}
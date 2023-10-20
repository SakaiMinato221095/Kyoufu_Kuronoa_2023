
//-===============================================
//-
//-	�S�[���̏���[goal.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "goal.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

#include "manager.h"
#include "fade.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �M�~�b�N�̃��f���̃R���X�g��`
const char *pModelGoal[] =
{
	"data\\MODEL\\Goal\\goal_000.x",			// �S�[��000
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

CGoal::ModelData CGoal::m_modelData[MODEL_MAX] = {};	// ���f�����
int CGoal::m_nModelNldx[MODEL_MAX] = {};					// ���f���̔ԍ�

//-------------------------------------
//-	�M�~�b�N�̃R���X�g���N�^
//-------------------------------------
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	�M�~�b�N�̃f�X�g���N�^
//-------------------------------------
CGoal::~CGoal()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CGoal::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGoal[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nModelNldx[nCount] = nModelNldx;
	}

	m_modelData[MODEL_GOAL_000].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CGoal::Unload(void)
{

}

//-------------------------------------
//- �M�~�b�N�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CGoal::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
	InitSet(model, pos, rot);

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
void CGoal::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();

		// �����蔻��̊J������
		delete m_pColl;
		m_pColl = NULL;
	}

	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �M�~�b�N�̍X�V����
//-------------------------------------
void CGoal::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();

	// �����蔻��̏��X�V����
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	// �G�Ƃ̓����蔻��
	if (m_pColl->Hit(CMgrColl::TAG_PLAYER, CMgrColl::STATE_HIT_NONE) == true)
	{
		// �Q�[�����[�h
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//- �M�~�b�N�̕`�揈��
//-------------------------------------
void CGoal::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �M�~�b�N�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CGoal * CGoal::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �M�~�b�N�̃|�C���^��錾
	CGoal *pCGoal = DBG_NEW CGoal(4);

	// �����̐����̗L���𔻒�
	if (pCGoal != NULL)
	{
		// ����������
		if (FAILED(pCGoal->Init(model, pos, rot)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCGoal == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �M�~�b�N�̃|�C���^��Ԃ�
	return pCGoal;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CGoal::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CGoal::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	���f���̏��̐ݒ菈��
//-------------------------------------
void CGoal::SetModelData(int nNum, CGoal::ModelData modelData)
{
	// ���f�����̑��
	m_modelData[nNum] = modelData;	// �傫��
}

//-------------------------------------
//-	���f���̏��̎擾����
//-------------------------------------
CGoal::ModelData CGoal::GetModelData(int nNum)
{
	// ���f������Ԃ�
	return m_modelData[nNum];
}

//-------------------------------------
//- �M�~�b�N�̏����ݒ菈��
//-------------------------------------
void CGoal::InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = m_modelData[model].size;

	SetVtxData(vtxData);

	// �����蔻��ݒ�
	m_pColl = CColl::Create(
		CMgrColl::TAG_GOAL,
		GetVtxData().pos,
		GetVtxData().size);

	// ����^�O�̐ݒ菈��
	m_pColl->SetTagTgt(CMgrColl::TAG_PLAYER, CMgrColl::TYPE_RECTANGLE, true);
}
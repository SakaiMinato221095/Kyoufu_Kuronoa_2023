
//-===============================================
//-
//-	�ێ��G�̏���[enemy_have.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "enemy_have.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

#include "kazedama.h"
#include "player.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �ێ��G�̃��f���̃R���X�g��`
const char *pModelEnemyHave[] =
{
	"data\\MODEL\\alien000.x",			// �G�C���A��000
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CEnemyHave::m_nModelNldx[MODEL_MAX] = {};	// ���f���̔ԍ�

//-------------------------------------
//-	�ێ��G�̃R���X�g���N�^
//-------------------------------------
CEnemyHave::CEnemyHave()
{
	m_model = MODEL(0);

	ZeroMemory(&m_data, sizeof(m_data));
	m_pColl = NULL;
}

//-------------------------------------
//-	�ێ��G�̃f�X�g���N�^
//-------------------------------------
CEnemyHave::~CEnemyHave()
{

}

//-------------------------------------
//- �ێ��G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CEnemyHave::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelEnemyHave[nCount]);

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
//- �ێ��G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CEnemyHave::Unload(void)
{

}

//-------------------------------------
//- �ێ��G�̏���������
//-------------------------------------
HRESULT CEnemyHave::Init(MODEL model, STATE state, D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// �����ݒ菈��
	InitSet(state,pos,rot,size);

	// ���f���ԍ����擾
	int nModelNldx = m_nModelNldx[model];

	// ���ʂȂ��I�u�W�F�N�g�̃��f������
	BindModel(nModelNldx, model);

	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����蔻��ݒ�
	m_pColl = CColl::Create(
		CMgrColl::TAG_ENEMY_HAVE,
		GetVtxData().pos,
		GetVtxData().size);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ێ��G�̏I������
//-------------------------------------
void CEnemyHave::Uninit(void)
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
//- �ێ��G�̍X�V����
//-------------------------------------
void CEnemyHave::Update(void)
{
	// �����蔻��̏��X�V����
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	switch (m_data.state)
	{
	case STATE_OBTAIN:

		// �l�����̍X�V����
		UpdateObtain();

		break;

	case STATE_WAIT:

		// �ҋ@���̍X�V����
		UpdateWait();

		break;

	case STATE_SHOT:

		// ���ˎ��̍X�V����
		if (UpdateShot())
		{
			return;
		}
		
		break;
	}

	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �ێ��G�̕`�揈��
//-------------------------------------
void CEnemyHave::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �ێ��G�̐�������
//-------------------------------------
CEnemyHave * CEnemyHave::Create(MODEL model, STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// �ێ��G�̐���
	CEnemyHave *pEnemy = DBG_NEW CEnemyHave;

	// �����̐����̗L���𔻒�
	if (pEnemy != NULL)
	{
		// ����������
		if (FAILED(pEnemy->Init(model,state, pos,rot, size)))
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

	// �ێ��G�̃|�C���^��Ԃ�
	return pEnemy;
}

//-------------------------------------
//-	�ێ��G�̃��f���̐ݒ菈��
//-------------------------------------
int CEnemyHave::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	�ێ��G�̃��f���̐ݒ菈��
//-------------------------------------
void CEnemyHave::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	�ێ��G�̊l���X�V����
//-------------------------------------
void CEnemyHave::UpdateObtain(void)
{

}

//-------------------------------------
//-	�ێ��G�̑ҋ@�X�V����
//-------------------------------------
void CEnemyHave::UpdateWait(void)
{

}

//-------------------------------------
//-	�ێ��G�̔��ˍX�V����
//-------------------------------------
bool CEnemyHave::UpdateShot(void)
{
	// �ϐ���錾�i���擾�j
	VtxData vtxData = GetVtxData();

	// ���Z����
	vtxData.pos += m_data.move;			// �ʒu

	// ���X�V
	SetVtxData(vtxData);

	// ��΂Ƃ̓����蔻��
	if (m_pColl->Hit(CMgrColl::TAG_GIMMICK_JEWEL, CMgrColl::STATE_HIT_DEAD) == true ||
		m_pColl->Hit(CMgrColl::TAG_BLOCK, CMgrColl::STATE_HIT_DEAD) == true)
	{
		// �I������
		Uninit();

		return true;
	}

	// �̗̓J�E���g
	m_data.nLifeCut++;

	// �̗̓J�E���g�̔���
	if (m_data.nLifeCut >= m_data.nLife)
	{
		// �I������
		Uninit();

		return true;
	}

	return false;
}

//-------------------------------------
//-	�ێ��G�̔��ːݒ菈��
//-------------------------------------
void CEnemyHave::SetShot(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, TYPE_ROT typeRot)
{
	m_data.state = STATE_SHOT;

	// �ϐ���錾�i���擾�j
	VtxData vtxData = GetVtxData();

	// ���Z����
	vtxData.pos = pos;			// �ʒu

	// ���X�V
	SetVtxData(vtxData);

	m_data.move = move;
	m_data.nLife = nLife;
	m_data.typeRot = typeRot;

	// ����^�O�̐ݒ菈��
	m_pColl->SetTagTgt(CMgrColl::TAG_GIMMICK_JEWEL, CMgrColl::TYPE_RECTANGLE, true);

	// ����^�O�̐ݒ菈��
	m_pColl->SetTagTgt(CMgrColl::TAG_BLOCK, CMgrColl::TYPE_RECTANGLE, true);
}

//-------------------------------------
//- �ێ��G�̐ݒ菈��
//-------------------------------------
void CEnemyHave::InitSet(STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	VtxData vtxData;

	m_data.state = state;
	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = size;

	SetVtxData(vtxData);
}
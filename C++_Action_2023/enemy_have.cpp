
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

#include "collision.h"

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
CEnemyHave *CEnemyHave::m_pInstance = NULL;		// ���g�̃|�C���^

//-------------------------------------
//-	�ێ��G�̃R���X�g���N�^
//-------------------------------------
CEnemyHave::CEnemyHave()
{
	ZeroMemory(&m_data, sizeof(m_data));

	m_model = MODEL(0);
	m_nCollNldx = -1;


	if (m_pInstance == NULL)
	{
		// ���g�̃|�C���^����
		m_pInstance = this;
	}
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
HRESULT CEnemyHave::Init(MODEL modelType)
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
		CCollision::TAG_ENEMY_HAVE,
		CCollision::TYPE_RECTANGLE,
		CObjectX::GetVtxData().pos,
		CObjectX::GetVtxData().size,
		this);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ێ��G�̏I������
//-------------------------------------
void CEnemyHave::Uninit(void)
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

	// ���g�̃|�C���^��������
	m_pInstance = NULL;

	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �ێ��G�̍X�V����
//-------------------------------------
void CEnemyHave::Update(void)
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
		UpdateShot();

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
//- �ێ��G�̐ݒ菈��
//-------------------------------------
void CEnemyHave::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.size = size;

	SetVtxData(vtxData);
}

//-------------------------------------
//- �ێ��G�̐�������
//-------------------------------------
CEnemyHave *CEnemyHave::Create(MODEL modelType)
{
	// �ێ��G�̐���
	CEnemyHave *pEnemy = DBG_NEW CEnemyHave;

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

	// �ێ��G�̃|�C���^��Ԃ�
	return pEnemy;
}

//-------------------------------------
//-	�ێ��G�̃��f���̃|�C���^�擾����
//-------------------------------------
CEnemyHave * CEnemyHave::GetInstance(void)
{
	return m_pInstance;
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
	// �����܂̎擾����
	CKazedama *pKazedama = CKazedama::GetInstance();

	// �����܂̗L���𔻒�
	if (pKazedama == NULL)
	{
		// �ҋ@��ԂɕύX
		m_data.state = STATE_WAIT;

		// �v���C���[�̎擾����
		CPlayer *pPlayer = CPlayer::GetInstance();

		if (pPlayer == NULL)
		{
			return;
		}

		// �ێ���Ԃ��X�V
		pPlayer->SetHave(true);

		return;
	}

	// ���擾
	VtxData vtxData = GetVtxData();
	
	// ���擾�i�����܁j
	D3DXVECTOR3 posKaze = pKazedama->GetVtxData().pos;	// �ʒu

	// �ʒu�𕗂��܂̈ʒu�ɕύX
	vtxData.pos = posKaze;

	// ���X�V
	SetVtxData(vtxData);
}

//-------------------------------------
//-	�ێ��G�̑ҋ@�X�V����
//-------------------------------------
void CEnemyHave::UpdateWait(void)
{
	// �v���C���[�̎擾����
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == NULL)
	{
		return;
	}

	// ���擾
	VtxData vtxData = GetVtxData();

	// ���擾�i�����܁j
	D3DXVECTOR3 posPlayer = pPlayer->GetData().pos;	// �ʒu

	// �ʒu�𕗂��܂̈ʒu�ɕύX
	vtxData.pos = D3DXVECTOR3(posPlayer.x,posPlayer.y + 300.0f,posPlayer.z);

	// ���X�V
	SetVtxData(vtxData);
}

//-------------------------------------
//-	�ێ��G�̔��ˍX�V����
//-------------------------------------
void CEnemyHave::UpdateShot(void)
{
	// �ϐ���錾�i���擾�j
	VtxData vtxData = GetVtxData();

	// ���Z����
	vtxData.pos += m_data.move;			// �ʒu

	// ���X�V
	SetVtxData(vtxData);

	// �̗̓J�E���g
	m_data.nLifeCut++;

	// �̗̓J�E���g�̔���
	if (m_data.nLifeCut >= m_data.nLife)
	{
		// �I������
		Uninit();
	}
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

	// �����蔻��̐ݒ�
}
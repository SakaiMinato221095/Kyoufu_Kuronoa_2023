
//-===============================================
//-
//-	��΃M�~�b�N����[gimmick_jewel.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "gimmick_jewel.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

#include "game.h"
#include "player.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	��΃M�~�b�N�R���X�g���N�^
//-------------------------------------
CGimmickJewel::CGimmickJewel(int nPriority) : CGimmick(nPriority)
{
	m_pColl = NULL;
}

//-------------------------------------
//-	��΃M�~�b�N�f�X�g���N�^
//-------------------------------------
CGimmickJewel::~CGimmickJewel()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CGimmickJewel::Load(void)
{
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CGimmickJewel::Unload(void)
{

}

//-------------------------------------
//- ��΃M�~�b�N����������
//-------------------------------------
HRESULT CGimmickJewel::Init(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// �M�~�b�N�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CGimmick::Init(model,pos,rot)))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����ݒ菈��
	InitSet(typeEffect);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- ��΃M�~�b�N�I������
//-------------------------------------
void CGimmickJewel::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();

		// �����蔻��̊J������
		delete m_pColl;
		m_pColl = NULL;
	}

	// �M�~�b�N�̏I��
	CGimmick::Uninit();
}

//-------------------------------------
//- ��΃M�~�b�N�X�V����
//-------------------------------------
void CGimmickJewel::Update(void)
{
	// �M�~�b�N�̍X�V����
	CGimmick::Update();

	// �����蔻��̏��X�V����
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	// �G�Ƃ̓����蔻��
	if (m_pColl->GetData().stateHit == CMgrColl::STATE_HIT_DEAD)
	{
		// �v���C���[�̋�������
		PlayerPlus();

		// �I������
		Uninit();

		return;
	}
}

//-------------------------------------
//- ��΃M�~�b�N�`�揈��
//-------------------------------------
void CGimmickJewel::Draw(void)
{
	// �M�~�b�N�̕`�揈��
	CGimmick::Draw();
}

//-------------------------------------
//- ��΃M�~�b�N���������i�M�~�b�N�ݒ�j
//-------------------------------------
CGimmickJewel * CGimmickJewel::Create(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ��΃M�~�b�N�|�C���^��錾
	CGimmickJewel *pCGimmickJewel = DBG_NEW CGimmickJewel(4);

	// �����̐����̗L���𔻒�
	if (pCGimmickJewel != NULL)
	{
		// ����������
		if (FAILED(pCGimmickJewel->Init(model, typeEffect, pos, rot)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCGimmickJewel == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ��΃M�~�b�N�|�C���^��Ԃ�
	return pCGimmickJewel;
}

//-------------------------------------
//- ��΃M�~�b�N�����ݒ菈��
//-------------------------------------
void CGimmickJewel::InitSet(TYPE_EFFECT typeEffect)
{
	m_type = typeEffect;	// ���ʂ̎��

	// �����蔻��ݒ�
	m_pColl = CColl::Create(
		CMgrColl::TAG_GIMMICK_JEWEL,
		GetVtxData().pos,
		GetVtxData().size);
}

//-------------------------------------
//- ��΃M�~�b�N�̃v���C���[��������
//-------------------------------------
void CGimmickJewel::PlayerPlus(void)
{
	// �v���C���[���̎擾����
	CPlayer *pPlayer = CGame::GetPlayer();
	
	if (pPlayer == NULL)
	{
		return;
	}
	
	// ��������
	pPlayer->SetPlus(1.5f,120);
}
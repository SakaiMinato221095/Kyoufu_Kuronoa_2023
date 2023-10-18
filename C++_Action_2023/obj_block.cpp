
//-===============================================
//-
//-	�u���b�O�I�u�W�F�N�g����[obj_block.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "obj_block.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

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
//-	�u���b�O�I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjBlock::CObjBlock(int nPriority) : CObjectXNone(nPriority)
{

}

//-------------------------------------
//-	�u���b�O�I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjBlock::~CObjBlock()
{

}

//-------------------------------------
//- �G�̃��f���ǂݍ���
//-------------------------------------
HRESULT CObjBlock::Load(void)
{
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �G�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CObjBlock::Unload(void)
{

}

//-------------------------------------
//- �u���b�O�I�u�W�F�N�g�̏����������i���ʂȂ��I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObjBlock::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���ʂȂ��I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectXNone::Init(model, pos, rot)))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����ݒ�
	InitSet();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �u���b�O�I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjBlock::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();

		// �����蔻��̊J������
		delete m_pColl;
		m_pColl = NULL;
	}

	// ���ʂȂ��I�u�W�F�N�g�̏I��
	CObjectXNone::Uninit();
}

//-------------------------------------
//- �u���b�O�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjBlock::Update(void)
{
	// ���ʂȂ��I�u�W�F�N�g�̍X�V����
	CObjectXNone::Update();

	// �����蔻��̏��X�V����
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);
}

//-------------------------------------
//- �u���b�O�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjBlock::Draw(void)
{
	// ���ʂȂ��I�u�W�F�N�g�̕`�揈��
	CObjectXNone::Draw();
}

//-------------------------------------
//- �u���b�O�I�u�W�F�N�g�̐��������i���ʂȂ��I�u�W�F�N�g�ݒ�j
//-------------------------------------
CObjBlock * CObjBlock::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �u���b�O�I�u�W�F�N�g�̃|�C���^��錾
	CObjBlock *pCObjBlock = DBG_NEW CObjBlock(4);

	// �����̐����̗L���𔻒�
	if (pCObjBlock != NULL)
	{
		// ����������
		if (FAILED(pCObjBlock->Init(model, pos, rot)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObjBlock == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �u���b�O�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pCObjBlock;
}

//-------------------------------------
//- �u���b�O�I�u�W�F�N�g�̏����ݒ�
//-------------------------------------
void CObjBlock::InitSet(void)
{
	// �����蔻��ݒ�
	m_pColl = CColl::Create(
		CMgrColl::TAG_BLOCK,
		GetVtxData().pos,
		GetVtxData().size);
}


//================================================
//=
//=	�����蔻��̏���[coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "coll.h"

#include "manager.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�R���X�g��`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�����蔻��̃R���X�g���N�^
//-------------------------------------
CColl::CColl()
{
	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	�����蔻��̃f�X�g���N�^
//-------------------------------------
CColl::~CColl()
{

}

//-------------------------------------
//- �����蔻��̏���������
//-------------------------------------
HRESULT CColl::Init(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �����ݒ菈��
	InitSet(tag, type, pos, size);

	return S_OK;
}

//-------------------------------------
//- �����蔻��̏I������
//-------------------------------------
void CColl::Uninit(void)
{

}

//-------------------------------------
//- �����蔻��̍X�V����
//-------------------------------------
void CColl::Update(void)
{

}

//-------------------------------------
//- �����蔻��̕`�揈��
//-------------------------------------
void CColl::Draw(void)
{
}

//-------------------------------------
//- �����蔻��̐�������
//-------------------------------------
CColl * CColl::Create(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)

{
	// �����蔻��̐���
	CColl *pCollision = DBG_NEW CColl;

	// �����̐����̗L���𔻒�
	if (pCollision != NULL)
	{
		// ����������
		if (FAILED(pCollision->Init(tag,type,pos,size)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCollision == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �����蔻��̃|�C���^��Ԃ�
	return pCollision;
}

//-------------------------------------
//- �^�O�̑���𔻒�ݒ菈��
//-------------------------------------
void CColl::UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ݒ肵���^�O�̓����蔻��̗L����ݒ�
	m_data.pos = pos;		// �ʒu
	m_data.size = size;		// �T�C�Y
}

//-------------------------------------
//- �����蔻��̐ڐG����
//-------------------------------------
bool CColl::Hit(CMgrColl::TAG hitTag, CMgrColl::STATE_HIT stateHit)
{
	// �����蔻��̃|�C���^�擾
	CMgrColl *pMgrColl = CManager::GetMgrColl();		

	// �����蔻��̗L���𔻒�
	if (pMgrColl == NULL)
	{
		// �����𔲂���
		return false;
	}

	// �ϐ��錾
	bool bHitTgt = false;	// �ړI�̐ڐG�̗L��

	// �����蔻��Ǘ��̐ڐG����
	bHitTgt = pMgrColl->Hit(m_data.nNldx,hitTag,stateHit);

	return bHitTgt;
}

//-------------------------------------
//- �^�O�̑���𔻒�ݒ菈��
//-------------------------------------
void CColl::SetTagTgt(CMgrColl::TAG hitTag, bool bIsActive)
{
	// �ݒ肵���^�O�̓����蔻��̗L����ݒ�
	m_data.bTagTgt[hitTag] = bIsActive;
}

//-------------------------------------
//- �����蔻��̏��̐ݒ菈��
//-------------------------------------
void CColl::SetData(Data data)
{
	m_data = data;
}

//-------------------------------------
//- �����蔻��̏��̎擾����
//-------------------------------------
CColl::Data CColl::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- �����蔻��̐ڐG���̐ݒ菈��
//-------------------------------------
void CColl::SetHitData(HitData data)
{
	// �ϐ��錾�i���擾�j
	int nHitNum = m_data.nHitNldxMax;	// ���݂̍ő�ڐG��

	// �ڐG�����i�[
	m_data.hitData[nHitNum].nNldx = data.nNldx;	// �����蔻��ԍ�

	// �ő�ڐG�������Z
	m_data.nHitNldxMax++;
}

//-------------------------------------
//- �����蔻��̐ڐG���̃��Z�b�g����
//-------------------------------------
void CColl::ResetHitData(void)
{
	// �ϐ��錾�i���擾�j
	int nHitNum = m_data.nHitNldxMax;	// ���݂̍ő�ڐG��

	for (int nCount = 0; nCount < nHitNum; nCount++)
	{
		// �ڐG�ԍ��̏�����
		m_data.hitData[nHitNum].nNldx = -1;
	}

	// �ڐG�ő吔�̏�����
	m_data.nHitNldxMax = 0;
}

//-------------------------------------
//- �����蔻��̏����ݒ菈��
//-------------------------------------
void CColl::InitSet(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_data.tag = tag;
	m_data.type = type;
	m_data.pos = pos;
	m_data.size = size;
}

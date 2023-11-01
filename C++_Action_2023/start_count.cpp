
//================================================
//=
//=	�X�^�[�g�J�E���g�̏���[start_count.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "start_count.h"

#include "renderer.h"
#include "game.h"

#include "manager_texture.h"

#include "object.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�^�C�}�[�̃R���X�g���N�^
//-------------------------------------
CStartCount::CStartCount()
{
	// �l�̃N���A
	m_pNumber = NULL;

	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	�^�C�}�[�̃f�X�g���N�^
//-------------------------------------
CStartCount::~CStartCount()
{

}

//-------------------------------------
//- �^�C�}�[�̏���������
//-------------------------------------
HRESULT CStartCount::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �^�C�}�[�̐����ݒ�
	if (m_pNumber == NULL)
	{
		// �����̐�������
		m_pNumber = CNumber::Create(CNumber::TEX_DARK_GREEN_001);

		// �����̐��������̗L���𔻒�
		if (m_pNumber == NULL)
		{
			// �u�Ȃ��v��Ԃ�
			return E_FAIL;
		}
	}

	// �����ݒ�
	InitSet(pos, size, color);

	// �S�X�V��~����
	CObject::SetIsUpdateAll(false);
		
	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�}�[�̏I������
//-------------------------------------
void CStartCount::Uninit(void)
{
	if (m_pNumber != NULL)
	{
		// �����̏�����
		m_pNumber->Uninit();
		m_pNumber = NULL;
	}

	// �S�X�V��~����
	CObject::SetIsUpdateAll(true);
}

//-------------------------------------
//- �^�C�}�[�̍X�V����
//-------------------------------------
void CStartCount::Update(void)
{
	if (m_pNumber != NULL)
	{
		// �����̍X�V����
		m_pNumber->Update();
	}

	if (m_data.nTimerCount < m_data.nTime)
	{
		// �J�E���g��i�߂�
		m_data.nTimerCount++;

		NumberTex();

		if (m_data.nTimerCount >= m_data.nTime)
		{
			// �I������
			Uninit();
		}
	}
}

//-------------------------------------
//- �^�C�}�[�̕`�揈��
//-------------------------------------
void CStartCount::Draw(void)
{

}

//-------------------------------------
//- �^�C�}�[�̐�������
//-------------------------------------
CStartCount * CStartCount::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �^�C�}�[�̐���
	CStartCount *pTimer = DBG_NEW CStartCount;

	// �����̐����̗L���𔻒�
	if (pTimer != NULL)
	{
		// ����������
		if (FAILED(pTimer->Init(pos, size, color)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pTimer == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �p�[�e�B�N���̃|�C���^��Ԃ�
	return pTimer;
}

//-------------------------------------
//- �^�C�}�[�̈ʒu���̐ݒ�
//-------------------------------------
void CStartCount::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �J�E���g�l
	m_data.nTime = STOP_COUNT;

	// �����̗L���𔻒�
	if (m_pNumber != NULL)
	{
		// ���_�l���
		CObject2d::VtxData vtxData = m_pNumber->GetVtxData();

		// �����̈ʒu������
		vtxData.pos = pos;
		vtxData.size = size;
		vtxData.color = color;

		// ���X�V�i���_�l���j
		m_pNumber->SetVtxData(vtxData);
	}

	// �����ݒ�
	NumberTex();
}

//-------------------------------------
//-	�^�C�}�[�̌����ƃe�N�X�`���̐ݒ菈��
//-------------------------------------
void CStartCount::NumberTex(void)
{
	// �ϐ��錾
	int aTexU = 0;	// �e���̐������i�[

	// �ϐ��錾�i�l���j
	CNumber::Data data = m_pNumber->GetData();

	int nDig = (m_data.nTime - m_data.nTimerCount) / 60;

	// ������ݒ�
	data.nDigits = nDig + 1;

	// �^�C�}�[�̍X�V����
	m_pNumber->SetData(data);
}

//-------------------------------------
//- �^�C�}�[�̒l�ݒ菈��
//-------------------------------------
void CStartCount::SetData(CStartCount::Data data)
{
	m_data = data;
}

//-------------------------------------
//- �^�C�}�[�̒l�擾����
//-------------------------------------
CStartCount::Data CStartCount::GetData(void)
{
	return m_data;
}


//================================================
//=
//=	�^�C�}�[����[timer.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "timer.h"

#include "renderer.h"
#include "game.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�^�C�}�[�̃R���X�g���N�^
//-------------------------------------
CTimer::CTimer()
{
	// �l�̃N���A
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		m_apNumber[nCount] = NULL;
	}

	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	�^�C�}�[�̃f�X�g���N�^
//-------------------------------------
CTimer::~CTimer()
{

}

//-------------------------------------
//- �^�C�}�[�̏���������
//-------------------------------------
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �^�C�}�[�̐����ݒ�
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] == NULL)
		{
			// �����̐�������
			m_apNumber[nCount] = CNumber::Create(CNumber::TEX_DARK_GREEN_001);

			// �����̐��������̗L���𔻒�
			if (m_apNumber[nCount] == NULL)
			{
				// �u�Ȃ��v��Ԃ�
				return E_FAIL;
			}
		}
	}

	// �����ݒ�
	InitSet(pos, interval, between, size, color);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �^�C�}�[�̏I������
//-------------------------------------
void CTimer::Uninit(void)
{
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			// �����̏�����
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//- �^�C�}�[�̍X�V����
//-------------------------------------
void CTimer::Update(void)
{
	// ���Z����
	Elapsed();

	// �e�N�X�`���̌����Ɛݒ菈��
	NumberTex();
}

//-------------------------------------
//- �^�C�}�[�̕`�揈��
//-------------------------------------
void CTimer::Draw(void)
{

}

//-------------------------------------
//- �^�C�}�[�̐�������
//-------------------------------------
CTimer * CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �^�C�}�[�̐���
	CTimer *pTimer = DBG_NEW CTimer;

	// �����̐����̗L���𔻒�
	if (pTimer != NULL)
	{
		// ����������
		if (FAILED(pTimer->Init(pos,interval,between,size,color)))
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
//- �^�C�}�[�̐����|�C���^����������
//-------------------------------------
void CTimer::NullAllNumber(void)
{
	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nCount] != NULL)
		{
			// �����̃|�C���^����������
			m_apNumber[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	�^�C�}�[�̌����ƃe�N�X�`���̐ݒ菈��
//-------------------------------------
void CTimer::NumberTex(void)
{
	// �ϐ��錾
	int aTexU[DIG_NUM_MAX];	// �e���̐������i�[

	int nMinutes = (m_data.nTime / 60);
	int nSeconds = (m_data.nTime % 60);
	int nMillSeco = (int)((m_data.nTimerCount % 60) * 1.67f);

	// �����Ƃ̐��l����
	aTexU[0] = ((nMinutes % 100) / 10);
	aTexU[1] = ((nMinutes % 10));

	aTexU[2] = ((nSeconds % 100) / 10);
	aTexU[3] = (nSeconds % 10);

	aTexU[4] = ((nMillSeco % 100) / 10);
	//aTexU[5] = (nMillSeco % 10);

	for (int nCount = 0; nCount < DIG_NUM_MAX; nCount++)
	{
		// �ϐ��錾�i�l���j
		CNumber::Data data = m_apNumber[nCount]->GetData();

		// ������ݒ�
		data.nDigits = aTexU[nCount];

		// �^�C�}�[�̍X�V����
		m_apNumber[nCount]->SetData(data);
	}
}

//-------------------------------------
//-	�^�C�}�[�̎��Ԍo�ߏ���
//-------------------------------------
void CTimer::Elapsed(void)
{
	// �J�E���^�[�����Z
	m_data.nTimerCount++;

	// �J�E���^�[�̔���
	if (m_data.nTimerCount % 60 == 0)
	{// 60�t���[���Ɉ��

		// ���Ԃ����Z
		m_data.nTime++;
	}
}

//-------------------------------------
//- �^�C�}�[�̈ʒu���̐ݒ�
//-------------------------------------
void CTimer::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �����
	m_data.pos = pos;
	m_data.interval = interval;
	m_data.between = between;

	// �ϐ��錾
	int nDigMax = 0;	// �����J�E���g
	int nDigCarr = 0;	// �����̌J��グ�J�E���g

	for (int nCount = 0; nCount < DIG_MINU_NUM_MAX; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nDigMax] != NULL)
		{
			// �����̈ʒu���Z�o
			D3DXVECTOR3 numPos = D3DXVECTOR3(
				pos.x + (interval.x * nDigMax),
				pos.y + (interval.y * nDigMax),
				pos.z + (interval.z * nDigMax));

			// ���_�l���
			CObject2d::VtxData vtxData = m_apNumber[nDigMax]->GetVtxData();

			// �����̈ʒu������
			vtxData.pos = numPos;
			vtxData.size = size;
			vtxData.color = color;

			// ���X�V�i���_�l���j
			m_apNumber[nDigMax]->SetVtxData(vtxData);
		}

		// ���J�E���g�����Z
		nDigMax++;
	}

	// �����J��グ�J�E���g�̉��Z
	nDigCarr++;

	for (int nCount = 0; nCount < DIG_SECO_NUM_MAX; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nDigMax] != NULL)
		{
			// �����̈ʒu���Z�o
			D3DXVECTOR3 numPos = D3DXVECTOR3(
				(pos.x + (between.x * nDigCarr)) + (interval.x * nDigMax),
				(pos.y + (between.y * nDigCarr)) + (interval.y * nDigMax),
				(pos.z + (between.z * nDigCarr)) + (interval.z * nDigMax));

			// ���_�l���
			CObject2d::VtxData vtxData = m_apNumber[nDigMax]->GetVtxData();

			// �����̈ʒu������
			vtxData.pos = numPos;
			vtxData.size = size;
			vtxData.color = color;

			// ���X�V�i���_�l���j
			m_apNumber[nDigMax]->SetVtxData(vtxData);
		}

		// ���J�E���g�����Z
		nDigMax++;
	}

	// �����J��グ�J�E���g�̉��Z
	nDigCarr++;

	for (int nCount = 0; nCount < DIG_MILL_NUM_MAX; nCount++)
	{
		// �����̗L���𔻒�
		if (m_apNumber[nDigMax] != NULL)
		{
			// �����̈ʒu���Z�o
			D3DXVECTOR3 numPos = D3DXVECTOR3(
				(pos.x + (between.x * nDigCarr)) + (interval.x * nDigMax),
				(pos.y + (between.y * nDigCarr)) + (interval.y * nDigMax),
				(pos.z + (between.z * nDigCarr)) + (interval.z * nDigMax));

			// ���_�l���
			CObject2d::VtxData vtxData = m_apNumber[nDigMax]->GetVtxData();

			// �����̈ʒu������
			vtxData.pos = numPos;
			vtxData.size = size;
			vtxData.color = color;

			// ���X�V�i���_�l���j
			m_apNumber[nDigMax]->SetVtxData(vtxData);
		}

		// ���J�E���g�����Z
		nDigMax++;
	}
}

//-------------------------------------
//- �^�C�}�[�̒l�ݒ菈��
//-------------------------------------
void CTimer::SetData(CTimer::Data data)
{
	m_data = data;
}

//-------------------------------------
//- �^�C�}�[�̒l�擾����
//-------------------------------------
CTimer::Data CTimer::GetData(void)
{
	return m_data;
}


//================================================
//=
//=	�����܂̏���[kazedama.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "kazedama.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

#include "player.h"

#include "coll.h"

#include "enemy_have.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//= �R���X�g��`
//=======================================

// �����܃e�N�X�`���̃R���X�g��`
const char *pTextureKazedama[] =
{
	NULL,
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CKazedama::m_nTextureNldx[TEX_MAX] = {};			// �e�N�X�`��

//-------------------------------------
//-	�����܂̃R���X�g���N�^
//-------------------------------------
CKazedama::CKazedama(int nPriority) : CObjectBillboard(nPriority)
{
	ZeroMemory(&m_data, sizeof(m_data));
	m_pColl = NULL;
	m_pEnemyHave = NULL;
}

//-------------------------------------
//-	�����܂̃f�X�g���N�^
//-------------------------------------
CKazedama::~CKazedama()
{

}

//-------------------------------------
//- �����܂̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CKazedama::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// �e�N�X�`���Ǘ��̗L���𔻒�
	if (pManagerTexture == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureKazedama[nCount]);

		// �e�N�X�`���̓ǂݍ��ݐ����̗L�����m�F
		if (m_nTextureNldx[nCount] == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �����܂̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CKazedama::Unload(void)
{

}

//-------------------------------------
//- �����܂̏���������
//-------------------------------------
HRESULT CKazedama::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// �����ݒ菈��
	InitSet(pos,size,color,move,typeRot);

	// �r���{�[�h�I�u�W�F�N�g�̏�����
	CObjectBillboard::Init();

	if (m_pColl == NULL)
	{
		// �����蔻��ݒ�
		m_pColl = CColl::Create(
			CMgrColl::TAG_KAZEDAMA,
			CMgrColl::TYPE_RECTANGLE,
			GetVtxData().pos,
			GetVtxData().size);

		// ����^�O�̐ݒ菈��
		m_pColl->SetTagTgt(CMgrColl::TAG_ENEMY, true);
	}
	else
	{
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �����܂̏I������
//-------------------------------------
void CKazedama::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// �����蔻��̏I������
		m_pColl->Uninit();

		// �����蔻��̊J������
		delete m_pColl;
		m_pColl = NULL;
	}

	if (m_pEnemyHave != NULL)
	{
		// �ێ��G�̏I������
		m_pEnemyHave->Uninit();
		m_pEnemyHave = NULL;
	}

	// �r���{�[�h�I�u�W�F�N�g�̏I��
	CObjectBillboard::Uninit();
}

//-------------------------------------
//- �����܂̍X�V����
//-------------------------------------
void CKazedama::Update(void)
{
	// �����蔻��̏��X�V����
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	switch (m_data.state)
	{
	case STATE_ACTIVE:

		// �s������
		Active();

		break;

	case STATE_RETURN:

		// �A�ҏ���
		Return();

		break;
	}

	// �ړ�����
	UpdateMove();

	// �r���{�[�h�I�u�W�F�N�g�̍X�V����
	CObjectBillboard::Update();
}

//-------------------------------------
//- �����܂̕`�揈��
//-------------------------------------
void CKazedama::Draw(void)
{
	// �f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pRenderer == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// Z�e�X�g�̐ݒ�
	pRenderer->SetZTest(true);

	// �A���t�@�e�X�g�̐ݒ�
	pRenderer->SetAlphaTest(true);

	// �����܂̕`�揈��
	CObjectBillboard::Draw();

	// Z�e�X�g�̉���
	pRenderer->SetZTest(false);

	// �A���t�@�e�X�g�̉���
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- �����܂̐�������
//-------------------------------------
CKazedama * CKazedama::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot)
{
	// �����܂̐���
	CKazedama *pCKazedama = DBG_NEW CKazedama(5);

	// �����̐����̗L���𔻒�
	if (pCKazedama != NULL)
	{
		// ����������
		if (FAILED(pCKazedama->Init(tex,pos,size,color,move,typeRot)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCKazedama == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �����܂̃|�C���^��Ԃ�
	return pCKazedama;
}

//-------------------------------------
//- �����܂̐e�̏��X�V����
//-------------------------------------
void CKazedama::SetParent(D3DXVECTOR3 pos)
{
	// �e�̈ʒu���X�V
	m_data.posParent = pos;
}

//-------------------------------------
//- �����܂̎��s���̏��Ŏ��̏���
//-------------------------------------
void CKazedama::LostFail(void)
{
	// �I������
	Uninit();
}

//-------------------------------------
//- �����܂̐������̏��Ŏ��̏���
//-------------------------------------
void CKazedama::LostSucce(void)
{
	// �I������
	Uninit();
}

//-------------------------------------
//- �����܂̐ݒ菈��
//-------------------------------------
void CKazedama::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, CKazedama::TYPE_ROT typeRot)
{
	// �ϐ���錾�i���擾�j
	CObjectBillboard::VtxData vtxData = GetVtxData();

	vtxData.pos = pos;			// �ʒu
	vtxData.size = size;		// �傫��
	vtxData.color = color;		// �F
	m_data.move = move;			// �ړ���
	m_data.typeRot = typeRot;	// �����̎��

	// ���X�V
	SetVtxData(vtxData);
}

//-------------------------------------
//- �����܂̈ړ�����
//-------------------------------------
void CKazedama::UpdateMove(void)
{
	// �ϐ���錾�i���擾�j
	CObjectBillboard::VtxData vtxData = GetVtxData();
	
	// ���Z����
	vtxData.pos += m_data.move;			// �ʒu
	m_data.moveAccum += m_data.move;	// �ړ��̒~�ϒl

	// ���X�V
	SetVtxData(vtxData);
}

//-------------------------------------
//- �����܂̊������̏���
//-------------------------------------
void CKazedama::Active(void)
{
	// �G�Ƃ̓����蔻��
	if (m_pColl->Hit(CMgrColl::TAG_ENEMY,CMgrColl::STATE_HIT_DEAD) == true)
	{
		// �l�����̏���
		Obtain();
	}
	else
	{
		// �ϐ��錾
		bool bIsSwitch = false;	// ��������̏����̗L��

		// �����̎��
		switch (m_data.typeRot)
		{
		case TYPE_ROT_LEFT:

			// �ړ��~�ϒl�̔���i�ړI�̈ړ��~�ρj
			if (m_data.moveAccum.x <= -200.0f)
			{
				bIsSwitch = true;
			}

			break;

		case TYPE_ROT_RIGHT:

			// �ړ��~�ϒl�̔���i�ړI�̈ړ��~�ρj
			if (m_data.moveAccum.x >= 200.0f)
			{
				bIsSwitch = true;
			}

			break;
		}

		// �����܂̒~�ϒl�𔻒�
		if (bIsSwitch == true)
		{
			// �A�ҏ�ԂɕύX
			m_data.state = STATE_RETURN;
		}
	}

}

//-------------------------------------
//- �����܂̋A�Ҏ��̏���
//-------------------------------------
void CKazedama::Return(void)
{
	// �ϐ���錾�i���擾�j
	CObjectBillboard::VtxData vtxData = GetVtxData();

	// �ړ��ʂ̊p�x���Z�o
	float fRotMove = atan2f(
		m_data.move.x, 
		m_data.move.y);

	// �ړI�̊p�x���Z�o
	float fRotDest = atan2f(
		vtxData.pos.x - m_data.posParent.x,
		vtxData.pos.y - m_data.posParent.y);
	
	// �ړ������̍���
	float fRotDiff = fRotDest - fRotMove;

	// �p�x�̏C��
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= (D3DX_PI * 2);
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	// �ړ������i�p�x�j�̕␳
	fRotMove += fRotDiff * 1.0f;

	// �p�x�̏C��
	if (fRotMove > D3DX_PI)
	{
		fRotMove -= (D3DX_PI * 2);
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotMove += (D3DX_PI * 2);
	}

	// �ړ��ʂ��Z�o
	m_data.move.x = sinf(fRotMove) * -50.0f;
	m_data.move.y = cosf(fRotMove) * -50.0f;

	// �ϐ��錾
	bool bIsSwitch = false;	// ��������̏����̗L��

	// �����̎��
	switch (m_data.typeRot)
	{
	case TYPE_ROT_LEFT:

		// �ʒu�̔���i�e�̈ʒu�j
		if (vtxData.pos.x >= m_data.posParent.x)
		{
			bIsSwitch = true;
		}

		break;

	case TYPE_ROT_RIGHT:

		// �ʒu�̔���i�e�̈ʒu�j
		if (vtxData.pos.x <= m_data.posParent.x)
		{
			bIsSwitch = true;
		}

		break;
	}

	if(bIsSwitch == true)
	{
		if (m_pEnemyHave != NULL)
		{
			// ������ԂɕύX
			m_data.state = STATE_SUCCE;
		}
		else if(m_pEnemyHave == NULL)
		{
			// ������ԂɕύX
			m_data.state = STATE_FAIL;
		}

	}
}

//-------------------------------------
//- �����܂̏��擾����
//-------------------------------------
CKazedama::Data CKazedama::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- �����܂̊l�����̏���
//-------------------------------------
void CKazedama::Obtain(void)
{
	// �A�ҏ�ԂɕύX
	m_data.state = STATE_RETURN;

	// �ێ��G�𐶐�
	m_pEnemyHave = CEnemyHave::Create(
		CEnemyHave::MODEL_ALIEN_000,
		CEnemyHave::STATE_OBTAIN,
		GetVtxData().pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(50.0f, 50.0f, 50.0f));
}
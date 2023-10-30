
//================================================
//=
//=	�}�b�v�G�f�B�^�̏���[edit_map.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "edit_map.h"

#include "Input.h"

#include "manager.h"
#include "camera.h"

#include "object.h"

#include "obj_block.h"
#include "goal.h"
#include "enemy.h"
#include "gimmick_jewel.h"
#include "obj_teach.h"

#include "file_map.h"

//=======================================
//=	�}�N����`
//=======================================

#define SIZE_TILE_CRITERIA_X	(150.0f)		// ��}�X�̊�iX���j
#define SIZE_TILE_CRITERIA_Y	(150.0f)		// ��}�X�̊�iY���j

//=======================================
//= �R���X�g��`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CEditMap::CEditMap()
{
	ZeroMemory(&m_editData, sizeof(m_editData));
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CEditMap::~CEditMap()
{

}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏���������
//-------------------------------------
HRESULT CEditMap::Init(void)
{
	// �G�f�B�b�g�I�u�W�F�N�g�𐶐�
	SetEditObj(m_editData.type);

	// �J�����̑����ύX
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != NULL)
	{
		pCamera->SetMode(CCamera::MODE_EDIT);
	}

	return S_OK;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏I������
//-------------------------------------
void CEditMap::Uninit(void)
{
	// �J�����̑����ύX
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != NULL)
	{
		pCamera->SetMode(CCamera::MODE_FOLLOWING);
	}

	if (m_editData.pObjX != NULL)
	{
		// �I������
		m_editData.pObjX->Uninit();
		m_editData.pObjX = NULL;
	}

	if (m_editData.pObjBill != NULL)
	{
		// �I������
		m_editData.pObjBill->Uninit();
		m_editData.pObjBill = NULL;
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̍X�V����
//-------------------------------------
void CEditMap::Update(void)
{
	// �G�f�B�b�g�I�u�W�F�N�g�̈ړ�����
	InputObjMove();

	// ��ޕύX���͏���
	InputChangeType();

	// �I�u�W�F�N�g�ݒu���͏���
	InputSetObj();

	// �}�b�v�I�u�W�F�N�g�Z�[�u����
	InputSave();
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̕`�揈��
//-------------------------------------
void CEditMap::Draw(void)
{
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̐�������
//-------------------------------------
CEditMap * CEditMap::Create(void)
{
	// �}�b�v�G�f�B�^�̐���
	CEditMap *pEditMap = DBG_NEW CEditMap;

	// �����̐����̗L���𔻒�
	if (pEditMap != NULL)
	{
		// ����������
		if (FAILED(pEditMap->Init()))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pEditMap == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�G�̃|�C���^��Ԃ�
	return pEditMap;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃I�u�W�F�N�g�ړ����͏���
//-------------------------------------
void CEditMap::InputObjMove(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (pInputKeyboard->GetPress(DIK_LSHIFT) == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_W) == true)
		{
			// ��̈ړ�����
			SetObjMove(D3DXVECTOR3(0.0f, SIZE_TILE_CRITERIA_Y,0.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_S) == true)
		{
			// ���̈ړ�����
			SetObjMove(D3DXVECTOR3(0.0f, -SIZE_TILE_CRITERIA_Y, 0.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_A) == true)
		{
			// ���̈ړ�����
			SetObjMove(D3DXVECTOR3(-SIZE_TILE_CRITERIA_X, 0.0f, 0.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_D) == true)
		{
			// �E�̈ړ�����
			SetObjMove(D3DXVECTOR3(SIZE_TILE_CRITERIA_X, 0.0f, 0.0f));
		}
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃I�u�W�F�N�g�ݒu���͏���
//-------------------------------------
void CEditMap::InputSetObj(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

	 // �X�V�����𔲂���
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		// �I�u�W�F�N�g�ݒu����
		SetObj();
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̎�މ��Z�ݒ菈��
//-------------------------------------
void CEditMap::InputChangeType(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_W) == true)
		{
			// ��ތ��Z�ݒ菈��
			SetSubType();
		}
		else if (pInputKeyboard->GetTrigger(DIK_S) == true)
		{
			// ��މ��Z�ݒ菈��
			SetAddType();
		}
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̎�މ��Z�ݒ菈��
//-------------------------------------
void CEditMap::InputSave(void)
{
	// �L�[�{�[�h�̃|�C���^��錾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// �L�[�{�[�h�̏��擾�̐����𔻒�
	if (pInputKeyboard == NULL)
	{// ���s��

		// �X�V�����𔲂���
		return;
	}

	// �}�b�v�t�@�C���̏��擾
	CFileMap *pFileMap = CManager::GetInstance()->GetFileMap();

	if (pFileMap == NULL)
	{
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		// �}�b�v�t�@�C���̃Z�[�u
		pFileMap->Save();
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃G�f�B�b�g�I�u�W�F�N�g�ݒ菈��
//-------------------------------------
void CEditMap::SetEditObj(TYPE type)
{
	if (m_editData.pObjX != NULL)
	{
		// �I������
		m_editData.pObjX->Uninit();
		m_editData.pObjX = NULL;
	}

	if (m_editData.pObjBill != NULL)
	{
		// �I������
		m_editData.pObjBill->Uninit();
		m_editData.pObjBill = NULL;
	}

	// �G�f�B�b�g�̎�ނ���
	m_editData.type = type;

	switch (type)
	{
	case TYPE_BLOCK:

		// �u���b�N�̐���
		m_editData.pObjX = CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_GOAL:

		// �S�[���̐���
		m_editData.pObjX = CGoal::Create(
			CGoal::MODEL_GOAL_000,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_PLAYER:

		break;

	case TYPE_ENEMY:

		// �G�̐���
		m_editData.pObjX = CEnemy::Create(
			CEnemy::MODEL_ALIEN_000,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_GIMMICK_SPEED:

		// ���x��΃M�~�b�N�̐���
		m_editData.pObjX = CGimmickJewel::Create(
			CGimmickJewel::MODEL_JEWEL_000,
			CGimmickJewel::TYPE_EFFECT_SPEED_UP,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_TEACH_MOVE:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_MOVE,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_JUMP:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_JUMP,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_KAZEDAMA:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_KAZEDAMA,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_SHOT:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_SHOT,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_DOUBLE_JUMP:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_DOUBLE_JUMP,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	}

	if (m_editData.pObjX != NULL)
	{
		// �I������
		m_editData.pObjX->IsUpdateStop(false);
	}

	if (m_editData.pObjBill != NULL)
	{
		// �I������
		m_editData.pObjBill->IsUpdateStop(false);
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̎�މ��Z�ݒ菈��
//-------------------------------------
void CEditMap::SetAddType(void)
{
	// ��ނ����Z
	m_editData.type = (TYPE)(m_editData.type + 1);

	if (m_editData.type == TYPE_MAX)
	{
		// ��ނ�������
		m_editData.type = (TYPE)(0);
	}

	// �G�f�B�b�g�I�u�W�F�N�g�̎�ސݒ菈��
	SetEditObj(m_editData.type);
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̎�ތ��Z�ݒ菈��
//-------------------------------------
void CEditMap::SetSubType(void)
{
	// ��ނ����Z
	m_editData.type = (TYPE)(m_editData.type - 1);

	if (m_editData.type <= TYPE(0))
	{
		// ��ނ�������
		m_editData.type = (TYPE)(TYPE_MAX - 1);
	}

	// �G�f�B�b�g�I�u�W�F�N�g�̎�ސݒ菈��
	SetEditObj(m_editData.type);
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃I�u�W�F�N�g�ړ�����
//-------------------------------------
void CEditMap::SetObjMove(D3DXVECTOR3 move)
{
	// �G�f�B�b�g�̈ʒu�Ɉړ��ʂ����Z
	m_editData.pos += move;

	if (m_editData.pObjX != NULL)
	{
		// ���𒸓_�l�擾
		CObjectX::VtxData vtxData = m_editData.pObjX->GetVtxData();

		// �ʒu�Ɉړ��ʂ����Z
		vtxData.pos += move;

		// ���X�V
		m_editData.pObjX->SetVtxData(vtxData);
	}

	if (m_editData.pObjBill != NULL)
	{
		// ���𒸓_�l�擾
		CObjectBillboard::VtxData vtxData = m_editData.pObjBill->GetVtxData();

		// �ʒu�Ɉړ��ʂ����Z
		vtxData.pos += move;

		// ���X�V
		m_editData.pObjBill->SetVtxData(vtxData);
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃I�u�W�F�N�g�ݒ菈��
//-------------------------------------
void CEditMap::SetObj(void)
{
	// �}�b�v�t�@�C���̏��擾
	CFileMap *pFileMap = CManager::GetInstance()->GetFileMap();

	if (pFileMap == NULL)
	{
		return;
	}

	// �G�f�B�b�g�̃I�u�W�F�N�g�ݒ菈��
	if (pFileMap->SetObj(m_editData) == true)
	{
		m_editData.pObjX = NULL;
		m_editData.pObjBill = NULL;

		SetEditObj(m_editData.type);
	}
}
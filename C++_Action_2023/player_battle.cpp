
//-===============================================
//-
//-	�퓬�v���C���[����[player_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "player_battle.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CPlayerBattle::CPlayerBattle()
{
	// �l���N���A
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeNew = m_stateType;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CPlayerBattle::~CPlayerBattle()
{

}

//-------------------------------------
//- �퓬�v���C���[�̏���������
//-------------------------------------
HRESULT CPlayerBattle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// �퓬�v���C���[�̐ݒ菈��
	Set(pos,rot);

	// �v���C���[�̏���������
	CPlayer::Init(modelType, motionType,STATE_TYPE_MAX);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �퓬�v���C���[�̏I������
//-------------------------------------
void CPlayerBattle::Uninit(void)
{
	// �v���C���[�̏I������
	CPlayer::Uninit();
}

//-------------------------------------
//- �퓬�v���C���[�̍X�V����
//-------------------------------------
void CPlayerBattle::Update(void)
{
	// �v���C���[�̍X�V����
	CPlayer::Update();

	// ���[�V�����̍X�V����
	UpdateMotion();
}

//-------------------------------------
//- �퓬�v���C���[�̕`�揈��
//-------------------------------------
void CPlayerBattle::Draw(void)
{
	// �v���C���[�̕`�揈��
	CPlayer::Draw();
}

//-------------------------------------
//- �퓬�v���C���[�̐�������
//-------------------------------------
CPlayerBattle *CPlayerBattle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// �퓬�v���C���[�̃|�C���^��錾
	CPlayerBattle *pCPlayerBattle = new CPlayerBattle;

	// �����̐����̗L���𔻒�
	if (pCPlayerBattle != NULL)
	{
		// ����������
		if (FAILED(pCPlayerBattle->Init(pos, rot,modelType,motionType,STATE_TYPE_MAX)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCPlayerBattle == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �퓬�v���C���[�̃|�C���^��Ԃ�
	return pCPlayerBattle;
}

//-------------------------------------
//- �퓬�v���C���[�̐ݒ菈��
//-------------------------------------
void CPlayerBattle::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �ϐ��錾�i�v���C���[�̒l�̏��擾�j
	CPlayer::Data data = CPlayer::GetData();

	// �l�̑��
	data.pos = pos;	// �ʒu
	data.rot = rot;	// ����

	// ���X�V�i�v���C���[�̒l�j
	CPlayer::SetData(data);
}

//-------------------------------------
//- �퓬�v���C���[�̃��[�V�����X�V����
//-------------------------------------
void CPlayerBattle::UpdateMotion(void)
{
	// �ϐ��錾�i���擾�j
	CMotion *pMotion = GetMotion();		// ���[�V����
	D3DXVECTOR3 move = GetData().move;	// �ړ���
	
	// ��Ԃ𔻒�
	if (m_stateTypeNew == STATE_TYPE_NEUTRAL ||
		m_stateTypeNew == STATE_TYPE_MOVE)
	{
		// �ړ��ʂŏ�Ԃ�ύX
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			// �ړ���ԂɕύX
			m_stateTypeNew = STATE_TYPE_MOVE;
		}
		else
		{
			// �ҋ@��Ԃ̕ύX
			m_stateTypeNew = STATE_TYPE_NEUTRAL;
		}
	}

	// ���[�V�����̏I���󋵂𔻒�
	if (pMotion->IsFinsih() == true)
	{
		// ���[�V�����̍X�V
		pMotion->Update();
	}
	else
	{
		// �ҋ@��Ԃ�ݒ�
		m_stateTypeNew = STATE_TYPE_NEUTRAL;
	}

	// ���[�V�����̐ݒ菈��
	if (m_stateType != m_stateTypeNew)
	{
		// ��Ԃ̍X�V
		m_stateType = m_stateTypeNew;

		// ��Ԃ̔���
		if (m_stateType == STATE_TYPE_NEUTRAL)
		{
			// �ҋ@���[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_NEUTRAL);
		}
		else if (m_stateType == STATE_TYPE_MOVE)
		{
			// �ړ����[�V�����̐ݒ�
			pMotion->Set(STATE_TYPE_MOVE);
		}
	}
}
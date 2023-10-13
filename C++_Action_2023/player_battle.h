
//-===============================================
//-
//-	�퓬�v���C���[�����̃w�b�_�[[player_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PLAYER_BATTLE_H_		// ���̃}�N������`����Ȃ�������
#define _PLAYER_BATTLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "player.h"

#include "model.h"
#include "motion.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�O���錾
//=======================================

//-======================================
//-	�N���X��`
//-======================================

class CPlayerBattle : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,		// �ҋ@
		STATE_TYPE_MOVE,			// �ړ�
		STATE_TYPE_HAVING,			// �������
		STATE_TYPE_MAX			
	}STATE_TYPE;

	CPlayerBattle();
	~CPlayerBattle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerBattle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void UpdateMotion(void);

	STATE_TYPE m_stateType;			// ��Ԃ̎��
	STATE_TYPE m_stateTypeNew;		// �ŐV�̏�Ԃ̎��
};

#endif	// ��d�C���N���[�h�h�~�̏I��

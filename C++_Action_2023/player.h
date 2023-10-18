
//-===============================================
//-
//-	�v���C���[�����̃w�b�_�[[player.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PLAYER_H_		// ���̃}�N������`����Ȃ�������
#define _PLAYER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "model.h"
#include "motion.h"

//=======================================
//=	�}�N����`
//=======================================

#define INSTANCE_MAX	(8)		// ���g�̃|�C���^�̍ő吔

//-======================================
//-	�O���錾
//-======================================

class CObjectX;
class CObject3d;
class CColl;

class CKazedama;
class CEnemyHave;

class CColl;

//-======================================
//-	�N���X��`
//-======================================

class CPlayer : public CObject
{

public:

	// ���
	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,		// �ҋ@
		STATE_TYPE_MOVE,			// �ړ�
		STATE_TYPE_HAVING,			// �������
		STATE_TYPE_MAX
	}STATE_TYPE;

	// �ǉ��l�̏��
	typedef struct
	{
		float speedRate;	// ���x�ǉ��̔{��
		int sppedPlusTime;	// ���x�ǉ��̎���

	}DataPlus;

	// ���l
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �O��̈ʒu

		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotDest;	// �ړI�̌���

		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 moveHold;	// �ێ������ړ���

		D3DXVECTOR3 size;		// �傫��

		DataPlus plus;			// �ǉ��l
	}Data;

	CPlayer();
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	CMotion *GetMotion(void);

	CModel *GetModel(int nNumParts);

	void SetData(Data data);
	Data GetData(void);

	void SetPlus(float fRate, int nTime);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void UpdatePos(void);
	void UpdateRot(void);
	void UpdatePlusData(void);
	void UpdateMotion(void);

	void UpdateKazedama(void);
	void UpdateEnemyHave(void);

	void InputMove(void);

	void InputJump(void);
	void InputNormalJump(void);
	void InputDoubleJump(void);

	void InputAction(void);
	void InputKazedama(void);
	void InputShot(void);

	void DebugPlayer(void);

	Data m_data;								// �l���i�[
	bool m_bJump;								// �W�����v��Ԃ̗L��
	bool m_bHave;								// ������Ԃ̗L��

	CColl *m_pColl;								// �����蔻����

	CKazedama *m_pKazedama;						// �����܂̃|�C���^
	CEnemyHave *m_pEnemyHave;					// �ێ��G�̃|�C���^

	STATE_TYPE m_stateType;						// ��Ԃ̎��
	STATE_TYPE m_stateTypeNew;					// �ŐV�̏�Ԃ̎��

	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X

	CModel *m_apModel[MODEL_PARTS_MAX];			// ���f���i�p�[�c�j�̃|�C���^
	int m_nNumModel;							// ���f���i�p�[�c�j�̑���

	CMotion *m_pMotion;							// ���[�V�����̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��

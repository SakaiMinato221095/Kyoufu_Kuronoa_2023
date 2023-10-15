
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

//-======================================
//-	�O���錾
//-======================================

class CObjectX;
class CObject3d;
class CColl;

//-======================================
//-	�N���X��`
//-======================================

class CPlayer : public CObject
{

public:

	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �O��̈ʒu

		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotDest;	// �ړI�̌���

		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 moveHold;	// �ێ������ړ���

		D3DXVECTOR3 size;		// �傫��
	}Data;

	CPlayer();
	~CPlayer();

	HRESULT Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Hit(int nDamage);

	void DebugPlayer(void);

	CMotion *GetMotion(void);

	CModel *GetModel(int nNumParts);

	void SetData(Data data);
	Data GetData(void);

	void SetHave(bool bHave);

private:

	void UpdatePos(void);
	void UpdateRot(void);

	void InputMove(void);

	void InputJump(void);
	void InputNormalJump(void);
	void InputDoubleJump(void);

	void InputAction(void);
	void InputKazedama(void);
	void InputShot(void);

	Data m_data;								// �l���i�[
	bool m_bJump;								// �W�����v��Ԃ̗L��
	bool m_bHave;								// ������Ԃ̗L��

	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X

	CColl *m_pColl;								// �����蔻��̏��

	CModel *m_apModel[MODEL_PARTS_MAX];			// ���f���i�p�[�c�j�̃|�C���^
	int m_nNumModel;							// ���f���i�p�[�c�j�̑���

	CMotion *m_pMotion;							// ���[�V�����̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��


//-===============================================
//-
//-	�ێ��G�̏����̃w�b�_�[[enemy_have.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_HAVE_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_HAVE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CEnemyHave : public CObjectX
{

public:

	typedef enum
	{
		MODEL_ALIEN_000 = 0,	// �G�C���A��_000
		MODEL_MAX
	}MODEL;

	// ���
	typedef enum
	{
		STATE_OBTAIN = 0,	// �l�����
		STATE_WAIT,			// �ҋ@���
		STATE_SHOT,			// ��������
		STATE_MAX
	}STATE;

	// �����̎��
	typedef enum
	{
		TYPE_ROT_LEFT = 0,	// ��
		TYPE_ROT_RIGHT,		// �E
		ROT_MAX
	}TYPE_ROT;

	// ���l
	typedef struct
	{
		D3DXVECTOR3 posParent;	// �e�̈ʒu
		STATE state;			// ���

		D3DXVECTOR3 move;		// �ړ���
		int nLife;				// �̗�
		int nLifeCut;			// �̗̓J�E���g
		TYPE_ROT typeRot;		// �����̎��
	}Data;

	CEnemyHave();
	~CEnemyHave();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	int GetModel(void);
	void SetModel(int nModelNldx);

	void UpdateObtain(void);
	void UpdateWait(void);
	void UpdateShot(void);

	void SetShot(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, TYPE_ROT typeRot);

	static CEnemyHave * Create(MODEL model);

	static CEnemyHave *GetInstance(void);

private:

	static int m_nModelNldx[MODEL_MAX];		// ���f���̔ԍ�
	static CEnemyHave *m_pInstance;			// ���g�̃|�C���^

	MODEL m_model;							// ���g�̃��f��

	Data m_data;							// ���l

	int m_nCollNldx;						// �����蔻��̔ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��
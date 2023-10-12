
//-===============================================
//-
//-	���[�V���������̃w�b�_�[[motion.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MOTION_H_		// ���̃}�N������`����Ȃ�������
#define _MOTION_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "model.h"

//-======================================
//-	�}�N����`
//-======================================

#define KEY_INFO_NUM_MAX	(32)	// �L�[�̑����̍ő吔
#define MOTION_TYPE_NUM_MAX	(64)	// ���[�V������ނ̑����̍ő吔

//-======================================
//-	�\���̒�`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CMotion
{

public:
	
	// ���f���̎��
	typedef enum
	{
		MOTION_TYPE_PLAYER = 0,	// �v���C���[
		MOTION_TYPE_MAX
	}MOTION_TYPE;

	// �L�[�v�f�̍\����
	typedef struct
	{
		float fPosX;	// X���̈ʒu
		float fPosY;	// Y���̈ʒu
		float fPosZ;	// Z���̈ʒu

		float fRotX;	// X���̌���
		float fRotY;	// Y���̌���
		float fRotZ;	// Z���̌���
	}Key;

	// �L�[���̍\����
	typedef struct
	{
		int nFrame;						// �Đ��t���[��
		Key aKey[MODEL_PARTS_MAX];		// �e���f���̃L�[�v�f
	}KeyInfo;
	
	// ���[�V�������̍\����
	typedef struct
	{
		bool bLoop;							// ���[�v�̗L��
		int nNumKey;						// �L�[�̑���
		KeyInfo aKeyInfo[KEY_INFO_NUM_MAX];	// �L�[���
	}Info;

	CMotion();
	~CMotion();

	HRESULT Init(int nNumModel, int nNumState);
	void Uninit(void);

	static CMotion * Create(int nNumModel,int nNumState);

	void Set(int nType);
	void BlendSet(void);
	void Update(void);

	int GetType(void);
	bool IsFinsih(void);
	int GetKey(void);

	void SetInfo(Info info);

	void SetModel(CModel **ppModel,int nNumModel);

	void SetFile(MOTION_TYPE MotionType);

	bool GetBlend(void);
	bool GetChangeBlend(void);

private:

	void UpdateNormal(void);
	void UpdateBlend(void);
	void UpdateChangeBlend(void);

	Info m_aInfo[MOTION_TYPE_NUM_MAX];	// �L�[���

	D3DXVECTOR3 m_motionPos[MODEL_PARTS_MAX];		// ���[�V�����̈ʒu
	D3DXVECTOR3 m_motionPosOld[MODEL_PARTS_MAX];	// ���[�V�����̑O��̈ʒu
	D3DXVECTOR3 m_motionRot[MODEL_PARTS_MAX];		// ���[�V�����̌���
	D3DXVECTOR3 m_motionRotOld[MODEL_PARTS_MAX];	// ���[�V�����̑O��̌���

	int m_nNumState;		// ���[�V�����̎�ނ̐�
	int m_nNumAll;			// 

	bool m_bMotionUse;		// ���݂̃��[�V�����̗L��

	int m_nType;			// ���[�V�����̎��
	bool m_bLoop;			// ���݂̃��[�v�̏�
	int m_nNumKey;			// �L�[�̐�
	int m_nKey;				// ���݂̃L�[
	int m_nCounter;			// ���݂̃J�E���^�[
	bool m_bFinish;			// �I���̗L��

	bool m_bBlend;			// ���[�V�����u�����h�̗L��
	bool m_bChangeBlend;	// �؂�ւ����̃��[�V�����u�����h�̗L��

	CModel ** m_ppModel;	// ���f���̃|�C���^
	int m_nNumModel;		// ���f���̑���
};

#endif	// ��d�C���N���[�h�h�~�̏I��


//-===============================================
//-
//-	�����蔻��̏����̃w�b�_�[[coll.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _COLL_H_		// ���̃}�N������`����Ȃ�������
#define _COLL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

#include "mgr_coll.h"

//-======================================
//-	�}�N����`
//-======================================

#define COLLSION_NUM_MAX		(1024)	// �����蔻��̍ő吔

//-======================================
//-	�N���X��`
//-======================================

// �ڐG�̃N���X
class CColl
{

public:

	// ��
	typedef enum
	{
		TYPE_SXIS_X = 0,	// X��
		TYPE_SXIS_Y,		// Y��
		TYPE_SXIS_Z,		// Z��
		TYPE_SXIS_MAX,
	}TYPE_SXIS;

	// �ڐG����Ƃ̏��
	typedef struct
	{
		int nNldx;						// �ԍ�
	}HitData;

	// �����蔻����
	typedef struct
	{
		CMgrColl::TAG tag;									// �^�O
		bool abTagTgt[CMgrColl::TAG_MAX];					// �ڐG�ݒ�̑���̃^�O
		CMgrColl::TYPE aType[CMgrColl::TAG_MAX];			// �ڐG�ݒ�̑���̔�����
		CMgrColl::STATE_HIT stateHit;						// �ڐG�̎��
		bool abHitSxis[TYPE_SXIS_MAX];						// ���̓����蔻��
		int nNldx;											// �ԍ�

		D3DXVECTOR3 pos;							// �ʒu
		D3DXVECTOR3 posOld;							// �O��̈ʒu
		D3DXVECTOR3 size;							// �傫��

		HitData hitData[COLLSION_NUM_MAX];			// �ڐG����̓����蔻����
		int nHitNldxMax;							// �ڐG����̔ԍ��̍ő吔
	}Data;

	CColl();
	~CColl();

	HRESULT Init(CMgrColl::TAG tag, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CColl *Create(CMgrColl::TAG tag, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size);

	bool Hit(CMgrColl::TAG hitTag, CMgrColl::STATE_HIT stateHit);

	void SetTagTgt(CMgrColl::TAG hitTag, CMgrColl::TYPE type, bool bIsActive);

	void SetData(Data data);
	Data GetData(void);

	void SetHitData(HitData data);
	void ResetHitData(void);

private:

	void InitSet(CMgrColl::TAG tag, D3DXVECTOR3 pos,  D3DXVECTOR3 size);

	Data m_data;
};

#endif	// ��d�C���N���[�h�h�~�̏I��

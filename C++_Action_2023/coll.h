
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

	// �ڐG����Ƃ̏��
	typedef struct
	{
		int nNldx;				// �ԍ�
	}HitData;

	// �����蔻����
	typedef struct
	{
		CMgrColl::TAG tag;					// �^�O
		bool bTagTgt[CMgrColl::TAG_MAX];	// �ڐG�ݒ�̑���̃^�O
		CMgrColl::TYPE type;				// ���
		CMgrColl::STATE_HIT stateHit;		// �ڐG�̎��
		int nNldx;							// �ԍ�

		D3DXVECTOR3 pos;					// �ʒu
		D3DXVECTOR3 size;					// �傫��

		HitData hitData[COLLSION_NUM_MAX];	// �ڐG����̓����蔻����
		int nHitNldxMax;					// �ڐG����̔ԍ��̍ő吔
	}Data;

	CColl();
	~CColl();

	HRESULT Init(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CColl *Create(CMgrColl::TAG tag, CMgrColl::TYPE type,D3DXVECTOR3 pos ,D3DXVECTOR3 size);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	bool Hit(CMgrColl::TAG hitTag, CMgrColl::STATE_HIT stateHit);

	void SetTagTgt(CMgrColl::TAG hitTag, bool bIsActive);

	void SetData(Data data);
	Data GetData(void);

	void SetHitData(HitData data);
	void ResetHitData(void);

private:

	void InitSet(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	Data m_data;
};

#endif	// ��d�C���N���[�h�h�~�̏I��

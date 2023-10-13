
//-===============================================
//-
//-	�ڐG�̏����̃w�b�_�[[collision.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _COLLSION_H_		// ���̃}�N������`����Ȃ�������
#define _COLLSION_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

//-======================================
//-	�}�N����`
//-======================================

#define COLLSION_NUM_MAX		(1024)	// �����蔻��̍ő吔

//-======================================
//-	�N���X��`
//-======================================

// �ڐG�̃N���X
class CCollision
{

public:

	// �����蔻��^�O
	typedef enum
	{
		TAG_NONE = 0,	// ���ʂȂ�
		TAG_PLAYER,		// �v���C���[
		TAG_ENEMY,		// �G
		TAG_KAZEDAMA,	// ������
		TAG_ENEMY_HAVE,	// �ێ��G
		TAG_MAX
	}TAG;

	// ��������
	typedef enum
	{
		TYPE_RECTANGLE = 0,	// ��`
		TYPE_MAX
	}TYPE;

	// �ڐG����̓����蔻����
	typedef struct
	{
		TAG tag;			// �^�O
		int nNldx;			// �ԍ�
		CObject *pObj;		// �I�u�W�F�N�g���
	}HitData;

	// �����蔻����
	typedef struct
	{
		TAG tag;							// �^�O
		bool bHitTag[TAG_MAX];				// ����̃^�O
		TYPE type;							// ���
		int nNldx;							// �ԍ�
		
		D3DXVECTOR3 pos;					// �ʒu
		D3DXVECTOR3 size;					// �傫��

		CObject *pObj;						// �I�u�W�F�N�g���

		HitData hitData[COLLSION_NUM_MAX];	// �ڐG����̓����蔻����
		int nHitNldxMax;					// �ڐG����̔ԍ��̍ő吔
	}Data;

	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCollision *Create(void);

	void UninitColl(int nNldxColl);
	void UpdateData(int nNldxColl, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	int SetColl(TAG tag, TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, CObject * pObj);
	void SetHit(int nNldxColl, TAG hitTag, bool bIsActive);

	bool Hit(int nNldxColl, TAG hitTag);

	bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	bool hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair);
	bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

private:

	Data m_data[COLLSION_NUM_MAX];	// �����蔻��̏��
	int m_nNldxMax;					// ���݂̔ԍ��̍ő吔
};

#endif	// ��d�C���N���[�h�h�~�̏I��


//================================================
//=
//=	�����蔻��Ǘ��̏����̃w�b�_�[[mgr_coll.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _MGR_COLL_H_		// ���̃}�N������`����Ȃ�������
#define _MGR_COLL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

//=======================================
//=	�}�N����`
//=======================================

#define COLLSION_NUM_MAX		(1024)	// �����蔻��̍ő吔

//=======================================
//=	�O���錾
//=======================================

class CColl;

//-======================================
//-	�N���X��`
//-======================================

// �ڐG�̃N���X
class CMgrColl
{

public:

	// �����蔻��^�O
	typedef enum
	{
		TAG_NONE = 0,		// ���ʂȂ�
		TAG_PLAYER,			// �v���C���[
		TAG_ENEMY,			// �G
		TAG_KAZEDAMA,		// ������
		TAG_ENEMY_HAVE,		// �ێ��G
		TAG_BLOCK,			// �u���b�N
		TAG_GIMMICK_JEWEL,	// ��΃M�~�b�N
		TAG_MAX
	}TAG;

	// ��������
	typedef enum
	{
		TYPE_RECTANGLE = 0,	// ��`
		TYPE_MAX
	}TYPE;

	// �ڐG�̎��
	typedef enum
	{
		STATE_HIT_NONE = 0,		// �����Ȃ��i�����j���
		STATE_HIT_NORMAL,		// �ʏ�ڐG�̏��
		STATE_HIT_DEAD,			// ���S�ڐG�̏��
		STATE_HIT_MAX
	}STATE_HIT;

	CMgrColl();
	~CMgrColl();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMgrColl *Create(void);

	bool Hit(int nNldxColl, TAG hitTag, STATE_HIT stateHit);

	int Set(CColl *pColl);
	void Reset(int nNldx);

	bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	bool hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair);
	bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

private:

	CColl *m_apColl[COLLSION_NUM_MAX];	// �����蔻��̏��
	int m_nNldxMax;						// ���݂̔ԍ��̍ő吔
};

#endif	// ��d�C���N���[�h�h�~�̏I��

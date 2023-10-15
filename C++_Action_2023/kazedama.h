
//-===============================================
//-
//-	�����܂̏����̃w�b�_�[[bullet.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _KAZEDAMA_H_		// ���̃}�N������`����Ȃ�������
#define _KAZEDAMA_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_billboard.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;

//-======================================
//-	�N���X��`
//-======================================

class CKazedama : public CObjectBillboard
{

public:

	// �e�N�X�`��
	typedef enum
	{
		TEX_NULL = 0,	// �Ȃ�
		TEX_MAX
	}TEX;

	// ���
	typedef enum
	{
		STATE_ACTIVE = 0,	// �������
		STATE_RETURN,		// �A�ҏ��
		STATE_LOST,			// ���ŏ��
		STATE_HIT,			// �q�b�g���
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
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 moveAccum;	// �ړ��̒~�ϒl
		STATE state;			// ���
		TYPE_ROT typeRot;		// �����̎��
	}Data;

	CKazedama(int nPriority = 3);
	~CKazedama();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot);

	static CKazedama * Create(TEX tex);

private:

	void UpdateData(void);
	void UpdateMove(void);

	void Active(void);
	void Return(void);
	void Lost(void);
	void Hit(void);

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�

	Data m_data;							// ���l

	CColl *m_pColl;							// �����蔻��̏��
	
};

#endif	// ��d�C���N���[�h�h�~�̏I��

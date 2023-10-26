
//-===============================================
//-
//-	�����܂̏����̃w�b�_�[[kazedama.h]
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
class CEnemyHave;

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
		TEX_KAZEDAMA,	// ������
		TEX_MAX
	}TEX;

	// ���
	typedef enum
	{
		STATE_ACTIVE = 0,	// �������
		STATE_RETURN,		// �A�ҏ��
		STATE_SUCCE,		// �������
		STATE_FAIL,			// ���s���
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

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CKazedama *Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot);

	void SetParent(D3DXVECTOR3 pos);

	void LostFail(void);
	void LostSucce(void);

	Data GetData(void);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot);

	void UpdateMove(void);

	void Active(void);
	void Return(void);

	void Obtain(void);

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�

	Data m_data;							// ���l

	CColl *m_pColl;							// �����蔻��̏��
	CEnemyHave *m_pEnemyHave;				// �ێ��G�̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��


//-===============================================
//-
//-	��΃M�~�b�N�����̃w�b�_�[[gimmick_jewel.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GIMMICK_JEWEL_H_		// ���̃}�N������`����Ȃ�������
#define _GIMMICK_JEWEL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "gimmick.h"

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

// ��΃M�~�b�N�̃N���X
class CGimmickJewel : public CGimmick
{

public:

	// ���ʂ̎��
	typedef enum
	{
		TYPE_EFFECT_NONE = 0,	// ���ʂȂ�
		TYPE_EFFECT_SPEED_UP,	// ���x�㏸
		TYPE_EFFECT_MAX
	}TYPE_EFFECT;

	CGimmickJewel(int nPriority = 3);
	~CGimmickJewel();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGimmickJewel * Create(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void InitSet(TYPE_EFFECT typeEffect);

	void PlayerPlus(void);

	TYPE_EFFECT m_type;	// ���ʂ̎��

	CColl *m_pColl;		// �����蔻��̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��
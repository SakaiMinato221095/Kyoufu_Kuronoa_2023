
//-===============================================
//-
//- �I�u�W�F�N�g�u���b�N�����̃w�b�_�[[obj_black.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _BLOCK_H_		// ���̃}�N������`����Ȃ�������
#define _BLOCK_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "objectx_none.h"

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

// �u���b�N�̃N���X
class CObjBlock : public CObjectXNone
{

public:

	CObjBlock(int nPriority = 3);
	~CObjBlock();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjBlock * Create(MODEL model,D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void InitSet(void);

	CColl *m_pColl;		// �����蔻��̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��

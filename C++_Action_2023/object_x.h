
//=======================
//=
//= X�t�@�C���I�u�W�F�N�g�����̃w�b�^�[[object_x.h]
//= Author Sakai Minato
//=
//=======================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_X_H_	// ���̃}�N������`����Ȃ�������
#define _OBJECT_X_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�N���X��`
//=======================================

// X�t�@�C���I�u�W�F�N�g�̃N���X
class CObjectX : public CObject
{
public:

	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 size;	// �T�C�Y
	}VtxData;

	CObjectX(int nPriority = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX *Create(void);

	void BindModel(int nModelNldx, int nModelNum);

	void SetVtxData(VtxData vtxData);
	VtxData GetVtxData(void);

	virtual void SetModel(int nModelNldx);

private:
	
	VtxData m_vtxData;		// ���_�l���

	int m_nModelNldxUse;	// ���f���ԍ�
	
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
};

#endif	// ��d�C���N���[�h�h�~�̏I��

//-===============================================
//-
//-	2D�I�u�W�F�N�g�����̃w�b�_�[[object2d.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_2D_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_2D_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CObject2d : public CObject
{

public:

	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 size;	// �傫��
		D3DXCOLOR color;	// �F
	}VtxData;

	CObject2d(int nPriority = 3);
	~CObject2d();

	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(int nTextureNldx);

	static CObject2d *CObject2d::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	virtual void SetVtx(void);

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

	CObject2d::VtxData GetVtxData(void);
	void SetVtxData(CObject2d::VtxData vtxData);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	VtxData m_vtxData;							// ���_�l���

	int m_nTextureNldxUse;						// �e�N�X�`���̔ԍ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@���i�[
};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��

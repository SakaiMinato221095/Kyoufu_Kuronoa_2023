
//================================================
//=
//= �r���{�[�h�I�u�W�F�N�g�����̃w�b�^�[[object_billboard.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_BILLBOARD_H_	// ���̃}�N������`����Ȃ�������
#define _OBJECT_BILLBOARD_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

//=======================================
//=	�N���X��`
//=======================================

// �r���{�[�h�I�u�W�F�N�g�̃N���X
class CObjectBillboard : public CObject
{
public:

	// ���_�l���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 size;	// �傫��
		D3DXCOLOR color;	// �F
	}VtxData;

	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectBillboard *Create(void);

	void BindTexture(int nTextureNldx);

	void SetVtx(void);

	void SetVtxData(VtxData vtxData);
	VtxData GetVtxData(void);

private:

	VtxData m_vtxData;					// ���_�l���

	int m_nTextureNldxUse;				// �e�N�X�`���̔ԍ�

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
};

#endif 
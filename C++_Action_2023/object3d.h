
//================================================
//=
//= 3D�I�u�W�F�N�g�����̃w�b�^�[[object3d.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _OBJECT_3D_H_	//���̃}�N������`����Ȃ�������
#define _OBJECT_3D_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

#include "object.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�N���X��`
//=======================================

class CObject3d : public CObject
{
public:

	// �������
	typedef enum
	{
		TYPE_CREATE_FIELD = 0,
		TYPE_CREATE_WALL,
		TYPE_CREATE_MAX
	}TYPE_CREATE;

	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 size;	// �傫��
		D3DXCOLOR color;	// �F
	}VtxData;

	CObject3d(int nPriority = 3);;
	~CObject3d();

	HRESULT Init(TYPE_CREATE type,D3DXVECTOR3 pos,D3DXVECTOR3 size ,D3DXVECTOR3 rot ,D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject3d *Create(TYPE_CREATE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);

	void BindTexture(int nTextureNldx);

	void SetVtxData(VtxData vtxData);
	VtxData GetVtxData(void);

	virtual void SetVtx(void);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);

	VtxData m_vtxData;					// ���_�l���

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X

	int m_nTextureNldxUse;				// �e�N�X�`���̔ԍ�

	TYPE_CREATE m_typeCreate;			// �������
};

#endif	// ��d�C���N���[�h�h�~�̏I��
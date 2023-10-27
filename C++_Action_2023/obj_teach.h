
//-===============================================
//-
//-	������I�u�W�F�N�g�����̃w�b�_�[[obj_teach.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJ_TEACH_H_		// ���̃}�N������`����Ȃ�������
#define _OBJ_TEACH_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_billboard.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// ������I�u�W�F�N�g�̃N���X
class CObjTeach : public CObjectBillboard 
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		TEX_TEACH_MOVE = 0,			// �ړ� 
		TEX_TEACH_JUMP,				// �W�����v
		TEX_TEACH_KAZEDAMA,			// ������
		TEX_TEACH_DOUBLE_JUMP,		// ��i�W�����v
		TEX_TEACH_SHOT,				// �V���b�g
		TEX_MAX
	}TEX;

	CObjTeach(int nPriority = 3);
	~CObjTeach();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjTeach *Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

private:

	void InitSet(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��

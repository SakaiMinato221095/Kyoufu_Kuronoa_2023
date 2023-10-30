
//-===============================================
//-
//-	�ʏ�2D�I�u�W�F�N�g�����̃w�b�_�[[obj_2d_none.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJ_2D_NONE_H_		// ���̃}�N������`����Ȃ�������
#define _OBJ_2D_NONE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

//-======================================
//-	�N���X��`
//-======================================

class CObj2dNone : public CObject2d
{

public:

	// �����̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_NULL = 0,		// �Ȃ�
		TEX_TITLE_LOGO,		// �^�C�g�����S
		TEX_TITLE_BUTTON,	// �^�C�g���{�^��
		//TEX_PAUSE_BG,		// �|�[�Y�̔w�i
		//TEX_PAUSE_GAME,		// �|�[�Y�̃Q�[��
		//TEX_PAUSE_RETRY,	// �|�[�Y�̃��g���C
		//TEX_PAUSE_TITLE,	// �|�[�Y�̃^�C�g��
		//TEX_PAUSE_CURSOR,	// �|�[�Y�̃J�[�\��
		TEX_MAX
	}TEX;

	CObj2dNone(int nPriority = 3);
	~CObj2dNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj2dNone *Create(TEX tex, D3DXVECTOR3 pos,D3DXVECTOR3 size,D3DXCOLOR color);

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��

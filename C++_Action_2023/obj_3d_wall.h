
//-===============================================
//-
//-	3D�n�ʏ����̃w�b�_�[[wall.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _WALL_H_		// ���̃}�N������`����Ȃ�������
#define _WALL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object3d.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �A�C�e���̃N���X
class CObj3dWall : public CObject3d
{

public:

	// �t�B�[���h�̃e�N�X�`���̗񋓌^
	typedef enum
	{
		TEX_NULL = 0,			// �e�N�X�`���̂Ȃ�
		TEX_BLOCKADE_WALL_000,	// ������000�̃e�N�X�`��
		TEX_DARK_WALL_000,		// �ŕ�000�̃e�N�X�`��
		TEX_MAX
	}TEX;

	CObj3dWall(int nPriority = 3);
	~CObj3dWall();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj3dWall * Create(TEX tex,D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color);

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��
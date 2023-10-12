
//-===============================================
//-
//-	3D�n�ʏ����̃w�b�_�[[obj_3d_field.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FIELD_H_		// ���̃}�N������`����Ȃ�������
#define _FIELD_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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
class CObj3dField : public CObject3d
{

public:

	// �t�B�[���h�̃e�N�X�`���̗񋓌^
	typedef enum
	{
		TEX_NULL = 0,			// �e�N�X�`���̂Ȃ�
		TEX_WHITE_TILE_000,		// ������000�̃e�N�X�`��
		TEX_ROAD_000,			// ���H000�̃e�N�X�`��
		TEX_ASPHALT_000,		// �A�X�t�@���g000�̃e�N�X�`��
		TEX_GLASS_000,			// ����000�̃e�N�X�`��
		TEX_MAX
	}TEX;

	CObj3dField(int nPriority = 3);;
	~CObj3dField();

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObj3dField * Create(TEX tex);

	void Set(
		D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,
		D3DXCOLOR color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��

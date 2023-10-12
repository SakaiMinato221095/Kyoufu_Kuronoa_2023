
//-===============================================
//-
//-	�\�������̃w�b�_�[[renderer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _RENDERER_H_		// ���̃}�N������`����Ȃ�������
#define _RENDERER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CRenderer
{

public:

	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAlphaBlend(bool bUse);
	void SetZTest(bool bUse);
	void SetAlphaTest(bool bUse);

	LPDIRECT3DDEVICE9 GetDevice(void);

private:

	LPDIRECT3D9 m_pD3D;						// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;			// Direct3D�f�o�C�X�ւ̃|�C���^
};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��

//-===============================================
//-
//-	�e�N�X�`���Ǘ������̃w�b�_�[[manager_texture.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MANAGER_TEXTURE_H_		// ���̃}�N������`����Ȃ�������
#define _MANAGER_TEXTURE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

#define MANAGER_TEXTUTE_MAX	(2048)	// �e�N�X�`���̍ő吔

//-======================================
//-	�N���X��`
//-======================================

class CManagerTexture
{

public:

	CManagerTexture();
	~CManagerTexture();

	HRESULT Load(HWND hWnd);
	void Unload(void);

	int Regist(const char *pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nldx);

private:

	LPDIRECT3DTEXTURE9 m_apTexture[MANAGER_TEXTUTE_MAX];	// �e�N�X�`��
	static int m_nNumAll;									// ����
};

#endif	// ��d�C���N���[�h�h�~�̏I��

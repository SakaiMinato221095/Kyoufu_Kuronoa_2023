
//-===============================================
//-
//-	���f���Ǘ������̃w�b�_�[[manager_model.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MANAGER_MODEL_H_		// ���̃}�N������`����Ȃ�������
#define _MANAGER_MODEL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

#define MANAGER_MODEL_MAX	(1024)	// ���f���̍ő吔

//-======================================
//-	�N���X��`
//-======================================

class CManagerModel
{

public:

	typedef struct
	{
		int *m_nldxTexture;				// �e�N�X�`���̔ԍ�
		LPDIRECT3DTEXTURE9 *m_pTexture;	// �e�N�X�`���̃|�C���^�i���I�m�ہj
		LPD3DXMESH m_pMesh;				// ���b�V���̏��̃|�C���^
		LPD3DXBUFFER m_pBuffMat;		// �}�e���A���̃|�C���^
		DWORD m_dwNumMat;				// �}�e���A���̐�
	}Model;

	CManagerModel();
	~CManagerModel();

	HRESULT Load(HWND hWnd);
	void Unload(void);

	int Regist(const char *pFilename);
	Model GetAddress(int nldx);

private:

	Model m_model[MANAGER_MODEL_MAX];	// ���f��

	static int m_nNumAll;				// ����
};

#endif	// ��d�C���N���[�h�h�~�̏I��

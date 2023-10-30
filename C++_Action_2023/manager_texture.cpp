
//================================================
//=
//= �e�N�X�`���Ǘ��̏���[manager_texture.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "manager_texture.h"

#include "renderer.h"
#include "manager.h"

#include "obj_3d_field.h"

#include "bg.h"
#include "number.h"

#include "kazedama.h"
#include "obj_teach.h"

//-------------------------------------
//-	�e�N�X�`���̃R���X�g���N�^
//-------------------------------------
CManagerTexture::CManagerTexture()
{
	// �l�̃N���A
	ZeroMemory(m_apTexture, sizeof(m_apTexture));
}

//-------------------------------------
//-	�e�N�X�`���̃f�X�g���N�^
//-------------------------------------
CManagerTexture::~CManagerTexture()
{
}


//-------------------------------------
//-	�e�N�X�`���̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CManagerTexture::Load(HWND hWnd)
{
	// �t�B�[���h
	if (FAILED(CObj3dField::Load()))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�t�B�[���h�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}
	
	// �w�i
	if (FAILED(CBg::Load()))
	{// ���s��

	 // ���s���b�Z�[�W
		MessageBox(hWnd, "�w�i�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ����
	if (FAILED(CNumber::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�����̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ������
	if (FAILED(CKazedama::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "�����܂̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ������I�u�W�F�N�g
	if (FAILED(CObjTeach::Load()))
	{// ���s��

		// ���s���b�Z�[�W
		MessageBox(hWnd, "������I�u�W�F�N�g�̃f�[�^", "�f�[�^�ǂݍ��ݏ������s�I", MB_ICONWARNING);

		// �f�[�^�ǂݍ��݂𔲂���
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�e�N�X�`���̔j������
//-------------------------------------
void CManagerTexture::Unload(void)
{
	for (int nCount = 0; nCount < MANAGER_TEXTUTE_MAX; nCount++)
	{
		// �e�N�X�`���̗L���𔻒�
		if (m_apTexture[nCount] != NULL)
		{
			// �J������
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//-------------------------------------
//-	�e�N�X�`���̎w��ǂݍ��ݏ���
//-------------------------------------
int CManagerTexture::Regist(const char *pFilename)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return -1;
	}

	// �t�@�C�����𔻒�i�e�N�X�`���Ȃ��j
	if (pFilename == NULL)
	{
		return 0;
	}
	
	for (int nCount = 1; nCount < MANAGER_TEXTUTE_MAX; nCount++)
	{
		// �e�N�X�`���̗L���𔻒�
		if (m_apTexture[nCount] == NULL)
		{
			// �e�N�X�`���̓ǂݍ��� if(�e�N�X�`���ǂݍ��ݐ����̗L���𔻒�)
			if (FAILED(D3DXCreateTextureFromFile(
				pDevice,
				pFilename,
				&m_apTexture[nCount])))
			{
				// ���s��Ԃ�
				return -1;
			}

			// ���݂̔ԍ���Ԃ�
			return nCount;
		}
	}
	
	// ���s��Ԃ�
	return -1;
}

//-------------------------------------
//-	�e�N�X�`���̎擾����
//-------------------------------------
LPDIRECT3DTEXTURE9 CManagerTexture::GetAddress(int nldx)
{
	// �e�N�X�`����Ԃ�
	return m_apTexture[nldx];
}

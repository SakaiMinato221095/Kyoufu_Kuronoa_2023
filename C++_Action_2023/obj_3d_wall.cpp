
//-===============================================
//-
//-	3D�Ǐ���[obj_3d_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "obj_3d_wall.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// 3D�ǂ̃e�N�X�`���̃R���X�g��`
const char *pTextureWall[] =
{
	NULL,										// �e�N�X�`���Ȃ�
	"data\\TEXTURE\\blockade_wall000.jpg",		// �����ǂ̃e�N�X�`��
	"data\\TEXTURE\\dark_wall000.png",			// �ŕǂ̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObj3dWall::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D�ǂ̃R���X�g���N�^
//-------------------------------------
CObj3dWall::CObj3dWall(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D�ǂ̃f�X�g���N�^
//-------------------------------------
CObj3dWall::~CObj3dWall()
{

}

//-------------------------------------
//- �w�i�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CObj3dWall::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// �e�N�X�`���Ǘ��̗L���𔻒�
	if (pManagerTexture == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���ݒ�
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// �e�N�X�`���ԍ��̎擾�i�e�N�X�`���̊����j
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureWall[nCount]);

		// �e�N�X�`���̓ǂݍ��ݐ����̗L�����m�F
		if (m_nTextureNldx[nCount] == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �w�i�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CObj3dWall::Unload(void)
{

}
//-------------------------------------
//- 3D�ǂ̏����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObj3dWall::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 3D�I�u�W�F�N�g�̏�����
	CObject3d::Init(CObject3d::TYPE_CREATE_WALL,pos,size,rot,color);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 3D�ǂ̏I������
//-------------------------------------
void CObj3dWall::Uninit(void)
{
	// 3D�I�u�W�F�N�g�̏I��
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D�ǂ̍X�V����
//-------------------------------------
void CObj3dWall::Update(void)
{
	// 3D�I�u�W�F�N�g�̍X�V����
	CObject3d::Update();
}

//-------------------------------------
//- 3D�ǂ̕`�揈��
//-------------------------------------
void CObj3dWall::Draw(void)
{
	// 3D�I�u�W�F�N�g�̕`�揈��
	CObject3d::Draw();
}

//-------------------------------------
//- 3D�ǂ̐�������
//-------------------------------------
CObj3dWall * CObj3dWall::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	// �t�B�[���h�̃|�C���^��錾
	CObj3dWall *pCObj3dWall = new CObj3dWall(5);

	// �����̐����̗L���𔻒�
	if (pCObj3dWall != NULL)
	{
		// ����������
		if (FAILED(pCObj3dWall->Init(tex,pos,size,rot,color)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObj3dWall == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �t�B�[���h�̃|�C���^��Ԃ�
	return pCObj3dWall;
}
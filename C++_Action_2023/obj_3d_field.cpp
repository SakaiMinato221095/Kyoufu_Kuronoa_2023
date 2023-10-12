
//-===============================================
//-
//-	�n�ʏ���[obj_3d_field.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "obj_3d_field.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// 3D�n�ʂ̃e�N�X�`���̃R���X�g��`
const char *pTextureField[] =
{
	NULL,										// �e�N�X�`���Ȃ�
	"data\\TEXTURE\\WhiteTile000.jpg",			// �t�B�[���h�̃e�N�X�`��
	"data\\TEXTURE\\road000.png",				// ���H�̃e�N�X�`��
	"data\\TEXTURE\\asphalt000.jpg",			// �A�X�t�@���g�̃e�N�X�`��
	"data\\TEXTURE\\field_glass000.jpg",		// �����̃e�N�X�`��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObj3dField::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D�n�ʂ̃R���X�g���N�^
//-------------------------------------
CObj3dField::CObj3dField(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D�n�ʂ̃f�X�g���N�^
//-------------------------------------
CObj3dField::~CObj3dField()
{

}

//-------------------------------------
//- 3D�n�ʂ̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CObj3dField::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// �e�N�X�`���Ǘ��̐���
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureField[nCount]);

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
//- 3D�n�ʂ̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CObj3dField::Unload(void)
{

}
//-------------------------------------
//- 3D�n�ʂ̏����������i3D�I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CObj3dField::Init(TEX tex)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// 3D�I�u�W�F�N�g�̏�����
	CObject3d::Init(CObject3d::TYPE_CREATE_FIELD);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- 3D�n�ʂ̏I������
//-------------------------------------
void CObj3dField::Uninit(void)
{
	// 3D�I�u�W�F�N�g�̏I��
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D�n�ʂ̍X�V����
//-------------------------------------
void CObj3dField::Update(void)
{
	// 3D�I�u�W�F�N�g�̍X�V����
	CObject3d::Update();
}

//-------------------------------------
//- 3D�n�ʂ̕`�揈��
//-------------------------------------
void CObj3dField::Draw(void)
{
	// 3D�I�u�W�F�N�g�̕`�揈��
	CObject3d::Draw();
}

//-------------------------------------
//- 3D�n�ʂ̐�������
//-------------------------------------
CObj3dField *CObj3dField::Create(TEX tex)
{
	// �t�B�[���h�̃|�C���^��錾
	CObj3dField *pCObj3dField = new CObj3dField(2);

	// �����̐����̗L���𔻒�
	if (pCObj3dField != NULL)
	{
		// ����������
		if (FAILED(pCObj3dField->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObj3dField == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �t�B�[���h�̃|�C���^��Ԃ�
	return pCObj3dField;
}

//-------------------------------------
//- 3D�n�ʂ̐ݒ菈��
//-------------------------------------
void CObj3dField::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,D3DXCOLOR color)
{
	// ���擾�i3D�I�u�W�F�N�g�j
	CObject3d::VtxData vtxData = GetVtxData();	// ���_�l���

	// ���X�V
	vtxData.pos = pos;		// �ʒu
	vtxData.size = size;	// �傫��
	vtxData.rot = rot;		// ����
	vtxData.color = color;	// �F

	// ���X�V�i3D�I�u�W�F�N�g�j
	SetVtxData(vtxData);	// ���_�l���

	// ���_���̐ݒ菈��
	SetVtx();
}

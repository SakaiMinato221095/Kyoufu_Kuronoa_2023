
//================================================
//=
//=	�ʏ�2D�I�u�W�F�N�g����[obj_2d_none.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "obj_2d_none.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//= �R���X�g��`
//=======================================

// �ʏ�I�u�W�F�N�g�e�N�X�`���̃R���X�g��`
const char *pTextureObj2dNone[] =
{
	NULL,										// �Ȃ�
	"data\\TEXTURE\\TitleLogo000.png",			// �^�C�g�����S�̃e�N�X�`��
	"data\\TEXTURE\\TitleButton000.png",		// �^�C�g���{�^���̃e�N�X�`��
	"data\\TEXTURE\\BgPause.jpg",				// �|�[�Y�̔w�i
	"data\\TEXTURE\\PauseGame.png",				// �|�[�Y�̃Q�[��
	"data\\TEXTURE\\PauseRetryText.png",		// �|�[�Y�̃��g���C
	"data\\TEXTURE\\PauseQuitText.png",			// �|�[�Y�̃^�C�g��
	"data\\TEXTURE\\GameTitleCursor.png",		// �|�[�Y�̃J�[�\��
};											   

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

int CObj2dNone::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	�ʏ�2D�I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObj2dNone::CObj2dNone(int nPriority) : CObject2d(nPriority)
{

}

//-------------------------------------
//-	�ʏ�2D�I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObj2dNone::~CObj2dNone()
{

}

//-------------------------------------
//- �ʏ�2D�I�u�W�F�N�g�̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CObj2dNone::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureObj2dNone[nCount]);

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
void CObj2dNone::Unload(void)
{

}

//-------------------------------------
//- �ʏ�2D�I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CObj2dNone::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �g�p�e�N�X�`���̐ݒ�
	BindTexture(m_nTextureNldx[tex]);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init(pos,size,color);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �ʏ�2D�I�u�W�F�N�g�̏I������
//-------------------------------------
void CObj2dNone::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2d::Uninit();
}

//-------------------------------------
//- �ʏ�2D�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObj2dNone::Update(void)
{
	// ���_���̐ݒ菈��
	SetVtx();
}

//-------------------------------------
//- �ʏ�2D�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObj2dNone::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//-	�ʏ�2D�I�u�W�F�N�g�̐�������
//-------------------------------------
CObj2dNone * CObj2dNone::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// ����
	CObj2dNone *pObj2dNone = DBG_NEW CObj2dNone(7);

	// �����̐����̗L���𔻒�
	if (pObj2dNone != NULL)
	{
		// ����������
		if (FAILED(pObj2dNone->Init(tex,pos,size,color)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObj2dNone == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�2D�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObj2dNone;
}
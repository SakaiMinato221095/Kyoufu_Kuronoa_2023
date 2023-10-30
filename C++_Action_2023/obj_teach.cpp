
//================================================
//=
//=	������I�u�W�F�N�g�̏���[obj_teach.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "obj_teach.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//= �R���X�g��`
//=======================================

// ������e�N�X�`���̃R���X�g��`
const char *pTextureTeach[] =
{
	"data\\TEXTURE\\Teach\\TeachMove.png",			// �ړ�
	"data\\TEXTURE\\Teach\\TeachJump.png",			// �W�����v
	"data\\TEXTURE\\Teach\\TeachKazedama.png",		// �����܃A�N�V����
	"data\\TEXTURE\\Teach\\TeachDoubleJump.png",	// ��i�W�����v
	"data\\TEXTURE\\Teach\\TeachShot.png",			// ����
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CObjTeach::m_nTextureNldx[TEX_MAX] = {};			// �e�N�X�`��

//-------------------------------------
//-	������I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CObjTeach::CObjTeach(int nPriority) : CObjectBillboard(nPriority)
{

}

//-------------------------------------
//-	������I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CObjTeach::~CObjTeach()
{

}

//-------------------------------------
//- ������I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
//-------------------------------------
HRESULT CObjTeach::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureTeach[nCount]);

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
//- ������I�u�W�F�N�g�̓ǂݍ��񂾃e�N�X�`���̔j��
//-------------------------------------
void CObjTeach::Unload(void)
{

}

//-------------------------------------
//- ������I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CObjTeach::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �e�N�X�`������
	BindTexture(m_nTextureNldx[tex]);

	// �����ݒ菈��
	InitSet(tex,pos, size, color);

	// �r���{�[�h�I�u�W�F�N�g�̏�����
	CObjectBillboard::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- ������I�u�W�F�N�g�̏I������
//-------------------------------------
void CObjTeach::Uninit(void)
{
	// �r���{�[�h�I�u�W�F�N�g�̏I��
	CObjectBillboard::Uninit();
}

//-------------------------------------
//- ������I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CObjTeach::Update(void)
{
	// �r���{�[�h�I�u�W�F�N�g�̍X�V����
	CObjectBillboard::Update();
}

//-------------------------------------
//- ������I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CObjTeach::Draw(void)
{
	// �f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pRenderer == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// Z�e�X�g�̐ݒ�
	pRenderer->SetZTest(true);

	// �A���t�@�e�X�g�̐ݒ�
	pRenderer->SetAlphaTest(true);

	// ������I�u�W�F�N�g�̕`�揈��
	CObjectBillboard::Draw();

	// Z�e�X�g�̉���
	pRenderer->SetZTest(false);

	// �A���t�@�e�X�g�̉���
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- ������I�u�W�F�N�g�̐�������
//-------------------------------------
CObjTeach *CObjTeach::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// ������I�u�W�F�N�g�̐���
	CObjTeach *pCObjTeach = DBG_NEW CObjTeach(3);

	// �����̐����̗L���𔻒�
	if (pCObjTeach != NULL)
	{
		// ����������
		if (FAILED(pCObjTeach->Init(tex, pos, size, color)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCObjTeach == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ������I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pCObjTeach;
}

//-------------------------------------
//- ������I�u�W�F�N�g�̐ݒ菈��
//-------------------------------------
void CObjTeach::InitSet(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	// �ϐ���錾�i���擾�j
	CObjectBillboard::VtxData vtxData = GetVtxData();

	vtxData.pos = pos;			// �ʒu
	vtxData.size = size;		// �傫��
	vtxData.color = color;		// �F

	// ���X�V
	SetVtxData(vtxData);
}
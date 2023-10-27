
//-===============================================
//-
//-	�X�J�C�{�b�N�X�̏���[skybox.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "skybox.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// �X�J�C�{�b�N�X�̃��f���̃R���X�g��`
const char *pModelSkybox[] =
{
	"data\\MODEL\\SkyBox\\sky_box000.x",			// �X�J�C�{�b�N�X000
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

int CSkybox::m_nModelNldx[MODEL_MAX] = {};			// ���f���̔ԍ�

//-------------------------------------
//-	�X�J�C�{�b�N�X�I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CSkybox::CSkybox(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	�X�J�C�{�b�N�X�I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CSkybox::~CSkybox()
{

}

//-------------------------------------
//- �X�J�C�{�b�N�X�̃��f���ǂݍ���
//-------------------------------------
HRESULT CSkybox::Load(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����������𔲂���
		return E_FAIL;
	}

	// ���f���ݒ�
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// ���f���ԍ����擾
		int nModelNldx = m_nModelNldx[nCount];

		// ���f���ԍ��̎擾�i���f���̊����j
		nModelNldx = pManagerModel->Regist(pModelSkybox[nCount]);

		// ���f���̓ǂݍ��ݐ����̗L�����m�F
		if (nModelNldx == -1)
		{
			// ���s���ɏ����������𔲂���
			return E_FAIL;
		}

		// ���f���ԍ���ݒ�
		m_nModelNldx[nCount] = nModelNldx;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �X�J�C�{�b�N�X�̓ǂݍ��񂾃��f���j��
//-------------------------------------
void CSkybox::Unload(void)
{

}

//-------------------------------------
//- �X�J�C�{�b�N�X�I�u�W�F�N�g�̏����������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
HRESULT CSkybox::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����𔲂���
		return E_FAIL;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nModelNldx[model];

	// �X�J�C�{�b�N�X�I�u�W�F�N�g�̃��f������
	BindModel(nModelNldx, model);

	// �����ݒ�
	InitSet(pos,rot);

	// X�t�@�C���I�u�W�F�N�g�̏����� if(�����������̗L���𔻒�)
	if (FAILED(CObjectX::Init()))
	{
		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �X�J�C�{�b�N�X�I�u�W�F�N�g�̏I������
//-------------------------------------
void CSkybox::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�̏I��
	CObjectX::Uninit();
}

//-------------------------------------
//- �X�J�C�{�b�N�X�I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CSkybox::Update(void)
{
	// X�t�@�C���I�u�W�F�N�g�̍X�V����
	CObjectX::Update();
}

//-------------------------------------
//- �X�J�C�{�b�N�X�I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CSkybox::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}

//-------------------------------------
//- �X�J�C�{�b�N�X�I�u�W�F�N�g�̐��������iX�t�@�C���I�u�W�F�N�g�ݒ�j
//-------------------------------------
CSkybox * CSkybox::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �X�J�C�{�b�N�X�I�u�W�F�N�g�̃|�C���^��錾
	CSkybox *pCSkybox = DBG_NEW CSkybox(4);

	// �����̐����̗L���𔻒�
	if (pCSkybox != NULL)
	{
		// ����������
		if (FAILED(pCSkybox->Init(model,pos,rot)))
		{// ���s��

		 // �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCSkybox == NULL)
	{// ���s��

	 // �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �X�J�C�{�b�N�X�I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pCSkybox;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
int CSkybox::GetModel(void)
{
	// ���f���ݒ�
	return(int)m_model;
}

//-------------------------------------
//-	���f���̐ݒ菈��
//-------------------------------------
void CSkybox::SetModel(int nModelNldx)
{
	// ���f���ݒ�
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	�X�J�C�{�b�N�X�̏����ݒ菈��
//-------------------------------------
void CSkybox::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ���_�l�����擾
	CObjectX::VtxData vtxData = GetVtxData();

	// �f�[�^�̑��
	vtxData.pos = pos;								// �ʒu
	vtxData.rot = rot;								// ����

	// ���X�V�i���_�l���j
	SetVtxData(vtxData);
}

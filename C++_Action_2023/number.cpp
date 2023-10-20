
//================================================
//=
//=	��������[number.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "number.h"

#include "manager.h"
#include "renderer.h"

#include "manager_texture.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//= �R���X�g��`
//=======================================

// �w�i�e�N�X�`���̃R���X�g��`
const char *pTextureNumber[] =
{
	"data\\TEXTURE\\number_000.png",	// ����_000�i���F�j�̃e�N�X�`��
	"data\\TEXTURE\\number_001.png",	// ����_001�i�[�ΐF�j�̃e�N�X�`��
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

int CNumber::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	�����̃R���X�g���N�^
//-------------------------------------
CNumber::CNumber(int nPriority) : CObject2d(nPriority)
{
	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	�����̃f�X�g���N�^
//-------------------------------------
CNumber::~CNumber()
{

}

//-------------------------------------
//- �����̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CNumber::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureNumber[nCount]);

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
void CNumber::Unload(void)
{

}

//-------------------------------------
//- �����̏���������
//-------------------------------------
HRESULT CNumber::Init(TEX tex)
{
	// �g�p�e�N�X�`���̐ݒ�
	BindTexture(m_nTextureNldx[tex]);

	// 2D�I�u�W�F�N�g�̏�����
	CObject2d::Init();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �����̏I������
//-------------------------------------
void CNumber::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2d::Uninit();
}

//-------------------------------------
//- �����̍X�V����
//-------------------------------------
void CNumber::Update(void)
{
	// ���_���̐ݒ菈��
	SetVtx();
}

//-------------------------------------
//- �����̕`�揈��
//-------------------------------------
void CNumber::Draw(void)
{
	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2d::Draw();
}

//-------------------------------------
//-	�����̐�������
//-------------------------------------
CNumber *CNumber::Create(TEX tex)
{
	// �����̐���
	CNumber *pNumber = DBG_NEW CNumber(7);

	// �����̐����̗L���𔻒�
	if (pNumber != NULL)
	{
		// ����������
		if (FAILED(pNumber->Init(tex)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pNumber == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �����̃|�C���^��Ԃ�
	return pNumber;
}

//-------------------------------------
//- �����̒��_���ݒ�
//-------------------------------------
void CNumber::SetVtx(void)
{
	// �ϐ��錾�i���̎擾�j
	D3DXVECTOR3 pos = GetVtxData().pos;		// �ʒu���
	D3DXVECTOR3 size = GetVtxData().size;	// �傫��
	D3DXCOLOR color = GetVtxData().color;	// �F

	// ���_�o�b�t�@���|�C���^��錾
	LPDIRECT3DVERTEXBUFFER9 vtxBuff = GetVtxBuff();

	// ���_�o�b�t�@�擾�����̗L���𔻒�
	if (vtxBuff == NULL)
	{// ���s��

		// ���_���ݒ�𔲂���
		return;
	}

	// 2D���_���̃|�C���^��錾
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	vtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0);

	// ���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[��ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// �e�N�X�`���̍��W��ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 0), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 1), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 0), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * (m_data.nDigits + 1), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	vtxBuff->Unlock();
}

//-------------------------------------
//- �����̒l���ݒ�
//-------------------------------------
void CNumber::SetData(Data data)
{
	m_data = data;
}

//-------------------------------------
//- �����̒l���ݒ�
//-------------------------------------
CNumber::Data CNumber::GetData(void)
{
	return m_data;
}


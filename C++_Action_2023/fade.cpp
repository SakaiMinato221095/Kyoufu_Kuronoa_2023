
//-===============================================
//-
//-	�t�F�[�h����[fade.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "fade.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFade::CFade()
{
	// �l���N���A
	m_pVtxBuff = NULL;
	m_state = STATE_NONE;
	m_mode = CScene::MODE(0);
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFade::~CFade()
{

}

//-------------------------------------
//- �t�F�[�h�̏���������
//-------------------------------------
HRESULT CFade::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@���������̗L���𔻒�
	if (m_pVtxBuff == NULL)
	{// ���s��

	 // �����������𔲂���
		return E_FAIL;

	}

	// �����ݒ菈��
	InitSet();

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �t�F�[�h�̏I������
//-------------------------------------
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̗L���𔻒�
	if (m_pVtxBuff != NULL)
	{
		// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//-------------------------------------
//- �t�F�[�h�̍X�V����
//-------------------------------------
void CFade::Update(void)
{
	// �ϐ��錾�i���擾�j
	D3DXCOLOR color = m_dataColor.Get();		// �F

	if (m_state == STATE_OUT)
	{// �t�F�[�h�A�E�g���

		// �����x�����Z
		color.a += 0.049f;

		// �����x�̔���
		if (color.a >= 1.0f)
		{
			// �����x�̐ݒ�
			color.a = 1.0f;

			// �t�F�[�h��ԂɕύX
			m_state = STATE_IN;

			// ���[�h��ݒ�
			CManager::SetMode(m_mode);
		}
	}
	else if (m_state == STATE_IN)
	{// �t�F�[�h�C�����

	 // �����x�����Z
		color.a -= 0.049f;

		// �����x�̔���
		if (color.a <= 0.0f)
		{
			// �����x�̐ݒ�
			color.a = 0.0f;

			// �������Ȃ���ԂɕύX
			m_state = STATE_NONE;
		}
	}

	// ���X�V
	m_dataColor.Set(color);		// �F

	// �t�F�[�h�̒��_���ݒ�
	SetVtx();
}

//-------------------------------------
//- �t�F�[�h�̕`�揈��
//-------------------------------------
void CFade::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �`�揈���𔲂���
		return;
	}

	// ���_���̕`��
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(
			0,
			m_pVtxBuff,
			0,
			sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(
			0,
			NULL);

		// �t�F�[�h�̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			0,								//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);								//�v���~�e�B�u�́i�|���S���j��
	}
}

//-------------------------------------
//- �t�F�[�h�̐�������
//-------------------------------------
CFade *CFade::Create(void)
{
	// �t�F�[�h�̐���
	CFade *pFade = DBG_NEW CFade;

	// �����̐����̗L���𔻒�
	if (pFade != NULL)
	{
		// ����������
		if (FAILED(pFade->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pFade == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// ���_���ݒ�
	pFade->SetVtx();

	// �t�F�[�h�̃|�C���^��Ԃ�
	return pFade;
}

//-------------------------------------
//- �t�F�[�h�̒��_���ݒ�
//-------------------------------------
void CFade::SetVtx(void)
{
	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_dataPos.Get();		// �ʒu
	D3DXVECTOR3 size = m_dataSize.Get();	// �傫��
	D3DXCOLOR color = m_dataColor.Get();	// �F

	// 2D���_���̃|�C���^��錾
	VERTEX_2D *pVtx = NULL;

	// ���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	m_pVtxBuff->Lock(
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// ���X�V
	m_dataPos.Set(pos);			// �ʒu
	m_dataSize.Set(size);		// �傫��
	m_dataColor.Set(color);		// �F
}

//-------------------------------------
//- �t�F�[�h�̒��_���ݒ�
//-------------------------------------
void CFade::SetFade(CScene::MODE mode)
{
	// ���[�h��ݒ�
	m_mode = mode;

	// �t�F�[�h�̏�Ԃ�ݒ�
	m_state = STATE_OUT;
}

//-------------------------------------
//- �t�F�[�h�̏�Ԃ̎擾����
//-------------------------------------
CFade::STATE CFade::GetFade(void)
{
	return m_state;
}

//-------------------------------------
//- �t�F�[�h�̏����ݒ菈��
//-------------------------------------
void CFade::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	m_dataPos.Set(pos);
	m_dataSize.Set(size);
	m_dataColor.Set(color);
}

//================================================
//=
//=	�����蔻��̏���[collision.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "collision.h"

#include "object.h"

//=======================================
//=	�}�N����`
//=======================================

//=======================================
//=	�R���X�g��`
//=======================================

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�����蔻��̃R���X�g���N�^
//-------------------------------------
CCollision::CCollision()
{
	ZeroMemory(&m_data, sizeof(m_data));
	m_nNldxMax = 0;
}

//-------------------------------------
//-	�����蔻��̃f�X�g���N�^
//-------------------------------------
CCollision::~CCollision()
{

}

//-------------------------------------
//- �����蔻��̏���������
//-------------------------------------
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- �����蔻��̏I������
//-------------------------------------
void CCollision::Uninit(void)
{

}

//-------------------------------------
//- �����蔻��̍X�V����
//-------------------------------------
void CCollision::Update(void)
{
	for (int nCount = 0; nCount < m_nNldxMax; nCount++)
	{
		for (int nCountPair = 0; nCountPair < m_nNldxMax; nCountPair++)
		{
			// �ϐ��錾
			TAG tag = m_data[nCountPair].tag;					// ����̃^�O
			bool bHitTag = m_data[nCount].bHitTag[tag];			// �^�O����̐ڐG�̗L��

			// �����蔻��^�O�̔���
			if (bHitTag == true)
			{
				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 posMy = m_data[nCount].pos;			// ���g�̈ʒu
				D3DXVECTOR3 sizeMy = m_data[nCount].size;		// ���g�̑傫��

				D3DXVECTOR3 posPair = m_data[nCountPair].pos;	// ����̈ʒu
				D3DXVECTOR3 sizePair = m_data[nCountPair].size;	// ����̑傫��

				bool bIsHit = false;							// �ڐG�̗L��

				switch (m_data->type)
				{
				case TYPE_RECTANGLE:

					// ��`�̓����蔻��
					if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
					{
						bIsHit = true;
					}

					break;
				}

				// �ڐG�̗L��
				if (bIsHit == true)
				{
					// �ڐG����̏��ݒ�
					int nHitNldxMax = m_data[nCount].nHitNldxMax;							// �z��ԍ�
					m_data[nCount].hitData[nHitNldxMax].tag = m_data[nCountPair].tag;		// ����̃^�O��ۑ�
					m_data[nCount].hitData[nHitNldxMax].nNldx = m_data[nCountPair].nNldx;	// �ڐG�ԍ���ۑ�
					m_data[nCount].hitData[nHitNldxMax].pObj = m_data[nCountPair].pObj;		// �I�u�W�F�N�g����ۑ�
					m_data[nCount].nHitNldxMax++;											// �z��ԍ���i�߂�
				}
			}
		}
	}
}

//-------------------------------------
//- �����蔻��̕`�揈��
//-------------------------------------
void CCollision::Draw(void)
{
}

//-------------------------------------
//- �����蔻��̐�������
//-------------------------------------
CCollision * CCollision::Create(void)
{
	// �����蔻��̐���
	CCollision *pCollision = DBG_NEW CCollision;

	// �����̐����̗L���𔻒�
	if (pCollision != NULL)
	{
		// ����������
		if (FAILED(pCollision->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCollision == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �����蔻��̃|�C���^��Ԃ�
	return pCollision;
}

//-------------------------------------
//- �����蔻��̏I������
//-------------------------------------
void CCollision::UninitColl(int nNldxColl)
{
	ZeroMemory(&m_data[nNldxColl], sizeof(m_data[nNldxColl]));
}

//-------------------------------------
//- �^�O�̑���𔻒�ݒ菈��
//-------------------------------------
void CCollision::UpdateData(int nNldxColl, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ݒ肵���^�O�̓����蔻��̗L����ݒ�
	m_data[nNldxColl].pos = pos;		// �ʒu
	m_data[nNldxColl].size = size;		// �T�C�Y
}

//-------------------------------------
//- �����蔻��̐ݒ菈��
//-------------------------------------
int CCollision::SetColl(TAG tag,TYPE type,D3DXVECTOR3 pos , D3DXVECTOR3 size,CObject *pObj)
{
	m_data[m_nNldxMax].tag = tag;		// �^�O
	m_data[m_nNldxMax].type = type;		// �����蔻����
	m_data[m_nNldxMax].pos = pos;		// �ʒu
	m_data[m_nNldxMax].size = size;		// �T�C�Y
	m_data[m_nNldxMax].pObj = pObj;		// �I�u�W�F�N�g���

	// �ԍ������Z
	m_nNldxMax++;

	// �ԍ���Ԃ�
	return m_nNldxMax - 1;
}

//-------------------------------------
//- �^�O�̑���𔻒�ݒ菈��
//-------------------------------------
void CCollision::SetHit(int nNldxColl,TAG hitTag,bool bIsActive)
{
	// �ݒ肵���^�O�̓����蔻��̗L����ݒ�
	m_data[nNldxColl].bHitTag[hitTag] = bIsActive;
}

//-------------------------------------
//- �^�O�̑���Ƃ̐ڐG���菈��
//-------------------------------------
bool CCollision::Hit(int nNldxColl, CCollision::TAG hitTag)
{
	for (int nCount = 0; nCount < m_data[nNldxColl].nHitNldxMax; nCount++)
	{
		if (m_data[nNldxColl].hitData[nCount].tag == hitTag)
		{
			// �I������
			m_data[nNldxColl].hitData[nCount].pObj->Uninit();

			return true;
		}
	}

	return false;
}

//-------------------------------------
//- �����蔻��̋�`�̓����蔻��
//-------------------------------------
bool CCollision::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- �����蔻��̉�]��`�̓����蔻��
//-------------------------------------
bool CCollision::hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair)
{
	if (rot.y >= 0.0f &&
		rot.y >= (D3DX_PI * 0.25f) &&
		rot.y <= (D3DX_PI * 0.75f))
	{
		float tenpSizeX = sizeMy.x;
		sizeMy.x = sizeMy.z;
		sizeMy.z = tenpSizeX;
	}
	else if (
		rot.y <= 0.0f &&
		rot.y <= (-D3DX_PI * 0.25f) &&
		rot.y >= (-D3DX_PI * 0.75f))
	{
		float tenpSizeX = sizeMy.x;
		sizeMy.x = sizeMy.z;
		sizeMy.z = tenpSizeX;
	}

	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- �����蔻��̕ӂ̓����蔻��
//-------------------------------------
bool CCollision::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}

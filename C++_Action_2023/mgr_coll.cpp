
//================================================
//=
//=	�����蔻��Ǘ��̏���[mgr_coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "mgr_coll.h"

#include "coll.h"

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
//-	�����蔻��Ǘ��̃R���X�g���N�^
//-------------------------------------
CMgrColl::CMgrColl()
{
	ZeroMemory(m_apColl, sizeof(m_apColl));
	m_nNldxMax = 0;
}

//-------------------------------------
//-	�����蔻��Ǘ��̃f�X�g���N�^
//-------------------------------------
CMgrColl::~CMgrColl()
{

}

//-------------------------------------
//- �����蔻��Ǘ��̏���������
//-------------------------------------
HRESULT CMgrColl::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- �����蔻��Ǘ��̏I������
//-------------------------------------
void CMgrColl::Uninit(void)
{

}

//-------------------------------------
//- �����蔻��Ǘ��̍X�V����
//-------------------------------------
void CMgrColl::Update(void)
{
	for (int nCountMy = 0; nCountMy < COLLSION_NUM_MAX; nCountMy++)
	{
		if (m_apColl[nCountMy] != NULL)
		{
			// �ϐ��錾
			CColl *pCollMy = m_apColl[nCountMy];	// ���g�̓����蔻����
			pCollMy->ResetHitData();				// �ڐG���̏�����

			for (int nCountPair = 0; nCountPair < COLLSION_NUM_MAX; nCountPair++)
			{
				if (m_apColl[nCountPair] != NULL)
				{
					CColl *pCollPair = m_apColl[nCountPair];			// ����̓����蔻����

					TAG tagTgt = pCollPair->GetData().tag;				// ����̃^�O���
					bool bTgt = pCollMy->GetData().abTagTgt[tagTgt];	// �^�O�̐ڐG�̗L��
					TYPE type = pCollMy->GetData().aType[tagTgt];		// ����Ƃ̐ڐG���

					// �����蔻��^�O�̔���
					if (bTgt == true)
					{
						// �ϐ��錾�i���擾�j
						D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// ���g�̈ʒu
						D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// ���g�̑傫��

						// �ϐ��錾 (����̏��擾)
						D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// ����̈ʒu
						D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// ����̑傫��

						// �ϐ��錾
						bool bIsHit = false;	// �ڐG�̗L��
					
						bool bIsHitX = false;	// X���̔���
						bool bIsHitY = false;	// Y���̔���
						bool bIsHitZ = false;	// Z���̔���

						switch (type)
						{

						case TYPE_RECTANGLE:

							// ��`�̓����蔻��
							if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
							{
								// �ڐG
								bIsHit = true;
							}

							break;

						case TYPE_RECTANGLE_SIDE:

							// ��`�̓����蔻��
							if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
							{
								// �ڐG
								bIsHit = true;
								
								// �ϐ��錾�i���g�̓����蔻��̏��擾�j
								CColl::Data data = pCollMy->GetData();

								// X���̓����蔻��
								data.abHitSxis[CColl::TYPE_SXIS_X] = hitRectangleSide(posMy.x, sizeMy.x, posPair.x, sizePair.x);
								data.abHitSxis[CColl::TYPE_SXIS_Y] = hitRectangleSide(posMy.y, sizeMy.y, posPair.y, sizePair.y);
								data.abHitSxis[CColl::TYPE_SXIS_Z] = hitRectangleSide(posMy.z, sizeMy.z, posPair.z, sizePair.z);

								// ���X�V�i���g�̓����蔻��j
								pCollMy->SetData(data);
							}

							break;
						}

						// �ڐG�̗L��
						if (bIsHit == true)
						{
							// �ڐG����̏��ݒ�
							CColl::HitData hitData;

							// ����̔ԍ�����
							hitData.nNldx = nCountPair;

							// �ڐG����̏���ݒ�
							pCollMy->SetHitData(hitData);
						}
					}
				}
			}
		}

	}
}

//-------------------------------------
//- �����蔻��Ǘ��̕`�揈��
//-------------------------------------
void CMgrColl::Draw(void)
{
}

//-------------------------------------
//- �����蔻��Ǘ��̐�������
//-------------------------------------
CMgrColl * CMgrColl::Create(void)
{
	// �����蔻��Ǘ��̐���
	CMgrColl *pCollision = DBG_NEW CMgrColl;

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

	// �����蔻��Ǘ��̃|�C���^��Ԃ�
	return pCollision;
}

//-------------------------------------
//- �����蔻��Ǘ��̃^�O�̑���Ƃ̐ڐG���菈��
//-------------------------------------
bool CMgrColl::Hit(int nNldxColl, CMgrColl::TAG hitTag, STATE_HIT stateHit)
{
	// �ϐ��錾
	CColl *pCollMy = m_apColl[nNldxColl];				// ���g�̓����蔻����
	int nHitNldxMax = pCollMy->GetData().nHitNldxMax;	// �ڐG�ő吔
	bool bHitTgt = false;								// �ړI�̐ڐG�̗L��

	for (int nCount = 0; nCount < nHitNldxMax; nCount++)
	{
		int hitNldx = pCollMy->GetData().hitData[nCount].nNldx;		// �ڐG����̔ԍ�
		CColl *pCollPair = m_apColl[hitNldx];						// �ڐG����̓����蔻����
		CColl::Data dataPair = m_apColl[hitNldx]->GetData();		// �ڐG����̏��
		TAG tagPair = dataPair.tag;									// �ڐG����̃^�O

		if (tagPair == hitTag)
		{
			if (pCollMy->GetData().aType[hitTag] == TYPE_RECTANGLE_SIDE)
			{
				// �ϐ��錾�i���擾�j
				D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// ���g�̈ʒu
				D3DXVECTOR3 posOldMy = pCollMy->GetData().posOld;	// ���g�̑O��̈ʒu
				D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// ���g�̑傫��

				// �ϐ��錾 (����̏��擾)
				D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// ����̈ʒu
				D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// ����̑傫��

				// ��`�̓����蔻��
				if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
				{
					// �ڐG
					bHitTgt = true;

					// �ϐ��錾�i���g�̓����蔻��̏��擾�j
					CColl::Data data = pCollMy->GetData();

					// X���̓����蔻��
					if (hitRectangleSide(posOldMy.y, sizeMy.y, posPair.y, sizePair.y))
					{
						data.abHitSxis[CColl::TYPE_SXIS_X] = hitRectangleSide(posMy.x, sizeMy.x, posPair.x, sizePair.x);
					}

					if (hitRectangleSide(posOldMy.x, sizeMy.x, posPair.x, sizePair.x))
					{
						data.abHitSxis[CColl::TYPE_SXIS_Y] = hitRectangleSide(posMy.y , sizeMy.y, posPair.y, sizePair.y);
					}

					data.abHitSxis[CColl::TYPE_SXIS_Z] = hitRectangleSide(posMy.z, sizeMy.z, posPair.z, sizePair.z);

					// ���X�V�i���g�̓����蔻��j
					pCollMy->SetData(data);
				}
			}
			else
			{
				// �ڐG�����ݒ�
				bHitTgt = true;

				// �ڐG��Ԃ���
				dataPair.stateHit = stateHit;

				// ���X�V�i�ڐG����j
				m_apColl[hitNldx]->SetData(dataPair);
			}
		}
	}

	return bHitTgt;
}

//-------------------------------------
//- �����蔻��Ǘ��̐ݒ菈��
//-------------------------------------
int CMgrColl::Set(CColl *pColl)
{
	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] == NULL)
		{
			m_apColl[nCount] = pColl;

			return nCount;
		}
	}

	return -1;
}

//-------------------------------------
//- �����蔻��Ǘ��̏������ݒ菈��
//-------------------------------------
void CMgrColl::Reset(int nNldx)
{
	m_apColl[nNldx] = NULL;
}

//-------------------------------------
//- �����蔻��Ǘ��̋�`�̓����蔻��
//-------------------------------------
bool CMgrColl::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.y + sizeMy.y >= posPair.y - sizePair.y &&
		posMy.y - sizeMy.y <= posPair.y + sizePair.y &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- �����蔻��Ǘ��̉�]��`�̓����蔻��
//-------------------------------------
bool CMgrColl::hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair)
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
//- �����蔻��Ǘ��̕ӂ̓����蔻��
//-------------------------------------
bool CMgrColl::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}
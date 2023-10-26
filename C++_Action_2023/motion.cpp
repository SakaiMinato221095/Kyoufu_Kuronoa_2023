
//-===============================================
//-
//-	���[�V�����̏���[motion.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "motion.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�R���X�g��`
//=======================================

// ���f���e�L�X�g�̃R���X�g��`
const char *pMotionText[] =
{
	"data\\TXT\\Motion\\MotionPlayerAonoa.txt",	// �v���C���[�i�A�I�m�A�j�̃��[�V�����t�@�C��
};

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	���[�V�����̃R���X�g���N�^
//-------------------------------------
CMotion::CMotion()
{
	memset(m_aInfo,NULL,sizeof(m_aInfo));

	m_bMotionUse = false;

	m_nNumState = 0;
	m_nNumAll = 0;
	m_nType = 0;
	m_bLoop = false;
	m_nNumKey = 0;
	m_nKey = 0;
	m_nCounter = 0;
	m_bFinish = false;

	m_bBlend = false;
	m_bChangeBlend = false;

	m_ppModel = NULL;
	m_nNumModel = 0;
}

//-------------------------------------
//-	���[�V�����̃f�X�g���N�^
//-------------------------------------
CMotion::~CMotion()
{

}

//-------------------------------------
//-	���[�V�����̏�����
//-------------------------------------
HRESULT CMotion::Init(int nNumModel, int nNumState)
{
	// ������
	m_nNumModel = nNumModel;	// ���f����
	m_nNumState = nNumState;	// �^�C�v

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	���[�V�����̏I������
//-------------------------------------
void CMotion::Uninit(void)
{

}

//-------------------------------------
//-	���[�V�����̐�������
//-------------------------------------
CMotion * CMotion::Create(int nNumModel, int nNumState)
{
	// �v���C���[�̃|�C���^��錾
	CMotion *pMotion = DBG_NEW CMotion;

	// �����̐����̗L���𔻒�
	if (pMotion != NULL)
	{
		// ����������
		if (FAILED(pMotion->Init(nNumModel, nNumState)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pMotion == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pMotion;
}

//-------------------------------------
//- ���[�V�����̐ݒ�
//-------------------------------------
void CMotion::Set(int nType)
{
	// ������
	m_nType = nType;
	m_nNumKey = m_aInfo[nType].nNumKey;
	m_bLoop = m_aInfo[nType].bLoop;

	// �L�[�������l�Őݒ�
	m_nKey = 0;
	m_nCounter = 0;

	m_bFinish = true;		// �I���̗L��

	// ���[�V�����̗L���𔻒�
	if (m_bMotionUse == false)
	{
		// ������
		m_bMotionUse = true;

		for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
		{
			// �L�[�̏����l�ňʒu��ݒ�
			m_ppModel[nCutModel]->GetData().posMotion =
				(D3DXVECTOR3(
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosX,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosY,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosZ));


			// �L�[�̏����l�Ō�����ݒ�
			m_ppModel[nCutModel]->GetData().rotMotion =
				(D3DXVECTOR3(
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotX,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotY,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotZ));
		}
	}
	else
	{
		// ������
		m_bChangeBlend = true;		// �؂�ւ��̃��[�V�����u�����h�̗L��

		for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
		{
			D3DXVECTOR3 motionPos = m_ppModel[nCutModel]->GetData().posMotion;
			D3DXVECTOR3 motionRot = m_ppModel[nCutModel]->GetData().rotMotion;

			m_motionPosOld[nCutModel] = motionPos;
			m_motionRotOld[nCutModel] = motionRot;
		}
	}
}

//-------------------------------------
//- ���[�V�����̐ݒ�
//-------------------------------------
void CMotion::BlendSet(void)
{
	// �L�[�������l�Őݒ�
	m_nKey = 0;
	m_nCounter = 0;

	m_bFinish = true;		// �I���̗L��

	// ���[�V�����u�����h�̗L����ݒ�
	m_bBlend = true;

	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		D3DXVECTOR3 motionPos = m_ppModel[nCutModel]->GetData().posMotion;
		D3DXVECTOR3 motionRot = m_ppModel[nCutModel]->GetData().rotMotion;

		m_motionPosOld[nCutModel] = motionPos;
		m_motionRotOld[nCutModel] = motionRot;
	}
}

//-------------------------------------
//- ���[�V�����̍X�V����
//-------------------------------------
void CMotion::Update(void)
{
	// ���[�V�����u�����h�̗L���𔻒�
	if (m_bBlend == true)
	{
		// ���[�V�����u�����h�̃��[�V�����̍X�V
		UpdateBlend();
	}
	else if(m_bChangeBlend == true)
	{
		// ���[�V�����u�����h�̃��[�V�����̍X�V
		UpdateChangeBlend();
	}
	else
	{
		// �ʏ�̃��[�V�����̍X�V
		UpdateNormal();
	}
}

//-------------------------------------
//- ���[�V�����̎�ގ擾����
//-------------------------------------
int CMotion::GetType(void)
{
	return m_nType;
}

//-------------------------------------
//- ���[�V�����̏I���̗L�����擾����
//-------------------------------------
bool CMotion::IsFinsih(void)
{
	return m_bFinish;
}

//-------------------------------------
//- ���[�V�����̃L�[���̎擾����
//-------------------------------------
int CMotion::GetKey(void)
{
	return m_nKey;
}

//-------------------------------------
//- ���[�V�����̃L�[���ݒ菈��
//-------------------------------------
void CMotion::SetInfo(Info info)
{
	m_aInfo[m_nType] = info;
}

//-------------------------------------
//- ���[�V�����̃��f���ݒ菈��
//-------------------------------------
void CMotion::SetModel(CModel **ppModel, int nNumModel)
{
	m_ppModel = &ppModel[nNumModel];
}

//-------------------------------------
//- ���[�V�����̃��f���ݒ菈��
//-------------------------------------
void CMotion::SetFile(MOTION_TYPE MotionType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pMotionText[MotionType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{// �t�@�C�����J����Ƃ�

		// �ϐ��錾
		char aFileData[256] = { 0 };	// �t�@�C���̕��͂��i�[
		int nMotion = -1;
		int nKey = -1;
		int nModel = -1;

		while (true)
		{
			// �������ǂݍ���
			fgets(aFileData, 256, pFile);

			for (int nCount = 0; nCount < 256; nCount++)
			{
				// �R�����g�𔻒�
				if (aFileData[nCount] == '#')
				{
					// �R�����g������
					memset(&aFileData[nCount], NULL, sizeof(256 - nCount));
					break;
				}
			}

			// ���[�V�����̐��𑝂₷
			if (strstr(aFileData, "MOTIONSET") != NULL)
			{
				// �ϐ��錾
				char aTenp[256] = {};	// �S�~����	

				// ���l�����o��
				sscanf(aFileData, "%s", aTenp);

				// �L�[�̔���
				if (strcmp(aTenp, "MOTIONSET") == 0)
				{
					nMotion++;

					nKey = -1;
					nModel = -1;
				}
			}

			// ���[�v�̐ݒ�𔻒�
			if (strstr(aFileData, "LOOP") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					int nValue = 0;				// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ���[�v�̔���
					if (nValue == 1)
					{
						// ���[�v���I��
						m_aInfo[nMotion].bLoop = true;
					}
					else
					{
						// ���[�v���I�t
						m_aInfo[nMotion].bLoop = false;
					}
				}
			}


			// �L�[���ݒ�𔻒�
			if (strstr(aFileData, "NUM_KEY") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					int nValue = 0;				// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// �L�[����ݒ�
					m_aInfo[nMotion].nNumKey = nValue;

				}
			}

			// �L�[�ݒ�𔻒�
			if (strstr(aFileData, "KEYSET") != NULL)
			{
				// �ϐ��錾
				char aTenp[256] = {};	// �S�~����	

				// ���l�����o��
				sscanf(aFileData, "%s", aTenp);

				// �L�[�̔���
				if (strcmp(aTenp, "KEYSET") == 0)
				{
					nKey++;

					nModel = -1;
				}
			}

			// �t���[���ݒ�𔻒�
			if (strstr(aFileData, "FRAME") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					int nValue = 0;				// ���l

					// ���l�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// �L�[����ݒ�
					m_aInfo[nMotion].aKeyInfo[nKey].nFrame = nValue;

				}
			}

			// �L�[�̔���
			if (strstr(aFileData, "KEY") != NULL)
			{
				// �ϐ��錾
				char aTenp[256] = {};	// �S�~����	
				
				// ���l�����o��
				sscanf(aFileData, "%s", aTenp);

				// �L�[�̔���
				if (strcmp(aTenp,"KEY") == 0)
				{
					nModel++;
				}

			}

			// �ʒu���̔���
			if (strstr(aFileData, "POS") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					float fPosX = 0;			// �ʒu�iX�j
					float fPosY = 0;			// �ʒu�iY�j
					float fPosZ = 0;			// �ʒu�iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fPosX, &fPosY, &fPosZ);

					// �ʒu�����X�V
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fPosX = fPosX;
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fPosY = fPosY;
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fRotZ = fPosZ;
				}
			}

			// �������̔���
			if (strstr(aFileData, "ROT") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][256] = {};	// �S�~����	
					float fRotX = 0;			// �����iX�j
					float fRotY = 0;			// �����iY�j
					float fRotZ = 0;			// �����iZ�j

					// ���l�����o��
					sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fRotX, &fRotY, &fRotZ);

					// ���������X�V
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fRotX = fRotX;
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fRotY = fRotY;
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fRotZ = fRotZ;

				}
			}

			if (strstr(aFileData, "END_SCRIPT") != NULL)
			{
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{

	}
}

//-------------------------------------
//- ���[�V�����̃u�����h�̗L���̎擾����
//-------------------------------------
bool CMotion::GetBlend(void)
{
	return m_bBlend;
}

//-------------------------------------
//- ���[�V�����̐؂�ւ��u�����h�̗L���̎擾����
//-------------------------------------
bool CMotion::GetChangeBlend(void)
{
	return m_bChangeBlend;
}

//-------------------------------------
//- ���[�V�����̒ʏ펞�̍X�V����
//-------------------------------------
void CMotion::UpdateNormal(void)
{
	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		// ���݂̃L�[�̈ʒu�ƌ���
		float fPosX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosX;
		float fPosY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosY;
		float fPosZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosZ;
		float fRotX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotX;
		float fRotY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotY;
		float fRotZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotZ;

		// ���̃L�[�̈ʒu�ƌ���
		float fNextPosX;
		float fNextPosY;
		float fNextPosZ;
		float fNextRotX;
		float fNextRotY;
		float fNextRotZ;

		if (m_nNumKey != m_nKey + 1)
		{
			// ���̃L�[�̈ʒu�ƌ���
			fNextPosX = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fPosX;
			fNextPosY = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fPosY;
			fNextPosZ = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fPosZ;
			fNextRotX = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fRotX;
			fNextRotY = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fRotY;
			fNextRotZ = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fRotZ;
		}
		else
		{
			// �Ō�̃L�[�̂Ƃ��̎��̃L�[�̈ʒu�ƌ���
			fNextPosX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosX;
			fNextPosY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosY;
			fNextPosZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosZ;
			fNextRotX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotX;
			fNextRotY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotY;
			fNextRotZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotZ;
		}

		// �����̈ʒu�ƌ���
		float fDiffPosX = fNextPosX - fPosX;
		float fDiffPosY = fNextPosY - fPosY;
		float fDiffPosZ = fNextPosZ - fPosZ;
		float fDiffRotX = fNextRotX - fRotX;
		float fDiffRotY = fNextRotY - fRotY;
		float fDiffRotZ = fNextRotZ - fRotZ;

		// �ϐ��錾�i�p�[�c���Ƃ̃��f�����̎擾�j
		CModel::Data modelData = m_ppModel[nCutModel]->GetData();

		// �ړI�̈ʒu��ݒ�
		modelData.posMotion = D3DXVECTOR3(
			(fPosX + fDiffPosX * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fPosY + fDiffPosY * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fPosZ + fDiffPosZ * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)));

		// �ړI�̌�����ݒ�
		modelData.rotMotion = (D3DXVECTOR3(
			(fRotX + fDiffRotX * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fRotY + fDiffRotY * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fRotZ + fDiffRotZ * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame))));

		// ���X�V�i�i�p�[�c���Ƃ̃��f�����̎擾�j
		m_ppModel[nCutModel]->SetData(modelData);
	}

	// �J�E���^�[��i�߂�
	m_nCounter++;

	// �L�[��i�߂锻��
	if (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame == 0)
	{// �J�E���^�[�ƍĐ��t���[��������

		// �J�E���^�[��������
		m_nCounter = 0;

		// �L�[��i�߂�
		m_nKey++;

		if (m_nNumKey == m_nKey)
		{// �L�[�̑����ƌ��݂̃L�[������

		 // ���[�v�̗L�����m�F
			if (m_aInfo[m_nType].bLoop == true)
			{
				// �L�[�̏�����
				m_nKey = 0;
			}
			else
			{
				// �I�����I��
				m_bFinish = false;
			}
		}
	}
}

//-------------------------------------
//- ���[�V�����̐؂�ւ����̃��[�V�����u�����h�̍X�V����
//-------------------------------------
void CMotion::UpdateChangeBlend(void)
{
	// �t���[�������擾
	int nFrame = 15;

	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		// �O��̏����擾
		D3DXVECTOR3 motionPosOld = m_motionPosOld[nCutModel];
		D3DXVECTOR3 motionRotOld = m_motionRotOld[nCutModel];
		
		// ���݂̃��[�V�����̈ʒu
		float fPosX = motionPosOld.x;
		float fPosY = motionPosOld.y;
		float fPosZ = motionPosOld.z;
		float fRotX = motionRotOld.x;
		float fRotY = motionRotOld.y;
		float fRotZ = motionRotOld.z;

		// ���̃L�[�̈ʒu�ƌ���
		float fNextPosX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosX;
		float fNextPosY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosY;
		float fNextPosZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosZ;
		float fNextRotX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotX;
		float fNextRotY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotY;
		float fNextRotZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotZ;

		// �����̈ʒu�ƌ���
		float fDiffPosX = fNextPosX - fPosX;
		float fDiffPosY = fNextPosY - fPosY;
		float fDiffPosZ = fNextPosZ - fPosZ;
		float fDiffRotX = fNextRotX - fRotX;
		float fDiffRotY = fNextRotY - fRotY;
		float fDiffRotZ = fNextRotZ - fRotZ;

		// �ϐ��錾�i�p�[�c���Ƃ̃��f�����̎擾�j
		CModel::Data modelData = m_ppModel[nCutModel]->GetData();

		// ���Ԕ{���̌v�Z
		modelData.posMotion = D3DXVECTOR3(
			(fPosX + (fDiffPosX * ((float)m_nCounter / (float)nFrame))),
			(fPosY + (fDiffPosY * ((float)m_nCounter / (float)nFrame))),
			(fPosZ + (fDiffPosZ * ((float)m_nCounter / (float)nFrame))));

		// ���Ԕ{���̌v�Z
		modelData.rotMotion = D3DXVECTOR3(
			(fRotX + (fDiffRotX * ((float)m_nCounter / (float)nFrame))),
			(fRotY + (fDiffRotY * ((float)m_nCounter / (float)nFrame))),
			(fRotZ + (fDiffRotZ * ((float)m_nCounter / (float)nFrame))));

		// ���X�V�i�i�p�[�c���Ƃ̃��f�����̎擾�j
		m_ppModel[nCutModel]->SetData(modelData);


	}

	// �J�E���^�[��i�߂�
	m_nCounter++;

	// �L�[��i�߂锻��
	if (m_nCounter % nFrame == 0)
	{// �J�E���^�[�ƍĐ��t���[��������

		// �J�E���^�[��������
		m_nCounter = 0;

		// ���݂̃L�[����������
		m_bChangeBlend = false;
	}
}

//-------------------------------------
//- ���[�V�����̃��[�V�����u�����h�̍X�V����
//-------------------------------------
void CMotion::UpdateBlend(void)
{
	// �t���[�������擾
	int nFrame = 10;

	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		// �O��̏����擾
		D3DXVECTOR3 motionPosOld = m_motionPosOld[nCutModel];
		D3DXVECTOR3 motionRotOld = m_motionRotOld[nCutModel];

		// ���݂̃��[�V�����̈ʒu
		float fPosX = motionPosOld.x;
		float fPosY = motionPosOld.y;
		float fPosZ = motionPosOld.z;
		float fRotX = motionRotOld.x;
		float fRotY = motionRotOld.y;
		float fRotZ = motionRotOld.z;

		// ���̃L�[�̈ʒu�ƌ���
		float fNextPosX = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fPosX;
		float fNextPosY = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fPosY;
		float fNextPosZ = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fPosZ;
		float fNextRotX = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fRotX;
		float fNextRotY = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fRotY;
		float fNextRotZ = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fRotZ;

		// �����̈ʒu�ƌ���
		float fDiffPosX = fNextPosX - fPosX;
		float fDiffPosY = fNextPosY - fPosY;
		float fDiffPosZ = fNextPosZ - fPosZ;
		float fDiffRotX = fNextRotX - fRotX;
		float fDiffRotY = fNextRotY - fRotY;
		float fDiffRotZ = fNextRotZ - fRotZ;

		// �ϐ��錾�i�p�[�c���Ƃ̃��f�����̎擾�j
		CModel::Data modelData = m_ppModel[nCutModel]->GetData();

		// ���Ԕ{���̌v�Z
		modelData.posMotion = D3DXVECTOR3(
			(fPosX + (fDiffPosX * ((float)m_nCounter / (float)nFrame))),
			(fPosY + (fDiffPosY * ((float)m_nCounter / (float)nFrame))),
			(fPosZ + (fDiffPosZ * ((float)m_nCounter / (float)nFrame))));

		// ���Ԕ{���̌v�Z
		modelData.rotMotion = D3DXVECTOR3(
			(fRotX + (fDiffRotX * ((float)m_nCounter / (float)nFrame))),
			(fRotY + (fDiffRotY * ((float)m_nCounter / (float)nFrame))),
			(fRotZ + (fDiffRotZ * ((float)m_nCounter / (float)nFrame))));

		// ���X�V�i�i�p�[�c���Ƃ̃��f�����̎擾�j
		m_ppModel[nCutModel]->SetData(modelData);
	}

	// �J�E���^�[��i�߂�
	m_nCounter++;

	// �L�[��i�߂锻��
	if (m_nCounter % nFrame == 0)
	{// �J�E���^�[�ƍĐ��t���[��������

		// �L�[�����ˌ���ԂɕύX
		m_nKey = 1;

		// �J�E���^�[��������
		m_nCounter = 0;

		// ���݂̃L�[����������
		m_bBlend = false;
	}
}
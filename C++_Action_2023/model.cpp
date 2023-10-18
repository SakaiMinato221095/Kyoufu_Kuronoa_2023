
//================================================
//=
//= �K�w�\���̃��f������[model.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "model.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "manager_texture.h"

//=======================================
//=	�R���X�g��`
//=======================================

// ���f���e�L�X�g�̃R���X�g��`
const char *pModelText[] =
{
	"data\\TXT\\Model\\Player.txt",	// �v���C���[�̃��f���t�@�C��
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

CModel::Model CModel::m_model[MODEL_NUM_MAX] = {};
int CModel::m_nModelNldx[MODEL_TYPE_MAX][MODEL_PARTS_MAX] = {};

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̃R���X�g���N�^
//-------------------------------------
CModel::CModel()
{
	// �l���N���A
	m_pParent = NULL;

	m_modelType = (MODEL_TYPE)0;
	m_nPartsNum = -1;

	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̃f�X�g���N�^
//-------------------------------------
CModel::~CModel()
{
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̓ǂݍ��ݏ���
//-------------------------------------
HRESULT CModel::Load(void)
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

	// �e�N�X�`���ݒ�
	for (int nCutModel = 0; nCutModel < MODEL_TYPE_MAX; nCutModel++)
	{
		// ���f���̓ǂݍ���
		SetFile((MODEL_TYPE)nCutModel);

		for (int nCntParts = 0; nCntParts < m_model[nCutModel].nPartsNum; nCntParts++)
		{
			// ���f���ԍ��̎擾�i���f���̊����j
			int nModelNldx = pManagerModel->Regist(m_model[nCutModel].modelParts[nCntParts].aFileName);

			// ���f���̓ǂݍ��ݐ����̗L�����m�F
			if (nModelNldx == -1)
			{
				// ���s���ɏ����������𔲂���
				return E_FAIL;
			}

			// ���f���ԍ���ݒ�
			m_nModelNldx[nCutModel][nCntParts] = nModelNldx;
		}
	}

	return S_OK;
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̏���������
//-------------------------------------
HRESULT CModel::Init(MODEL_TYPE modelType , int nCount)
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
	int nModelNldx = m_nModelNldx[modelType][nCount];
	m_modelType = modelType;
	m_nPartsNum = nCount;

	// ����ݒ�
	m_data.pos = m_model[modelType].modelParts[nCount].pos;	// �ʒu
	m_data.rot = m_model[modelType].modelParts[nCount].rot;	// ����

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̏I������
//-------------------------------------
void CModel::Uninit(void)
{
	// �e�̃|�C���^����������
	if (m_pParent != NULL)
	{
		m_pParent = NULL;
	}
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̍X�V����
//-------------------------------------
void CModel::Update(void)
{

}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̕`�揈��
//-------------------------------------
void CModel::Draw(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

	 // �����������𔲂���
		return;
	}

	// ���f���Ǘ��̐���
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// ���f���Ǘ��̗L���𔻒�
	if (pManagerModel == NULL)
	{
		// �����������𔲂���
		return;
	}

	// ���f���ԍ����擾
	int nModelNldx = m_nModelNldx[m_modelType][m_nPartsNum];

	// ���f�������擾
	CManagerModel::Model model = pManagerModel->GetAddress(nModelNldx);

	// ���f���̗L���𔻒�
	if (model.m_pMesh == NULL)
	{
		// �`�揈���𔲂���
		return;
	}

	// �ϐ��錾�i���擾�j
	D3DXVECTOR3 pos = m_data.pos + m_data.posMotion;	// �ʒu���
	D3DXVECTOR3 rot = m_data.rot + m_data.rotMotion;	// �������
		
	// �ϐ��錾
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̌v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	//�p�[�c�́u�e�}�g���b�N�X�v��ݒ�
	if (m_pParent != NULL)
	{//�e���f��������ꍇ

		// �e�̃}�g���b�N�X����
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//�e���f�����Ȃ��ꍇ

		//�v���C���[�̃}�g���b�N�X��ݒ�
		pDevice->GetTransform(D3DTS_WORLD,&mtxParent);
	}

	//�Z�o�����p�[�c�̃}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// ���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���̃|�C���^���擾
	pMat = (D3DXMATERIAL*)model.m_pBuffMat->GetBufferPointer();
	
	// �}�e���A�����Ƃ̕`��
	for (int nCutMat = 0; nCutMat < (int)model.m_dwNumMat; nCutMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		// �e�N�X�`���̐ݒ�i���j
		pDevice->SetTexture(0, model.m_pTexture[nCutMat]);

		// �K�w�\����X�t�@�C���I�u�W�F�N�g�i�p�[�c�j�̕`��
		model.m_pMesh->DrawSubset(nCutMat);
	}

	// �ۑ����Ă����}�e���A���ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̐�������
//-------------------------------------
CModel *CModel::Create(MODEL_TYPE modelType, int nCount)
{
	// �K�w�\����X�t�@�C���I�u�W�F�N�g�̃|�C���^��錾
	CModel *pObjectX = DBG_NEW CModel;

	// �����̐����̗L���𔻒�
	if (pObjectX != NULL)
	{
		// ����������
		if (FAILED(pObjectX->Init(modelType,nCount)))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pObjectX == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �K�w�\����X�t�@�C���I�u�W�F�N�g�̃|�C���^��Ԃ�
	return pObjectX;
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̐e�q�֌W�ݒ菈��
//-------------------------------------
void CModel::SetParent(CModel **pObjectModel, MODEL_TYPE modelType,int nCount)
{
	// �e�̔ԍ����擾
	int nParent = m_model[modelType].modelParts[nCount].nParent;

	if (nParent != -1)
	{
		// �e�̃��f��������
		m_pParent = pObjectModel[nParent];
	}
	else
	{
		m_pParent = NULL;
	}
}

//-------------------------------------
//-	�K�w�\����X�t�@�C���I�u�W�F�N�g�̃��[���h�}�g���b�N�X�擾����
//-------------------------------------
D3DXMATRIX CModel::GetMtxWorld(void)
{
	// ���[���h�}�g���b�N�X��Ԃ�
	return m_mtxWorld;
}

//-------------------------------------
//- �K�w�\���̃��f���擾����
//-------------------------------------
void CModel::SetData(CModel::Data data)
{
	m_data = data;
}

//-------------------------------------
//- �K�w�\���̃��f���擾����
//-------------------------------------
CModel::Data CModel::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- �K�w�\����X�t�@�C���I�u�W�F�N�g�̃��f���ݒ菈��
//-------------------------------------
void CModel::SetFile(MODEL_TYPE modelType)
{
	//�ϐ��錾
	FILE *pFile;	// �t�@�C���̃|�C���^

	// �t�@�C���̏�����
	pFile = fopen(pModelText[modelType], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{// �t�@�C�����J����Ƃ�

		// �ϐ��錾
		char aFileData[256] = {};		// �t�@�C���̕��͂��i�[

		int nFileNameCount = -1;		// �t�@�C���̖��O�̃J�E���g 
		int nIndex = -1;				// �p�[�c�����i�[

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

			// ���f���̃p�[�c����ݒ�
			if (strstr(aFileData, "NUM_MODEL") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				int nPartsNum = 0;			// �p�[�c��

				// �p�[�c�������o��
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nPartsNum);

				// �p�[�c������
				m_model[modelType].nPartsNum = nPartsNum;
			}

			// �p�[�c�̃t�@�C������ݒ�
			if (strstr(aFileData, "MODEL_FILENAME") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				char aFileName[256] = {};	// �t�@�C���̖��O���i�[

				// �p�[�c�J�E���g��i�߂�
				nFileNameCount++;

				// �t�@�C���̖��O�����o��
				sscanf(aFileData, "%s %s %s", aTenp[0], aTenp[1], aFileName);

				// �t�@�C���̖��O����
				strcpy(m_model[modelType].modelParts[nFileNameCount].aFileName, aFileName);
			}

			// �p�[�c�ԍ��̐ݒ�
			if (strstr(aFileData, "INDEX") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	

				// �p�[�c�̔ԍ������o��
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nIndex);

				// �p�[�c�̔ԍ�����
				m_model[modelType].modelParts[nIndex].nIndex = nIndex;
			}

			// �e�̐ݒ�
			if (strstr(aFileData, "PARENT") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				int nParent = -1;

				// �e�̔ԍ������o��
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nParent);

				// �e�̔ԍ�����
				m_model[modelType].modelParts[nIndex].nParent = nParent;
			}

			// �ʒu���̐ݒ�
			if (strstr(aFileData, "POS") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				float fPosX = 0;			// �ʒu�iX�j
				float fPosY = 0;			// �ʒu�iY�j
				float fPosZ = 0;			// �ʒu�iZ�j

				// �ʒu�����o��
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fPosX, &fPosY, &fPosZ);

				// �ʒu����
				m_model[modelType].modelParts[nIndex].pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			}

			// �������̐ݒ�
			if (strstr(aFileData, "ROT") != NULL)
			{
				// �ϐ��錾
				char aTenp[2][256] = {};	// �S�~����	
				float fRotX = 0;			// �����iX�j
				float fRotY = 0;			// �����iY�j
				float fRotZ = 0;			// �����iZ�j

				// ���������o��
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fRotX, &fRotY, &fRotZ);

				// ��������
				m_model[modelType].modelParts[nIndex].rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
			}

			// �I��
			if (strstr(aFileData, "END_CHARACTERSET") != NULL)
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
//- �K�w�\����X�t�@�C���I�u�W�F�N�g�̃��f���ݒ菈��
//-------------------------------------
int CModel::GetPartsNum(MODEL_TYPE modelType)
{
	// �p�[�c����Ԃ�
	return m_model[modelType].nPartsNum;
}
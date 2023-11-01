
//================================================
//=
//=	�}�b�v�t�@�C���̏���[file_map.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "file_map.h"

#include "edit_map.h"

#include "obj_block.h"
#include "goal.h"
#include "enemy.h"
#include "gimmick_jewel.h"
#include "obj_teach.h"

//=======================================
//=	�}�N����`
//=======================================

#define ARRAY_SIZE	(128)		// �z��̃T�C�Y

//=======================================
//= �R���X�g��`
//=======================================

// �}�b�v�̃e�L�X�g�̃R���X�g��`
const char *pTextMap[] =
{
	"data\\TXT\\Map\\MapNormal.txt",	//	�ʏ�}�b�v�̃e�L�X�g
	"data\\TXT\\Map\\MapTitle.txt",		//	�^�C�g���}�b�v�̃e�L�X�g
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CFileMap::CFileMap()
{
	ZeroMemory(m_aMapData, sizeof(m_aMapData));
	m_nNumMax = 0;
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CFileMap::~CFileMap()
{

}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏���������
//-------------------------------------
HRESULT CFileMap::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̏I������
//-------------------------------------
void CFileMap::Uninit(void)
{
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̍X�V����
//-------------------------------------
void CFileMap::Update(void)
{
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̕`�揈��
//-------------------------------------
void CFileMap::Draw(void)
{
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̐�������
//-------------------------------------
CFileMap * CFileMap::Create(void)
{
	// ��������
	CFileMap *pFileMap = DBG_NEW CFileMap;

	// �����̐����̗L���𔻒�
	if (pFileMap != NULL)
	{
		// ����������
		if (FAILED(pFileMap->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pFileMap == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �|�C���^��Ԃ�
	return pFileMap;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃Z�[�u����
//-------------------------------------
void CFileMap::Save(void)
{
	// �t�@�C�����J���i�����o���j
	FILE *pFile = fopen(pTextMap[TEXT_NORMAL], "w");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// ���o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [�}�b�v] \n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		// ���f�����̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [�ő僂�f����] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "%d\n", m_nNumMax);
		fprintf(pFile, "\n");

		// �z�u�󋵌��o���̏����o��
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [�z�u���] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		for (int nCount = 0; nCount < m_nNumMax; nCount++)
		{
			// �ϐ��錾�i�G�̏��擾�j
			int nModelType = m_aMapData[nCount].type;				// ���f�����
			D3DXVECTOR3 pos = m_aMapData[nCount].pos;				// �ʒu
			int nTileLineNum = m_aMapData[nCount].nTileLineNum;		// �s�^�C���ԍ�
			int nTileCuluNum = m_aMapData[nCount].nTileCiluNum;		// ��^�C���ԍ�

			// �z�u���f���̏��̏����o��
			fprintf(pFile, "MODEL_TYPE = %d\n", nModelType);
			fprintf(pFile, " --- POS = %3.1f %3.1f %3.1f \n", pos.x, pos.y, pos.z);
			fprintf(pFile, " --- TILE_LINE_NUM = %d \n", nTileLineNum);
			fprintf(pFile, " --- TILE_CULU_NUM = %d \n", nTileCuluNum);
			fprintf(pFile, "END_MODEL_SET \n");
			fprintf(pFile, "\n");
		}

		// �����o���̏I��
		fprintf(pFile, "SET_END");
	}

	// �t�@�C�������
	fclose(pFile);
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃��[�h����
//-------------------------------------
void CFileMap::Load(TEXT text)
{
	// �t�@�C�����J���i�ǂݍ��݁j
	FILE *pFile = fopen(pTextMap[text], "r");

	// �t�@�C���̗L���𔻒�
	if (pFile != NULL)
	{
		// �ϐ��錾
		char aFileData[ARRAY_SIZE] = { 0 };		// �t�@�C���̕��͂��i�[
		CEditMap::EditData editMap = {};		// �}�b�v�f�[�^

		while (true)
		{
			// �������ǂݍ���
			fgets(aFileData, ARRAY_SIZE, pFile);

			// ���������ǂݍ���
			for (int nCount = 0; nCount < ARRAY_SIZE; nCount++)
			{
				// �R�����g�𔻒�
				if (aFileData[nCount] == '#')
				{
					// �R�����g������
					memset(&aFileData[nCount], NULL, sizeof(ARRAY_SIZE - nCount));
					break;
				}
			}

			if (strstr(aFileData, "MODEL") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// �l�i���f���ԍ��j�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ��ނ��i�[
					editMap.type = (CEditMap::TYPE)nValue;
				}
			}

			if (strstr(aFileData, "POS") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[3][ARRAY_SIZE] = {};	// �S�~����	
					float fPosX = 0;				// �ʒu�iX�j
					float fPosY = 0;				// �ʒu�iY�j
					float fPosZ = 0;				// �ʒu�iZ�j

					// �l�i�ʒu�j�����o��
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// �ʒu���i�[
					editMap.pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
				}
			}

			if (strstr(aFileData, "TILE_LINE_NUM") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// �l�i���f���ԍ��j�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ��ނ��i�[
					editMap.nTileLineNum = (CEditMap::TYPE)nValue;
				}
			}

			if (strstr(aFileData, "TILE_CULU_NUM") != NULL)
			{
				// ����̕����𔻒�
				if (strstr(aFileData, "=") != NULL)
				{
					// �ϐ��錾
					char aTenp[2][ARRAY_SIZE] = {};	// �S�~����	
					int nValue = 0;					// ���l

					// �l�i���f���ԍ��j�����o��
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ��ނ��i�[
					editMap.nTileCiluNum = (CEditMap::TYPE)nValue;
				}
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// �I�u�W�F�N�g�̃|�C���^��������
				SetMapObj(editMap);
			}

			// ���f���ݒ�̏I��
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// �t�@�C�������
		fclose(pFile);
	}
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃I�u�W�F�N�g�ݒ菈��
//-------------------------------------
bool CFileMap::SetObj(CEditMap::EditData editData)
{
	bool bIsUse = false;

	if (editData.pObjX != NULL)
	{
		for (int nCount = m_nNumMax; nCount < MAP_OBJ_MAX; nCount++)
		{
			if (m_aMapData[nCount].pObjX == NULL)
			{
				m_aMapData[nCount] = editData;

				bIsUse = true;

				m_nNumMax++;

				break;
			}
		}
	}
	else if (editData.pObjBill != NULL)
	{
		for (int nCount = m_nNumMax; nCount < MAP_OBJ_MAX; nCount++)
		{
			if (m_aMapData[nCount].pObjBill == NULL)
			{
				m_aMapData[nCount] = editData;

				bIsUse = true;

				m_nNumMax++;

				break;
			}
		}
	}

	return bIsUse;
}

//-------------------------------------
//- �}�b�v�G�f�B�^�̃I�u�W�F�N�g�ݒ菈��
//-------------------------------------
void CFileMap::SetMapObj(CEditMap::EditData editData)
{
	CObjectX *pObjX = NULL;
	CObjectBillboard *pObjBill = NULL;

	switch (editData.type)
	{
	case CEditMap::TYPE_BLOCK:

		// �u���b�N�̐���
		pObjX = CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_GOAL:

		// �S�[���̐���
		pObjX = CGoal::Create(
			CGoal::MODEL_GOAL_000,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_PLAYER:

		break;

	case CEditMap::TYPE_ENEMY:

		// �G�̐���
		pObjX = CEnemy::Create(
			CEnemy::MODEL_ALIEN_000,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_GIMMICK_SPEED:

		// ���x��΃M�~�b�N�̐���
		pObjX = CGimmickJewel::Create(
			CGimmickJewel::MODEL_JEWEL_000,
			CGimmickJewel::TYPE_EFFECT_SPEED_UP,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_TEACH_MOVE:

		pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_MOVE,
			D3DXVECTOR3(editData.pos.x, editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case CEditMap::TYPE_TEACH_JUMP:

		pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_JUMP,
			D3DXVECTOR3(editData.pos.x, editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case CEditMap::TYPE_TEACH_KAZEDAMA:

		pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_KAZEDAMA,
			D3DXVECTOR3(editData.pos.x, editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case CEditMap::TYPE_TEACH_SHOT:

		pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_SHOT,
			D3DXVECTOR3(editData.pos.x, editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case CEditMap::TYPE_TEACH_DOUBLE_JUMP:

		pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_DOUBLE_JUMP,
			D3DXVECTOR3(editData.pos.x, editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	}

	if (pObjX != NULL)
	{
		for (int nCount = m_nNumMax; nCount < MAP_OBJ_MAX; nCount++)
		{
			if (m_aMapData[nCount].pObjX == NULL)
			{
				m_aMapData[nCount] = editData;
				m_aMapData[nCount].pObjX = pObjX;

				m_nNumMax++;

				break;
			}
		}
	}
	else if (pObjBill != NULL)
	{
		for (int nCount = m_nNumMax; nCount < MAP_OBJ_MAX; nCount++)
		{
			if (m_aMapData[nCount].pObjBill == NULL)
			{
				m_aMapData[nCount] = editData;
				m_aMapData[nCount].pObjBill = pObjBill;

				m_nNumMax++;

				break;
			}
		}
	}
}
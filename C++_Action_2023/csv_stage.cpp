
//================================================
//=
//=	�X�e�[�WCSV����[csv_stage.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "csv_stage.h"

#include "obj_block.h"
#include "goal.h"
#include "enemy.h"
#include "gimmick_jewel.h"

//=======================================
//=	�}�N����`
//=======================================

#define SIZE_TILE_CRITERIA_X	(150.0f)		// ��}�X�̊�iX���j
#define SIZE_TILE_CRITERIA_Y	(150.0f)		// ��}�X�̊�iY���j

//=======================================
//= �R���X�g��`
//=======================================

// �X�e�[�WCSV�̃e�L�X�g�̃R���X�g��`
const char *pCsvStage[] =
{
	"data\\CSV\\Stage\\stage_000.csv"		// �ʏ�G_000�̃e�L�X�g
};

// �X�e�[�WCSV�̎�ރe�L�X�g�̃R���X�g��`
const char *pCsvStageText[] =
{
	"0",	// ���ʂȂ��̃e�L�X�g
	"1",	// �ǂ̃e�L�X�g
	"B",	// �u���b�N�̃e�L�X�g
	"T0",	// �`���[�g���A��_000�̃e�L�X�g
	"T1",	// �`���[�g���A��_001�̃e�L�X�g
	"T2",	// �`���[�g���A��_002�̃e�L�X�g
	"GG",	// �S�[���̃e�L�X�g
	"P",	// �v���C���[�̃e�L�X�g
	"E",	// �G�̃e�L�X�g
	"GS",	// ���xUP�M�~�b�N�̃e�L�X�g
};

//=======================================
//=	�ÓI�ϐ��錾
//=======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CCsvStage::CCsvStage()
{
	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(&m_acCsvData, sizeof(m_acCsvData));
}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CCsvStage::~CCsvStage()
{

}

//-------------------------------------
//- CSV�X�e�[�W�̏���������
//-------------------------------------
HRESULT CCsvStage::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- CSV�X�e�[�W�̏I������
//-------------------------------------
void CCsvStage::Uninit(void)
{
}

//-------------------------------------
//- CSV�X�e�[�W�̍X�V����
//-------------------------------------
void CCsvStage::Update(void)
{
}

//-------------------------------------
//- CSV�X�e�[�W�̕`�揈��
//-------------------------------------
void CCsvStage::Draw(void)
{
}

//-------------------------------------
//- CSV�X�e�[�W�̐�������
//-------------------------------------
CCsvStage * CCsvStage::Create(void)
{
	// �ʏ�G�̐���
	CCsvStage *pCsvStage = DBG_NEW CCsvStage;

	// �����̐����̗L���𔻒�
	if (pCsvStage != NULL)
	{
		// ����������
		if (FAILED(pCsvStage->Init()))
		{// ���s��

			// �u�Ȃ��v��Ԃ�
			return NULL;
		}
	}
	else if (pCsvStage == NULL)
	{// ���s��

		// �u�Ȃ��v��Ԃ�
		return NULL;
	}

	// �ʏ�G�̃|�C���^��Ԃ�
	return pCsvStage;
}

//-------------------------------------
//- CSV�X�e�[�W�̓ǂݍ��ݏ���
//-------------------------------------
void CCsvStage::Load(CCsvStage::CSV csv)
{
	//�ϐ��錾
	int nCount = 0;

	//�t�@�C���|�C���^�錾
	FILE *pFile = fopen(pCsvStage[csv], "r");

	//�t�@�C����ǂݍ���
	if (pFile != NULL)
	{
		// �o�C�i���t�@�C���ɓǂݍ���
		for (; fscanf(pFile, "%s,\n", &m_acCsvData[nCount]) != EOF; )
		{
			nCount++;

			if (nCount > 64 * 16)
			{
				break;
			}
		}
	}
	else
	{
		return;
	}

	//�t�@�C�������
	fclose(pFile);

	// CSV�X�e�[�W�̕����鏈��
	Divide();
}

//-------------------------------------
//- CSV�X�e�[�W�̕����鏈��
//-------------------------------------
void CCsvStage::Divide(void)
{
	// �ϐ��錾
	int nCntCsv = 0;	// CSV�J�E���g

	D3DXVECTOR3 stagePos = D3DXVECTOR3(
		0.0f,
		(SIZE_TILE_CRITERIA_Y * COLU_MAX)  - (SIZE_TILE_CRITERIA_Y * 2),
		0.0f);

	for (int nCntLine = 0; nCntLine < COLU_MAX ; nCntLine++)
	{
		for (int nCntColu = 0; nCntColu < LINE_MAX; nCntColu++)
		{
			for (int nCntType = 0; nCntType < TYPE_TEXT_MAX; nCntType++)
			{
				// ���������ǂݍ���
				for (int nCntArray = 0; nCntArray < ARRAY_SIZE; nCntArray++)
				{
					// �R�����g�𔻒�
					if (m_acCsvData[nCntCsv][nCntArray] == '0')
					{
						// �R�����g������
						memset(&m_acCsvData[nCntCsv][nCntArray], NULL, sizeof(ARRAY_SIZE - nCntArray));

						break;
					}
				}

				// ��������r
				if (strncmp(m_acCsvData[nCntCsv], pCsvStageText[nCntType], sizeof(m_acCsvData[nCntCsv])) == 0)
				{
					// ��ނ��Ƃ̃I�u�W�F�N�g�ݒ菈��
					SetObjData((TYPE_TEXT)nCntType, stagePos);
				}
			}

			// X����
			stagePos.x += SIZE_TILE_CRITERIA_X;

			// CSV�J�E���g�̉��Z
			nCntCsv++;
		}

		stagePos.x = 0.0f;
		stagePos.y -= SIZE_TILE_CRITERIA_Y;
	}
}

//-------------------------------------
//- CSV�X�e�[�W�̎�ނ̂��Ƃ̃I�u�W�F�N�g�ݒ菈��
//-------------------------------------
void CCsvStage::SetObjData(TYPE_TEXT typeText, D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < CSV_DATA_MAX; nCnt++)
	{
		if (m_data[nCnt].bUse != true)
		{
			m_data[nCnt].bUse = true;
			m_data[nCnt].type = typeText;
			m_data[nCnt].pos = pos;

			break;
		}
	}
}

//-------------------------------------
//- CSV�X�e�[�W�̎�ނ̂��Ƃ̃I�u�W�F�N�g�ݒ菈��
//-------------------------------------
void CCsvStage::SetObj(void)
{
	for (int nCount = 0; nCount < CSV_DATA_MAX; nCount++)
	{
		if (m_data[nCount].bUse == true)
		{
			switch (m_data[nCount].type)
			{
			case TYPE_TEXT_NONE:

				break;

			case TYPE_TEXT_WALL:


				break;

			case TYPE_TEXT_BLOCK:

				CObjBlock::Create(
					CObjBlock::MODEL_BLOCK_000,
					m_data[nCount].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				break;

			case TYPE_TEXT_TUTORIAL_000:


				break;

			case TYPE_TEXT_TUTORIAL_001:


				break;

			case TYPE_TEXT_TUTORIAL_002:

				break;

			case TYPE_TEXT_GOAL:

				CGoal::Create(
					CGoal::MODEL_GOAL_000,
					m_data[nCount].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				break;

			case TYPE_TEXT_PLAYER:


				break;

			case TYPE_TEXT_ENEMY:

				CEnemy::Create(
					CEnemy::MODEL_ALIEN_000,
					m_data[nCount].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				break;

			case TYPE_TEXT_GIMMICK_SPEED:

				CGimmickJewel::Create(
					CGimmickJewel::MODEL_JEWEL_000,
					CGimmickJewel::TYPE_EFFECT_SPEED_UP,
					m_data[nCount].pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				break;
			}
		}
	}
}
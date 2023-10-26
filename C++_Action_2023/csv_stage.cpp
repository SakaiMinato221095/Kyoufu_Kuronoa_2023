
//================================================
//=
//=	ステージCSV処理[csv_stage.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "csv_stage.h"

#include "obj_block.h"
#include "goal.h"
#include "enemy.h"
#include "gimmick_jewel.h"

//=======================================
//=	マクロ定義
//=======================================

#define SIZE_TILE_CRITERIA_X	(150.0f)		// 一マスの基準（X軸）
#define SIZE_TILE_CRITERIA_Y	(150.0f)		// 一マスの基準（Y軸）

//=======================================
//= コンスト定義
//=======================================

// ステージCSVのテキストのコンスト定義
const char *pCsvStage[] =
{
	"data\\CSV\\Stage\\stage_000.csv"		// 通常敵_000のテキスト
};

// ステージCSVの種類テキストのコンスト定義
const char *pCsvStageText[] =
{
	"0",	// 効果なしのテキスト
	"1",	// 壁のテキスト
	"B",	// ブロックのテキスト
	"T0",	// チュートリアル_000のテキスト
	"T1",	// チュートリアル_001のテキスト
	"T2",	// チュートリアル_002のテキスト
	"GG",	// ゴールのテキスト
	"P",	// プレイヤーのテキスト
	"E",	// 敵のテキスト
	"GS",	// 速度UPギミックのテキスト
};

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CCsvStage::CCsvStage()
{
	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(&m_acCsvData, sizeof(m_acCsvData));
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CCsvStage::~CCsvStage()
{

}

//-------------------------------------
//- CSVステージの初期化処理
//-------------------------------------
HRESULT CCsvStage::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- CSVステージの終了処理
//-------------------------------------
void CCsvStage::Uninit(void)
{
}

//-------------------------------------
//- CSVステージの更新処理
//-------------------------------------
void CCsvStage::Update(void)
{
}

//-------------------------------------
//- CSVステージの描画処理
//-------------------------------------
void CCsvStage::Draw(void)
{
}

//-------------------------------------
//- CSVステージの生成処理
//-------------------------------------
CCsvStage * CCsvStage::Create(void)
{
	// 通常敵の生成
	CCsvStage *pCsvStage = DBG_NEW CCsvStage;

	// 生成の成功の有無を判定
	if (pCsvStage != NULL)
	{
		// 初期化処理
		if (FAILED(pCsvStage->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCsvStage == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 通常敵のポインタを返す
	return pCsvStage;
}

//-------------------------------------
//- CSVステージの読み込み処理
//-------------------------------------
void CCsvStage::Load(CCsvStage::CSV csv)
{
	//変数宣言
	int nCount = 0;

	//ファイルポインタ宣言
	FILE *pFile = fopen(pCsvStage[csv], "r");

	//ファイルを読み込み
	if (pFile != NULL)
	{
		// バイナリファイルに読み込み
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

	//ファイルを閉じる
	fclose(pFile);

	// CSVステージの分ける処理
	Divide();
}

//-------------------------------------
//- CSVステージの分ける処理
//-------------------------------------
void CCsvStage::Divide(void)
{
	// 変数宣言
	int nCntCsv = 0;	// CSVカウント

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
				// 文字数分読み込み
				for (int nCntArray = 0; nCntArray < ARRAY_SIZE; nCntArray++)
				{
					// コメントを判定
					if (m_acCsvData[nCntCsv][nCntArray] == '0')
					{
						// コメントを除去
						memset(&m_acCsvData[nCntCsv][nCntArray], NULL, sizeof(ARRAY_SIZE - nCntArray));

						break;
					}
				}

				// 文字列を比較
				if (strncmp(m_acCsvData[nCntCsv], pCsvStageText[nCntType], sizeof(m_acCsvData[nCntCsv])) == 0)
				{
					// 種類ごとのオブジェクト設定処理
					SetObjData((TYPE_TEXT)nCntType, stagePos);
				}
			}

			// X軸を
			stagePos.x += SIZE_TILE_CRITERIA_X;

			// CSVカウントの加算
			nCntCsv++;
		}

		stagePos.x = 0.0f;
		stagePos.y -= SIZE_TILE_CRITERIA_Y;
	}
}

//-------------------------------------
//- CSVステージの種類のごとのオブジェクト設定処理
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
//- CSVステージの種類のごとのオブジェクト設定処理
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
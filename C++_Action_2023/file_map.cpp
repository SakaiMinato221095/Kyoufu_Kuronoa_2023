
//================================================
//=
//=	マップファイルの処理[file_map.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "file_map.h"

#include "edit_map.h"

#include "obj_block.h"
#include "goal.h"
#include "enemy.h"
#include "gimmick_jewel.h"
#include "obj_teach.h"

//=======================================
//=	マクロ定義
//=======================================

#define ARRAY_SIZE	(128)		// 配列のサイズ

//=======================================
//= コンスト定義
//=======================================

// マップのテキストのコンスト定義
const char *pTextMap[] =
{
	"data\\TXT\\Map\\MapNormal.txt"		//	通常マップのテキスト
};

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CFileMap::CFileMap()
{
	ZeroMemory(m_aMapData, sizeof(m_aMapData));
	m_nNumMax = 0;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CFileMap::~CFileMap()
{

}

//-------------------------------------
//- マップエディタの初期化処理
//-------------------------------------
HRESULT CFileMap::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- マップエディタの終了処理
//-------------------------------------
void CFileMap::Uninit(void)
{
}

//-------------------------------------
//- マップエディタの更新処理
//-------------------------------------
void CFileMap::Update(void)
{
}

//-------------------------------------
//- マップエディタの描画処理
//-------------------------------------
void CFileMap::Draw(void)
{
}

//-------------------------------------
//- マップエディタの生成処理
//-------------------------------------
CFileMap * CFileMap::Create(void)
{
	// 生成処理
	CFileMap *pFileMap = DBG_NEW CFileMap;

	// 生成の成功の有無を判定
	if (pFileMap != NULL)
	{
		// 初期化処理
		if (FAILED(pFileMap->Init()))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pFileMap == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// ポインタを返す
	return pFileMap;
}

//-------------------------------------
//- マップエディタのセーブ処理
//-------------------------------------
void CFileMap::Save(void)
{
	// ファイルを開く（書き出し）
	FILE *pFile = fopen(pTextMap[TEXT_MAP_NORMAL], "w");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 見出しの書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#= [マップ] \n");
		fprintf(pFile, "#=\n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		// モデル数の書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [最大モデル数] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "%d\n", m_nNumMax);
		fprintf(pFile, "\n");

		// 配置状況見出しの書き出し
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "#= [配置情報] \n");
		fprintf(pFile, "#==============================================================================\n");
		fprintf(pFile, "\n");

		for (int nCount = 0; nCount < m_nNumMax; nCount++)
		{
			// 変数宣言（敵の情報取得）
			int nModelType = m_aMapData[nCount].type;			// モデル種類
			D3DXVECTOR3 pos = m_aMapData[nCount].pos;			// 位置

			// 配置モデルの情報の書き出し
			fprintf(pFile, "MODEL_TYPE = %d\n", nModelType);
			fprintf(pFile, " --- POS = %3.1f %3.1f %3.1f \n", pos.x, pos.y, pos.z);
			fprintf(pFile, "END_MODEL_SET \n");
			fprintf(pFile, "\n");
		}

		// 書き出しの終了
		fprintf(pFile, "SET_END");
	}

	// ファイルを閉じる
	fclose(pFile);
}

//-------------------------------------
//- マップエディタのロード処理
//-------------------------------------
void CFileMap::Load(void)
{
	// ファイルを開く（読み込み）
	FILE *pFile = fopen(pTextMap[TEXT_MAP_NORMAL], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{
		// 変数宣言
		char aFileData[ARRAY_SIZE] = { 0 };		// ファイルの文章を格納
		CEditMap::EditData editMap = {};		// マップデータ

		while (true)
		{
			// 文字列を読み込み
			fgets(aFileData, ARRAY_SIZE, pFile);

			// 文字数分読み込み
			for (int nCount = 0; nCount < ARRAY_SIZE; nCount++)
			{
				// コメントを判定
				if (aFileData[nCount] == '#')
				{
					// コメントを除去
					memset(&aFileData[nCount], NULL, sizeof(ARRAY_SIZE - nCount));
					break;
				}
			}

			if (strstr(aFileData, "MODEL") != NULL)
			{
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[2][ARRAY_SIZE] = {};	// ゴミ入れ	
					int nValue = 0;					// 数値

					// 値（モデル番号）を取り出す
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// 種類を格納
					editMap.type = (CEditMap::TYPE)nValue;
				}
			}

			if (strstr(aFileData, "POS") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[3][ARRAY_SIZE] = {};	// ゴミ入れ	
					float fPosX = 0;				// 位置（X）
					float fPosY = 0;				// 位置（Y）
					float fPosZ = 0;				// 位置（Z）

					// 値（位置）を取り出す
					sscanf(aFileData, "%s %s %s %f %f %f", aTenp[0], aTenp[1], aTenp[2], &fPosX, &fPosY, &fPosZ);

					// 位置を格納
					editMap.pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
				}
			}


			// モデル設定の終了
			if (strstr(aFileData, "END_MODEL_SET") != NULL)
			{
				// オブジェクトのポインタを初期化
				SetMapObj(editMap);
			}

			// モデル設定の終了
			if (strstr(aFileData, "SET_END") != NULL)
			{
				break;
			}
		}

		// ファイルを閉じる
		fclose(pFile);
	}
}

//-------------------------------------
//- マップエディタのオブジェクト設定処理
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
//- マップエディタのオブジェクト設定処理
//-------------------------------------
void CFileMap::SetMapObj(CEditMap::EditData editData)
{
	CObjectX *pObjX = NULL;
	CObjectBillboard *pObjBill = NULL;

	switch (editData.type)
	{
	case CEditMap::TYPE_BLOCK:

		// ブロックの生成
		pObjX = CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_GOAL:

		// ゴールの生成
		pObjX = CGoal::Create(
			CGoal::MODEL_GOAL_000,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_PLAYER:

		break;

	case CEditMap::TYPE_ENEMY:

		// 敵の生成
		pObjX = CEnemy::Create(
			CEnemy::MODEL_ALIEN_000,
			editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case CEditMap::TYPE_GIMMICK_SPEED:

		// 速度宝石ギミックの生成
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
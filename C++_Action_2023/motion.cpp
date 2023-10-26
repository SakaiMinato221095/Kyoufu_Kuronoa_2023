
//-===============================================
//-
//-	モーションの処理[motion.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "motion.h"

#include "renderer.h"
#include "manager.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// モデルテキストのコンスト定義
const char *pMotionText[] =
{
	"data\\TXT\\Motion\\MotionPlayerAonoa.txt",	// プレイヤー（アオノア）のモーションファイル
};

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	モーションのコンストラクタ
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
//-	モーションのデストラクタ
//-------------------------------------
CMotion::~CMotion()
{

}

//-------------------------------------
//-	モーションの初期化
//-------------------------------------
HRESULT CMotion::Init(int nNumModel, int nNumState)
{
	// 情報を代入
	m_nNumModel = nNumModel;	// モデル数
	m_nNumState = nNumState;	// タイプ

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	モーションの終了処理
//-------------------------------------
void CMotion::Uninit(void)
{

}

//-------------------------------------
//-	モーションの生成処理
//-------------------------------------
CMotion * CMotion::Create(int nNumModel, int nNumState)
{
	// プレイヤーのポインタを宣言
	CMotion *pMotion = DBG_NEW CMotion;

	// 生成の成功の有無を判定
	if (pMotion != NULL)
	{
		// 初期化処理
		if (FAILED(pMotion->Init(nNumModel, nNumState)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pMotion == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// プレイヤーのポインタを返す
	return pMotion;
}

//-------------------------------------
//- モーションの設定
//-------------------------------------
void CMotion::Set(int nType)
{
	// 情報を代入
	m_nType = nType;
	m_nNumKey = m_aInfo[nType].nNumKey;
	m_bLoop = m_aInfo[nType].bLoop;

	// キーを初期値で設定
	m_nKey = 0;
	m_nCounter = 0;

	m_bFinish = true;		// 終了の有無

	// モーションの有無を判定
	if (m_bMotionUse == false)
	{
		// 情報を代入
		m_bMotionUse = true;

		for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
		{
			// キーの初期値で位置を設定
			m_ppModel[nCutModel]->GetData().posMotion =
				(D3DXVECTOR3(
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosX,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosY,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosZ));


			// キーの初期値で向きを設定
			m_ppModel[nCutModel]->GetData().rotMotion =
				(D3DXVECTOR3(
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotX,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotY,
					m_aInfo[nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotZ));
		}
	}
	else
	{
		// 情報を代入
		m_bChangeBlend = true;		// 切り替えのモーションブレンドの有無

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
//- モーションの設定
//-------------------------------------
void CMotion::BlendSet(void)
{
	// キーを初期値で設定
	m_nKey = 0;
	m_nCounter = 0;

	m_bFinish = true;		// 終了の有無

	// モーションブレンドの有無を設定
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
//- モーションの更新処理
//-------------------------------------
void CMotion::Update(void)
{
	// モーションブレンドの有無を判定
	if (m_bBlend == true)
	{
		// モーションブレンドのモーションの更新
		UpdateBlend();
	}
	else if(m_bChangeBlend == true)
	{
		// モーションブレンドのモーションの更新
		UpdateChangeBlend();
	}
	else
	{
		// 通常のモーションの更新
		UpdateNormal();
	}
}

//-------------------------------------
//- モーションの種類取得処理
//-------------------------------------
int CMotion::GetType(void)
{
	return m_nType;
}

//-------------------------------------
//- モーションの終了の有無を取得処理
//-------------------------------------
bool CMotion::IsFinsih(void)
{
	return m_bFinish;
}

//-------------------------------------
//- モーションのキー数の取得処理
//-------------------------------------
int CMotion::GetKey(void)
{
	return m_nKey;
}

//-------------------------------------
//- モーションのキー情報設定処理
//-------------------------------------
void CMotion::SetInfo(Info info)
{
	m_aInfo[m_nType] = info;
}

//-------------------------------------
//- モーションのモデル設定処理
//-------------------------------------
void CMotion::SetModel(CModel **ppModel, int nNumModel)
{
	m_ppModel = &ppModel[nNumModel];
}

//-------------------------------------
//- モーションのモデル設定処理
//-------------------------------------
void CMotion::SetFile(MOTION_TYPE MotionType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pMotionText[MotionType], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{// ファイルが開けるとき

		// 変数宣言
		char aFileData[256] = { 0 };	// ファイルの文章を格納
		int nMotion = -1;
		int nKey = -1;
		int nModel = -1;

		while (true)
		{
			// 文字列を読み込み
			fgets(aFileData, 256, pFile);

			for (int nCount = 0; nCount < 256; nCount++)
			{
				// コメントを判定
				if (aFileData[nCount] == '#')
				{
					// コメントを除去
					memset(&aFileData[nCount], NULL, sizeof(256 - nCount));
					break;
				}
			}

			// モーションの数を増やす
			if (strstr(aFileData, "MOTIONSET") != NULL)
			{
				// 変数宣言
				char aTenp[256] = {};	// ゴミ入れ	

				// 数値を取り出す
				sscanf(aFileData, "%s", aTenp);

				// キーの判定
				if (strcmp(aTenp, "MOTIONSET") == 0)
				{
					nMotion++;

					nKey = -1;
					nModel = -1;
				}
			}

			// ループの設定を判定
			if (strstr(aFileData, "LOOP") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[2][256] = {};	// ゴミ入れ	
					int nValue = 0;				// 数値

					// 数値を取り出す
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// ループの判定
					if (nValue == 1)
					{
						// ループをオン
						m_aInfo[nMotion].bLoop = true;
					}
					else
					{
						// ループをオフ
						m_aInfo[nMotion].bLoop = false;
					}
				}
			}


			// キー数設定を判定
			if (strstr(aFileData, "NUM_KEY") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[2][256] = {};	// ゴミ入れ	
					int nValue = 0;				// 数値

					// 数値を取り出す
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// キー数を設定
					m_aInfo[nMotion].nNumKey = nValue;

				}
			}

			// キー設定を判定
			if (strstr(aFileData, "KEYSET") != NULL)
			{
				// 変数宣言
				char aTenp[256] = {};	// ゴミ入れ	

				// 数値を取り出す
				sscanf(aFileData, "%s", aTenp);

				// キーの判定
				if (strcmp(aTenp, "KEYSET") == 0)
				{
					nKey++;

					nModel = -1;
				}
			}

			// フレーム設定を判定
			if (strstr(aFileData, "FRAME") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[2][256] = {};	// ゴミ入れ	
					int nValue = 0;				// 数値

					// 数値を取り出す
					sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nValue);

					// キー数を設定
					m_aInfo[nMotion].aKeyInfo[nKey].nFrame = nValue;

				}
			}

			// キーの判定
			if (strstr(aFileData, "KEY") != NULL)
			{
				// 変数宣言
				char aTenp[256] = {};	// ゴミ入れ	
				
				// 数値を取り出す
				sscanf(aFileData, "%s", aTenp);

				// キーの判定
				if (strcmp(aTenp,"KEY") == 0)
				{
					nModel++;
				}

			}

			// 位置情報の判定
			if (strstr(aFileData, "POS") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[2][256] = {};	// ゴミ入れ	
					float fPosX = 0;			// 位置（X）
					float fPosY = 0;			// 位置（Y）
					float fPosZ = 0;			// 位置（Z）

					// 数値を取り出す
					sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fPosX, &fPosY, &fPosZ);

					// 位置情報を更新
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fPosX = fPosX;
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fPosY = fPosY;
					m_aInfo[nMotion].aKeyInfo[nKey].aKey[nModel].fRotZ = fPosZ;
				}
			}

			// 向き情報の判定
			if (strstr(aFileData, "ROT") != NULL)
			{
				// 特定の文字を判定
				if (strstr(aFileData, "=") != NULL)
				{
					// 変数宣言
					char aTenp[2][256] = {};	// ゴミ入れ	
					float fRotX = 0;			// 向き（X）
					float fRotY = 0;			// 向き（Y）
					float fRotZ = 0;			// 向き（Z）

					// 数値を取り出す
					sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fRotX, &fRotY, &fRotZ);

					// 向き情報を更新
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

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{

	}
}

//-------------------------------------
//- モーションのブレンドの有無の取得処理
//-------------------------------------
bool CMotion::GetBlend(void)
{
	return m_bBlend;
}

//-------------------------------------
//- モーションの切り替えブレンドの有無の取得処理
//-------------------------------------
bool CMotion::GetChangeBlend(void)
{
	return m_bChangeBlend;
}

//-------------------------------------
//- モーションの通常時の更新処理
//-------------------------------------
void CMotion::UpdateNormal(void)
{
	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		// 現在のキーの位置と向き
		float fPosX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosX;
		float fPosY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosY;
		float fPosZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fPosZ;
		float fRotX = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotX;
		float fRotY = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotY;
		float fRotZ = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCutModel].fRotZ;

		// 次のキーの位置と向き
		float fNextPosX;
		float fNextPosY;
		float fNextPosZ;
		float fNextRotX;
		float fNextRotY;
		float fNextRotZ;

		if (m_nNumKey != m_nKey + 1)
		{
			// 次のキーの位置と向き
			fNextPosX = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fPosX;
			fNextPosY = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fPosY;
			fNextPosZ = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fPosZ;
			fNextRotX = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fRotX;
			fNextRotY = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fRotY;
			fNextRotZ = m_aInfo[m_nType].aKeyInfo[m_nKey + 1].aKey[nCutModel].fRotZ;
		}
		else
		{
			// 最後のキーのときの次のキーの位置と向き
			fNextPosX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosX;
			fNextPosY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosY;
			fNextPosZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosZ;
			fNextRotX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotX;
			fNextRotY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotY;
			fNextRotZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotZ;
		}

		// 差分の位置と向き
		float fDiffPosX = fNextPosX - fPosX;
		float fDiffPosY = fNextPosY - fPosY;
		float fDiffPosZ = fNextPosZ - fPosZ;
		float fDiffRotX = fNextRotX - fRotX;
		float fDiffRotY = fNextRotY - fRotY;
		float fDiffRotZ = fNextRotZ - fRotZ;

		// 変数宣言（パーツごとのモデル情報の取得）
		CModel::Data modelData = m_ppModel[nCutModel]->GetData();

		// 目的の位置を設定
		modelData.posMotion = D3DXVECTOR3(
			(fPosX + fDiffPosX * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fPosY + fDiffPosY * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fPosZ + fDiffPosZ * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)));

		// 目的の向きを設定
		modelData.rotMotion = (D3DXVECTOR3(
			(fRotX + fDiffRotX * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fRotY + fDiffRotY * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame)),
			(fRotZ + fDiffRotZ * ((float)m_nCounter / (float)m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame))));

		// 情報更新（（パーツごとのモデル情報の取得）
		m_ppModel[nCutModel]->SetData(modelData);
	}

	// カウンターを進める
	m_nCounter++;

	// キーを進める判定
	if (m_nCounter % m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame == 0)
	{// カウンターと再生フレームが同じ

		// カウンターを初期化
		m_nCounter = 0;

		// キーを進める
		m_nKey++;

		if (m_nNumKey == m_nKey)
		{// キーの総数と現在のキーが同じ

		 // ループの有無を確認
			if (m_aInfo[m_nType].bLoop == true)
			{
				// キーの初期化
				m_nKey = 0;
			}
			else
			{
				// 終了をオン
				m_bFinish = false;
			}
		}
	}
}

//-------------------------------------
//- モーションの切り替え時のモーションブレンドの更新処理
//-------------------------------------
void CMotion::UpdateChangeBlend(void)
{
	// フレーム数を取得
	int nFrame = 15;

	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		// 前回の情報を取得
		D3DXVECTOR3 motionPosOld = m_motionPosOld[nCutModel];
		D3DXVECTOR3 motionRotOld = m_motionRotOld[nCutModel];
		
		// 現在のモーションの位置
		float fPosX = motionPosOld.x;
		float fPosY = motionPosOld.y;
		float fPosZ = motionPosOld.z;
		float fRotX = motionRotOld.x;
		float fRotY = motionRotOld.y;
		float fRotZ = motionRotOld.z;

		// 次のキーの位置と向き
		float fNextPosX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosX;
		float fNextPosY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosY;
		float fNextPosZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fPosZ;
		float fNextRotX = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotX;
		float fNextRotY = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotY;
		float fNextRotZ = m_aInfo[m_nType].aKeyInfo[0].aKey[nCutModel].fRotZ;

		// 差分の位置と向き
		float fDiffPosX = fNextPosX - fPosX;
		float fDiffPosY = fNextPosY - fPosY;
		float fDiffPosZ = fNextPosZ - fPosZ;
		float fDiffRotX = fNextRotX - fRotX;
		float fDiffRotY = fNextRotY - fRotY;
		float fDiffRotZ = fNextRotZ - fRotZ;

		// 変数宣言（パーツごとのモデル情報の取得）
		CModel::Data modelData = m_ppModel[nCutModel]->GetData();

		// 時間倍率の計算
		modelData.posMotion = D3DXVECTOR3(
			(fPosX + (fDiffPosX * ((float)m_nCounter / (float)nFrame))),
			(fPosY + (fDiffPosY * ((float)m_nCounter / (float)nFrame))),
			(fPosZ + (fDiffPosZ * ((float)m_nCounter / (float)nFrame))));

		// 時間倍率の計算
		modelData.rotMotion = D3DXVECTOR3(
			(fRotX + (fDiffRotX * ((float)m_nCounter / (float)nFrame))),
			(fRotY + (fDiffRotY * ((float)m_nCounter / (float)nFrame))),
			(fRotZ + (fDiffRotZ * ((float)m_nCounter / (float)nFrame))));

		// 情報更新（（パーツごとのモデル情報の取得）
		m_ppModel[nCutModel]->SetData(modelData);


	}

	// カウンターを進める
	m_nCounter++;

	// キーを進める判定
	if (m_nCounter % nFrame == 0)
	{// カウンターと再生フレームが同じ

		// カウンターを初期化
		m_nCounter = 0;

		// 現在のキー数を初期化
		m_bChangeBlend = false;
	}
}

//-------------------------------------
//- モーションのモーションブレンドの更新処理
//-------------------------------------
void CMotion::UpdateBlend(void)
{
	// フレーム数を取得
	int nFrame = 10;

	for (int nCutModel = 0; nCutModel < m_nNumModel; nCutModel++)
	{
		// 前回の情報を取得
		D3DXVECTOR3 motionPosOld = m_motionPosOld[nCutModel];
		D3DXVECTOR3 motionRotOld = m_motionRotOld[nCutModel];

		// 現在のモーションの位置
		float fPosX = motionPosOld.x;
		float fPosY = motionPosOld.y;
		float fPosZ = motionPosOld.z;
		float fRotX = motionRotOld.x;
		float fRotY = motionRotOld.y;
		float fRotZ = motionRotOld.z;

		// 次のキーの位置と向き
		float fNextPosX = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fPosX;
		float fNextPosY = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fPosY;
		float fNextPosZ = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fPosZ;
		float fNextRotX = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fRotX;
		float fNextRotY = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fRotY;
		float fNextRotZ = m_aInfo[m_nType].aKeyInfo[1].aKey[nCutModel].fRotZ;

		// 差分の位置と向き
		float fDiffPosX = fNextPosX - fPosX;
		float fDiffPosY = fNextPosY - fPosY;
		float fDiffPosZ = fNextPosZ - fPosZ;
		float fDiffRotX = fNextRotX - fRotX;
		float fDiffRotY = fNextRotY - fRotY;
		float fDiffRotZ = fNextRotZ - fRotZ;

		// 変数宣言（パーツごとのモデル情報の取得）
		CModel::Data modelData = m_ppModel[nCutModel]->GetData();

		// 時間倍率の計算
		modelData.posMotion = D3DXVECTOR3(
			(fPosX + (fDiffPosX * ((float)m_nCounter / (float)nFrame))),
			(fPosY + (fDiffPosY * ((float)m_nCounter / (float)nFrame))),
			(fPosZ + (fDiffPosZ * ((float)m_nCounter / (float)nFrame))));

		// 時間倍率の計算
		modelData.rotMotion = D3DXVECTOR3(
			(fRotX + (fDiffRotX * ((float)m_nCounter / (float)nFrame))),
			(fRotY + (fDiffRotY * ((float)m_nCounter / (float)nFrame))),
			(fRotZ + (fDiffRotZ * ((float)m_nCounter / (float)nFrame))));

		// 情報更新（（パーツごとのモデル情報の取得）
		m_ppModel[nCutModel]->SetData(modelData);
	}

	// カウンターを進める
	m_nCounter++;

	// キーを進める判定
	if (m_nCounter % nFrame == 0)
	{// カウンターと再生フレームが同じ

		// キー数を射撃状態に変更
		m_nKey = 1;

		// カウンターを初期化
		m_nCounter = 0;

		// 現在のキー数を初期化
		m_bBlend = false;
	}
}
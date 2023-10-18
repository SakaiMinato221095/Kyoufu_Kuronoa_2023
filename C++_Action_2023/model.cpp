
//================================================
//=
//= 階層構造のモデル処理[model.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "model.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"
#include "manager_texture.h"

//=======================================
//=	コンスト定義
//=======================================

// モデルテキストのコンスト定義
const char *pModelText[] =
{
	"data\\TXT\\Model\\Player.txt",	// プレイヤーのモデルファイル
};

//=======================================
//=	静的変数宣言
//=======================================

CModel::Model CModel::m_model[MODEL_NUM_MAX] = {};
int CModel::m_nModelNldx[MODEL_TYPE_MAX][MODEL_PARTS_MAX] = {};

//-------------------------------------
//-	階層構造のXファイルオブジェクトのコンストラクタ
//-------------------------------------
CModel::CModel()
{
	// 値をクリア
	m_pParent = NULL;

	m_modelType = (MODEL_TYPE)0;
	m_nPartsNum = -1;

	ZeroMemory(&m_data, sizeof(m_data));
	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトのデストラクタ
//-------------------------------------
CModel::~CModel()
{
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの読み込み処理
//-------------------------------------
HRESULT CModel::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCutModel = 0; nCutModel < MODEL_TYPE_MAX; nCutModel++)
	{
		// モデルの読み込み
		SetFile((MODEL_TYPE)nCutModel);

		for (int nCntParts = 0; nCntParts < m_model[nCutModel].nPartsNum; nCntParts++)
		{
			// モデル番号の取得（モデルの割当）
			int nModelNldx = pManagerModel->Regist(m_model[nCutModel].modelParts[nCntParts].aFileName);

			// モデルの読み込み成功の有無を確認
			if (nModelNldx == -1)
			{
				// 失敗時に初期化処理を抜ける
				return E_FAIL;
			}

			// モデル番号を設定
			m_nModelNldx[nCutModel][nCntParts] = nModelNldx;
		}
	}

	return S_OK;
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの初期化処理
//-------------------------------------
HRESULT CModel::Init(MODEL_TYPE modelType , int nCount)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// モデル番号を取得
	int nModelNldx = m_nModelNldx[modelType][nCount];
	m_modelType = modelType;
	m_nPartsNum = nCount;

	// 情報を設定
	m_data.pos = m_model[modelType].modelParts[nCount].pos;	// 位置
	m_data.rot = m_model[modelType].modelParts[nCount].rot;	// 向き

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの終了処理
//-------------------------------------
void CModel::Uninit(void)
{
	// 親のポインタ初期化処理
	if (m_pParent != NULL)
	{
		m_pParent = NULL;
	}
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの更新処理
//-------------------------------------
void CModel::Update(void)
{

}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの描画処理
//-------------------------------------
void CModel::Draw(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 初期化処理を抜ける
		return;
	}

	// モデル番号を取得
	int nModelNldx = m_nModelNldx[m_modelType][m_nPartsNum];

	// モデル情報を取得
	CManagerModel::Model model = pManagerModel->GetAddress(nModelNldx);

	// モデルの有無を判定
	if (model.m_pMesh == NULL)
	{
		// 描画処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_data.pos + m_data.posMotion;	// 位置情報
	D3DXVECTOR3 rot = m_data.rot + m_data.rotMotion;	// 向き情報
		
	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				// マテリアルへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//親の計算用マトリックス
	D3DXMATRIX mtxParent;

	//パーツの「親マトリックス」を設定
	if (m_pParent != NULL)
	{//親モデルがある場合

		// 親のマトリックスを代入
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{//親モデルがない場合

		//プレイヤーのマトリックスを設定
		pDevice->GetTransform(D3DTS_WORLD,&mtxParent);
	}

	//算出したパーツのマトリックスと親のマトリックスを掛け合わせる
	D3DXMatrixMultiply(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent);

	// ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// 現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルのポインタを取得
	pMat = (D3DXMATERIAL*)model.m_pBuffMat->GetBufferPointer();
	
	// マテリアルごとの描画
	for (int nCutMat = 0; nCutMat < (int)model.m_dwNumMat; nCutMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCutMat].MatD3D);

		// テクスチャの設定（仮）
		pDevice->SetTexture(0, model.m_pTexture[nCutMat]);

		// 階層構造のXファイルオブジェクト（パーツ）の描画
		model.m_pMesh->DrawSubset(nCutMat);
	}

	// 保存していたマテリアルに戻す
	pDevice->SetMaterial(&matDef);
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの生成処理
//-------------------------------------
CModel *CModel::Create(MODEL_TYPE modelType, int nCount)
{
	// 階層構造のXファイルオブジェクトのポインタを宣言
	CModel *pObjectX = DBG_NEW CModel;

	// 生成の成功の有無を判定
	if (pObjectX != NULL)
	{
		// 初期化処理
		if (FAILED(pObjectX->Init(modelType,nCount)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pObjectX == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 階層構造のXファイルオブジェクトのポインタを返す
	return pObjectX;
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトの親子関係設定処理
//-------------------------------------
void CModel::SetParent(CModel **pObjectModel, MODEL_TYPE modelType,int nCount)
{
	// 親の番号を取得
	int nParent = m_model[modelType].modelParts[nCount].nParent;

	if (nParent != -1)
	{
		// 親のモデル情報を代入
		m_pParent = pObjectModel[nParent];
	}
	else
	{
		m_pParent = NULL;
	}
}

//-------------------------------------
//-	階層構造のXファイルオブジェクトのワールドマトリックス取得処理
//-------------------------------------
D3DXMATRIX CModel::GetMtxWorld(void)
{
	// ワールドマトリックスを返す
	return m_mtxWorld;
}

//-------------------------------------
//- 階層構造のモデル取得処理
//-------------------------------------
void CModel::SetData(CModel::Data data)
{
	m_data = data;
}

//-------------------------------------
//- 階層構造のモデル取得処理
//-------------------------------------
CModel::Data CModel::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- 階層構造のXファイルオブジェクトのモデル設定処理
//-------------------------------------
void CModel::SetFile(MODEL_TYPE modelType)
{
	//変数宣言
	FILE *pFile;	// ファイルのポインタ

	// ファイルの情報を代入
	pFile = fopen(pModelText[modelType], "r");

	// ファイルの有無を判定
	if (pFile != NULL)
	{// ファイルが開けるとき

		// 変数宣言
		char aFileData[256] = {};		// ファイルの文章を格納

		int nFileNameCount = -1;		// ファイルの名前のカウント 
		int nIndex = -1;				// パーツ数を格納

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

			// モデルのパーツ数を設定
			if (strstr(aFileData, "NUM_MODEL") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				int nPartsNum = 0;			// パーツ数

				// パーツ数を取り出す
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nPartsNum);

				// パーツ数を代入
				m_model[modelType].nPartsNum = nPartsNum;
			}

			// パーツのファイル名を設定
			if (strstr(aFileData, "MODEL_FILENAME") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				char aFileName[256] = {};	// ファイルの名前を格納

				// パーツカウントを進める
				nFileNameCount++;

				// ファイルの名前を取り出す
				sscanf(aFileData, "%s %s %s", aTenp[0], aTenp[1], aFileName);

				// ファイルの名前を代入
				strcpy(m_model[modelType].modelParts[nFileNameCount].aFileName, aFileName);
			}

			// パーツ番号の設定
			if (strstr(aFileData, "INDEX") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	

				// パーツの番号を取り出す
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nIndex);

				// パーツの番号を代入
				m_model[modelType].modelParts[nIndex].nIndex = nIndex;
			}

			// 親の設定
			if (strstr(aFileData, "PARENT") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				int nParent = -1;

				// 親の番号を取り出す
				sscanf(aFileData, "%s %s %d", aTenp[0], aTenp[1], &nParent);

				// 親の番号を代入
				m_model[modelType].modelParts[nIndex].nParent = nParent;
			}

			// 位置情報の設定
			if (strstr(aFileData, "POS") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				float fPosX = 0;			// 位置（X）
				float fPosY = 0;			// 位置（Y）
				float fPosZ = 0;			// 位置（Z）

				// 位置を取り出す
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fPosX, &fPosY, &fPosZ);

				// 位置を代入
				m_model[modelType].modelParts[nIndex].pos = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			}

			// 向き情報の設定
			if (strstr(aFileData, "ROT") != NULL)
			{
				// 変数宣言
				char aTenp[2][256] = {};	// ゴミ入れ	
				float fRotX = 0;			// 向き（X）
				float fRotY = 0;			// 向き（Y）
				float fRotZ = 0;			// 向き（Z）

				// 向きを取り出す
				sscanf(aFileData, "%s %s %f %f %f", aTenp[0], aTenp[1], &fRotX, &fRotY, &fRotZ);

				// 向きを代入
				m_model[modelType].modelParts[nIndex].rot = D3DXVECTOR3(fRotX, fRotY, fRotZ);
			}

			// 終了
			if (strstr(aFileData, "END_CHARACTERSET") != NULL)
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
//- 階層構造のXファイルオブジェクトのモデル設定処理
//-------------------------------------
int CModel::GetPartsNum(MODEL_TYPE modelType)
{
	// パーツ数を返す
	return m_model[modelType].nPartsNum;
}
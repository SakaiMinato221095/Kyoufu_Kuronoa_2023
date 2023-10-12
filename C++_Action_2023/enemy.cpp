
//-===============================================
//-
//-	敵の処理[enemy.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "enemy.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "file_data_emy_nor.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 敵のモデルのコンスト定義
const char *pModelEnemy[] =
{
	"data\\MODEL\\alien000.x",			// エイリアン000
	"data\\MODEL\\alien001.x",			// エイリアン001
};

//-======================================
//-	静的変数宣言
//-======================================

CDataInt CEnemy::m_nDataModelNldx[MODEL_TYPE_MAX] = {};			// モデルの番号

CEnemy::ModelData CEnemy::m_modelData[MODEL_TYPE_MAX] = {};		// モデル情報

//-------------------------------------
//-	敵のコンストラクタ
//-------------------------------------
CEnemy::CEnemy()
{

}

//-------------------------------------
//-	敵のデストラクタ
//-------------------------------------
CEnemy::~CEnemy()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CEnemy::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < MODEL_TYPE_MAX; nCount++)
	{
		// モデル番号を取得
		int nModelNldx = m_nDataModelNldx[nCount].Get();

		// モデル番号の取得（モデルの割当）
		nModelNldx = pManagerModel->Regist(pModelEnemy[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nDataModelNldx[nCount].Set(nModelNldx);
	}

	// 通常敵の情報の読み込み
	CFileDataEmyNor::Load();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の読み込んだモデル破棄
//-------------------------------------
void CEnemy::Unload(void)
{

}

//-------------------------------------
//- 敵の初期化処理
//-------------------------------------
HRESULT CEnemy::Init(MODEL_TYPE modelType)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// モデル番号を取得
	int nModelNldx = m_nDataModelNldx[modelType].Get();

	// 効果なしオブジェクトのモデル割当
	BindModel(nModelNldx, modelType);

	// データ設定
	m_dataSize.Set(m_modelData[modelType].size);

	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の終了処理
//-------------------------------------
void CEnemy::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- 敵の更新処理
//-------------------------------------
void CEnemy::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- 敵の描画処理
//-------------------------------------
void CEnemy::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//-	敵のモデルの設定処理
//-------------------------------------
int CEnemy::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	敵のモデルの設定処理
//-------------------------------------
void CEnemy::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL_TYPE)nModelNldx;
}

//-------------------------------------
//-	敵のモデルの情報の設定処理
//-------------------------------------
void CEnemy::SetModelData(int nNum, CEnemy::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	敵のモデルの情報の取得処理
//-------------------------------------
CEnemy::ModelData CEnemy::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}
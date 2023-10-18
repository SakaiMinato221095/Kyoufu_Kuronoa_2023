
//-===============================================
//-
//-	効果なしオブジェクトの処理[object_none.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "objectx_none.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 効果なしオブジェクトのモデルのコンスト定義
const char *pModelObjectXNone[] =
{
	"data\\MODEL\\None\\Block_000.x",			// ブロック
};

//-======================================
//-	静的変数宣言
//-======================================

CObjectXNone::ModelData CObjectXNone::m_modelData[MODEL_MAX] = {};	// モデル情報
int CObjectXNone::m_nModelNldx[MODEL_MAX] = {};						// モデルの番号

//-------------------------------------
//-	効果なしオブジェクトのコンストラクタ
//-------------------------------------
CObjectXNone::CObjectXNone(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	効果なしオブジェクトのデストラクタ
//-------------------------------------
CObjectXNone::~CObjectXNone()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CObjectXNone::Load(void)
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

	// モデル設定
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// モデル番号を取得
		int nModelNldx = m_nModelNldx[nCount];

		// モデル番号の取得（モデルの割当）
		nModelNldx = pManagerModel->Regist(pModelObjectXNone[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nModelNldx[nCount] = nModelNldx;
	}

	m_modelData[MODEL_BLOCK_000].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の読み込んだモデル破棄
//-------------------------------------
void CObjectXNone::Unload(void)
{

}

//-------------------------------------
//- 効果なしオブジェクトの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CObjectXNone::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
	int nModelNldx = m_nModelNldx[model];

	// 効果なしオブジェクトのモデル割当
	BindModel(nModelNldx,model);

	// 初期設定処理
	InitSet(model,pos,rot);

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
//- 効果なしオブジェクトの終了処理
//-------------------------------------
void CObjectXNone::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- 効果なしオブジェクトの更新処理
//-------------------------------------
void CObjectXNone::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- 効果なしオブジェクトの描画処理
//-------------------------------------
void CObjectXNone::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- 効果なしオブジェクトの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CObjectXNone * CObjectXNone::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 効果なしオブジェクトのポインタを宣言
	CObjectXNone *pCObjectXNone = DBG_NEW CObjectXNone(4);

	// 生成の成功の有無を判定
	if (pCObjectXNone != NULL)
	{
		// 初期化処理
		if (FAILED(pCObjectXNone->Init(model,pos,rot)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObjectXNone == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 効果なしオブジェクトのポインタを返す
	return pCObjectXNone;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CObjectXNone::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CObjectXNone::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	モデルの情報の設定処理
//-------------------------------------
void CObjectXNone::SetModelData(int nNum, CObjectXNone::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CObjectXNone::ModelData CObjectXNone::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- 効果なしオブジェクトの初期設定処理
//-------------------------------------
void CObjectXNone::InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = m_modelData[model].size;

	SetVtxData(vtxData);
}
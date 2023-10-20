
//-===============================================
//-
//-	ゴールの処理[goal.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "goal.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

#include "manager.h"
#include "fade.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// ギミックのモデルのコンスト定義
const char *pModelGoal[] =
{
	"data\\MODEL\\Goal\\goal_000.x",			// ゴール000
};

//-======================================
//-	静的変数宣言
//-======================================

CGoal::ModelData CGoal::m_modelData[MODEL_MAX] = {};	// モデル情報
int CGoal::m_nModelNldx[MODEL_MAX] = {};					// モデルの番号

//-------------------------------------
//-	ギミックのコンストラクタ
//-------------------------------------
CGoal::CGoal(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	ギミックのデストラクタ
//-------------------------------------
CGoal::~CGoal()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CGoal::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelGoal[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nModelNldx[nCount] = nModelNldx;
	}

	m_modelData[MODEL_GOAL_000].size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の読み込んだモデル破棄
//-------------------------------------
void CGoal::Unload(void)
{

}

//-------------------------------------
//- ギミックの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CGoal::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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

	// ギミックのモデル割当
	BindModel(nModelNldx, model);

	// 初期設定処理
	InitSet(model, pos, rot);

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
//- ギミックの終了処理
//-------------------------------------
void CGoal::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// 当たり判定の終了処理
		m_pColl->Uninit();

		// 当たり判定の開放処理
		delete m_pColl;
		m_pColl = NULL;
	}

	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- ギミックの更新処理
//-------------------------------------
void CGoal::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();

	// 当たり判定の情報更新処理
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	// 敵との当たり判定
	if (m_pColl->Hit(CMgrColl::TAG_PLAYER, CMgrColl::STATE_HIT_NONE) == true)
	{
		// ゲームモード
		CManager::GetInstance()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//-------------------------------------
//- ギミックの描画処理
//-------------------------------------
void CGoal::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- ギミックの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CGoal * CGoal::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ギミックのポインタを宣言
	CGoal *pCGoal = DBG_NEW CGoal(4);

	// 生成の成功の有無を判定
	if (pCGoal != NULL)
	{
		// 初期化処理
		if (FAILED(pCGoal->Init(model, pos, rot)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCGoal == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// ギミックのポインタを返す
	return pCGoal;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CGoal::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CGoal::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	モデルの情報の設定処理
//-------------------------------------
void CGoal::SetModelData(int nNum, CGoal::ModelData modelData)
{
	// モデル情報の代入
	m_modelData[nNum] = modelData;	// 大きさ
}

//-------------------------------------
//-	モデルの情報の取得処理
//-------------------------------------
CGoal::ModelData CGoal::GetModelData(int nNum)
{
	// モデル情報を返す
	return m_modelData[nNum];
}

//-------------------------------------
//- ギミックの初期設定処理
//-------------------------------------
void CGoal::InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = m_modelData[model].size;

	SetVtxData(vtxData);

	// 当たり判定設定
	m_pColl = CColl::Create(
		CMgrColl::TAG_GOAL,
		GetVtxData().pos,
		GetVtxData().size);

	// 相手タグの設定処理
	m_pColl->SetTagTgt(CMgrColl::TAG_PLAYER, CMgrColl::TYPE_RECTANGLE, true);
}
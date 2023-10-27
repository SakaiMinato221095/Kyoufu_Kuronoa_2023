
//-===============================================
//-
//-	保持敵の処理[enemy_have.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "enemy_have.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

#include "kazedama.h"
#include "player.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 保持敵のモデルのコンスト定義
const char *pModelEnemyHave[] =
{
	"data\\MODEL\\alien000.x",			// エイリアン000
};

//-======================================
//-	静的変数宣言
//-======================================

int CEnemyHave::m_nModelNldx[MODEL_MAX] = {};	// モデルの番号

//-------------------------------------
//-	保持敵のコンストラクタ
//-------------------------------------
CEnemyHave::CEnemyHave()
{
	m_model = MODEL(0);

	ZeroMemory(&m_data, sizeof(m_data));
	m_pColl = NULL;
}

//-------------------------------------
//-	保持敵のデストラクタ
//-------------------------------------
CEnemyHave::~CEnemyHave()
{

}

//-------------------------------------
//- 保持敵のモデル読み込み
//-------------------------------------
HRESULT CEnemyHave::Load(void)
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
		nModelNldx = pManagerModel->Regist(pModelEnemyHave[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nModelNldx[nCount] = nModelNldx;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 保持敵の読み込んだモデル破棄
//-------------------------------------
void CEnemyHave::Unload(void)
{

}

//-------------------------------------
//- 保持敵の初期化処理
//-------------------------------------
HRESULT CEnemyHave::Init(MODEL model, STATE state, D3DXVECTOR3 pos,D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// 初期設定処理
	InitSet(state,pos,rot,size);

	// モデル番号を取得
	int nModelNldx = m_nModelNldx[model];

	// 効果なしオブジェクトのモデル割当
	BindModel(nModelNldx, model);

	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 当たり判定設定
	m_pColl = CColl::Create(
		CMgrColl::TAG_ENEMY_HAVE,
		GetVtxData().pos,
		GetVtxData().size);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 保持敵の終了処理
//-------------------------------------
void CEnemyHave::Uninit(void)
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
//- 保持敵の更新処理
//-------------------------------------
void CEnemyHave::Update(void)
{
	// 当たり判定の情報更新処理
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	switch (m_data.state)
	{
	case STATE_OBTAIN:

		// 獲得時の更新処理
		UpdateObtain();

		break;

	case STATE_WAIT:

		// 待機時の更新処理
		UpdateWait();

		break;

	case STATE_SHOT:

		// 発射時の更新処理
		if (UpdateShot())
		{
			return;
		}
		
		break;
	}

	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- 保持敵の描画処理
//-------------------------------------
void CEnemyHave::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- 保持敵の生成処理
//-------------------------------------
CEnemyHave * CEnemyHave::Create(MODEL model, STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// 保持敵の生成
	CEnemyHave *pEnemy = DBG_NEW CEnemyHave;

	// 生成の成功の有無を判定
	if (pEnemy != NULL)
	{
		// 初期化処理
		if (FAILED(pEnemy->Init(model,state, pos,rot, size)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pEnemy == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 保持敵のポインタを返す
	return pEnemy;
}

//-------------------------------------
//-	保持敵のモデルの設定処理
//-------------------------------------
int CEnemyHave::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	保持敵のモデルの設定処理
//-------------------------------------
void CEnemyHave::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	保持敵の獲得更新処理
//-------------------------------------
void CEnemyHave::UpdateObtain(void)
{

}

//-------------------------------------
//-	保持敵の待機更新処理
//-------------------------------------
void CEnemyHave::UpdateWait(void)
{

}

//-------------------------------------
//-	保持敵の発射更新処理
//-------------------------------------
bool CEnemyHave::UpdateShot(void)
{
	// 変数を宣言（情報取得）
	VtxData vtxData = GetVtxData();

	// 加算処理
	vtxData.pos += m_data.move;			// 位置

	// 情報更新
	SetVtxData(vtxData);

	// 宝石との当たり判定
	if (m_pColl->Hit(CMgrColl::TAG_GIMMICK_JEWEL, CMgrColl::STATE_HIT_DEAD) == true ||
		m_pColl->Hit(CMgrColl::TAG_BLOCK, CMgrColl::STATE_HIT_DEAD) == true)
	{
		// 終了処理
		Uninit();

		return true;
	}

	// 体力カウント
	m_data.nLifeCut++;

	// 体力カウントの判定
	if (m_data.nLifeCut >= m_data.nLife)
	{
		// 終了処理
		Uninit();

		return true;
	}

	return false;
}

//-------------------------------------
//-	保持敵の発射設定処理
//-------------------------------------
void CEnemyHave::SetShot(D3DXVECTOR3 pos,D3DXVECTOR3 move, int nLife, TYPE_ROT typeRot)
{
	m_data.state = STATE_SHOT;

	// 変数を宣言（情報取得）
	VtxData vtxData = GetVtxData();

	// 加算処理
	vtxData.pos = pos;			// 位置

	// 情報更新
	SetVtxData(vtxData);

	m_data.move = move;
	m_data.nLife = nLife;
	m_data.typeRot = typeRot;

	// 相手タグの設定処理
	m_pColl->SetTagTgt(CMgrColl::TAG_GIMMICK_JEWEL, CMgrColl::TYPE_RECTANGLE, true);

	// 相手タグの設定処理
	m_pColl->SetTagTgt(CMgrColl::TAG_BLOCK, CMgrColl::TYPE_RECTANGLE, true);
}

//-------------------------------------
//- 保持敵の設定処理
//-------------------------------------
void CEnemyHave::InitSet(STATE state, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	VtxData vtxData;

	m_data.state = state;
	vtxData.pos = pos;
	vtxData.rot = rot;
	vtxData.size = size;

	SetVtxData(vtxData);
}
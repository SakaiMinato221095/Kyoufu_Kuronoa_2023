
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

#include "collision.h"

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
CEnemyHave *CEnemyHave::m_pInstance = NULL;		// 自身のポインタ

//-------------------------------------
//-	保持敵のコンストラクタ
//-------------------------------------
CEnemyHave::CEnemyHave()
{
	ZeroMemory(&m_data, sizeof(m_data));

	m_model = MODEL(0);
	m_nCollNldx = -1;


	if (m_pInstance == NULL)
	{
		// 自身のポインタを代入
		m_pInstance = this;
	}
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
HRESULT CEnemyHave::Init(MODEL modelType)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// 当たり判定のポインタ取得
	CCollision *pCollision = CManager::GetCollision();

	// 当たり判定の有無を判定
	if (pCollision == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// モデル番号を取得
	int nModelNldx = m_nModelNldx[modelType];

	// 効果なしオブジェクトのモデル割当
	BindModel(nModelNldx, modelType);

	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 頂点値情報を取得
	VtxData vtxData = GetVtxData();

	// サイズを設定
	vtxData.size = D3DXVECTOR3(50.0f, 50.0f, 50.0f);

	// 頂点値情報を更新
	SetVtxData(vtxData);

	// 当たり判定設定
	m_nCollNldx = pCollision->SetColl(
		CCollision::TAG_ENEMY_HAVE,
		CCollision::TYPE_RECTANGLE,
		CObjectX::GetVtxData().pos,
		CObjectX::GetVtxData().size,
		this);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 保持敵の終了処理
//-------------------------------------
void CEnemyHave::Uninit(void)
{
	// 当たり判定のポインタ取得
	CCollision *pCollision = CManager::GetCollision();

	// 当たり判定の有無を判定
	if (pCollision == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 当たり判定の終了処理
	pCollision->UninitColl(m_nCollNldx);

	// 自身のポインタを初期化
	m_pInstance = NULL;

	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- 保持敵の更新処理
//-------------------------------------
void CEnemyHave::Update(void)
{
	// 当たり判定のポインタ取得
	CCollision *pCollision = CManager::GetCollision();

	// 当たり判定の有無を判定
	if (pCollision == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 当たり判定位置の更新処理
	pCollision->UpdateData(
		m_nCollNldx,
		CObjectX::GetVtxData().pos,
		CObjectX::GetVtxData().size);

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
		UpdateShot();

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
//- 保持敵の設定処理
//-------------------------------------
void CEnemyHave::Set(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	VtxData vtxData;

	vtxData.pos = pos;
	vtxData.size = size;

	SetVtxData(vtxData);
}

//-------------------------------------
//- 保持敵の生成処理
//-------------------------------------
CEnemyHave *CEnemyHave::Create(MODEL modelType)
{
	// 保持敵の生成
	CEnemyHave *pEnemy = DBG_NEW CEnemyHave;

	// 生成の成功の有無を判定
	if (pEnemy != NULL)
	{
		// 初期化処理
		if (FAILED(pEnemy->Init(modelType)))
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
//-	保持敵のモデルのポインタ取得処理
//-------------------------------------
CEnemyHave * CEnemyHave::GetInstance(void)
{
	return m_pInstance;
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
	// 風だまの取得処理
	CKazedama *pKazedama = CKazedama::GetInstance();

	// 風だまの有無を判定
	if (pKazedama == NULL)
	{
		// 待機状態に変更
		m_data.state = STATE_WAIT;

		// プレイヤーの取得処理
		CPlayer *pPlayer = CPlayer::GetInstance();

		if (pPlayer == NULL)
		{
			return;
		}

		// 保持状態を更新
		pPlayer->SetHave(true);

		return;
	}

	// 情報取得
	VtxData vtxData = GetVtxData();
	
	// 情報取得（風だま）
	D3DXVECTOR3 posKaze = pKazedama->GetVtxData().pos;	// 位置

	// 位置を風だまの位置に変更
	vtxData.pos = posKaze;

	// 情報更新
	SetVtxData(vtxData);
}

//-------------------------------------
//-	保持敵の待機更新処理
//-------------------------------------
void CEnemyHave::UpdateWait(void)
{
	// プレイヤーの取得処理
	CPlayer *pPlayer = CPlayer::GetInstance();

	if (pPlayer == NULL)
	{
		return;
	}

	// 情報取得
	VtxData vtxData = GetVtxData();

	// 情報取得（風だま）
	D3DXVECTOR3 posPlayer = pPlayer->GetData().pos;	// 位置

	// 位置を風だまの位置に変更
	vtxData.pos = D3DXVECTOR3(posPlayer.x,posPlayer.y + 300.0f,posPlayer.z);

	// 情報更新
	SetVtxData(vtxData);
}

//-------------------------------------
//-	保持敵の発射更新処理
//-------------------------------------
void CEnemyHave::UpdateShot(void)
{
	// 変数を宣言（情報取得）
	VtxData vtxData = GetVtxData();

	// 加算処理
	vtxData.pos += m_data.move;			// 位置

	// 情報更新
	SetVtxData(vtxData);

	// 体力カウント
	m_data.nLifeCut++;

	// 体力カウントの判定
	if (m_data.nLifeCut >= m_data.nLife)
	{
		// 終了処理
		Uninit();
	}
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

	// 当たり判定の設定
}
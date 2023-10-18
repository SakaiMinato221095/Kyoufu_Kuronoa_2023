
//-===============================================
//-
//-	宝石ギミック処理[gimmick_jewel.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "gimmick_jewel.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

#include "game.h"
#include "player.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	宝石ギミックコンストラクタ
//-------------------------------------
CGimmickJewel::CGimmickJewel(int nPriority) : CGimmick(nPriority)
{
	m_pColl = NULL;
}

//-------------------------------------
//-	宝石ギミックデストラクタ
//-------------------------------------
CGimmickJewel::~CGimmickJewel()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CGimmickJewel::Load(void)
{
	return S_OK;
}

//-------------------------------------
//- 敵の読み込んだモデル破棄
//-------------------------------------
void CGimmickJewel::Unload(void)
{

}

//-------------------------------------
//- 宝石ギミック初期化処理
//-------------------------------------
HRESULT CGimmickJewel::Init(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// ギミックの初期化 if(初期化成功の有無を判定)
	if (FAILED(CGimmick::Init(model,pos,rot)))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 初期設定処理
	InitSet(typeEffect);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 宝石ギミック終了処理
//-------------------------------------
void CGimmickJewel::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// 当たり判定の終了処理
		m_pColl->Uninit();

		// 当たり判定の開放処理
		delete m_pColl;
		m_pColl = NULL;
	}

	// ギミックの終了
	CGimmick::Uninit();
}

//-------------------------------------
//- 宝石ギミック更新処理
//-------------------------------------
void CGimmickJewel::Update(void)
{
	// ギミックの更新処理
	CGimmick::Update();

	// 当たり判定の情報更新処理
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	// 敵との当たり判定
	if (m_pColl->GetData().stateHit == CMgrColl::STATE_HIT_DEAD)
	{
		// プレイヤーの強化処理
		PlayerPlus();

		// 終了処理
		Uninit();

		return;
	}
}

//-------------------------------------
//- 宝石ギミック描画処理
//-------------------------------------
void CGimmickJewel::Draw(void)
{
	// ギミックの描画処理
	CGimmick::Draw();
}

//-------------------------------------
//- 宝石ギミック生成処理（ギミック設定）
//-------------------------------------
CGimmickJewel * CGimmickJewel::Create(MODEL model, TYPE_EFFECT typeEffect, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 宝石ギミックポインタを宣言
	CGimmickJewel *pCGimmickJewel = DBG_NEW CGimmickJewel(4);

	// 生成の成功の有無を判定
	if (pCGimmickJewel != NULL)
	{
		// 初期化処理
		if (FAILED(pCGimmickJewel->Init(model, typeEffect, pos, rot)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCGimmickJewel == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 宝石ギミックポインタを返す
	return pCGimmickJewel;
}

//-------------------------------------
//- 宝石ギミック初期設定処理
//-------------------------------------
void CGimmickJewel::InitSet(TYPE_EFFECT typeEffect)
{
	m_type = typeEffect;	// 効果の種類

	// 当たり判定設定
	m_pColl = CColl::Create(
		CMgrColl::TAG_GIMMICK_JEWEL,
		GetVtxData().pos,
		GetVtxData().size);
}

//-------------------------------------
//- 宝石ギミックのプレイヤー強化処理
//-------------------------------------
void CGimmickJewel::PlayerPlus(void)
{
	// プレイヤー情報の取得処理
	CPlayer *pPlayer = CGame::GetPlayer();
	
	if (pPlayer == NULL)
	{
		return;
	}
	
	// 強化処理
	pPlayer->SetPlus(1.5f,120);
}
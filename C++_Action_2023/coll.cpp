
//================================================
//=
//=	当たり判定の処理[coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "coll.h"

#include "manager.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	コンスト定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	当たり判定のコンストラクタ
//-------------------------------------
CColl::CColl()
{
	ZeroMemory(&m_data, sizeof(m_data));
}

//-------------------------------------
//-	当たり判定のデストラクタ
//-------------------------------------
CColl::~CColl()
{

}

//-------------------------------------
//- 当たり判定の初期化処理
//-------------------------------------
HRESULT CColl::Init(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期設定処理
	InitSet(tag, type, pos, size);

	return S_OK;
}

//-------------------------------------
//- 当たり判定の終了処理
//-------------------------------------
void CColl::Uninit(void)
{

}

//-------------------------------------
//- 当たり判定の更新処理
//-------------------------------------
void CColl::Update(void)
{

}

//-------------------------------------
//- 当たり判定の描画処理
//-------------------------------------
void CColl::Draw(void)
{
}

//-------------------------------------
//- 当たり判定の生成処理
//-------------------------------------
CColl * CColl::Create(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)

{
	// 当たり判定の生成
	CColl *pCollision = DBG_NEW CColl;

	// 生成の成功の有無を判定
	if (pCollision != NULL)
	{
		// 初期化処理
		if (FAILED(pCollision->Init(tag,type,pos,size)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCollision == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// 当たり判定のポインタを返す
	return pCollision;
}

//-------------------------------------
//- タグの相手を判定設定処理
//-------------------------------------
void CColl::UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 設定したタグの当たり判定の有無を設定
	m_data.pos = pos;		// 位置
	m_data.size = size;		// サイズ
}

//-------------------------------------
//- 当たり判定の接触処理
//-------------------------------------
bool CColl::Hit(CMgrColl::TAG hitTag, CMgrColl::STATE_HIT stateHit)
{
	// 当たり判定のポインタ取得
	CMgrColl *pMgrColl = CManager::GetMgrColl();		

	// 当たり判定の有無を判定
	if (pMgrColl == NULL)
	{
		// 処理を抜ける
		return false;
	}

	// 変数宣言
	bool bHitTgt = false;	// 目的の接触の有無

	// 当たり判定管理の接触処理
	bHitTgt = pMgrColl->Hit(m_data.nNldx,hitTag,stateHit);

	return bHitTgt;
}

//-------------------------------------
//- タグの相手を判定設定処理
//-------------------------------------
void CColl::SetTagTgt(CMgrColl::TAG hitTag, bool bIsActive)
{
	// 設定したタグの当たり判定の有無を設定
	m_data.bTagTgt[hitTag] = bIsActive;
}

//-------------------------------------
//- 当たり判定の情報の設定処理
//-------------------------------------
void CColl::SetData(Data data)
{
	m_data = data;
}

//-------------------------------------
//- 当たり判定の情報の取得処理
//-------------------------------------
CColl::Data CColl::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- 当たり判定の接触情報の設定処理
//-------------------------------------
void CColl::SetHitData(HitData data)
{
	// 変数宣言（情報取得）
	int nHitNum = m_data.nHitNldxMax;	// 現在の最大接触数

	// 接触情報を格納
	m_data.hitData[nHitNum].nNldx = data.nNldx;	// 当たり判定番号

	// 最大接触数を加算
	m_data.nHitNldxMax++;
}

//-------------------------------------
//- 当たり判定の接触情報のリセット処理
//-------------------------------------
void CColl::ResetHitData(void)
{
	// 変数宣言（情報取得）
	int nHitNum = m_data.nHitNldxMax;	// 現在の最大接触数

	for (int nCount = 0; nCount < nHitNum; nCount++)
	{
		// 接触番号の初期化
		m_data.hitData[nHitNum].nNldx = -1;
	}

	// 接触最大数の初期化
	m_data.nHitNldxMax = 0;
}

//-------------------------------------
//- 当たり判定の初期設定処理
//-------------------------------------
void CColl::InitSet(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_data.tag = tag;
	m_data.type = type;
	m_data.pos = pos;
	m_data.size = size;
}

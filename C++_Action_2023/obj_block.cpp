
//-===============================================
//-
//-	ブロッグオブジェクト処理[obj_block.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "obj_block.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

#include "coll.h"

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
//-	ブロッグオブジェクトのコンストラクタ
//-------------------------------------
CObjBlock::CObjBlock(int nPriority) : CObjectXNone(nPriority)
{

}

//-------------------------------------
//-	ブロッグオブジェクトのデストラクタ
//-------------------------------------
CObjBlock::~CObjBlock()
{

}

//-------------------------------------
//- 敵のモデル読み込み
//-------------------------------------
HRESULT CObjBlock::Load(void)
{
	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 敵の読み込んだモデル破棄
//-------------------------------------
void CObjBlock::Unload(void)
{

}

//-------------------------------------
//- ブロッグオブジェクトの初期化処理（効果なしオブジェクト設定）
//-------------------------------------
HRESULT CObjBlock::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 効果なしオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectXNone::Init(model, pos, rot)))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 初期設定
	InitSet();

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- ブロッグオブジェクトの終了処理
//-------------------------------------
void CObjBlock::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// 当たり判定の終了処理
		m_pColl->Uninit();

		// 当たり判定の開放処理
		delete m_pColl;
		m_pColl = NULL;
	}

	// 効果なしオブジェクトの終了
	CObjectXNone::Uninit();
}

//-------------------------------------
//- ブロッグオブジェクトの更新処理
//-------------------------------------
void CObjBlock::Update(void)
{
	// 効果なしオブジェクトの更新処理
	CObjectXNone::Update();

	// 当たり判定の情報更新処理
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);
}

//-------------------------------------
//- ブロッグオブジェクトの描画処理
//-------------------------------------
void CObjBlock::Draw(void)
{
	// 効果なしオブジェクトの描画処理
	CObjectXNone::Draw();
}

//-------------------------------------
//- ブロッグオブジェクトの生成処理（効果なしオブジェクト設定）
//-------------------------------------
CObjBlock * CObjBlock::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ブロッグオブジェクトのポインタを宣言
	CObjBlock *pCObjBlock = DBG_NEW CObjBlock(4);

	// 生成の成功の有無を判定
	if (pCObjBlock != NULL)
	{
		// 初期化処理
		if (FAILED(pCObjBlock->Init(model, pos, rot)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCObjBlock == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// ブロッグオブジェクトのポインタを返す
	return pCObjBlock;
}

//-------------------------------------
//- ブロッグオブジェクトの初期設定
//-------------------------------------
void CObjBlock::InitSet(void)
{
	// 当たり判定設定
	m_pColl = CColl::Create(
		CMgrColl::TAG_BLOCK,
		GetVtxData().pos,
		GetVtxData().size);
}

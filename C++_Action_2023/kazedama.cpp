
//================================================
//=
//=	風だまの処理[kazedama.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "kazedama.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

#include "player.h"

#include "coll.h"

#include "enemy_have.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//= コンスト定義
//=======================================

// 風だまテクスチャのコンスト定義
const char *pTextureKazedama[] =
{
	NULL,
};

//-======================================
//-	静的変数宣言
//-======================================

int CKazedama::m_nTextureNldx[TEX_MAX] = {};			// テクスチャ

//-------------------------------------
//-	風だまのコンストラクタ
//-------------------------------------
CKazedama::CKazedama(int nPriority) : CObjectBillboard(nPriority)
{
	ZeroMemory(&m_data, sizeof(m_data));
	m_pColl = NULL;
	m_pEnemyHave = NULL;
}

//-------------------------------------
//-	風だまのデストラクタ
//-------------------------------------
CKazedama::~CKazedama()
{

}

//-------------------------------------
//- 風だまのテクスチャの読み込み
//-------------------------------------
HRESULT CKazedama::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetInstance()->GetManagerTexture();

	// テクスチャ管理の有無を判定
	if (pManagerTexture == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// テクスチャ設定
	for (int nCount = 0; nCount < TEX_MAX; nCount++)
	{
		// テクスチャ番号の取得（テクスチャの割当）
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureKazedama[nCount]);

		// テクスチャの読み込み成功の有無を確認
		if (m_nTextureNldx[nCount] == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 風だまの読み込んだテクスチャの破棄
//-------------------------------------
void CKazedama::Unload(void)
{

}

//-------------------------------------
//- 風だまの初期化処理
//-------------------------------------
HRESULT CKazedama::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 初期設定処理
	InitSet(pos,size,color,move,typeRot);

	// ビルボードオブジェクトの初期化
	CObjectBillboard::Init();

	if (m_pColl == NULL)
	{
		// 当たり判定設定
		m_pColl = CColl::Create(
			CMgrColl::TAG_KAZEDAMA,
			CMgrColl::TYPE_RECTANGLE,
			GetVtxData().pos,
			GetVtxData().size);

		// 相手タグの設定処理
		m_pColl->SetTagTgt(CMgrColl::TAG_ENEMY, true);
	}
	else
	{
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 風だまの終了処理
//-------------------------------------
void CKazedama::Uninit(void)
{
	if (m_pColl != NULL)
	{
		// 当たり判定の終了処理
		m_pColl->Uninit();

		// 当たり判定の開放処理
		delete m_pColl;
		m_pColl = NULL;
	}

	if (m_pEnemyHave != NULL)
	{
		// 保持敵の終了処理
		m_pEnemyHave->Uninit();
		m_pEnemyHave = NULL;
	}

	// ビルボードオブジェクトの終了
	CObjectBillboard::Uninit();
}

//-------------------------------------
//- 風だまの更新処理
//-------------------------------------
void CKazedama::Update(void)
{
	// 当たり判定の情報更新処理
	m_pColl->UpdateData(
		GetVtxData().pos,
		GetVtxData().size);

	switch (m_data.state)
	{
	case STATE_ACTIVE:

		// 行動処理
		Active();

		break;

	case STATE_RETURN:

		// 帰還処理
		Return();

		break;
	}

	// 移動処理
	UpdateMove();

	// ビルボードオブジェクトの更新処理
	CObjectBillboard::Update();
}

//-------------------------------------
//- 風だまの描画処理
//-------------------------------------
void CKazedama::Draw(void)
{
	// デバイスを取得
	CRenderer *pRenderer = CManager::GetInstance()->GetRenderer();

	// デバイスの情報取得の成功を判定
	if (pRenderer == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// Zテストの設定
	pRenderer->SetZTest(true);

	// アルファテストの設定
	pRenderer->SetAlphaTest(true);

	// 風だまの描画処理
	CObjectBillboard::Draw();

	// Zテストの解除
	pRenderer->SetZTest(false);

	// アルファテストの解除
	pRenderer->SetAlphaTest(false);
}

//-------------------------------------
//- 風だまの生成処理
//-------------------------------------
CKazedama * CKazedama::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, TYPE_ROT typeRot)
{
	// 風だまの生成
	CKazedama *pCKazedama = DBG_NEW CKazedama(5);

	// 生成の成功の有無を判定
	if (pCKazedama != NULL)
	{
		// 初期化処理
		if (FAILED(pCKazedama->Init(tex,pos,size,color,move,typeRot)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCKazedama == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 風だまのポインタを返す
	return pCKazedama;
}

//-------------------------------------
//- 風だまの親の情報更新処理
//-------------------------------------
void CKazedama::SetParent(D3DXVECTOR3 pos)
{
	// 親の位置を更新
	m_data.posParent = pos;
}

//-------------------------------------
//- 風だまの失敗時の消滅時の処理
//-------------------------------------
void CKazedama::LostFail(void)
{
	// 終了処理
	Uninit();
}

//-------------------------------------
//- 風だまの成功時の消滅時の処理
//-------------------------------------
void CKazedama::LostSucce(void)
{
	// 終了処理
	Uninit();
}

//-------------------------------------
//- 風だまの設定処理
//-------------------------------------
void CKazedama::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color, D3DXVECTOR3 move, CKazedama::TYPE_ROT typeRot)
{
	// 変数を宣言（情報取得）
	CObjectBillboard::VtxData vtxData = GetVtxData();

	vtxData.pos = pos;			// 位置
	vtxData.size = size;		// 大きさ
	vtxData.color = color;		// 色
	m_data.move = move;			// 移動量
	m_data.typeRot = typeRot;	// 向きの種類

	// 情報更新
	SetVtxData(vtxData);
}

//-------------------------------------
//- 風だまの移動処理
//-------------------------------------
void CKazedama::UpdateMove(void)
{
	// 変数を宣言（情報取得）
	CObjectBillboard::VtxData vtxData = GetVtxData();
	
	// 加算処理
	vtxData.pos += m_data.move;			// 位置
	m_data.moveAccum += m_data.move;	// 移動の蓄積値

	// 情報更新
	SetVtxData(vtxData);
}

//-------------------------------------
//- 風だまの活動時の処理
//-------------------------------------
void CKazedama::Active(void)
{
	// 敵との当たり判定
	if (m_pColl->Hit(CMgrColl::TAG_ENEMY,CMgrColl::STATE_HIT_DEAD) == true)
	{
		// 獲得時の処理
		Obtain();
	}
	else
	{
		// 変数宣言
		bool bIsSwitch = false;	// 条件分岐の条件の有無

		// 向きの種類
		switch (m_data.typeRot)
		{
		case TYPE_ROT_LEFT:

			// 移動蓄積値の判定（目的の移動蓄積）
			if (m_data.moveAccum.x <= -200.0f)
			{
				bIsSwitch = true;
			}

			break;

		case TYPE_ROT_RIGHT:

			// 移動蓄積値の判定（目的の移動蓄積）
			if (m_data.moveAccum.x >= 200.0f)
			{
				bIsSwitch = true;
			}

			break;
		}

		// 風だまの蓄積値を判定
		if (bIsSwitch == true)
		{
			// 帰還状態に変更
			m_data.state = STATE_RETURN;
		}
	}

}

//-------------------------------------
//- 風だまの帰還時の処理
//-------------------------------------
void CKazedama::Return(void)
{
	// 変数を宣言（情報取得）
	CObjectBillboard::VtxData vtxData = GetVtxData();

	// 移動量の角度を算出
	float fRotMove = atan2f(
		m_data.move.x, 
		m_data.move.y);

	// 目的の角度を算出
	float fRotDest = atan2f(
		vtxData.pos.x - m_data.posParent.x,
		vtxData.pos.y - m_data.posParent.y);
	
	// 移動方向の差分
	float fRotDiff = fRotDest - fRotMove;

	// 角度の修正
	if (fRotDiff > D3DX_PI)
	{
		fRotDiff -= (D3DX_PI * 2);
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotDiff += (D3DX_PI * 2);
	}

	// 移動方向（角度）の補正
	fRotMove += fRotDiff * 1.0f;

	// 角度の修正
	if (fRotMove > D3DX_PI)
	{
		fRotMove -= (D3DX_PI * 2);
	}
	else if (fRotDiff < -D3DX_PI)
	{
		fRotMove += (D3DX_PI * 2);
	}

	// 移動量を算出
	m_data.move.x = sinf(fRotMove) * -50.0f;
	m_data.move.y = cosf(fRotMove) * -50.0f;

	// 変数宣言
	bool bIsSwitch = false;	// 条件分岐の条件の有無

	// 向きの種類
	switch (m_data.typeRot)
	{
	case TYPE_ROT_LEFT:

		// 位置の判定（親の位置）
		if (vtxData.pos.x >= m_data.posParent.x)
		{
			bIsSwitch = true;
		}

		break;

	case TYPE_ROT_RIGHT:

		// 位置の判定（親の位置）
		if (vtxData.pos.x <= m_data.posParent.x)
		{
			bIsSwitch = true;
		}

		break;
	}

	if(bIsSwitch == true)
	{
		if (m_pEnemyHave != NULL)
		{
			// 成功状態に変更
			m_data.state = STATE_SUCCE;
		}
		else if(m_pEnemyHave == NULL)
		{
			// 成功状態に変更
			m_data.state = STATE_FAIL;
		}

	}
}

//-------------------------------------
//- 風だまの情報取得処理
//-------------------------------------
CKazedama::Data CKazedama::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- 風だまの獲得時の処理
//-------------------------------------
void CKazedama::Obtain(void)
{
	// 帰還状態に変更
	m_data.state = STATE_RETURN;

	// 保持敵を生成
	m_pEnemyHave = CEnemyHave::Create(
		CEnemyHave::MODEL_ALIEN_000,
		CEnemyHave::STATE_OBTAIN,
		GetVtxData().pos,
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(50.0f, 50.0f, 50.0f));
}
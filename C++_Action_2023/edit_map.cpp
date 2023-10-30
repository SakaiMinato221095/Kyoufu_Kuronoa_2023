
//================================================
//=
//=	マップエディタの処理[edit_map.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "edit_map.h"

#include "Input.h"

#include "manager.h"
#include "camera.h"

#include "object.h"

#include "obj_block.h"
#include "goal.h"
#include "enemy.h"
#include "gimmick_jewel.h"
#include "obj_teach.h"

#include "file_map.h"

//=======================================
//=	マクロ定義
//=======================================

#define SIZE_TILE_CRITERIA_X	(150.0f)		// 一マスの基準（X軸）
#define SIZE_TILE_CRITERIA_Y	(150.0f)		// 一マスの基準（Y軸）

//=======================================
//= コンスト定義
//=======================================

//=======================================
//=	静的変数宣言
//=======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CEditMap::CEditMap()
{
	ZeroMemory(&m_editData, sizeof(m_editData));
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CEditMap::~CEditMap()
{

}

//-------------------------------------
//- マップエディタの初期化処理
//-------------------------------------
HRESULT CEditMap::Init(void)
{
	// エディットオブジェクトを生成
	SetEditObj(m_editData.type);

	// カメラの操作を変更
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != NULL)
	{
		pCamera->SetMode(CCamera::MODE_EDIT);
	}

	return S_OK;
}

//-------------------------------------
//- マップエディタの終了処理
//-------------------------------------
void CEditMap::Uninit(void)
{
	// カメラの操作を変更
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	if (pCamera != NULL)
	{
		pCamera->SetMode(CCamera::MODE_FOLLOWING);
	}

	if (m_editData.pObjX != NULL)
	{
		// 終了処理
		m_editData.pObjX->Uninit();
		m_editData.pObjX = NULL;
	}

	if (m_editData.pObjBill != NULL)
	{
		// 終了処理
		m_editData.pObjBill->Uninit();
		m_editData.pObjBill = NULL;
	}
}

//-------------------------------------
//- マップエディタの更新処理
//-------------------------------------
void CEditMap::Update(void)
{
	// エディットオブジェクトの移動処理
	InputObjMove();

	// 種類変更入力処理
	InputChangeType();

	// オブジェクト設置入力処理
	InputSetObj();

	// マップオブジェクトセーブ処理
	InputSave();
}

//-------------------------------------
//- マップエディタの描画処理
//-------------------------------------
void CEditMap::Draw(void)
{
}

//-------------------------------------
//- マップエディタの生成処理
//-------------------------------------
CEditMap * CEditMap::Create(void)
{
	// マップエディタの生成
	CEditMap *pEditMap = DBG_NEW CEditMap;

	// 生成の成功の有無を判定
	if (pEditMap != NULL)
	{
		// 初期化処理
		if (FAILED(pEditMap->Init()))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pEditMap == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 通常敵のポインタを返す
	return pEditMap;
}

//-------------------------------------
//- マップエディタのオブジェクト移動入力処理
//-------------------------------------
void CEditMap::InputObjMove(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	if (pInputKeyboard->GetPress(DIK_LSHIFT) == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_W) == true)
		{
			// 上の移動処理
			SetObjMove(D3DXVECTOR3(0.0f, SIZE_TILE_CRITERIA_Y,0.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_S) == true)
		{
			// 下の移動処理
			SetObjMove(D3DXVECTOR3(0.0f, -SIZE_TILE_CRITERIA_Y, 0.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_A) == true)
		{
			// 左の移動処理
			SetObjMove(D3DXVECTOR3(-SIZE_TILE_CRITERIA_X, 0.0f, 0.0f));
		}
		else if (pInputKeyboard->GetTrigger(DIK_D) == true)
		{
			// 右の移動処理
			SetObjMove(D3DXVECTOR3(SIZE_TILE_CRITERIA_X, 0.0f, 0.0f));
		}
	}
}

//-------------------------------------
//- マップエディタのオブジェクト設置入力処理
//-------------------------------------
void CEditMap::InputSetObj(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		// オブジェクト設置処理
		SetObj();
	}
}

//-------------------------------------
//- マップエディタの種類加算設定処理
//-------------------------------------
void CEditMap::InputChangeType(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_W) == true)
		{
			// 種類減算設定処理
			SetSubType();
		}
		else if (pInputKeyboard->GetTrigger(DIK_S) == true)
		{
			// 種類加算設定処理
			SetAddType();
		}
	}
}

//-------------------------------------
//- マップエディタの種類加算設定処理
//-------------------------------------
void CEditMap::InputSave(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	// マップファイルの情報取得
	CFileMap *pFileMap = CManager::GetInstance()->GetFileMap();

	if (pFileMap == NULL)
	{
		return;
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		// マップファイルのセーブ
		pFileMap->Save();
	}
}

//-------------------------------------
//- マップエディタのエディットオブジェクト設定処理
//-------------------------------------
void CEditMap::SetEditObj(TYPE type)
{
	if (m_editData.pObjX != NULL)
	{
		// 終了処理
		m_editData.pObjX->Uninit();
		m_editData.pObjX = NULL;
	}

	if (m_editData.pObjBill != NULL)
	{
		// 終了処理
		m_editData.pObjBill->Uninit();
		m_editData.pObjBill = NULL;
	}

	// エディットの種類を代入
	m_editData.type = type;

	switch (type)
	{
	case TYPE_BLOCK:

		// ブロックの生成
		m_editData.pObjX = CObjBlock::Create(
			CObjBlock::MODEL_BLOCK_000,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_GOAL:

		// ゴールの生成
		m_editData.pObjX = CGoal::Create(
			CGoal::MODEL_GOAL_000,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_PLAYER:

		break;

	case TYPE_ENEMY:

		// 敵の生成
		m_editData.pObjX = CEnemy::Create(
			CEnemy::MODEL_ALIEN_000,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_GIMMICK_SPEED:

		// 速度宝石ギミックの生成
		m_editData.pObjX = CGimmickJewel::Create(
			CGimmickJewel::MODEL_JEWEL_000,
			CGimmickJewel::TYPE_EFFECT_SPEED_UP,
			m_editData.pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		break;

	case TYPE_TEACH_MOVE:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_MOVE,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_JUMP:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_JUMP,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_KAZEDAMA:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_KAZEDAMA,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_SHOT:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_SHOT,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;

	case TYPE_TEACH_DOUBLE_JUMP:

		m_editData.pObjBill = CObjTeach::Create(
			CObjTeach::TEX_TEACH_DOUBLE_JUMP,
			D3DXVECTOR3(m_editData.pos.x, m_editData.pos.y, 100.0f),
			D3DXVECTOR3(400.0f, 200.0f, 50.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		break;
	}

	if (m_editData.pObjX != NULL)
	{
		// 終了処理
		m_editData.pObjX->IsUpdateStop(false);
	}

	if (m_editData.pObjBill != NULL)
	{
		// 終了処理
		m_editData.pObjBill->IsUpdateStop(false);
	}
}

//-------------------------------------
//- マップエディタの種類加算設定処理
//-------------------------------------
void CEditMap::SetAddType(void)
{
	// 種類を加算
	m_editData.type = (TYPE)(m_editData.type + 1);

	if (m_editData.type == TYPE_MAX)
	{
		// 種類を初期化
		m_editData.type = (TYPE)(0);
	}

	// エディットオブジェクトの種類設定処理
	SetEditObj(m_editData.type);
}

//-------------------------------------
//- マップエディタの種類減算設定処理
//-------------------------------------
void CEditMap::SetSubType(void)
{
	// 種類を加算
	m_editData.type = (TYPE)(m_editData.type - 1);

	if (m_editData.type <= TYPE(0))
	{
		// 種類を初期化
		m_editData.type = (TYPE)(TYPE_MAX - 1);
	}

	// エディットオブジェクトの種類設定処理
	SetEditObj(m_editData.type);
}

//-------------------------------------
//- マップエディタのオブジェクト移動処理
//-------------------------------------
void CEditMap::SetObjMove(D3DXVECTOR3 move)
{
	// エディットの位置に移動量を加算
	m_editData.pos += move;

	if (m_editData.pObjX != NULL)
	{
		// 情報を頂点値取得
		CObjectX::VtxData vtxData = m_editData.pObjX->GetVtxData();

		// 位置に移動量を加算
		vtxData.pos += move;

		// 情報更新
		m_editData.pObjX->SetVtxData(vtxData);
	}

	if (m_editData.pObjBill != NULL)
	{
		// 情報を頂点値取得
		CObjectBillboard::VtxData vtxData = m_editData.pObjBill->GetVtxData();

		// 位置に移動量を加算
		vtxData.pos += move;

		// 情報更新
		m_editData.pObjBill->SetVtxData(vtxData);
	}
}

//-------------------------------------
//- マップエディタのオブジェクト設定処理
//-------------------------------------
void CEditMap::SetObj(void)
{
	// マップファイルの情報取得
	CFileMap *pFileMap = CManager::GetInstance()->GetFileMap();

	if (pFileMap == NULL)
	{
		return;
	}

	// エディットのオブジェクト設定処理
	if (pFileMap->SetObj(m_editData) == true)
	{
		m_editData.pObjX = NULL;
		m_editData.pObjBill = NULL;

		SetEditObj(m_editData.type);
	}
}
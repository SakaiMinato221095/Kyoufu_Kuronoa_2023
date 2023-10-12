
//-===============================================
//-
//-	戦闘プレイヤー処理[player_battle.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player_battle.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"

#include "Input.h"
#include "xinput.h"
#include "sound.h"
#include "debugproc.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayerBattle::CPlayerBattle()
{
	// 値をクリア
	m_stateType = STATE_TYPE_NEUTRAL;
	m_stateTypeNew = m_stateType;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPlayerBattle::~CPlayerBattle()
{

}

//-------------------------------------
//- 戦闘プレイヤーの初期化処理
//-------------------------------------
HRESULT CPlayerBattle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// 戦闘プレイヤーの設定処理
	Set(pos,rot);

	// プレイヤーの初期化処理
	CPlayer::Init(modelType, motionType,STATE_TYPE_MAX);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 戦闘プレイヤーの終了処理
//-------------------------------------
void CPlayerBattle::Uninit(void)
{
	// プレイヤーの終了処理
	CPlayer::Uninit();
}

//-------------------------------------
//- 戦闘プレイヤーの更新処理
//-------------------------------------
void CPlayerBattle::Update(void)
{
	// プレイヤーの更新処理
	CPlayer::Update();

	// モーションの更新処理
	UpdateMotion();
}

//-------------------------------------
//- 戦闘プレイヤーの描画処理
//-------------------------------------
void CPlayerBattle::Draw(void)
{
	// プレイヤーの描画処理
	CPlayer::Draw();
}

//-------------------------------------
//- 戦闘プレイヤーの生成処理
//-------------------------------------
CPlayerBattle *CPlayerBattle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType)
{
	// 戦闘プレイヤーのポインタを宣言
	CPlayerBattle *pCPlayerBattle = new CPlayerBattle;

	// 生成の成功の有無を判定
	if (pCPlayerBattle != NULL)
	{
		// 初期化処理
		if (FAILED(pCPlayerBattle->Init(pos, rot,modelType,motionType,STATE_TYPE_MAX)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCPlayerBattle == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// 戦闘プレイヤーのポインタを返す
	return pCPlayerBattle;
}

//-------------------------------------
//- 戦闘プレイヤーの設定処理
//-------------------------------------
void CPlayerBattle::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 変数宣言（プレイヤーの値の情報取得）
	CPlayer::Data data = CPlayer::GetData();

	// 値の代入
	data.pos = pos;	// 位置
	data.rot = rot;	// 向き

	// 情報更新（プレイヤーの値）
	CPlayer::SetData(data);
}

//-------------------------------------
//- 戦闘プレイヤーのモーション更新処理
//-------------------------------------
void CPlayerBattle::UpdateMotion(void)
{
	// 変数宣言（情報取得）
	CMotion *pMotion = GetMotion();		// モーション
	D3DXVECTOR3 move = GetData().move;	// 移動量
	
	// 状態を判定
	if (m_stateTypeNew == STATE_TYPE_NEUTRAL ||
		m_stateTypeNew == STATE_TYPE_MOVE)
	{
		// 移動量で状態を変更
		if (move.x >= 0.3f ||
			move.x <= -0.3f ||
			move.z >= 0.3f ||
			move.z <= -0.3f)
		{
			// 移動状態に変更
			m_stateTypeNew = STATE_TYPE_MOVE;
		}
		else
		{
			// 待機状態の変更
			m_stateTypeNew = STATE_TYPE_NEUTRAL;
		}
	}

	// モーションの終了状況を判定
	if (pMotion->IsFinsih() == true)
	{
		// モーションの更新
		pMotion->Update();
	}
	else
	{
		// 待機状態を設定
		m_stateTypeNew = STATE_TYPE_NEUTRAL;
	}

	// モーションの設定処理
	if (m_stateType != m_stateTypeNew)
	{
		// 状態の更新
		m_stateType = m_stateTypeNew;

		// 状態の判定
		if (m_stateType == STATE_TYPE_NEUTRAL)
		{
			// 待機モーションの設定
			pMotion->Set(STATE_TYPE_NEUTRAL);
		}
		else if (m_stateType == STATE_TYPE_MOVE)
		{
			// 移動モーションの設定
			pMotion->Set(STATE_TYPE_MOVE);
		}
	}
}
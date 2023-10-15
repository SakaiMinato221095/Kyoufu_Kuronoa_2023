
//-===============================================
//-
//-	プレイヤー処理[player.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "Input.h"
#include "xinput.h"

#include "sound.h"
#include "debugproc.h"

#include "camera.h"

#include "coll.h"

#include "kazedama.h"
#include "enemy_have.h"

//-======================================
//-	マクロ定義
//-======================================

#define PLAYER_SPEED	(4.0f)	//プレイヤーの速度

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CPlayer::CPlayer()
{
	// 値をクリア
	ZeroMemory(&m_data, sizeof(m_data));

	m_bJump = false;
	m_bHave = false;

	ZeroMemory(m_mtxWorld, sizeof(D3DXMATRIX));

	m_pColl = NULL;

	ZeroMemory(m_apModel, sizeof(m_apModel));

	m_nNumModel = 0;

	m_pMotion = NULL;

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CPlayer::~CPlayer()
{

}

//-------------------------------------
//- プレイヤーの初期化処理
//-------------------------------------
HRESULT CPlayer::Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax)
{
	// モデルのパーツ数を取得
	m_nNumModel = CModel::GetPartsNum(modelType);

	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		// 階層構造Xオブジェクトの有無を判定
		if (m_apModel[nCount] == NULL)
		{
			// 階層構造Xオブジェクトの生成
			m_apModel[nCount] = CModel::Create(modelType, nCount);

			// 階層構造Xオブジェクトの設定
			m_apModel[nCount]->SetParent(m_apModel, modelType, nCount);
		}
	}

	if (m_pMotion == NULL)
	{
		// モーションの生成
		m_pMotion = CMotion::Create(m_nNumModel, nStateMax);

		// ファイルを読み込み
		m_pMotion->SetFile(motionType);

		// モデルの設定
		m_pMotion->SetModel(m_apModel, 0);

		// 待機モーションを設定
		m_pMotion->Set(0);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- プレイヤーの終了処理
//-------------------------------------
void CPlayer::Uninit(void)
{
	// モデルの終了処理
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		if (m_nNumModel - 1 == nCount)
		{
			int nData = 0;
		}

		if (m_apModel[nCount] != NULL)
		{
			// モデルの開放処理
			m_apModel[nCount]->Uninit();

			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	// モーションの終了処理
	if (m_pMotion != NULL)
	{
		// モーションの開放
		m_pMotion->Uninit();

		delete m_pMotion;
		m_pMotion = NULL;
	}

	// 自身のポインタを初期化
	m_pInstance = NULL;

	// 自分自身のポインタの開放
	Release();
}

//-------------------------------------
//- プレイヤーの更新処理
//-------------------------------------
void CPlayer::Update(void)
{
	// 前回の位置を更新
	m_data.posOld = m_data.pos;

	// 移動の入力処理
	InputMove();

	// ジャンプの入力処理
	InputJump();

	// アクションの入力処理
	InputAction();

	// 向きの更新処理
	UpdateRot();

	// 位置情報の更新処理
	UpdatePos();

	// デバック表示
	DebugPlayer();
}

//-------------------------------------
//- プレイヤーの描画処理
//-------------------------------------
void CPlayer::Draw(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_data.pos;	// 位置情報
	D3DXVECTOR3 rot = m_data.rot;	// 向き情報

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return;
	}

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(
		D3DTS_WORLD,
		&m_mtxWorld);

	// パーツ数の描画処理
	for (int nCount = 0; nCount < m_nNumModel; nCount++)
	{
		m_apModel[nCount]->Draw();
	}
}

//-------------------------------------
//- プレイヤーのモーション情報取得処理
//-------------------------------------
void CPlayer::Hit(int nDamage)
{

}

//-------------------------------------
//- プレイヤーのモーション情報取得処理
//-------------------------------------
CMotion *CPlayer::GetMotion(void)
{
	// モーションを返す
	return m_pMotion;
}

//-------------------------------------
//- プレイヤーのモデルの情報取得
//-------------------------------------
CModel *CPlayer::GetModel(int nNumParts)
{
	return m_apModel[nNumParts];
}

//-------------------------------------
//- プレイヤーの値設定処理
//-------------------------------------
void CPlayer::SetData(Data data)
{
	m_data = data;
}

//-------------------------------------
//- プレイヤーの値取得処理
//-------------------------------------
CPlayer::Data CPlayer::GetData(void)
{
	return m_data;
}

//-------------------------------------
//- プレイヤーの所持状態の設定処理
//-------------------------------------
void CPlayer::SetHave(bool bHave)
{
	m_bHave = bHave;
}

//-------------------------------------
//- プレイヤーのインスタンス取得処理
//-------------------------------------
CPlayer * CPlayer::GetInstance(void)
{
	return m_pInstance;
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CPlayer::UpdatePos(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 pos = m_data.pos;	// 位置
	D3DXVECTOR3 move = m_data.move;	// 移動量

	// 重力の処理
	move.y -= 1.0f;

	// 位置情報に移動量を加算
	pos += move;

	// 移動量を減衰
	move.x += (0.0f - move.x) * 0.3f;
	move.z += (0.0f - move.z) * 0.3f;

	//縦幅の処理
	if (pos.y <= 0.0f)
	{
		m_bJump = false;
		pos.y = 0.0f;
	}

	// 情報更新
	m_data.pos = pos;
	m_data.move = move;
}

//-------------------------------------
//- プレイヤーの向き処理
//-------------------------------------
void CPlayer::UpdateRot(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_data.rot;			// 向き
	D3DXVECTOR3 rotDest = m_data.rotDest;	// 目的の向き

	// 目的の向きの補正
	if (rotDest.y > D3DX_PI)
	{
		rotDest.y += -D3DX_PI * 2;
	}
	else if (rotDest.y < -D3DX_PI)
	{
		rotDest.y += D3DX_PI * 2;
	}

	// 差分の向きを算出
	float rotDiff = rotDest.y - rot.y;

	// 差分の向きを補正
	if (rotDiff > D3DX_PI)
	{
		rotDiff += -D3DX_PI * 2;
	}
	else if (rotDiff < -D3DX_PI)
	{
		rotDiff += D3DX_PI * 2;
	}

	//移動方向（角度）の補正
	rot.y += rotDiff * 0.15f;

	// 向きの補正
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	// 情報更新
	m_data.rot = rot;			// 向き
	m_data.rotDest = rotDest;	// 目的の向き
}

//-------------------------------------
//- プレイヤーの移動処理
//-------------------------------------
void CPlayer::InputMove(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言
	D3DXVECTOR3 move = m_data.move;			// 移動量を取得
	D3DXVECTOR3 rotDest = m_data.rotDest;	// 目的の回転量を取得

	// カメラの情報を取得
	CCamera *pCamera = CManager::GetCamera();

	// カメラの向きを取得
	D3DXVECTOR3 rotCamera = pCamera->GetData().rot;

	if (
		pInputKeyboard->GetPress(DIK_A) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_LEFT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Aキーが押されたとき

		move.x -= sinf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;
		move.z -= cosf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;

		rotDest.y = (D3DX_PI * 0.5f) + rotCamera.y;
	}
	else if (
		pInputKeyboard->GetPress(DIK_D) == true ||
		pXInput->GetPress(CXInput::TYPE_STICK_RIGHT, CXInput::TYPE_INPUT_STICK_L) == true)
	{//Dキーが押されたとき

		move.x += sinf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;
		move.z += cosf((D3DX_PI * 0.5f) + rotCamera.y) * PLAYER_SPEED;

		rotDest.y = -(D3DX_PI * 0.5f) + rotCamera.y;
	}

	// 情報更新
	m_data.move = move;			// 移動量
	m_data.rotDest = rotDest;	// 目的の向き

}

//-------------------------------------
//- プレイヤーのジャンプ入力処理
//-------------------------------------
void CPlayer::InputJump(void)
{
	if (m_bJump == false)
	{
		// 通常ジャンプ処理
		InputNormalJump();
	}
	else if (m_bJump == true && m_bHave == true)
	{
		// 二段ジャンプ
		InputDoubleJump();
	}
}

//-------------------------------------
//- プレイヤーの通常ジャンプ入力処理
//-------------------------------------
void CPlayer::InputNormalJump(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言
	D3DXVECTOR3 move = m_data.move;			// 移動量を取得

	// 入力処理（SPACEキー / Aボタン）
	if (pInputKeyboard->GetTrigger(DIK_SPACE) != NULL && m_bJump == false ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) && m_bJump == false)
	{
		// ジャンプ状態に変更
		m_bJump = true;

		// ジャンプ量を設定
		move.y = 20.0f;
	}

	// 情報更新
	m_data.move = move;			// 移動量
}

//-------------------------------------
//- プレイヤーの二段ジャンプ入力処理
//-------------------------------------
void CPlayer::InputDoubleJump(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 変数宣言
	D3DXVECTOR3 move = m_data.move;			// 移動量を取得

	if (pInputKeyboard->GetTrigger(DIK_SPACE) != NULL && m_bJump == true && m_bHave == true ||
		pXInput->GetTrigger(XINPUT_GAMEPAD_A, CXInput::TYPE_INPUT_BUTTON) && m_bJump == true && m_bHave == true)
	{
		// 保持状態を解除
		m_bHave = false;

		// 保持敵の有無を判定
		if (CEnemyHave::GetInstance() != NULL)
		{
			// 保持敵の終了処理
			CEnemyHave::GetInstance()->Uninit();
		}

		// ジャンプ量を設定
		move.y = 30.0f;
	}

	// 情報更新
	m_data.move = move;			// 移動量
}

//-------------------------------------
//- プレイヤーのアクション入力処理
//-------------------------------------
void CPlayer::InputAction(void)
{
	// 所持状態の有無を判定
	if (m_bHave == true)
	{
		// 発射入力処理
		InputShot();
	}
	else
	{
		// 風だま入力処理
		InputKazedama();
	}
}

//-------------------------------------
//- プレイヤーの風だま入力処理
//-------------------------------------
void CPlayer::InputKazedama(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	// 風だまのポインタの有無を判定
	if (CKazedama::GetInstance() == NULL)
	{
		// 入力処理（Jキー / Bボタン）
		if (pInputKeyboard->GetTrigger(DIK_J) != NULL ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON))
		{
			// 情報取得
			D3DXVECTOR3 pos = m_data.pos;
			D3DXVECTOR3 rot = m_data.rot;

			// 変数宣言
			D3DXVECTOR3 posBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 銃の位置を代入（番号ベタ打ち[15]番）
			posBody.x = m_apModel[0]->GetMtxWorld()._41;
			posBody.y = m_apModel[0]->GetMtxWorld()._42;
			posBody.z = m_apModel[0]->GetMtxWorld()._43;

			// 風だまの生成処理
			CKazedama *pKazedama = CKazedama::Create(CKazedama::TEX_NULL);

			if (rot.y >= 0.0f && rot.y <= D3DX_PI)
			{
				// 風だまの設定処理
				pKazedama->Set(
					posBody,
					D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					D3DXVECTOR3(-20.0f, 0.0f, 0.0f),
					CKazedama::TYPE_ROT_LEFT);
			}
			else if (rot.y <= 0.0f && rot.y <= D3DX_PI)
			{
				// 風だまの設定処理
				pKazedama->Set(
					posBody,
					D3DXVECTOR3(50.0f, 50.0f, 0.0f),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					D3DXVECTOR3(20.0f, 0.0f, 0.0f),
					CKazedama::TYPE_ROT_RIGHT);
			}
		}
	}
}

//-------------------------------------
//- プレイヤーの発射入力処理
//-------------------------------------
void CPlayer::InputShot(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 移動処理を抜ける
		return;
	}

	// X入力のポインタを宣言
	CXInput *pXInput = CManager::GetXInput();

	// X入力の情報取得の成功を判定
	if (pXInput == NULL)
	{
		// 処理を抜ける
		return;
	}

	CEnemyHave *pEnemyHave = CEnemyHave::GetInstance();

	// 風だまのポインタの有無を判定
	if (pEnemyHave != NULL)
	{
		// 入力処理（Jキー / Bボタン）
		if (pInputKeyboard->GetTrigger(DIK_J) != NULL ||
			pXInput->GetTrigger(XINPUT_GAMEPAD_B, CXInput::TYPE_INPUT_BUTTON))
		{
			// 保持状態を解除
			m_bHave = false;

			// 情報取得
			D3DXVECTOR3 pos = m_data.pos;
			D3DXVECTOR3 rot = m_data.rot;

			// 変数宣言
			D3DXVECTOR3 posBody = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 銃の位置を代入（番号ベタ打ち[15]番）
			posBody.x = m_apModel[0]->GetMtxWorld()._41;
			posBody.y = m_apModel[0]->GetMtxWorld()._42;
			posBody.z = m_apModel[0]->GetMtxWorld()._43;

			if (rot.y >= 0.0f && rot.y <= D3DX_PI)
			{
				pEnemyHave->SetShot(
					posBody,
					D3DXVECTOR3(-30.0f,0.0f,0.0f),
					60,
					CEnemyHave::TYPE_ROT_LEFT);
			}
			else if (rot.y <= 0.0f && rot.y <= D3DX_PI)
			{
				pEnemyHave->SetShot(
					posBody,
					D3DXVECTOR3(30.0f, 0.0f, 0.0f),
					60,
					CEnemyHave::TYPE_ROT_RIGHT);
			}
		}
	}
}

//-------------------------------------
//- プレイヤーのデバック表示
//-------------------------------------
void CPlayer::DebugPlayer(void)
{
	// デバックプロックの取得
	CDebugProc *pDebugProc = CManager::GetDbugProc();

	// デバックプロック取得の有無を判定
	if (pDebugProc == NULL)
	{
		return;
	}

	pDebugProc->Print("\n");
	pDebugProc->Print("プレイヤーの位置");
	pDebugProc->Print("\n");
	pDebugProc->Print("%f,%f,%f",m_data.pos.x, m_data.pos.y, m_data.pos.z);
	pDebugProc->Print("\n");
	pDebugProc->Print("プレイヤーの所持状況 %d",m_bHave);
	pDebugProc->Print("\n");
}
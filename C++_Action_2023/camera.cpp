
//================================================
//=
//= カメラの処理[camera.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "camera.h"

#include "main.h"

#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "manager_object.h"
#include "sys_game_phase.h"

#include "input.h"

#include "time_stop.h"

#include "player_search.h"
#include "player_battle.h"
#include "player_shop.h"

#include "objectx_none.h"
#include "event_object.h"

//=======================================
//=	マクロ定義
//=======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	カメラのコンストラクタ
//-------------------------------------
CCamera::CCamera()
{
	ZeroMemory(m_mtxProjectien, sizeof(D3DXMATRIX));
	ZeroMemory(m_mtxView, sizeof(D3DXMATRIX));

	m_mode = MODE_FOLLOWING;
}

//-------------------------------------
//-	カメラのデストラクタ
//-------------------------------------
CCamera::~CCamera()
{
}

//-------------------------------------
//-	カメラの初期化処理
//-------------------------------------
HRESULT CCamera::Init(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き
	float fLength = m_fDataLength.Get();	// カメラとの長さ
	D3DXVECTOR3 vecU = m_dataVecU.Get();	// 上方向のベクトル

	// グローバル変数の初期化
	{
		// 情報設定
		posV = D3DXVECTOR3(0.0f, 500.0f, 500.0f);	// 視点
		posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		// 注視点
		fLength = (700.0f);							// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
		vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 上方向のベクトル

		// 情報更新
		m_dataPosV.Set(posV);			// 視点
		m_dataPosR.Set(posR);			// 注視点
		m_fDataLength.Set(fLength);		// カメラとの長さ
		m_dataRot.Set(rot);				// 向き
		m_dataVecU.Set(vecU);			// 上方向のベクトル

		m_dataPosVDest.Set(posV);		// 目的の視点
		m_dataPosRDest.Set(posR);		// 目的の注視点
		m_dataRotDest.Set(rot);			// 目的の向き
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	カメラの終了処理
//-------------------------------------
void CCamera::Uninit(void)
{

}

//-------------------------------------
//-	カメラの更新処理
//-------------------------------------
void CCamera::Update(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		// カメラのモード
		switch (m_mode)
		{
		case MODE_NORMAL:

			// カメラの移動処理
			UpdateOperation();

			break;

		case MODE_FOLLOWING:

			// カメラの追尾処理
			UpdateFollowing();

			// カメラの向き追尾処理
			UpdateRot();

			// 入力の判定（F2キー）
			if (pInputKeyboard->GetTrigger(DIK_F2) == true)
			{
				// ショップ視点に変更
				SetMode(MODE_SHOP);
			}

			break;

		case MODE_SHOP:

			// 入力の判定（F2キー）
			if (pInputKeyboard->GetTrigger(DIK_F2) == true)
			{
				// ショップ視点に変更
				SetMode(MODE_FOLLOWING);
			}

			break;
		}
	}
	else if (CManager::GetMode() == CScene::MODE_TITEL)
	{
		// タイトルの更新処理
		UpdateTitle();
	}


	// カメラの当たり判定
	Collision();
}

//-------------------------------------
//-	カメラの操作処理
//-------------------------------------
void CCamera::UpdateOperation(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き
	float fLength = m_fDataLength.Get();	// カメラとの距離

	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

		// 更新処理を抜ける
		return;
	}

	// 時間管理の情報を取得
	CTimeStop *pManagerTime = CManager::GetManagerTime();

	// 時間管理取得の有無を判定
	if (pManagerTime == NULL)
	{
		// 処理を抜ける
		return;
	}

	//移動
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{//左の移動[Aキーが押されたとき]

		posV.x -= 2.0f;
		posR.x -= 2.0f;

	}
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{//右の移動[Dキーが押されたとき]

		posV.x += 2.0f;
		posR.x += 2.0f;

	}
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{//右の移動[Wキーが押されたとき]

		posV.z += 2.0f;
		posR.z += 2.0f;

	}
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{//右の移動[Sキーが押されたとき]

		posV.z -= 2.0f;
		posR.z -= 2.0f;

	}

	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{//[Qキーが押されたとき]

		rot.y -= 0.05f;

		//注視点の位置を更新
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;
	}

	if (pInputKeyboard->GetPress(DIK_E) == true)
	{//[Eキーが押されたとき]

		rot.y += 0.05f;

		//注視点の位置を更新
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;

	}

	if (pInputKeyboard->GetPress(DIK_Y) == true)
	{
		rot.y -= 0.05f;

		//注視点の位置を更新
		posV.x = posR.x + sinf(rot.y) * -fLength;
		posV.z = posR.z + cosf(rot.y) * -fLength;
	}
	if (pInputKeyboard->GetPress(DIK_T) == true)
	{//[Eキーが押されたとき]

		rot.y += 0.05f;

		//注視点の位置を更新
		posV.x = posR.x + sinf(rot.y) * -fLength;
		posV.z = posR.z + cosf(rot.y) * -fLength;
	}

	if (pInputKeyboard->GetPress(DIK_RETURN) == true)
	{//[エンターキーが押されたとき]

		posV = D3DXVECTOR3(0.0f, 50.0f, -200.0f);
		posR = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//注視点の位置を更新
		posR.x = posV.x + sinf(rot.y) * fLength;
		posR.z = posV.z + cosf(rot.y) * fLength;

		posV.x = posR.x + sinf(rot.y) * -fLength;
		posV.z = posR.z + cosf(rot.y) * -fLength;
	}

	//角度の修正
	if (rot.y > D3DX_PI)
	{
		rot.y = (-D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = (D3DX_PI);
	}

	// 情報更新
	m_dataPosV.Set(posV);		// 視点
	m_dataPosR.Set(posR);		// 注視点
	m_dataRot.Set(rot);			// カメラの向き
	m_fDataLength.Set(fLength);	// カメラとの距離
}

//-------------------------------------
//-	カメラの追尾処理
//-------------------------------------
void CCamera::UpdateFollowing(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();			// 視点
	D3DXVECTOR3 posVDest = m_dataPosVDest.Get();	// 目的の視点
	D3DXVECTOR3 posR = m_dataPosR.Get();			// 注視点
	D3DXVECTOR3 posRDest = m_dataPosRDest.Get();	// 目的の注視点
	D3DXVECTOR3 rot = m_dataRot.Get();				// 向き
	float fLength = m_fDataLength.Get();			// カメラとの距離

	// プレイヤーの情報を取得
	CPlayer *pPlayer = CSysGamePhase::GetPlayer();

	// プレイヤーの情報取得の成功を判定
	if (pPlayer == NULL)
	{// 失敗時

		// 追尾処理を抜ける
		return;
	}

	// 変数宣言（プレイヤーの情報取得）
	D3DXVECTOR3 playerPos = pPlayer->m_dataPos.Get();		// 位置
	D3DXVECTOR3 playerRot = pPlayer->m_dataRot.Get();		// 向き

	//注視点とプレイヤーの距離
	D3DXVECTOR3 cameraPlayer = D3DXVECTOR3(
		sinf(playerRot.y) * -50.0f,
		0.0f,
		cosf(playerRot.y) * -50.0f);

	//視点の位置を更新
	posV.x = posR.x + sinf(rot.y) * -fLength;
	posV.z = posR.z + cosf(rot.y) * -fLength;

	//目的の視点の位置
	posVDest.x = playerPos.x + (sinf(rot.y) * -fLength) + cameraPlayer.x;
	posVDest.z = playerPos.z + (cosf(rot.y) * -fLength) + cameraPlayer.z;

	//目的の注視点の位置
	posRDest.x = playerPos.x + cameraPlayer.x;
	posRDest.z = playerPos.z + cameraPlayer.z;

	//視点の補正
	posV.x += (posVDest.x - posV.x) * 0.1f;
	posV.z += (posVDest.z - posV.z) * 0.1f;

	//注視点の補正
	posR.x += (posRDest.x - posR.x) * 0.1f;
	posR.z += (posRDest.z - posR.z) * 0.1f;

	// 情報更新
	m_dataPosV.Set(posV);			// 視点
	m_dataPosVDest.Set(posVDest);	// 目的の視点
	m_dataPosR.Set(posR);			// 注視点
	m_dataPosRDest.Set(posRDest);	// 目的の注視点
	m_fDataLength.Set(fLength);		// カメラとの距離
}

//-------------------------------------
//-	カメラの向き追尾処理
//-------------------------------------
void CCamera::UpdateRot(void)
{
	// キーボードのポインタを宣言
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// キーボードの情報取得の成功を判定
	if (pInputKeyboard == NULL)
	{// 失敗時

	 // 更新処理を抜ける
		return;
	}

	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_dataRot.Get();				// 向き
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();		// 目的の向き

	// プレイヤーの情報を取得
	CPlayer *pPlayer = CSysGamePhase::GetPlayer();

	// プレイヤーの情報取得の成功を判定
	if (pPlayer == NULL)
	{// 失敗時

		// 追尾処理を抜ける
		return;
	}

	// 変数宣言（プレイヤーの情報取得）
	D3DXVECTOR3 playerRot = pPlayer->m_dataRot.Get();		// 向き
	
	//if (pInputKeyboard->GetPress(DIK_LSHIFT) == true)
	//{
	//	// 目的の視点を更新
	//	rotDest.y = (playerRot.y - D3DX_PI);
	//}


	//if (pInputKeyboard->GetPress(DIK_Q) == true)
	//{//[Qキーが押されたとき]

	//	rotDest.y -= 0.015f;
	//	rot = rotDest;
	//}

	//if (pInputKeyboard->GetPress(DIK_E) == true)
	//{//[Eキーが押されたとき]

	//	rotDest.y += 0.015f;
	//	rot = rotDest;
	//}

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

	// 角度の移動
	rot.y += rotDiff * 0.02f;

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
	m_dataRot.Set(rot);			// 向き
	m_dataRotDest.Set(rotDest);	// 目的の向き
}

//-------------------------------------
//-	タイトルカメラの更新処理
//-------------------------------------
void CCamera::UpdateTitle(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 rot = m_dataRot.Get();				// 向き
	D3DXVECTOR3 rotDest = m_dataRotDest.Get();		// 目的の向き
	D3DXVECTOR3 posV = m_dataPosV.Get();			// 視点
	D3DXVECTOR3 posVDest = m_dataPosVDest.Get();	// 目的の視点
	D3DXVECTOR3 posR = m_dataPosR.Get();			// 注視点
	D3DXVECTOR3 posRDest = m_dataPosRDest.Get();	// 目的の注視点
	float fLength = m_fDataLength.Get();			// カメラとの距離

	// カメラの回転
	rotDest.y += 0.002f;

	//角度の修正
	if (rot.y > D3DX_PI)
	{
		rot.y = -D3DX_PI;
		rotDest.y = -D3DX_PI + (rotDest.y - D3DX_PI);
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y = D3DX_PI;
		rotDest.y = D3DX_PI + (rotDest.y + D3DX_PI);
	}

	//視点の位置を更新
	posV.x = posR.x + sinf(rot.y) * -fLength;
	posV.z = posR.z + cosf(rot.y) * -fLength;

	//目的の視点の位置
	posVDest.x = 0.0f + (sinf(rot.y) * -fLength) + 0.0f;
	posVDest.z = 0.0f + (cosf(rot.y) * -fLength) + 0.0f;

	//目的の注視点の位置
	posRDest.x = 0.0f + 0.0f;
	posRDest.z = 0.0f + 0.0f;

	//視点の補正
	posV.x += (posVDest.x - posV.x) * 0.3f;
	posV.z += (posVDest.z - posV.z) * 0.3f;

	//注視点の補正
	posR.x += (posRDest.x - posR.x) * 0.3f;
	posR.z += (posRDest.z - posR.z) * 0.3f;

	//角度の補正
	rot.y += (rotDest.y - rot.y) * 0.3f;

	// 情報更新
	m_dataRot.Set(rot);				// 向き
	m_dataRotDest.Set(rotDest);		// 目的の向き
	m_dataPosV.Set(posV);			// 視点
	m_dataPosVDest.Set(posVDest);	// 目的の視点
	m_dataPosR.Set(posR);			// 注視点
	m_dataPosRDest.Set(posRDest);	// 目的の注視点
	m_fDataLength.Set(fLength);		// カメラとの距離
}

//-------------------------------------
//-	カメラの設定処理
//-------------------------------------
void CCamera::SetCamera(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 vecU = m_dataVecU.Get();	// 上方向のベクトル

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return;
	}

	// 変数宣言
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	// プロジェションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjectien);

	// プロジェションマトリックスを生成（基本カメラ）
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjectien,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		40000.0f);

	//// プロジェションマトリックスを生成（平行投影）
	//D3DXMatrixOrthoLH(
	//	&m_mtxProjectien,
	//	(float)SCREEN_WIDTH,
	//	(float)SCREEN_HEIGHT,
	//	10.0f,
	//	1000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(
		D3DTS_PROJECTION,
		&m_mtxProjectien);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);
		
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&posV,		// 視点
		&posR,		// 注視点
		&vecU);		// 上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(
		D3DTS_VIEW,
		&m_mtxView);

	// 情報更新
	m_dataPosV.Set(posV);	// 視点
	m_dataPosR.Set(posR);	// 注視点
	m_dataVecU.Set(vecU);	// 上方向のベクトル
}

//-------------------------------------
//-	カメラの各モードの設定処理
//-------------------------------------
void CCamera::SetMode(CCamera::MODE mode)
{
	// モードの設定
	m_mode = mode;

	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点
	D3DXVECTOR3 posR = m_dataPosR.Get();	// 注視点
	D3DXVECTOR3 rot = m_dataRot.Get();		// 向き
	float fLength = m_fDataLength.Get();	// カメラとの長さ

	switch (m_mode)
	{
	case MODE_NORMAL:

		// 情報設定
		posV = D3DXVECTOR3(0.0f, 1250.0f, -500.0f);		// 視点
		posR = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// 注視点
		fLength = 1250.0f;								// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き

		break;

	case MODE_FOLLOWING:

		// 情報設定
		posV = D3DXVECTOR3(0.0f, 500.0f, 500.0f);	// 視点
		posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		// 注視点
		fLength = 700.0f;							// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き

		break;

	case MODE_SHOP:

		// 情報設定
		posV = D3DXVECTOR3(0.0f, 1250.0f, -500.0f);		// 視点
		posR = D3DXVECTOR3(0.0f, 0.0f, 500.0f);			// 注視点
		fLength = 1250.0f;								// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き

		break;

	case MODE_TITLE:

		// 情報設定
		posV = D3DXVECTOR3(0.0f, 3000.0f, -5000.0f);	// 視点
		posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 注視点
		fLength = 12500.0f;								// カメラとの長さ
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き

		break;
	}

	// 情報更新
	m_dataPosR.Set(posR);					// 視点
	m_dataPosV.Set(posV);					// 注視点
	m_fDataLength.Set(fLength);				// カメラとの長さ
	m_dataRot.Set(rot);						// 向き

	// 目的の情報の更新
	m_dataPosVDest.Set(m_dataPosV.Get());	// 目的の視点
	m_dataPosRDest.Set(m_dataPosR.Get());	// 目的の注視点
	m_dataRotDest.Set(m_dataRot.Get());		// 目的の向き
}

//-------------------------------------
//-	カメラの当たり判定
//-------------------------------------
void CCamera::Collision(void)
{
	// 変数宣言（情報取得）
	D3DXVECTOR3 posV = m_dataPosV.Get();	// 視点

	for (int nCutObjectNone = 0; nCutObjectNone < OBJECTX_NONE_NUM_MAX; nCutObjectNone++)
	{
		// 効果なしオブジェクトの情報を取得
		CObjectXNone *pObjectNone = CManagerObject::GetObjectNone(nCutObjectNone);

		// 効果なしオブジェクトの有無を判定
		if (pObjectNone != NULL)
		{
			// 変数宣言（効果なしオブジェクトの情報取得）
			D3DXVECTOR3 objectNonePos = pObjectNone->m_dataPos.Get();	// 位置
			D3DXVECTOR3 objectNoneSize = pObjectNone->m_dataSize.Get();	// 大きさ

			// 矩形の当たり判定
			if (posV.x + 200.0f >= objectNonePos.x - objectNoneSize.x &&
				posV.x - 200.0f <= objectNonePos.x + objectNoneSize.x &&
				posV.z + 400.0f >= objectNonePos.z - objectNoneSize.z &&
				posV.z - 400.0f <= objectNonePos.z + objectNoneSize.z)
			{
				// オブジェクトの描画を外す
				pObjectNone->SetDrawRemove();

				// 後回し描画
				pObjectNone->m_bDataAfterDraw.Set(true);
			}
		}
	}

	for (int nCutEventObject = 0; nCutEventObject < EVENT_OBJECT_NUM_MAX; nCutEventObject++)
	{
		// イベントオブジェクトの情報を取得
		CEventObject *pEventObject = CManagerObject::GetEventObject(nCutEventObject);

		// イベントオブジェクトの有無を判定
		if (pEventObject != NULL)
		{
			// 変数宣言（イベントオブジェクトの情報取得）
			D3DXVECTOR3 eventObjectPos = pEventObject->m_dataPos.Get();		// 位置
			D3DXVECTOR3 eventObjectSize = pEventObject->m_dataSize.Get();	// 大きさ

			// 矩形の当たり判定
			if (posV.x + 200.0f >= eventObjectPos.x - eventObjectSize.x &&
				posV.x - 200.0f <= eventObjectPos.x + eventObjectSize.x &&
				posV.z + 400.0f >= eventObjectPos.z - eventObjectSize.z &&
				posV.z - 400.0f <= eventObjectPos.z + eventObjectSize.z)
			{
				// オブジェクトの描画を外す
				pEventObject->SetDrawRemove();

				// 後回し描画
				pEventObject->m_bDataAfterDraw.Set(true);
			}
		}
	}
}


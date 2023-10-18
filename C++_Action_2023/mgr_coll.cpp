
//================================================
//=
//=	当たり判定管理の処理[mgr_coll.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "mgr_coll.h"

#include "coll.h"

#include "object.h"

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
//-	当たり判定管理のコンストラクタ
//-------------------------------------
CMgrColl::CMgrColl()
{
	ZeroMemory(m_apColl, sizeof(m_apColl));
	m_nNldxMax = 0;
}

//-------------------------------------
//-	当たり判定管理のデストラクタ
//-------------------------------------
CMgrColl::~CMgrColl()
{

}

//-------------------------------------
//- 当たり判定管理の初期化処理
//-------------------------------------
HRESULT CMgrColl::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- 当たり判定管理の終了処理
//-------------------------------------
void CMgrColl::Uninit(void)
{

}

//-------------------------------------
//- 当たり判定管理の更新処理
//-------------------------------------
void CMgrColl::Update(void)
{
	for (int nCountMy = 0; nCountMy < COLLSION_NUM_MAX; nCountMy++)
	{
		if (m_apColl[nCountMy] != NULL)
		{
			// 変数宣言
			CColl *pCollMy = m_apColl[nCountMy];	// 自身の当たり判定情報
			pCollMy->ResetHitData();				// 接触情報の初期化

			for (int nCountPair = 0; nCountPair < COLLSION_NUM_MAX; nCountPair++)
			{
				if (m_apColl[nCountPair] != NULL)
				{
					CColl *pCollPair = m_apColl[nCountPair];			// 相手の当たり判定情報

					TAG tagTgt = pCollPair->GetData().tag;				// 相手のタグ情報
					bool bTgt = pCollMy->GetData().abTagTgt[tagTgt];	// タグの接触の有無
					TYPE type = pCollMy->GetData().aType[tagTgt];		// 相手との接触種類

					// 当たり判定タグの判定
					if (bTgt == true)
					{
						// 変数宣言（情報取得）
						D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// 自身の位置
						D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// 自身の大きさ

						// 変数宣言 (相手の情報取得)
						D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// 相手の位置
						D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// 相手の大きさ

						// 変数宣言
						bool bIsHit = false;	// 接触の有無
					
						bool bIsHitX = false;	// X軸の判定
						bool bIsHitY = false;	// Y軸の判定
						bool bIsHitZ = false;	// Z軸の判定

						switch (type)
						{

						case TYPE_RECTANGLE:

							// 矩形の当たり判定
							if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
							{
								// 接触
								bIsHit = true;
							}

							break;

						case TYPE_RECTANGLE_SIDE:

							// 矩形の当たり判定
							if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
							{
								// 接触
								bIsHit = true;
								
								// 変数宣言（自身の当たり判定の情報取得）
								CColl::Data data = pCollMy->GetData();

								// X軸の当たり判定
								data.abHitSxis[CColl::TYPE_SXIS_X] = hitRectangleSide(posMy.x, sizeMy.x, posPair.x, sizePair.x);
								data.abHitSxis[CColl::TYPE_SXIS_Y] = hitRectangleSide(posMy.y, sizeMy.y, posPair.y, sizePair.y);
								data.abHitSxis[CColl::TYPE_SXIS_Z] = hitRectangleSide(posMy.z, sizeMy.z, posPair.z, sizePair.z);

								// 情報更新（自身の当たり判定）
								pCollMy->SetData(data);
							}

							break;
						}

						// 接触の有無
						if (bIsHit == true)
						{
							// 接触相手の情報設定
							CColl::HitData hitData;

							// 相手の番号を代入
							hitData.nNldx = nCountPair;

							// 接触相手の情報を設定
							pCollMy->SetHitData(hitData);
						}
					}
				}
			}
		}

	}
}

//-------------------------------------
//- 当たり判定管理の描画処理
//-------------------------------------
void CMgrColl::Draw(void)
{
}

//-------------------------------------
//- 当たり判定管理の生成処理
//-------------------------------------
CMgrColl * CMgrColl::Create(void)
{
	// 当たり判定管理の生成
	CMgrColl *pCollision = DBG_NEW CMgrColl;

	// 生成の成功の有無を判定
	if (pCollision != NULL)
	{
		// 初期化処理
		if (FAILED(pCollision->Init()))
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

	// 当たり判定管理のポインタを返す
	return pCollision;
}

//-------------------------------------
//- 当たり判定管理のタグの相手との接触判定処理
//-------------------------------------
bool CMgrColl::Hit(int nNldxColl, CMgrColl::TAG hitTag, STATE_HIT stateHit)
{
	// 変数宣言
	CColl *pCollMy = m_apColl[nNldxColl];				// 自身の当たり判定情報
	int nHitNldxMax = pCollMy->GetData().nHitNldxMax;	// 接触最大数
	bool bHitTgt = false;								// 目的の接触の有無

	for (int nCount = 0; nCount < nHitNldxMax; nCount++)
	{
		int hitNldx = pCollMy->GetData().hitData[nCount].nNldx;		// 接触相手の番号
		CColl *pCollPair = m_apColl[hitNldx];						// 接触相手の当たり判定情報
		CColl::Data dataPair = m_apColl[hitNldx]->GetData();		// 接触相手の情報
		TAG tagPair = dataPair.tag;									// 接触相手のタグ

		if (tagPair == hitTag)
		{
			if (pCollMy->GetData().aType[hitTag] == TYPE_RECTANGLE_SIDE)
			{
				// 変数宣言（情報取得）
				D3DXVECTOR3 posMy = pCollMy->GetData().pos;			// 自身の位置
				D3DXVECTOR3 posOldMy = pCollMy->GetData().posOld;	// 自身の前回の位置
				D3DXVECTOR3 sizeMy = pCollMy->GetData().size;		// 自身の大きさ

				// 変数宣言 (相手の情報取得)
				D3DXVECTOR3 posPair = pCollPair->GetData().pos;		// 相手の位置
				D3DXVECTOR3 sizePair = pCollPair->GetData().size;	// 相手の大きさ

				// 矩形の当たり判定
				if (hitRectangle(posMy, sizeMy, posPair, sizePair) == true)
				{
					// 接触
					bHitTgt = true;

					// 変数宣言（自身の当たり判定の情報取得）
					CColl::Data data = pCollMy->GetData();

					// X軸の当たり判定
					if (hitRectangleSide(posOldMy.y, sizeMy.y, posPair.y, sizePair.y))
					{
						data.abHitSxis[CColl::TYPE_SXIS_X] = hitRectangleSide(posMy.x, sizeMy.x, posPair.x, sizePair.x);
					}

					if (hitRectangleSide(posOldMy.x, sizeMy.x, posPair.x, sizePair.x))
					{
						data.abHitSxis[CColl::TYPE_SXIS_Y] = hitRectangleSide(posMy.y , sizeMy.y, posPair.y, sizePair.y);
					}

					data.abHitSxis[CColl::TYPE_SXIS_Z] = hitRectangleSide(posMy.z, sizeMy.z, posPair.z, sizePair.z);

					// 情報更新（自身の当たり判定）
					pCollMy->SetData(data);
				}
			}
			else
			{
				// 接触判定を設定
				bHitTgt = true;

				// 接触状態を代入
				dataPair.stateHit = stateHit;

				// 情報更新（接触相手）
				m_apColl[hitNldx]->SetData(dataPair);
			}
		}
	}

	return bHitTgt;
}

//-------------------------------------
//- 当たり判定管理の設定処理
//-------------------------------------
int CMgrColl::Set(CColl *pColl)
{
	for (int nCount = 0; nCount < COLLSION_NUM_MAX; nCount++)
	{
		if (m_apColl[nCount] == NULL)
		{
			m_apColl[nCount] = pColl;

			return nCount;
		}
	}

	return -1;
}

//-------------------------------------
//- 当たり判定管理の初期化設定処理
//-------------------------------------
void CMgrColl::Reset(int nNldx)
{
	m_apColl[nNldx] = NULL;
}

//-------------------------------------
//- 当たり判定管理の矩形の当たり判定
//-------------------------------------
bool CMgrColl::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.y + sizeMy.y >= posPair.y - sizePair.y &&
		posMy.y - sizeMy.y <= posPair.y + sizePair.y &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- 当たり判定管理の回転矩形の当たり判定
//-------------------------------------
bool CMgrColl::hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair)
{
	if (rot.y >= 0.0f &&
		rot.y >= (D3DX_PI * 0.25f) &&
		rot.y <= (D3DX_PI * 0.75f))
	{
		float tenpSizeX = sizeMy.x;
		sizeMy.x = sizeMy.z;
		sizeMy.z = tenpSizeX;
	}
	else if (
		rot.y <= 0.0f &&
		rot.y <= (-D3DX_PI * 0.25f) &&
		rot.y >= (-D3DX_PI * 0.75f))
	{
		float tenpSizeX = sizeMy.x;
		sizeMy.x = sizeMy.z;
		sizeMy.z = tenpSizeX;
	}

	if (posMy.x + sizeMy.x >= posPair.x - sizePair.x &&
		posMy.x - sizeMy.x <= posPair.x + sizePair.x &&
		posMy.z + sizeMy.z >= posPair.z - sizePair.z &&
		posMy.z - sizeMy.z <= posPair.z + sizePair.z)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//- 当たり判定管理の辺の当たり判定
//-------------------------------------
bool CMgrColl::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}
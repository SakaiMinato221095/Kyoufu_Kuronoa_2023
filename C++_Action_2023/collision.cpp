
//================================================
//=
//=	当たり判定の処理[collision.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "collision.h"

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
//-	当たり判定のコンストラクタ
//-------------------------------------
CCollision::CCollision()
{
	ZeroMemory(&m_data, sizeof(m_data));
	m_nNldxMax = -1;
}

//-------------------------------------
//-	当たり判定のデストラクタ
//-------------------------------------
CCollision::~CCollision()
{

}

//-------------------------------------
//- 当たり判定の初期化処理
//-------------------------------------
HRESULT CCollision::Init(void)
{
	return S_OK;
}

//-------------------------------------
//- 当たり判定の終了処理
//-------------------------------------
void CCollision::Uninit(void)
{

}

//-------------------------------------
//- 当たり判定の更新処理
//-------------------------------------
void CCollision::Update(void)
{
	for (int nCount = 0; nCount < m_nNldxMax; nCount++)
	{
		for (int nCountPair = 0; nCountPair < m_nNldxMax; nCountPair++)
		{
			// 変数宣言
			TAG tag = m_data[nCountPair].tag;					// 相手のタグ
			bool bHitTag = m_data[nCount].bHitTag[tag];			// タグ相手の接触の有無

			// 当たり判定タグの判定
			if (bHitTag == true)
			{
				// 変数宣言（情報取得）
				D3DXVECTOR3 posMy = m_data[nCount].pos;			// 自身の位置
				D3DXVECTOR3 sizeMy = m_data[nCount].size;		// 自身の大きさ

				D3DXVECTOR3 posPair = m_data[nCountPair].pos;	// 相手の位置
				D3DXVECTOR3 sizePair = m_data[nCountPair].size;	// 相手の大きさ

				bool bIsHit = false;							// 接触の有無

				switch (m_data->type)
				{
				case TYPE_RECTANGLE:

					// 矩形の当たり判定
					if(hitRectangle(posMy,sizeMy,posPair, sizePair) == true)
					{
						bIsHit = true;
					}

					break;
				}

				// 接触の有無
				if (bIsHit == true)
				{
					// 接触相手の情報設定
					int nHitNldxMax = m_data[nCount].nHitNldxMax;							// 配列番号
					m_data[nCount].hitData[nHitNldxMax].tag = m_data[nCountPair].tag;		// 相手のタグを保存
					m_data[nCount].hitData[nHitNldxMax].nNldx = m_data[nCountPair].nNldx;	// 接触番号を保存
					m_data[nCount].nHitNldxMax++;											// 配列番号を進める
				}
			}
		}
	}
}

//-------------------------------------
//- 当たり判定の描画処理
//-------------------------------------
void CCollision::Draw(void)
{
}

//-------------------------------------
//- 当たり判定の生成処理
//-------------------------------------
CCollision * CCollision::Create(void)
{
	// 当たり判定の生成
	CCollision *pCollision = DBG_NEW CCollision;

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

	// 当たり判定のポインタを返す
	return pCollision;
}

//-------------------------------------
//- 当たり判定の設定処理
//-------------------------------------
void CCollision::SetColl(TAG tag,TYPE type,D3DXVECTOR3 pos , D3DXVECTOR3 size)
{
	m_nNldxMax++;
}

//-------------------------------------
//- 当たり判定の矩形の当たり判定
//-------------------------------------
bool CCollision::hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair)
{
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
//- 当たり判定の回転矩形の当たり判定
//-------------------------------------
bool CCollision::hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair)
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
//- 当たり判定の辺の当たり判定
//-------------------------------------
bool CCollision::hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair)
{
	if (fPos + fSize >= fPosPair - fSizePair &&
		fPos - fSize <= fPosPair + fSizePair)
	{
		return true;
	}

	return false;
}


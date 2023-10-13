
//================================================
//=
//= モデル管理の処理[manager_model.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "manager_model.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

#include "model.h"

#include "objectx_none.h"
#include "enemy.h"
#include "enemy_have.h"

//-------------------------------------
//-	モデル管理のコンストラクタ
//-------------------------------------
CManagerModel::CManagerModel()
{
	// 値のクリア
	ZeroMemory(m_model, sizeof(m_model));
}

//-------------------------------------
//-	モデル管理のデストラクタ
//-------------------------------------
CManagerModel::~CManagerModel()
{
}

//-------------------------------------
//-	モデル管理の読み込み処理
//-------------------------------------
HRESULT CManagerModel::Load(HWND hWnd)
{
	// 階層構造モデル
	if (FAILED(CModel::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "階層構造モデルのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 効果なしオブジェクト
	if (FAILED(CObjectXNone::Load()))
	{// 失敗時

		// 失敗メッセージ
		MessageBox(hWnd, "効果なしオブジェクトのデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 敵オブジェクト
	if (FAILED(CEnemy::Load()))
	{// 失敗時

	 // 失敗メッセージ
		MessageBox(hWnd, "敵のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}

	// 保持敵オブジェクト
	if (FAILED(CEnemyHave::Load()))
	{// 失敗時

	 // 失敗メッセージ
		MessageBox(hWnd, "保持敵のデータ", "データ読み込み処理失敗！", MB_ICONWARNING);

		// データ読み込みを抜ける
		return E_FAIL;
	}


	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	モデル管理の破棄処理
//-------------------------------------
void CManagerModel::Unload(void)
{
	for (int nCount = 0; nCount < MANAGER_MODEL_MAX; nCount++)
	{
		// テクスチャの破棄
		if (m_model[nCount].m_pTexture != NULL)
		{
			// 動的確保分
			for (int nCutMat = 0; nCutMat < (int)m_model[nCount].m_dwNumMat; nCutMat++)
			{
				// テクスチャの有無を判定
				if (m_model[nCount].m_pTexture[nCutMat] != NULL)
				{
					// テクスチャの開放処理
					m_model[nCount].m_pTexture[nCutMat]->Release();
				}
			}

			// テクスチャの開放
			delete[] m_model[nCount].m_pTexture;
			m_model[nCount].m_pTexture = NULL;

			// テクスチャ番号の開放
			delete[] m_model[nCount].m_nldxTexture;
			m_model[nCount].m_nldxTexture = NULL;
		}

		// メッシュの破棄
		if (m_model[nCount].m_pMesh != NULL)
		{
			m_model[nCount].m_pMesh->Release();
			m_model[nCount].m_pMesh = NULL;
		}

		// マテリアルの破棄
		if (m_model[nCount].m_pBuffMat != NULL)
		{
			m_model[nCount].m_pBuffMat->Release();
			m_model[nCount].m_pBuffMat = NULL;
		}
	}
}

//-------------------------------------
//-	モデル管理の指定読み込み処理
//-------------------------------------
int CManagerModel::Regist(const char *pFilename)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 処理を抜ける
		return -1;
	}

	// テクスチャ管理の生成
	CManagerTexture *pManagerTexture = CManager::GetManagerTexture();

	// テクスチャ管理の有無を判定
	if (pManagerTexture == NULL)
	{
		// 初期化処理を抜ける
		return -1;
	}

	for (int nCount = 0; nCount < MANAGER_MODEL_MAX; nCount++)
	{
		// モデルの有無を判定
		if (m_model[nCount].m_pMesh == NULL)
		{
			// Xファイルの読み込み
			if (FAILED(D3DXLoadMeshFromX(
				pFilename,						// Xファイルオブジェクト名
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_model[nCount].m_pBuffMat,	// マテリアルの情報
				NULL,
				&m_model[nCount].m_dwNumMat,	// マテリアルの数
				&m_model[nCount].m_pMesh)))		// メッシュの情報
			{
				// 処理を抜ける
				return -1;
			}

			// テクスチャの使用の有無を確認
			if (m_model[nCount].m_pTexture == NULL)
			{
				// マテリアル数分動的確保
				m_model[nCount].m_pTexture = DBG_NEW LPDIRECT3DTEXTURE9[m_model[nCount].m_dwNumMat];
				m_model[nCount].m_nldxTexture = DBG_NEW int[m_model[nCount].m_dwNumMat];

				// テクスチャ情報を初期化
				ZeroMemory(m_model[nCount].m_pTexture, sizeof(m_model[nCount].m_pTexture));
				ZeroMemory(m_model[nCount].m_nldxTexture, sizeof(m_model[nCount].m_nldxTexture));
			}
			else
			{
				// 初期化処理を抜ける
				return -1;
			}

			// マテリアルの情報を取得
			D3DXMATERIAL *pMat = (D3DXMATERIAL*)m_model[nCount].m_pBuffMat->GetBufferPointer();

			// マテリアルの情報取得の成功を判定
			if (pDevice == NULL)
			{// 失敗

				// 初期化を抜ける
				return -1;

			}

			// マテリアルごとの読み込み
			for (int nCutMat = 0; nCutMat < (int)m_model[nCount].m_dwNumMat; nCutMat++)
			{
				// テクスチャ設定の有無を判定
				if (pMat[nCutMat].pTextureFilename != NULL)
				{// テクスチャ設定が存在する

				 // テクスチャの読み込み if(テクスチャ読み込み成功の有無を判定)
					if (FAILED(D3DXCreateTextureFromFile(
						pDevice,
						pMat[nCutMat].pTextureFilename,
						&m_model[nCount].m_pTexture[nCutMat])))
					{
						// 失敗を返す
						return -1;
					}

					// テクスチャ設定
					m_model[nCount].m_nldxTexture[nCutMat] = pManagerTexture->Regist(pMat[nCutMat].pTextureFilename);

				}
				else
				{
					// 「なし」を代入
					m_model[nCount].m_pTexture[nCutMat] = NULL;
				}
			}

			// 番号を返す
			return nCount;
		}
	}

	// 失敗を返す
	return -1;
}

//-------------------------------------
//-	モデル管理の取得処理
//-------------------------------------
CManagerModel::Model CManagerModel::GetAddress(int nldx)
{
	// 番号のモデル管理情報を返す
	return m_model[nldx];
}

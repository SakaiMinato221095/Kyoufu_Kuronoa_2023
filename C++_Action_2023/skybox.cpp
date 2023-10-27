
//-===============================================
//-
//-	スカイボックスの処理[skybox.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "skybox.h"

#include "renderer.h"
#include "manager.h"

#include "manager_model.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// スカイボックスのモデルのコンスト定義
const char *pModelSkybox[] =
{
	"data\\MODEL\\SkyBox\\sky_box000.x",			// スカイボックス000
};

//-======================================
//-	静的変数宣言
//-======================================

int CSkybox::m_nModelNldx[MODEL_MAX] = {};			// モデルの番号

//-------------------------------------
//-	スカイボックスオブジェクトのコンストラクタ
//-------------------------------------
CSkybox::CSkybox(int nPriority) : CObjectX(nPriority)
{
	m_model = MODEL(0);
}

//-------------------------------------
//-	スカイボックスオブジェクトのデストラクタ
//-------------------------------------
CSkybox::~CSkybox()
{

}

//-------------------------------------
//- スカイボックスのモデル読み込み
//-------------------------------------
HRESULT CSkybox::Load(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

	 // 初期化処理を抜ける
		return E_FAIL;
	}

	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 初期化処理を抜ける
		return E_FAIL;
	}

	// モデル設定
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		// モデル番号を取得
		int nModelNldx = m_nModelNldx[nCount];

		// モデル番号の取得（モデルの割当）
		nModelNldx = pManagerModel->Regist(pModelSkybox[nCount]);

		// モデルの読み込み成功の有無を確認
		if (nModelNldx == -1)
		{
			// 失敗時に初期化処理を抜ける
			return E_FAIL;
		}

		// モデル番号を設定
		m_nModelNldx[nCount] = nModelNldx;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- スカイボックスの読み込んだモデル破棄
//-------------------------------------
void CSkybox::Unload(void)
{

}

//-------------------------------------
//- スカイボックスオブジェクトの初期化処理（Xファイルオブジェクト設定）
//-------------------------------------
HRESULT CSkybox::Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// モデル管理の生成
	CManagerModel *pManagerModel = CManager::GetInstance()->GetManagerModel();

	// モデル管理の有無を判定
	if (pManagerModel == NULL)
	{
		// 処理を抜ける
		return E_FAIL;
	}

	// モデル番号を取得
	int nModelNldx = m_nModelNldx[model];

	// スカイボックスオブジェクトのモデル割当
	BindModel(nModelNldx, model);

	// 初期設定
	InitSet(pos,rot);

	// Xファイルオブジェクトの初期化 if(初期化成功の有無を判定)
	if (FAILED(CObjectX::Init()))
	{
		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- スカイボックスオブジェクトの終了処理
//-------------------------------------
void CSkybox::Uninit(void)
{
	// Xファイルオブジェクトの終了
	CObjectX::Uninit();
}

//-------------------------------------
//- スカイボックスオブジェクトの更新処理
//-------------------------------------
void CSkybox::Update(void)
{
	// Xファイルオブジェクトの更新処理
	CObjectX::Update();
}

//-------------------------------------
//- スカイボックスオブジェクトの描画処理
//-------------------------------------
void CSkybox::Draw(void)
{
	// Xファイルオブジェクトの描画処理
	CObjectX::Draw();
}

//-------------------------------------
//- スカイボックスオブジェクトの生成処理（Xファイルオブジェクト設定）
//-------------------------------------
CSkybox * CSkybox::Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// スカイボックスオブジェクトのポインタを宣言
	CSkybox *pCSkybox = DBG_NEW CSkybox(4);

	// 生成の成功の有無を判定
	if (pCSkybox != NULL)
	{
		// 初期化処理
		if (FAILED(pCSkybox->Init(model,pos,rot)))
		{// 失敗時

		 // 「なし」を返す
			return NULL;
		}
	}
	else if (pCSkybox == NULL)
	{// 失敗時

	 // 「なし」を返す
		return NULL;
	}

	// スカイボックスオブジェクトのポインタを返す
	return pCSkybox;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
int CSkybox::GetModel(void)
{
	// モデル設定
	return(int)m_model;
}

//-------------------------------------
//-	モデルの設定処理
//-------------------------------------
void CSkybox::SetModel(int nModelNldx)
{
	// モデル設定
	m_model = (MODEL)nModelNldx;
}

//-------------------------------------
//-	スカイボックスの初期設定処理
//-------------------------------------
void CSkybox::InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 頂点値情報を取得
	CObjectX::VtxData vtxData = GetVtxData();

	// データの代入
	vtxData.pos = pos;								// 位置
	vtxData.rot = rot;								// 向き

	// 情報更新（頂点値情報）
	SetVtxData(vtxData);
}

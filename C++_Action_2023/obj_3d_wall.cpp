
//-===============================================
//-
//-	3D壁処理[obj_3d_wall.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "obj_3d_wall.h"

#include "renderer.h"
#include "manager.h"

#include "manager_texture.h"

//-======================================
//-	マクロ定義
//-======================================

//=======================================
//=	コンスト定義
//=======================================

// 3D壁のテクスチャのコンスト定義
const char *pTextureWall[] =
{
	NULL,										// テクスチャなし
	"data\\TEXTURE\\blockade_wall000.jpg",		// 封鎖壁のテクスチャ
	"data\\TEXTURE\\dark_wall000.png",			// 闇壁のテクスチャ
};

//-======================================
//-	静的変数宣言
//-======================================

int CObj3dWall::m_nTextureNldx[TEX_MAX] = {};

//-------------------------------------
//-	3D壁のコンストラクタ
//-------------------------------------
CObj3dWall::CObj3dWall(int nPriority) : CObject3d(nPriority)
{

}

//-------------------------------------
//-	3D壁のデストラクタ
//-------------------------------------
CObj3dWall::~CObj3dWall()
{

}

//-------------------------------------
//- 背景のテクスチャの読み込み
//-------------------------------------
HRESULT CObj3dWall::Load(void)
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
		m_nTextureNldx[nCount] = pManagerTexture->Regist(pTextureWall[nCount]);

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
//- 背景の読み込んだテクスチャの破棄
//-------------------------------------
void CObj3dWall::Unload(void)
{

}
//-------------------------------------
//- 3D壁の初期化処理（3Dオブジェクト設定）
//-------------------------------------
HRESULT CObj3dWall::Init(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	// テクスチャ割当
	BindTexture(m_nTextureNldx[tex]);

	// 3Dオブジェクトの初期化
	CObject3d::Init(CObject3d::TYPE_CREATE_WALL,pos,size,rot,color);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- 3D壁の終了処理
//-------------------------------------
void CObj3dWall::Uninit(void)
{
	// 3Dオブジェクトの終了
	CObject3d::Uninit();
}

//-------------------------------------
//- 3D壁の更新処理
//-------------------------------------
void CObj3dWall::Update(void)
{
	// 3Dオブジェクトの更新処理
	CObject3d::Update();
}

//-------------------------------------
//- 3D壁の描画処理
//-------------------------------------
void CObj3dWall::Draw(void)
{
	// 3Dオブジェクトの描画処理
	CObject3d::Draw();
}

//-------------------------------------
//- 3D壁の生成処理
//-------------------------------------
CObj3dWall * CObj3dWall::Create(TEX tex, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR color)
{
	// フィールドのポインタを宣言
	CObj3dWall *pCObj3dWall = new CObj3dWall(5);

	// 生成の成功の有無を判定
	if (pCObj3dWall != NULL)
	{
		// 初期化処理
		if (FAILED(pCObj3dWall->Init(tex,pos,size,rot,color)))
		{// 失敗時

			// 「なし」を返す
			return NULL;
		}
	}
	else if (pCObj3dWall == NULL)
	{// 失敗時

		// 「なし」を返す
		return NULL;
	}

	// フィールドのポインタを返す
	return pCObj3dWall;
}

//================================================
//=
//= ライトの処理[light.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	インクルード
//=======================================

#include "light.h"

#include "renderer.h"
#include "manager.h"

//-------------------------------------
//-	ライトのコンストラクタ
//-------------------------------------
CLight::CLight()
{
	for (int nCount = 0; nCount < LIGHT_MAX; nCount++)
	{
		ZeroMemory(&m_light[nCount], sizeof(D3DLIGHT9));
	}
}

//-------------------------------------
//-	ライトのデストラクタ
//-------------------------------------
CLight::~CLight()
{
}


//-------------------------------------
//-	ライトの初期化処理
//-------------------------------------
HRESULT CLight::Init(void)
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバイスの情報取得の成功を判定
	if (pDevice == NULL)
	{// 失敗時

		// 初期化処理を抜ける
		return E_FAIL;
	}

	// 変数宣言
	D3DXVECTOR3 vecDir[LIGHT_MAX];	// 設定用方向ベクトル

	for (int nCount = 0; nCount < LIGHT_MAX; nCount++)
	{
		// ライトの種類を設定
		m_light[nCount].Type = D3DLIGHT_DIRECTIONAL;
		
		if (nCount == 0)
		{
			// ライトの拡散光を設定
			m_light[nCount].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ライトの方向を設定
			vecDir[nCount] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		}
		else  if (nCount == 1)
		{
			//ライトの拡散光を設定
			m_light[nCount].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			// ライトの方向を設定
			vecDir[nCount] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
		}
		else if (nCount == 2)
		{
			// ライトの拡散光を設定
			m_light[nCount].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

			// ライトの方向を設定
			vecDir[nCount] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
		}

		// ベクトルを正規化する（1.0f）にする
		D3DXVec3Normalize(&vecDir[nCount], &vecDir[nCount]);
		m_light[nCount].Direction = vecDir[nCount];

		// ライトを設定する
		pDevice->SetLight(nCount, &m_light[nCount]);

		// ライトを有効にする
		pDevice->LightEnable(nCount, TRUE);

	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	ライトの終了処理
//-------------------------------------
void CLight::Uninit(void)
{
}

//-------------------------------------
//-	ライトの更新処理
//-------------------------------------
void CLight::Update(void)
{

}


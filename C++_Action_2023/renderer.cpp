
//-===============================================
//-
//-	構成処理[renderer.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "renderer.h"

#include "object.h"

#include "manager.h"

#include "fade.h"
#include "debugproc.h"

//-======================================
//-	マクロ定義
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CRenderer::CRenderer()
{
	// 値をクリア
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CRenderer::~CRenderer()
{

}

//-------------------------------------
//-	初期化処理
//-------------------------------------
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンラーションパラメータ

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現存のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンパラメーターを設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	// パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3dpp.BackBufferFormat;				// バックバッファの形式
	d3dpp.BackBufferCount = 1;										// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// ダブルバッファを切り替え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;							// デプスバッファとスランシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート				
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル				

	// Dirext3Dデバイスの生成
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// レンダーステート設定
	{
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	// サンプラーステートの設定			
	{
		// テクスチャの縮小補間の設定
		m_pD3DDevice->SetSamplerState(
			0,
			D3DSAMP_MINFILTER,
			D3DTEXF_LINEAR);

		m_pD3DDevice->SetSamplerState(
			0,
			D3DSAMP_MAGFILTER,
			D3DTEXF_LINEAR);

		//テクスチャの繰り返し
		m_pD3DDevice->SetSamplerState(
			0,
			D3DSAMP_ADDRESSU,
			D3DTADDRESS_WRAP);

		m_pD3DDevice->SetSamplerState(
			0,
			D3DSAMP_ADDRESSV,
			D3DTADDRESS_WRAP);
	}

	// テクスチャステージステートの設定		
	{
		// テクスチャとポリゴンの透明度をブレンド
		m_pD3DDevice->SetTextureStageState(
			0,
			D3DTSS_ALPHAOP,
			D3DTOP_MODULATE);

		m_pD3DDevice->SetTextureStageState(
			0,
			D3DTSS_ALPHAARG1,
			D3DTA_TEXTURE);

		m_pD3DDevice->SetTextureStageState(
			0,
			D3DTSS_ALPHAARG2,
			D3DTA_CURRENT);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//-	終了処理
//-------------------------------------
void CRenderer::Uninit(void)
{
	
	// Direct3Dデバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//-------------------------------------
//- 更新処理
//-------------------------------------
void CRenderer::Update(void)
{
	// オブジェクトの更新処理
	CObject::UpdateAll();
}

//-------------------------------------
//- 描画処理
//-------------------------------------
void CRenderer::Draw(void)
{
	// 画面クリア（バックバッファとZバッファをクリア）
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// 描画開始が成功した場合

		{
			// オブジェクトの描画処理
			CObject::DrawAll();

			// フェードの取得
			CFade *pFade = CManager::GetFade();

			// フェードの有無を判定
			if (pFade != NULL)
			{
				// フェードの描画処理
				pFade->Draw();
			}

			// デバックプロックの取得
			CDebugProc *pDbugProc = CManager::GetDbugProc();

			// デバックプロックの有無を判定
			if (pDbugProc != NULL)
			{
				// デバックプロックの描画処理
				pDbugProc->Draw();
			}
		}

		// 描画終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-------------------------------------
//- レンダラーのアルファブレディング設定
//-------------------------------------
void CRenderer::SetAlphaBlend(bool bUse)
{
	// 使用方法を判定
	if (bUse == true)
	{
		// デバイスの有無を確認
		if (m_pD3DDevice != NULL)
		{
			// aブレンディングを加算合成に設定
			m_pD3DDevice->SetRenderState(
				D3DRS_BLENDOP,
				D3DBLENDOP_ADD);

			m_pD3DDevice->SetRenderState(
				D3DRS_SRCBLEND,
				D3DBLEND_SRCALPHA);

			m_pD3DDevice->SetRenderState(
				D3DRS_DESTBLEND,
				D3DBLEND_ONE);
		}

	}
	else if (bUse == false)
	{
		// デバイスの有無を確認
		if (m_pD3DDevice != NULL)
		{
			// aブレンディングをもとに戻す
			m_pD3DDevice->SetRenderState(
				D3DRS_BLENDOP,
				D3DBLENDOP_ADD);

			m_pD3DDevice->SetRenderState(
				D3DRS_SRCBLEND,
				D3DBLEND_SRCALPHA);

			m_pD3DDevice->SetRenderState(
				D3DRS_DESTBLEND,
				D3DBLEND_INVSRCALPHA);
		}
	}

}

//-------------------------------------
//- レンダラーのZテスト設定
//-------------------------------------
void CRenderer::SetZTest(bool bUse)
{
	// 使用方法を判定
	if (bUse == true)
	{
		// デバイスの有無を確認
		if (m_pD3DDevice != NULL)
		{
			// Zテストを無効化
			m_pD3DDevice->SetRenderState(
				D3DRS_ZFUNC,
				D3DCMP_ALWAYS);

			m_pD3DDevice->SetRenderState(
				D3DRS_ZWRITEENABLE,
				FALSE);
		}

	}
	else if (bUse == false)
	{
		// デバイスの有無を確認
		if (m_pD3DDevice != NULL)
		{
			// Zテストを有効にする
			m_pD3DDevice->SetRenderState(
				D3DRS_ZFUNC,
				D3DCMP_LESSEQUAL);

			m_pD3DDevice->SetRenderState(
				D3DRS_ZWRITEENABLE,
				TRUE);
		}
	}
}

//-------------------------------------
//- レンダラーのアルファテスト設定
//-------------------------------------
void CRenderer::SetAlphaTest(bool bUse)
{
	// 使用方法を判定
	if (bUse == true)
	{
		// デバイスの有無を確認
		if (m_pD3DDevice != NULL)
		{
			// アルファテストの有効化
			m_pD3DDevice->SetRenderState(
				D3DRS_ALPHATESTENABLE,
				TRUE);

			m_pD3DDevice->SetRenderState(
				D3DRS_ALPHAFUNC,
				D3DCMP_GREATER);

			m_pD3DDevice->SetRenderState(
				D3DRS_ALPHAREF,
				0);
		}

	}
	else if (bUse == false)
	{
		// デバイスの有無を確認
		if (m_pD3DDevice != NULL)
		{
			// アルファテストの無効化
			m_pD3DDevice->SetRenderState(
				D3DRS_ALPHATESTENABLE,
				FALSE);

			m_pD3DDevice->SetRenderState(
				D3DRS_ALPHAFUNC,
				D3DCMP_ALWAYS);

			m_pD3DDevice->SetRenderState(
				D3DRS_ALPHAREF,
				0);
		}
	}
}



//-------------------------------------
//- デバイスの取得処理
//-------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	// デバイスの情報を返す
	return m_pD3DDevice;
}
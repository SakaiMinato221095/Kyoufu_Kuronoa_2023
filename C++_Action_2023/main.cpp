
//-===============================================
//-
//-	ゼニセンシのa版
//-	基本処理[main.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "main.h"

#include "manager.h"

//-======================================
//-	ライブラリのリンク
//-======================================

#pragma comment(lib,"d3d9.lib")			// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")		// DirectXコンポーネント（部品）使用に必要

#pragma comment(lib,"winmm.lib")		// システム時刻を取得

#pragma comment(lib,"dinput8.lib")		// 入力処理に必要
#pragma comment (lib, "xinput.lib")		// XINPUT

//-======================================
//-	マクロ定義
//-======================================

#define CLASS_NAME			"Window class"			// ウィンドウクラスの名前
#define WINDOW_NAME			"ゼニセンシ"			// ウィンドウの名前
#define ID_BUTTON_FINISH	(101)					// 終了ボタンのID

//-======================================
//-	プロトタイプ宣言
//-======================================

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-======================================
//-	グローバル変数
//-======================================

int g_nCountFPS = 0;					//FPSカウンタ	

//-====================================
//-	メイン関数
//-====================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLime, int nCmdShow)
{
	// 終了時にメモリリークを出力
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEXのメモリサイズ
		CS_CLASSDC,							// ウィンドウのスタイル
		WindowProc,							// ウィンドウプロシージャ
		0,									// 0にする（通常はしようしない）
		0,									// 0にする（通常はしようしない）
		hInstance,							// インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		// タスクバーアイコン
		LoadCursor(NULL,IDC_ARROW),			// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			// クライアント領域の背景色
		NULL,								// メニューバー
		CLASS_NAME,							// ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),		// ファイルアイコン
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		// 画面サイズの構造体

	HWND hWnd;	// ウィンドルハンドル（認別子）
	MSG msg;	// メッセージを格納する変数

	DWORD dwCurrentTime = 0;		//現在時刻
	DWORD dwExecLastTime = 0;		//最後に処理した時刻
	DWORD dwFrameCount = 0;			//フレームカウント
	DWORD dwFPSLastTime = 0;		//最後にFPSを計測した時刻
	dwFrameCount = 0;				//フレームカウントを初期化
	dwFPSLastTime = timeGetTime();	//現在時刻を取得

	//乱数の初期化
	srand((unsigned int)time(0));

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウを生成
	hWnd = CreateWindowEx(0,		// 拡張ウィンドウスタイル
		CLASS_NAME,					// ウィンドウクラスの名前
		WINDOW_NAME,				// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		// ウィンドウスタイル
		CW_USEDEFAULT,				// ウィンドウの左上X座標
		CW_USEDEFAULT,				// ウィンドウの左上Y座標
		(rect.right - rect.left),	// ウィンドウの幅
		(rect.bottom - rect.top),	// ウィンドウの高さ
		NULL,						// 親ウィンドウのハンドル
		NULL,						// メニューハンドルまたは子ウィンドウID
		hInstance,					// インスタンスハンドル
		NULL);						// ウィンドウ作成データ


	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);		// ウィンドウ表示状態を設定
	UpdateWindow(hWnd);				// クライアント領域を更新

	// マネージャのポインタを宣言
	CManager *pManager = NULL;

	// マネージャを生成
	pManager = DBG_NEW CManager;

	// マネージャの初期化
	if (pManager != NULL)
	{
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			return E_FAIL;
		}
	}

	// メッセージをループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windosの処理

			if (msg.message == WM_QUIT)
			{// WM_メッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{
				// メッセージを設定
				TranslateMessage(&msg);	// 仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);	// ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{// DirectXの処理

			// 現在時刻を取得
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒経過

			 // FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPSを計測した時刻を保存
				dwFPSLastTime = dwCurrentTime;

				// フレームカウントを加算
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60分の1秒経過

				// 処理開始の時刻[現在時刻]を保存
				dwExecLastTime = dwCurrentTime;

				if (pManager != NULL)
				{
					// レンダラーの更新処理
					pManager->Update();

					// レンダラーの描画処理
					pManager->Draw();
				}

				// フレームカウントを加算
				dwFrameCount++;
			}
		}
	}

	// マネージャの終了処理
	pManager->Uninit();

	// レンダラーの破棄
	if (pManager != NULL)
	{
		// レンダラーの終了処理
		pManager->Uninit();

		// レンダラーの開放
		delete pManager;
		pManager = NULL;
	}

	_CrtDumpMemoryLeaks();


	//分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	// リターン
	return(int)msg.wParam;
}

//-====================================
//-	ウィンドウプロシージャ
//-====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 変数宣言
	int nID;					// 返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:	// ウィンドウ破棄のメッセージ

		// WM_QUIZメッセージを送る
		PostQuitMessage(0);
		
		break;

	case WM_KEYDOWN:	// キー押下のメッセージ

		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]キーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				// ウィンドウを破棄する（WN_DESTROYメッセージを送る）
				DestroyWindow(hWnd);
			}

			break;
		}
		break;

	case WM_COMMAND:	// コマンド発行メッセージ

		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{// 終了ボタンが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				// ウィンドウを破棄する（WN_DESTROYメッセージを送る）
				DestroyWindow(hWnd);
			}
		}

		break;

	case WM_LBUTTONDOWN:	// マウス右クリックのメッセージ

		// 対象ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);

		break;

	case WM_CLOSE:	// 閉じるボタンのメッセージ

		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			// ウィンドウを破棄する（WN_DESTROYメッセージを送る）
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	// 0を返さないと終了してします
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 現在の処理を繰り返す
}
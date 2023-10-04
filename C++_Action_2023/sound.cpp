
//-===============================================
//-
//-	サウンド処理[sound.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	インクルード
//-======================================

#include "sound.h"

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	静的変数宣言
//-======================================

//-------------------------------------
//-	コンストラクタ
//-------------------------------------
CSound::CSound()
{
	// 値をクリア
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;

	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		m_apSourceVoice[nCount] = NULL;
		m_apDataAudio[nCount] = NULL;
		m_aSizeAudio[nCount] = NULL;
	}

}

//-------------------------------------
//-	デストラクタ
//-------------------------------------
CSound::~CSound()
{
}

//-------------------------------------
//- サウンドの初期化処理
//-------------------------------------
HRESULT CSound::Init(HWND hWnd)
{
	// ポインタ宣言
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);

	// XAudio2オブジェクト生成成功の有無を判定
	if (FAILED(hr))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		// 失敗を返す
		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);

	// マスターボイス生成成功の有無を判定
	if (FAILED(hr))
	{
		// 失敗メッセージ
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		// XAudio2オブジェクトの有無を判定
		if (m_pXAudio2 != NULL)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		// 失敗を返す
		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		// ポインタを宣言
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(g_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		// サウンドデータファイル生成成功の有無を判定
		if (hFile == INVALID_HANDLE_VALUE)
		{
			// 失敗メッセージ
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);

			// エラーを返す
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// ファイルポインタの先頭を判定
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動

			// 失敗メッセージ
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);

			// エラーを返す
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

		// WAVEファイルのチェックの有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// ファイルの情報を代入
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);

		// ファイル情報の有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// 
		if (dwFiletype != 'EVAW')
		{
			// 失敗メッセージ
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);

		// ファーマットの有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// チャンクデータの読み込み
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

		// チャンクデータの有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);

		// オーディオデータの有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// オーディオデータを設定
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		// オーディオのチャンクデータの取得
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);

		// オーディオデータの有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// ソースボイスの有無を判定
		if (FAILED(hr))
		{
			// 失敗メッセージ
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);

			// 失敗を返す
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = g_aSoundInfo[nCntSound].nCntLoop;

		// オーディオバッファの登録
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- サウンドの終了処理
//-------------------------------------
void CSound::Uninit(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		// ソースボイスの有無を判定
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	// XAudio2オブジェクトの有無を判定
	if (m_pXAudio2 != NULL)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//-------------------------------------
//- サウンドのセグメント再生(再生中なら停止)
//-------------------------------------
HRESULT CSound::Play(LABEL label)
{
	// 変数宣言
	XAUDIO2_VOICE_STATE xa2state;	// オーディオの状態を格納
	XAUDIO2_BUFFER buffer;			// オーディオバッファ

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = g_aSoundInfo[label].nCntLoop;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);

	// 状態の判定
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 
		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[label]->Start(0);

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- サウンドのセグメント停止(ラベル指定)
//-------------------------------------
void CSound::Stop(LABEL label)
{
	// 変数宣言
	XAUDIO2_VOICE_STATE xa2state;	// オーディオの状態を格納

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);

	// 状態の判定
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 
		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//-------------------------------------
//- サウンドのセグメント停止(全て)
//-------------------------------------
void CSound::Stop(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		// 状態の判定
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//-------------------------------------
//- サウンドのチャンクのチェック
//-------------------------------------
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	// 変数宣言
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	// ファイルポインタの先頭を判定
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動

		// 失敗を返す
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// ファイルポインタの有無を判定
	while (hr == S_OK)
	{
		// チャンクタイプの有無を判定
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み

			// 失敗を返す
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		// チャンクサイズの有無を判定
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み

			// 失敗を返す
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		// チャンクタイプの判定
		switch (dwChunkType)
		{

		case 'FFIR':

			// チャンクサイズを代入
			dwRIFFDataSize = dwChunkDataSize;

			// チャンクサイズに4を代入
			dwChunkDataSize = 4;

			// ファイルタイプの有無を判定
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み

				// 失敗を返す
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default:

			// ファイルポインタの判定
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動

				// 失敗を返す
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		//
		dwOffset += sizeof(DWORD) * 2;

		//
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			// 成功を返す
			return S_OK;
		}

		//
		dwOffset += dwChunkDataSize;

		if (dwBytesRead >= dwRIFFDataSize)
		{
			// 失敗を返す
			return S_FALSE;
		}
	}

	// 成功を返す
	return S_OK;
}

//-------------------------------------
//- チャンクデータの読み込み
//-------------------------------------
HRESULT CSound::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	// 変数宣言
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動

		// 失敗を返す
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み

		// 失敗を返す
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}


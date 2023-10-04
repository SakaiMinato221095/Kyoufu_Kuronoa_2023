
//-===============================================
//-
//-	のヘッダー[precompile.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PRECOMPILE_H_		// このマクロが定義されなかったら
#define _PRECOMPILE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include <windows.h>
#include <time.h>

#include <stdio.h>

#include <d3dx9.h>						// 描画処理に必要

#define DIRECTINPUT_VERSION (0x0800)	// ビルド時の警告対処用のマクロ

#include <dinput.h>						// 入力処理に必要
#include <Xinput.h>						// XINPUT

#include <xaudio2.h>					// サウンド処理に必要

// メモリリーク出力用マクロ
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#endif	// 二重インクルード防止の終了

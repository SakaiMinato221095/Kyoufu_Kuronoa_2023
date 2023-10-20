
//-===============================================
//-
//-	タイマーの処理のヘッダー[timer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _TIMER_H_		// このマクロが定義されなかったら
#define _TIMER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "number.h"

//=======================================
//=	マクロ定義
//=======================================

#define DIG_MINU_NUM_MAX	(2)	// 使用する時間（分）の最大数
#define DIG_SECO_NUM_MAX	(2)	// 使用する時間（秒）の最大数
#define DIG_MILL_NUM_MAX	(1)	// 使用する時間（ミリ秒）の最大数

#define DIG_NUM_MAX			(DIG_MINU_NUM_MAX + DIG_SECO_NUM_MAX + DIG_MILL_NUM_MAX)	// 使用する時間の最大数

//-======================================
//-	クラス定義
//-======================================

class CTimer
{

public:

	// 情報値
	typedef struct
	{
		D3DXVECTOR3 pos;			// 位置
		D3DXVECTOR3 size;			// サイズ
		D3DXVECTOR3 interval;		// 間隔
		D3DXVECTOR3 between;		// 区切りの間隔

		int nTime;					// タイムの値
		int nTimerCount;			// タイマーのカウント
	}Data;

	CTimer();
	~CTimer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color);

	void NullAllNumber(void);

	void NumberTex(void);

	void Elapsed(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color);

	void SetData(Data data);
	Data GetData(void);

private:

	Data m_data;						// 値情報

	CNumber *m_apNumber[DIG_NUM_MAX];	// タイマー用の数字

};

#endif	// 二重インクルード防止の終了

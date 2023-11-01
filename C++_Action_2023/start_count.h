
//-===============================================
//-
//-	スタートカウントの処理のヘッダー[start_count.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _START_COUNT_H_		// このマクロが定義されなかったら
#define _START_COUNT_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "number.h"

//=======================================
//=	マクロ定義
//=======================================

#define STOP_COUNT	(179)	// 停止する時間

//-======================================
//-	クラス定義
//-======================================

class CStartCount
{

public:

	// 情報値
	typedef struct
	{
		int nTime;					// タイムの値
		int nTimerCount;			// タイマーのカウント
	}Data;

	CStartCount();
	~CStartCount();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStartCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	void NumberTex(void);

	void SetData(Data data);
	Data GetData(void);

private:

	Data m_data;		// 値情報

	CNumber *m_pNumber;	// 数字

};

#endif	// 二重インクルード防止の終了

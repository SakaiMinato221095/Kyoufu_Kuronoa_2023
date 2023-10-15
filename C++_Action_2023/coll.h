
//-===============================================
//-
//-	当たり判定の処理のヘッダー[coll.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _COLL_H_		// このマクロが定義されなかったら
#define _COLL_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "mgr_coll.h"

//-======================================
//-	マクロ定義
//-======================================

#define COLLSION_NUM_MAX		(1024)	// 当たり判定の最大数

//-======================================
//-	クラス定義
//-======================================

// 接触のクラス
class CColl
{

public:

	// 接触相手との情報
	typedef struct
	{
		int nNldx;				// 番号
	}HitData;

	// 当たり判定情報
	typedef struct
	{
		CMgrColl::TAG tag;					// タグ
		bool bTagTgt[CMgrColl::TAG_MAX];	// 接触設定の相手のタグ
		CMgrColl::TYPE type;				// 種類
		CMgrColl::STATE_HIT stateHit;		// 接触の種類
		int nNldx;							// 番号

		D3DXVECTOR3 pos;					// 位置
		D3DXVECTOR3 size;					// 大きさ

		HitData hitData[COLLSION_NUM_MAX];	// 接触相手の当たり判定情報
		int nHitNldxMax;					// 接触相手の番号の最大数
	}Data;

	CColl();
	~CColl();

	HRESULT Init(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CColl *Create(CMgrColl::TAG tag, CMgrColl::TYPE type,D3DXVECTOR3 pos ,D3DXVECTOR3 size);

	void UpdateData(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	bool Hit(CMgrColl::TAG hitTag, CMgrColl::STATE_HIT stateHit);

	void SetTagTgt(CMgrColl::TAG hitTag, bool bIsActive);

	void SetData(Data data);
	Data GetData(void);

	void SetHitData(HitData data);
	void ResetHitData(void);

private:

	void InitSet(CMgrColl::TAG tag, CMgrColl::TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	Data m_data;
};

#endif	// 二重インクルード防止の終了

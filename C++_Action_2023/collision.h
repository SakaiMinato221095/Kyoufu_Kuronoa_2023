
//-===============================================
//-
//-	接触の処理のヘッダー[collision.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _COLLSION_H_		// このマクロが定義されなかったら
#define _COLLSION_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

//-======================================
//-	マクロ定義
//-======================================

#define COLLSION_NUM_MAX		(1024)	// 当たり判定の最大数

//-======================================
//-	クラス定義
//-======================================

// 接触のクラス
class CCollision
{

public:

	// 当たり判定タグ
	typedef enum
	{
		TAG_NONE = 0,	// 効果なし
		TAG_PLAYER,		// プレイヤー
		TAG_ENEMY,		// 敵
		TAG_KAZEDAMA,	// 風だま
		TAG_ENEMY_HAVE,	// 保持敵
		TAG_MAX
	}TAG;

	// 当たり種類
	typedef enum
	{
		TYPE_RECTANGLE = 0,	// 矩形
		TYPE_MAX
	}TYPE;

	// 接触相手の当たり判定情報
	typedef struct
	{
		TAG tag;			// タグ
		int nNldx;			// 番号
		CObject *pObj;		// オブジェクト情報
	}HitData;

	// 当たり判定情報
	typedef struct
	{
		TAG tag;							// タグ
		bool bHitTag[TAG_MAX];				// 相手のタグ
		TYPE type;							// 種類
		int nNldx;							// 番号
		
		D3DXVECTOR3 pos;					// 位置
		D3DXVECTOR3 size;					// 大きさ

		CObject *pObj;						// オブジェクト情報

		HitData hitData[COLLSION_NUM_MAX];	// 接触相手の当たり判定情報
		int nHitNldxMax;					// 接触相手の番号の最大数
	}Data;

	CCollision();
	~CCollision();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCollision *Create(void);

	void UninitColl(int nNldxColl);
	void UpdateData(int nNldxColl, D3DXVECTOR3 pos, D3DXVECTOR3 size);

	int SetColl(TAG tag, TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 size, CObject * pObj);
	void SetHit(int nNldxColl, TAG hitTag, bool bIsActive);

	bool Hit(int nNldxColl, TAG hitTag);

	bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	bool hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair);
	bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

private:

	Data m_data[COLLSION_NUM_MAX];	// 当たり判定の情報
	int m_nNldxMax;					// 現在の番号の最大数
};

#endif	// 二重インクルード防止の終了

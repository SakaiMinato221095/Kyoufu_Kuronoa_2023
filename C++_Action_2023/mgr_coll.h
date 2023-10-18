
//================================================
//=
//=	当たり判定管理の処理のヘッダー[mgr_coll.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _MGR_COLL_H_		// このマクロが定義されなかったら
#define _MGR_COLL_H_		// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

#include "object.h"

//=======================================
//=	マクロ定義
//=======================================

#define COLLSION_NUM_MAX		(1024)	// 当たり判定の最大数

//=======================================
//=	前方宣言
//=======================================

class CColl;

//-======================================
//-	クラス定義
//-======================================

// 接触のクラス
class CMgrColl
{

public:

	// 当たり判定タグ
	typedef enum
	{
		TAG_NONE = 0,		// 効果なし
		TAG_PLAYER,			// プレイヤー
		TAG_ENEMY,			// 敵
		TAG_KAZEDAMA,		// 風だま
		TAG_ENEMY_HAVE,		// 保持敵
		TAG_BLOCK,			// ブロック
		TAG_GIMMICK_JEWEL,	// 宝石ギミック
		TAG_MAX
	}TAG;

	// 当たり種類
	typedef enum
	{
		TYPE_RECTANGLE = 0,	// 矩形
		TYPE_MAX
	}TYPE;

	// 接触の種類
	typedef enum
	{
		STATE_HIT_NONE = 0,		// 何もなし（初期）状態
		STATE_HIT_NORMAL,		// 通常接触の状態
		STATE_HIT_DEAD,			// 死亡接触の状態
		STATE_HIT_MAX
	}STATE_HIT;

	CMgrColl();
	~CMgrColl();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CMgrColl *Create(void);

	bool Hit(int nNldxColl, TAG hitTag, STATE_HIT stateHit);

	int Set(CColl *pColl);
	void Reset(int nNldx);

	bool hitRectangle(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair);
	bool hitRectangleRot(D3DXVECTOR3 posMy, D3DXVECTOR3 sizeMy, D3DXVECTOR3 rot, D3DXVECTOR3 posPair, D3DXVECTOR3 sizePair, D3DXVECTOR3 rotPair);
	bool hitRectangleSide(float fPos, float fSize, float fPosPair, float fSizePair);

private:

	CColl *m_apColl[COLLSION_NUM_MAX];	// 当たり判定の情報
	int m_nNldxMax;						// 現在の番号の最大数
};

#endif	// 二重インクルード防止の終了

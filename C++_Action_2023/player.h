
//-===============================================
//-
//-	プレイヤー処理のヘッダー[player.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_H_		// このマクロが定義されなかったら
#define _PLAYER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "object.h"

#include "model.h"
#include "motion.h"

//=======================================
//=	マクロ定義
//=======================================

#define INSTANCE_MAX	(8)		// 自身のポインタの最大数

//-======================================
//-	前方宣言
//-======================================

class CObjectX;
class CObject3d;
class CColl;

class CKazedama;
class CEnemyHave;

class CColl;

//-======================================
//-	クラス定義
//-======================================

class CPlayer : public CObject
{

public:

	// 状態
	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,		// 待機
		STATE_TYPE_MOVE,			// 移動
		STATE_TYPE_HAVING,			// 所持状態
		STATE_TYPE_MAX
	}STATE_TYPE;

	// 追加値の情報
	typedef struct
	{
		float speedRate;	// 速度追加の倍率
		int sppedPlusTime;	// 速度追加の時間

	}DataPlus;

	// 情報値
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 前回の位置

		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 rotDest;	// 目的の向き

		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 moveHold;	// 保持した移動量

		D3DXVECTOR3 size;		// 大きさ

		DataPlus plus;			// 追加値
	}Data;

	CPlayer();
	~CPlayer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	CMotion *GetMotion(void);

	CModel *GetModel(int nNumParts);

	void SetData(Data data);
	Data GetData(void);

	void SetPlus(float fRate, int nTime);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void UpdatePos(void);
	void UpdateRot(void);
	void UpdatePlusData(void);
	void UpdateMotion(void);

	void UpdateKazedama(void);
	void UpdateEnemyHave(void);

	void InputMove(void);

	void InputJump(void);
	void InputNormalJump(void);
	void InputDoubleJump(void);

	void InputAction(void);
	void InputKazedama(void);
	void InputShot(void);

	void DebugPlayer(void);

	Data m_data;								// 値を格納
	bool m_bJump;								// ジャンプ状態の有無
	bool m_bHave;								// 所持状態の有無

	CColl *m_pColl;								// 当たり判定情報

	CKazedama *m_pKazedama;						// 風だまのポインタ
	CEnemyHave *m_pEnemyHave;					// 保持敵のポインタ

	STATE_TYPE m_stateType;						// 状態の種類
	STATE_TYPE m_stateTypeNew;					// 最新の状態の種類

	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス

	CModel *m_apModel[MODEL_PARTS_MAX];			// モデル（パーツ）のポインタ
	int m_nNumModel;							// モデル（パーツ）の総数

	CMotion *m_pMotion;							// モーションのポインタ
};

#endif	// 二重インクルード防止の終了

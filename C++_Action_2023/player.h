
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

//-======================================
//-	前方宣言
//-======================================

class CObjectX;
class CObject3d;
class CColl;

//-======================================
//-	クラス定義
//-======================================

class CPlayer : public CObject
{

public:

	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 前回の位置

		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 rotDest;	// 目的の向き

		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 moveHold;	// 保持した移動量

		D3DXVECTOR3 size;		// 大きさ
	}Data;

	CPlayer();
	~CPlayer();

	HRESULT Init(CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);

	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Hit(int nDamage);

	void DebugPlayer(void);

	CMotion *GetMotion(void);

	CModel *GetModel(int nNumParts);

	void SetData(Data data);
	Data GetData(void);

	void SetHave(bool bHave);

private:

	void UpdatePos(void);
	void UpdateRot(void);

	void InputMove(void);

	void InputJump(void);
	void InputNormalJump(void);
	void InputDoubleJump(void);

	void InputAction(void);
	void InputKazedama(void);
	void InputShot(void);

	Data m_data;								// 値を格納
	bool m_bJump;								// ジャンプ状態の有無
	bool m_bHave;								// 所持状態の有無

	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス

	CColl *m_pColl;								// 当たり判定の情報

	CModel *m_apModel[MODEL_PARTS_MAX];			// モデル（パーツ）のポインタ
	int m_nNumModel;							// モデル（パーツ）の総数

	CMotion *m_pMotion;							// モーションのポインタ
};

#endif	// 二重インクルード防止の終了

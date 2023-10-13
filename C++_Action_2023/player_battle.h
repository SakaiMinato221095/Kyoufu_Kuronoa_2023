
//-===============================================
//-
//-	戦闘プレイヤー処理のヘッダー[player_battle.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _PLAYER_BATTLE_H_		// このマクロが定義されなかったら
#define _PLAYER_BATTLE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "player.h"

#include "model.h"
#include "motion.h"

//=======================================
//=	マクロ定義
//=======================================

//=======================================
//=	前方宣言
//=======================================

//-======================================
//-	クラス定義
//-======================================

class CPlayerBattle : public CPlayer
{

public:

	typedef enum
	{
		STATE_TYPE_NEUTRAL = 0,		// 待機
		STATE_TYPE_MOVE,			// 移動
		STATE_TYPE_HAVING,			// 所持状態
		STATE_TYPE_MAX			
	}STATE_TYPE;

	CPlayerBattle();
	~CPlayerBattle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType, int nStateMax);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerBattle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CModel::MODEL_TYPE modelType, CMotion::MOTION_TYPE motionType);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void UpdateMotion(void);

	STATE_TYPE m_stateType;			// 状態の種類
	STATE_TYPE m_stateTypeNew;		// 最新の状態の種類
};

#endif	// 二重インクルード防止の終了

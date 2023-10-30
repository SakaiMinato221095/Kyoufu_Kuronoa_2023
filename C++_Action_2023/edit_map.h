
//================================================
//=
//=	マップエディットの処理のヘッダー[edit_map.h]
//= Author Sakai Minato
//=
//================================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _EDIT_MAP_H_		// このマクロが定義されなかったら
#define _EDIT_MAP_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CObjectX;
class CObjectBillboard;

class CObject;

//-======================================
//-	クラス定義
//-======================================

class CEditMap
{

public:

	typedef enum
	{
		TYPE_BLOCK = 0,				// ブロック
		TYPE_GOAL,					// ゴール
		TYPE_PLAYER,				// プレイヤー
		TYPE_ENEMY,					// 敵
		TYPE_GIMMICK_SPEED,			// 速度UPギミック
		TYPE_TEACH_MOVE,			// 移動 
		TYPE_TEACH_JUMP,			// ジャンプ
		TYPE_TEACH_KAZEDAMA,		// 風だま
		TYPE_TEACH_DOUBLE_JUMP,		// 二段ジャンプ
		TYPE_TEACH_SHOT,			// ショット
		TYPE_MAX
	}TYPE;

	// エディット時のデータ
	typedef struct
	{
		CObjectX *pObjX;				// エディット中のXファイルオブジェクト
		CObjectBillboard *pObjBill;		// エディット中のビルボードオブジェクト
		TYPE type;						// 現在のタイプ
		D3DXVECTOR3 pos;				// 位置
	}EditData;

	CEditMap();
	~CEditMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEditMap *Create(void);

private:

	void InputObjMove(void);
	void InputSetObj(void);
	void InputChangeType(void);
	void InputSave(void);

	void SetEditObj(TYPE type);
	void SetAddType(void);
	void SetSubType(void);
	void SetObjMove(D3DXVECTOR3 move);

	void SetObj(void);

	EditData m_editData;		// エディット時のデータ
};

#endif	// 二重インクルード防止の終了


//-===============================================
//=
//= 階層構造のモデル処理のヘッター[model.h]
//= Author Sakai Minato
//=
//-===============================================

//=======================================
//=	二重インクルード防止
//=======================================

#ifndef _MODEL_H_	// このマクロが定義されなかったら
#define _MODEL_H_	// 二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

//-======================================
//-	マクロ定義
//-======================================

#define MODEL_PARTS_MAX	(32)	// モデルパーツの最大数
#define MODEL_NUM_MAX	(32)	// モデルの最大数

//=======================================
//=	クラス定義
//=======================================

// 階層構造のXファイルオブジェクトのクラス
class CModel
{
public:
	
	// モデルの種類
	typedef enum
	{
		MODEL_TYPE_PLAYER_AONOA = 0,	// プレイヤー（アオノア）
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	// （モデル）パーツの情報
	typedef struct
	{
		int nIndex;				// パーツの番号
		int nParent;			// 親の番号
		char aFileName[256];	// ファイルの名前

		D3DXVECTOR3 pos;		// 位置情報
		D3DXVECTOR3 rot;		// 向き情報
	}Parts;

	// モデルの情報
	typedef struct
	{
		Parts modelParts[MODEL_PARTS_MAX];		// モデルパーツの情報
		int nPartsNum;							// パーツ数
	}Model;

	// モデルの値情報
	typedef struct
	{
		D3DXVECTOR3 pos;			// モデル本体の位置情報
		D3DXVECTOR3 posMotion;	// モーションの位置情報
		D3DXVECTOR3 rot;			// モデル本体の向き情報
		D3DXVECTOR3 rotMotion;	// モーションの位置情報
	}Data;

	CModel();
	~CModel();

	static HRESULT Load(void);

	HRESULT Init(MODEL_TYPE modelType, int nCount);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel * Create(MODEL_TYPE modelType, int nCount);

	void SetParent(CModel ** pModel, MODEL_TYPE modelType, int nCount);

	D3DXMATRIX GetMtxWorld(void);

	void SetData(CModel::Data data);
	Data GetData(void);

	static void SetFile(MODEL_TYPE modelType);
	static int GetPartsNum(MODEL_TYPE modelType);

	static int m_nModelNldx[MODEL_TYPE_MAX][MODEL_PARTS_MAX];	// モデルの番号

private:

	Data m_data;							// モデルの値情報

	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	CModel *m_pParent;						// 親モデルのポインタ

	MODEL_TYPE m_modelType;					// 自分のモデルの種類
	int m_nPartsNum;						// 自分のパーツ番号

	static Model m_model[MODEL_NUM_MAX];	// モデルの情報
};

#endif	// 二重インクルード防止の終了
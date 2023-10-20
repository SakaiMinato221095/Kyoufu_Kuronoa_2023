

//-===============================================
//-
//-	ステージCSV処理のヘッダー[csv_stage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _CSV_STAGE_H_		// このマクロが定義されなかったら
#define _CSV_STAGE_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

#define LINE_MAX		(64)					// 横列の最大数
#define COLU_MAX		(16)					// 縦列の最大数

#define CSV_DATA_MAX	(LINE_MAX * COLU_MAX)	// 横と縦の最大数

#define ARRAY_SIZE		(8)						// 配列のサイズ

//-======================================
//-	前方宣言
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CCsvStage
{

public:

	typedef enum
	{
		CSV_STAGE_000 = 0,	// ステージ_000のテキスト
		CSV_STAGE_MAX,
	}CSV;

	typedef enum
	{
		TYPE_TEXT_NONE = 0,				// なし
		TYPE_TEXT_WALL,					// 壁
		TYPE_TEXT_BLOCK,				// ブロック
		TYPE_TEXT_TUTORIAL_000,			// チュートリアル_000
		TYPE_TEXT_TUTORIAL_001,			// チュートリアル_001
		TYPE_TEXT_TUTORIAL_002,			// チュートリアル_002
		TYPE_TEXT_GOAL,					// ゴール
		TYPE_TEXT_PLAYER,				// プレイヤー
		TYPE_TEXT_ENEMY,				// 敵
		TYPE_TEXT_GIMMICK_SPEED,		// 速度UPギミック
		TYPE_TEXT_MAX
	}TYPE_TEXT;

	typedef struct
	{
		bool bUse;				// 使用の有無
		TYPE_TEXT type;			// 種類
		D3DXVECTOR3 pos;		// 位置
	}Data;

	CCsvStage();
	~CCsvStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCsvStage *Create(void);

	void Load(CCsvStage::CSV csv);

	void SetObj(void);

private:

	void Divide(void);

	void SetObjData(TYPE_TEXT typeText, D3DXVECTOR3 pos);

	Data m_data[CSV_DATA_MAX];						// データ
	char m_acCsvData[CSV_DATA_MAX][ARRAY_SIZE];		// 文字データ
};

#endif	// 二重インクルード防止の終了

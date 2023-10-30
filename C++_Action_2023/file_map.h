
//-===============================================
//-
//-	マップファイル処理のヘッダー[file_map.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _FILE_MAP_H_		// このマクロが定義されなかったら
#define _FILE_MAP_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

#include "edit_map.h"

//-======================================
//-	マクロ定義
//-======================================

#define MAP_OBJ_MAX	(1024)

//-======================================
//-	前方宣言
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CFileMap
{

public:

	typedef enum
	{
		TEXT_MAP_NORMAL = 0,	// 通常マップ
	}TEXT;

	CFileMap();
	~CFileMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFileMap *Create(void);

	void Save(void);
	void Load(void);

	bool SetObj(CEditMap::EditData editData);

private:

	void SetMapObj(CEditMap::EditData editData);

	CEditMap::EditData m_aMapData[MAP_OBJ_MAX];		// マップデータ
	int m_nNumMax;									// 最大数
};

#endif	// 二重インクルード防止の終了
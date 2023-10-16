
//-===============================================
//-
//-	オブジェクト管理処理のヘッダー[mgr_obj.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MAR_OBJ_H_		// このマクロが定義されなかったら
#define _MAR_OBJ_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	前方宣言
//-======================================

//-======================================
//-	クラス定義
//-======================================

class CMgrObj
{

public:

	CMgrObj();
	~CMgrObj();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * GetObjectNone(int nNum);
	static void SetObjectNone(int nNum, CObjectXNone *pObjectXNone);
	static void ReleaseObjectNone(int nNum);

private:

	HRESULT CreateAll(HWND hWnd);

	static CObjectXNone *m_apObjectXNone[OBJECTX_NONE_NUM_MAX];				// 効果なしオブジェクト

};

#endif	// 二重インクルード防止の終了

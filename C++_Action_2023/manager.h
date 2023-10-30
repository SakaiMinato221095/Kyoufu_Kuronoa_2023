
//-===============================================
//-
//-	管理処理のヘッダー[manager.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _MANAGER_H_		// このマクロが定義されなかったら
#define _MANAGER_H_		// 二重インクルード帽子のマクロを定義

//-======================================
//-	インクルード
//-======================================

//-======================================
//-	前方宣言
//-======================================

class CRenderer;
class CInputKeyboard;
class CXInput;
class CSound;
class CDebugProc;

class CFade;

class CManagerTexture;
class CManagerModel;

class CCamera;
class CLight;

class CMgrColl;

class CCsvStage;
class CFileMap;

//-======================================
//-	クラス定義
//-======================================

// シーンクラス
class CScene
{
public:

	typedef enum
	{
		MODE_TITEL = 0,	// タイトル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_MAX
	}MODE;

	CScene();

	virtual ~CScene();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static CScene *Create(MODE mode,HINSTANCE hInstance = NULL, HWND hWnd = 0, BOOL bWindow = true);

	void SetMode(MODE mode);
	MODE GetMode(void);

private:

	MODE m_mode;	// モードの情報
};

// マネージャークラス
class CManager
{

public:

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void SetMode(CScene::MODE mode);
	CScene::MODE GetMode(void);

	CFade *GetFade(void);

	CRenderer *GetRenderer(void);
	CInputKeyboard *GetInputKeyboard(void);
	CXInput *GetXInput(void);
	CSound *GetSound(void);
	CDebugProc *GetDbugProc(void);

	CManagerTexture *GetManagerTexture(void);
	CManagerModel *GetManagerModel(void);

	CCamera *GetCamera(void);
	CLight *GetLight(void);

	CMgrColl *GetMgrColl(void);

	CFileMap *GetFileMap(void);

	static CManager *GetInstance();
private:

	void Debug(void);

	CScene *m_pScene;					// シーンのポインタ
	CFade *m_pFade;						// フェードのポインタ

	CRenderer *m_pRenderer;				// レンダラーのポインタ
	CInputKeyboard *m_pInputKeyboard;	// キーボードのポインタ
	CXInput *m_pXInput;					// X入力のポインタ
	CSound *m_pSound;					// サウンドのポインタ
	CDebugProc *m_pDbugProc;				// デバックのポインタ

	CManagerTexture *m_pManagerTexture;	// テクスチャ管理のポインタ
	CManagerModel *m_pManagerModel;		// モデル管理のポインタ

	CCamera *m_pCamera;					// カメラのポインタ
	CLight *m_pLight;					// ライトのポインタ

	CMgrColl *m_pMgrColl;				// 当たり判定管理のポインタ

	CFileMap *m_pFileMap;				// ステージのCSVのポインタ

	static CManager *m_pManager;		// 自身のポインタ
};

#endif	// 二重インクルード防止の終了


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
class CTimeStop;

class CCamera;
class CLight;

class CEffectGame;

class CStateMode;

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
	virtual ~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static void SetMode(CScene::MODE mode);
	static CScene::MODE GetMode(void);

	static CFade *GetFade(void);

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CXInput *GetXInput(void);
	static CSound *GetSound(void);
	static CDebugProc *GetDbugProc(void);

	static CManagerTexture *GetManagerTexture(void);
	static CManagerModel *GetManagerModel(void);
	static CTimeStop *GetManagerTime(void);

	static CCamera *GetCamera(void);
	static CLight *GetLight(void);

	static CEffectGame *GetEffectGame(void);

	static CStateMode *GetStateMode(void);

private:

	static CScene *m_pScene;					// シーンのポインタ
	static CFade *m_pFade;						// フェードのポインタ

	static CRenderer *m_pRenderer;				// レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;	// キーボードのポインタ
	static CXInput *m_pXInput;					// X入力のポインタ
	static CSound *m_pSound;					// サウンドのポインタ
	static CDebugProc *m_pDbugProc;				// デバックのポインタ

	static CManagerTexture *m_pManagerTexture;	// テクスチャ管理のポインタ
	static CManagerModel *m_pManagerModel;		// モデル管理のポインタ
	static CTimeStop *m_pManagerTime;			// 時間管理のポインタ

	static CCamera *m_pCamera;					// カメラのポインタ
	static CLight *m_pLight;					// ライトのポインタ

	static CEffectGame *m_pEffectGame;			// ゲームエフェクト

	static CStateMode *m_pStateMode;			// モードステータス

};

#endif	// 二重インクルード防止の終了

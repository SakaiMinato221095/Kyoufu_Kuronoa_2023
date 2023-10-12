
//-===============================================
//-
//- X入力処理のヘッダー[xinput.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _X_INPUT_H_	//このマクロが定義されなかったら
#define _X_INPUT_H_	//二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

//-======================================
//-	マクロ定義
//-======================================

//-======================================
//-	クラス定義
//-======================================

// 入力処理のクラス
class CXInput
{
public:

	// 入力種類
	typedef enum
	{
		TYPE_INPUT_BUTTON = 0,	// ボタン
		TYPE_INPUT_TRIGGER_R,	// 右トリガー
		TYPE_INPUT_TRIGGER_L,	// 左トリガー
		TYPE_INPUT_STICK_R,		// 右スティック
		TYPE_INPUT_STICK_L,		// 左スティック
		TYPE_INPUT_MAX
	}TYPE_INPUT;

	// スティック方向
	typedef enum
	{
		TYPE_STICK_NONE = 0,	// 方向なし
		TYPE_STICK_UP,			// 上方向
		TYPE_STICK_DOWN,		// 下方向
		TYPE_STICK_LEFT,		// 左方向
		TYPE_STICK_RIGHT,		// 右方向
		TYPE_STICK_MAX,
	}TYPE_STICK;

	CXInput();
	~CXInput();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	static CXInput *Create(HINSTANCE hInstance, HWND hWnd);

	bool GetPress(int nKey, TYPE_INPUT type);
	bool GetTrigger(int nKey, TYPE_INPUT type);

protected:

	void UpdateTrigger(void);
	void UpdateStick(void);

	static LPDIRECTINPUT8 m_pInput;			// 入力処理のオブジェクト
	LPDIRECTINPUTDEVICE8 m_pDevice;			// 入力処理のデバイス

	XINPUT_GAMEPAD m_gamepad;				// ゲームパッドの入力情報
	XINPUT_GAMEPAD m_gamepadOld;			// 前回のゲームパッドの入力情報

	bool m_aStickRight[TYPE_STICK_MAX];		// 右スティック方向の有無 
	bool m_aStickLeft[TYPE_STICK_MAX];		// 左スティック方向の有無

	bool m_aStickRightOld[TYPE_STICK_MAX];	// 前回の右スティック方向の有無 
	bool m_aStickLeftOld[TYPE_STICK_MAX];	// 前回の左スティック方向の有無

	bool m_bTriggerRight;					// 右トリガーの有無 
	bool m_bTriggerLeft;					// 左トリガーの有無

	bool m_bTriggerRightOld;				// 前回の右トリガーの有無 
	bool m_bTriggerLeftOld;					// 前回の左トリガーの有無
};

#endif

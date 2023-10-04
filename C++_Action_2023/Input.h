
//-===============================================
//-
//- 入力処理のヘッダー[input.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	二重インクルード防止
//-======================================

#ifndef _INPUT_H_	//このマクロが定義されなかったら
#define _INPUT_H_	//二重インクルード帽子のマクロを定義

//=======================================
//=	インクルード
//=======================================

//-======================================
//-	マクロ定義
//-======================================

#define NUM_KEY_MAX		(256)	// キーの最大数

//-======================================
//-	クラス定義
//-======================================

// 入力処理のクラス
class CInput
{
public:

	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:

	static LPDIRECTINPUT8 m_pInput;		// 入力処理のオブジェクト
	LPDIRECTINPUTDEVICE8 m_pDevice;		// 入力処理のデバイス

};

// キーボードの入力処理（入力処理の子クラス）
class CInputKeyboard : public CInput
{
public:

	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];					// キーボードのブレス情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			// キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			// キーボードのリリース情報

};

#endif 
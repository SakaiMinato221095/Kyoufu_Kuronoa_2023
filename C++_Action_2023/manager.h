
//-===============================================
//-
//-	�Ǘ������̃w�b�_�[[manager.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MANAGER_H_		// ���̃}�N������`����Ȃ�������
#define _MANAGER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�O���錾
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
//-	�N���X��`
//-======================================

// �V�[���N���X
class CScene
{
public:

	typedef enum
	{
		MODE_TITEL = 0,	// �^�C�g��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
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

	MODE m_mode;	// ���[�h�̏��
};

// �}�l�[�W���[�N���X
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

	static CScene *m_pScene;					// �V�[���̃|�C���^
	static CFade *m_pFade;						// �t�F�[�h�̃|�C���^

	static CRenderer *m_pRenderer;				// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	static CXInput *m_pXInput;					// X���͂̃|�C���^
	static CSound *m_pSound;					// �T�E���h�̃|�C���^
	static CDebugProc *m_pDbugProc;				// �f�o�b�N�̃|�C���^

	static CManagerTexture *m_pManagerTexture;	// �e�N�X�`���Ǘ��̃|�C���^
	static CManagerModel *m_pManagerModel;		// ���f���Ǘ��̃|�C���^
	static CTimeStop *m_pManagerTime;			// ���ԊǗ��̃|�C���^

	static CCamera *m_pCamera;					// �J�����̃|�C���^
	static CLight *m_pLight;					// ���C�g�̃|�C���^

	static CEffectGame *m_pEffectGame;			// �Q�[���G�t�F�N�g

	static CStateMode *m_pStateMode;			// ���[�h�X�e�[�^�X

};

#endif	// ��d�C���N���[�h�h�~�̏I��

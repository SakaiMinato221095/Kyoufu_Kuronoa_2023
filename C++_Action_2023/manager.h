
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

class CCamera;
class CLight;

class CMgrColl;

class CCsvStage;
class CFileMap;

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

	CScene *m_pScene;					// �V�[���̃|�C���^
	CFade *m_pFade;						// �t�F�[�h�̃|�C���^

	CRenderer *m_pRenderer;				// �����_���[�̃|�C���^
	CInputKeyboard *m_pInputKeyboard;	// �L�[�{�[�h�̃|�C���^
	CXInput *m_pXInput;					// X���͂̃|�C���^
	CSound *m_pSound;					// �T�E���h�̃|�C���^
	CDebugProc *m_pDbugProc;				// �f�o�b�N�̃|�C���^

	CManagerTexture *m_pManagerTexture;	// �e�N�X�`���Ǘ��̃|�C���^
	CManagerModel *m_pManagerModel;		// ���f���Ǘ��̃|�C���^

	CCamera *m_pCamera;					// �J�����̃|�C���^
	CLight *m_pLight;					// ���C�g�̃|�C���^

	CMgrColl *m_pMgrColl;				// �����蔻��Ǘ��̃|�C���^

	CFileMap *m_pFileMap;				// �X�e�[�W��CSV�̃|�C���^

	static CManager *m_pManager;		// ���g�̃|�C���^
};

#endif	// ��d�C���N���[�h�h�~�̏I��

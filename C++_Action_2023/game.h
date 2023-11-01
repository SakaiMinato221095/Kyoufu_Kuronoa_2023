
//-===============================================
//-
//-	�Q�[���̏����̃w�b�_�[[game.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GAME_H_		// ���̃}�N������`����Ȃ�������
#define _GAME_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�O���錾
//-======================================

class CPlayer;

class CTimer;

class CEditMap;

class CPause;

class CStartCount;

//-======================================
//-	�N���X��`
//-======================================

class CGame : public CScene
{

public:

	typedef enum
	{
		GAME_NONE = 0,	// �Q�[���̒ʏ���
		GAME_PAUSE,		// �|�[�Y���
		GAME_MAX
	}GAME;

	CGame();
	~CGame();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CPlayer *GetPlayer(void);

	static CStartCount *GetStartCount(void);


private:

	static CPlayer *m_pPlayer;				// �v���C���[
	static CTimer *m_pTimer;				// �^�C�}�[

	static CStartCount *m_pStartCount;		// �X�^�[�g�J�E���g

	static CEditMap *m_pEditMap;			// �}�b�v�G�f�B�b�g

	static CPause *m_pPause;				// �|�[�Y

	GAME m_game;							// �Q�[�����
};

#endif	// ��d�C���N���[�h�h�~�̏I��

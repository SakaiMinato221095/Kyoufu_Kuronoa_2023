
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

class CPause;

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

	static CPause *GetPause(void);

private:

	static CPause *m_pPause;				// �|�[�Y

	GAME m_game;							// �Q�[�����
};

#endif	// ��d�C���N���[�h�h�~�̏I��


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

#include "sys_game_phase.h"

//=======================================
//=	�}�N����`
//=======================================

#define OBJ_2D_NONE_NUM_MAX	(8)		// ���ʂȂ�2D�̍ő吔
#define EFFECT_2D_NUM_MAX	(8)		// 2D�G�t�F�N�g�̍ő吔

//-======================================
//-	�O���錾
//-======================================

class CMgrSysObj;

class CManagerObject;

class CStateGame;
class CStateBattle;

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

	static void SetPhase(CSysGamePhase::TYPE type);
	static CSysGamePhase::TYPE GetPhase(void);

	static CSysGamePhase *GetSysGamePhase(void);

	static CMgrSysObj *GetMgrSysObj(void);
	
	static CStateGame *GetStateGame(void);
	static CStateBattle *GetStateBattle(void);

	static CPause *GetPause(void);

private:

	void UpdateSetResult(void);
	void UpdateTimeEndResult(void);

	static CSysGamePhase *m_pSysGamePhase;	// �Q�[���t�F�[�Y�̃|�C���^

	static CMgrSysObj *m_pMgrSysObj;		// �V�X�e���I�u�W�F�N�g�Ǘ��̃|�C���^

	static CStateGame *m_pStateGame;		// �Q�[���X�e�[�^�X
	static CStateBattle *m_pStateBattle;	// �퓬�X�e�[�^�X

	static CPause *m_pPause;				// �|�[�Y

	GAME m_game;							// �Q�[�����
};

#endif	// ��d�C���N���[�h�h�~�̏I��

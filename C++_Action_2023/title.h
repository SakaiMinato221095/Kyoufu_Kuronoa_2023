
//-===============================================
//-
//-	�^�C�g���̏����̃w�b�_�[[title.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _TITLE_H_		// ���̃}�N������`����Ȃ�������
#define _TITLE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

class CObj2dNone;

//-======================================
//-	�N���X��`
//-======================================

class CTitle : public CScene
{

public:

	typedef enum
	{
		TYPE_NONE_2D_LOGO = 0,	// �^�C�g�����S
		TYPE_NONE_2D_BUTTON,	// �^�C�g���{�^��
		TYPE_NONE_2D_MAX
	}TYPE_NONE_2D;

	CTitle();
	~CTitle();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	static CPlayer *m_pPlayer;

	static CObj2dNone *m_apObj2dNone[TYPE_NONE_2D_MAX];
};

#endif	// ��d�C���N���[�h�h�~�̏I��

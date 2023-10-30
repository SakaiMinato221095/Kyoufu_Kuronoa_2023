
//-===============================================
//-
//-	�|�[�Y�̏����̃w�b�_�[[pause.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PAUSE_H_		// ���̃}�N������`����Ȃ�������
#define _PAUSE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object.h"

//=======================================
//=	�}�N����`
//=======================================

//-======================================
//-	�O���錾
//-======================================

class CObj2dNone;

//-======================================
//-	�N���X��`
//-======================================

class CPause : public CObject
{

public:

	typedef enum
	{
		TYPE_BG = 0,	// �w�i
		TYPE_GAME,		// �Q�[��
		TYPE_RETRY,		// ���g���C
		TYPE_TITLE,		// �^�C�g��
		TYPE_CURSOR,	// �J�[�\��
		TYPE_MAX
	}TYPE;

	typedef enum
	{
		TYPE_SELECT_GAME = 0,	// �Q�[��
		TYPE_SELECT_RETRY,		// ���g���C
		TYPE_SELECT_TITLE,		// �^�C�g��
		TYPE_SELECT_MAX,
	}TYPE_SELECT;

	CPause();
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPause * Create(void);

	static CObj2dNone *GetObj2dNone(int nNum);

	TYPE_SELECT GetTypeSelect(void);

	bool GetOk(void);
private:

	static CObj2dNone *m_apObj2dNone[TYPE_MAX];	// ���ʂȂ�2D�I�u�W�F�N�g�̃|�C���^
	TYPE_SELECT m_typeSelect;					// ���݂̑I���̎��

	bool m_bOk;

};

#endif	// ��d�C���N���[�h�h�~�̏I��


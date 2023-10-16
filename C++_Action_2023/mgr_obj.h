
//-===============================================
//-
//-	�I�u�W�F�N�g�Ǘ������̃w�b�_�[[mgr_obj.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _MAR_OBJ_H_		// ���̃}�N������`����Ȃ�������
#define _MAR_OBJ_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CMgrObj
{

public:

	CMgrObj();
	~CMgrObj();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * GetObjectNone(int nNum);
	static void SetObjectNone(int nNum, CObjectXNone *pObjectXNone);
	static void ReleaseObjectNone(int nNum);

private:

	HRESULT CreateAll(HWND hWnd);

	static CObjectXNone *m_apObjectXNone[OBJECTX_NONE_NUM_MAX];				// ���ʂȂ��I�u�W�F�N�g

};

#endif	// ��d�C���N���[�h�h�~�̏I��

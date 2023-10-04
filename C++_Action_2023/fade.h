
//-===============================================
//-
//-	�t�F�[�h�����̃w�b�_�[[fade.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FADE_H_		// ���̃}�N������`����Ȃ�������
#define _FADE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "manager.h"

#include "main.h"
#include "object.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CFade
{

public:

	typedef enum
	{
		STATE_NONE = 0,	// �������Ă��Ȃ����
		STATE_IN,		// �t�F�[�h�C�����
		STATE_OUT,		// �t�F�[�h�A�E�g���
		STATE_MAX
	}STATE;

	CFade();
	~CFade();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade *CFade::Create(void);

	virtual void SetVtx(void);

	void SetFade(CScene::MODE mode);
	STATE GetFade(void);

	CDataD3DXVECTOR3 m_dataPos;		// �ʒu
	CDataD3DXVECTOR3 m_dataSize;	// �傫��
	CDataD3DXCOLOR m_dataColor;		// �F

private:

	void InitSet(
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@���i�[
	STATE m_state;								// �t�F�[�h���
	CScene::MODE m_mode;						// ���[�h��ݒ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��

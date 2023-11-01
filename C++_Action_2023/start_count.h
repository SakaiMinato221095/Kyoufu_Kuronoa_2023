
//-===============================================
//-
//-	�X�^�[�g�J�E���g�̏����̃w�b�_�[[start_count.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _START_COUNT_H_		// ���̃}�N������`����Ȃ�������
#define _START_COUNT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "number.h"

//=======================================
//=	�}�N����`
//=======================================

#define STOP_COUNT	(179)	// ��~���鎞��

//-======================================
//-	�N���X��`
//-======================================

class CStartCount
{

public:

	// ���l
	typedef struct
	{
		int nTime;					// �^�C���̒l
		int nTimerCount;			// �^�C�}�[�̃J�E���g
	}Data;

	CStartCount();
	~CStartCount();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStartCount *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color);

	void NumberTex(void);

	void SetData(Data data);
	Data GetData(void);

private:

	Data m_data;		// �l���

	CNumber *m_pNumber;	// ����

};

#endif	// ��d�C���N���[�h�h�~�̏I��

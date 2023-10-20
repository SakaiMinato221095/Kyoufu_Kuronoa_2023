
//-===============================================
//-
//-	�^�C�}�[�̏����̃w�b�_�[[timer.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _TIMER_H_		// ���̃}�N������`����Ȃ�������
#define _TIMER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "number.h"

//=======================================
//=	�}�N����`
//=======================================

#define DIG_MINU_NUM_MAX	(2)	// �g�p���鎞�ԁi���j�̍ő吔
#define DIG_SECO_NUM_MAX	(2)	// �g�p���鎞�ԁi�b�j�̍ő吔
#define DIG_MILL_NUM_MAX	(1)	// �g�p���鎞�ԁi�~���b�j�̍ő吔

#define DIG_NUM_MAX			(DIG_MINU_NUM_MAX + DIG_SECO_NUM_MAX + DIG_MILL_NUM_MAX)	// �g�p���鎞�Ԃ̍ő吔

//-======================================
//-	�N���X��`
//-======================================

class CTimer
{

public:

	// ���l
	typedef struct
	{
		D3DXVECTOR3 pos;			// �ʒu
		D3DXVECTOR3 size;			// �T�C�Y
		D3DXVECTOR3 interval;		// �Ԋu
		D3DXVECTOR3 between;		// ��؂�̊Ԋu

		int nTime;					// �^�C���̒l
		int nTimerCount;			// �^�C�}�[�̃J�E���g
	}Data;

	CTimer();
	~CTimer();

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color);

	void NullAllNumber(void);

	void NumberTex(void);

	void Elapsed(void);

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 interval, D3DXVECTOR3 between, D3DXVECTOR3 size, D3DXCOLOR color);

	void SetData(Data data);
	Data GetData(void);

private:

	Data m_data;						// �l���

	CNumber *m_apNumber[DIG_NUM_MAX];	// �^�C�}�[�p�̐���

};

#endif	// ��d�C���N���[�h�h�~�̏I��

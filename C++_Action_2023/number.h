
//-===============================================
//-
//-	���������̃w�b�_�[[object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _NUMBER_H_		// ���̃}�N������`����Ȃ�������
#define _NUMBER_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object2d.h"

//-======================================
//-	�N���X��`
//-======================================

class CNumber : public CObject2d
{

public:

	// �����̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_GOLD_000 = 0,		// ����_000�i���F�j
		TEX_DARK_GREEN_001,		// ����_001�i�[�΁j
		TEX_MAX
	}TEX;

	typedef struct
	{
		int nDigits;		// ����
	}Data;

	CNumber(int nPriority = 3);
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CNumber *Create(TEX tex);

	void SetVtx(void);

	void SetData(Data data);
	Data GetData(void);

private:

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�

	Data m_data;							// �l���
};

#endif	// ��d�C���N���[�h�h�~�̏I��

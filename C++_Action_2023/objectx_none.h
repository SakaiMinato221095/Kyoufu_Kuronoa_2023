
//-===============================================
//-
//-	���ʂȂ���X�t�@�C���I�u�W�F�N�g�����̃w�b�_�[[objectx_none.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_X_NONE_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_X_NONE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �A�C�e���̃N���X
class CObjectXNone : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_SAKURA_000,			// ��
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CObjectXNone(int nPriority = 3);
	~CObjectXNone();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectXNone * Create(MODEL model);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	void InitSet(MODEL model);

	MODEL m_model;	// ���g�̃��f��
	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
	static int m_nModelNldx[MODEL_MAX];			// ���f���̔ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��


//-===============================================
//-
//-	�M�~�b�N�����̃w�b�_�[[gimmick.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GIMMICK_H_		// ���̃}�N������`����Ȃ�������
#define _GIMMICK_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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

// �M�~�b�N�̃N���X
class CGimmick : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_JEWEL_000,			// ��
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CGimmick(int nPriority = 3);
	~CGimmick();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGimmick * Create(MODEL model,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	void InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	MODEL m_model;								// ���g�̃��f��
	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
	static int m_nModelNldx[MODEL_MAX];			// ���f���̔ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��

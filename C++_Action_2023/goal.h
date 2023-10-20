
//-===============================================
//-
//-	�S�[�������̃w�b�_�[[goal.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _GOAL_H_		// ���̃}�N������`����Ȃ�������
#define _GOAL_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

//-======================================
//-	�}�N����`
//-======================================

//=======================================
//=	�O���錾
//=======================================

class CColl;

//-======================================
//-	�N���X��`
//-======================================

// �M�~�b�N�̃N���X
class CGoal : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_GOAL_000 = 0,	// �S�[��000
		MODEL_MAX
	}MODEL;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CGoal(int nPriority = 3);
	~CGoal();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGoal * Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

private:

	void InitSet(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	MODEL m_model;								// ���g�̃��f��
	static ModelData m_modelData[MODEL_MAX];	// ���f���̏��
	static int m_nModelNldx[MODEL_MAX];			// ���f���̔ԍ�

	CColl *m_pColl;		// �����蔻��̔ԍ�

};

#endif	// ��d�C���N���[�h�h�~�̏I��

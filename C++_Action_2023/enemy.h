
//-===============================================
//-
//-	�G�̏����̃w�b�_�[[enemy.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _ENEMY_H_		// ���̃}�N������`����Ȃ�������
#define _ENEMY_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "object_x.h"

#include "data.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

// �G�̃N���X
class CEnemy : public CObjectX
{

public:

	typedef enum
	{
		MODEL_TYPE_ALIEN_000 = 0,			// �G�C���A��_000
		MODEL_TYPE_ALIEN_001,				// �G�C���A��_001
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	// ���f�����
	typedef struct
	{
		D3DXVECTOR3 size;	// �傫��
	}ModelData;

	CEnemy();
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL_TYPE modelType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetModel(void);
	void SetModel(int nModelNldx);

	static void SetModelData(int nNum, ModelData modelData);
	static ModelData GetModelData(int nNum);

	static CDataInt m_nDataModelNldx[MODEL_TYPE_MAX];	// ���f���̔ԍ�
	static ModelData m_modelData[MODEL_TYPE_MAX];		// ���f���̏��

	CDataD3DXVECTOR3 m_dataMove;	// �ړ���
	CDataInt m_nDataLife;			// �̗�

private:

	MODEL_TYPE m_model;	// ���g�̃��f��

};

#endif	// ��d�C���N���[�h�h�~�̏I��


//-===============================================
//-
//-	�X�J�C�{�b�N�X�����̃w�b�_�[[skybox.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SKYBOX_H_		// ���̃}�N������`����Ȃ�������
#define _SKYBOX_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

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
class CSkybox : public CObjectX
{

public:

	// ���f���̗񋓌^
	typedef enum
	{
		MODEL_SKYBOX_000 = 0,
		MODEL_MAX
	}MODEL;

	CSkybox(int nPriority = 3);
	~CSkybox();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(MODEL model,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSkybox * Create(MODEL model, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	int GetModel(void);
	void SetModel(int nModelNldx);

private:

	void InitSet(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static int m_nModelNldx[MODEL_MAX];		// ���f���̔ԍ�

	MODEL m_model;							// ���g�̃��f��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
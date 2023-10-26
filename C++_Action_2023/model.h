
//-===============================================
//=
//= �K�w�\���̃��f�������̃w�b�^�[[model.h]
//= Author Sakai Minato
//=
//-===============================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _MODEL_H_	// ���̃}�N������`����Ȃ�������
#define _MODEL_H_	// ��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

//-======================================
//-	�}�N����`
//-======================================

#define MODEL_PARTS_MAX	(32)	// ���f���p�[�c�̍ő吔
#define MODEL_NUM_MAX	(32)	// ���f���̍ő吔

//=======================================
//=	�N���X��`
//=======================================

// �K�w�\����X�t�@�C���I�u�W�F�N�g�̃N���X
class CModel
{
public:
	
	// ���f���̎��
	typedef enum
	{
		MODEL_TYPE_PLAYER_AONOA = 0,	// �v���C���[�i�A�I�m�A�j
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	// �i���f���j�p�[�c�̏��
	typedef struct
	{
		int nIndex;				// �p�[�c�̔ԍ�
		int nParent;			// �e�̔ԍ�
		char aFileName[256];	// �t�@�C���̖��O

		D3DXVECTOR3 pos;		// �ʒu���
		D3DXVECTOR3 rot;		// �������
	}Parts;

	// ���f���̏��
	typedef struct
	{
		Parts modelParts[MODEL_PARTS_MAX];		// ���f���p�[�c�̏��
		int nPartsNum;							// �p�[�c��
	}Model;

	// ���f���̒l���
	typedef struct
	{
		D3DXVECTOR3 pos;			// ���f���{�̂̈ʒu���
		D3DXVECTOR3 posMotion;	// ���[�V�����̈ʒu���
		D3DXVECTOR3 rot;			// ���f���{�̂̌������
		D3DXVECTOR3 rotMotion;	// ���[�V�����̈ʒu���
	}Data;

	CModel();
	~CModel();

	static HRESULT Load(void);

	HRESULT Init(MODEL_TYPE modelType, int nCount);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CModel * Create(MODEL_TYPE modelType, int nCount);

	void SetParent(CModel ** pModel, MODEL_TYPE modelType, int nCount);

	D3DXMATRIX GetMtxWorld(void);

	void SetData(CModel::Data data);
	Data GetData(void);

	static void SetFile(MODEL_TYPE modelType);
	static int GetPartsNum(MODEL_TYPE modelType);

	static int m_nModelNldx[MODEL_TYPE_MAX][MODEL_PARTS_MAX];	// ���f���̔ԍ�

private:

	Data m_data;							// ���f���̒l���

	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	CModel *m_pParent;						// �e���f���̃|�C���^

	MODEL_TYPE m_modelType;					// �����̃��f���̎��
	int m_nPartsNum;						// �����̃p�[�c�ԍ�

	static Model m_model[MODEL_NUM_MAX];	// ���f���̏��
};

#endif	// ��d�C���N���[�h�h�~�̏I��
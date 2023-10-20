

//-===============================================
//-
//-	�X�e�[�WCSV�����̃w�b�_�[[csv_stage.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _CSV_STAGE_H_		// ���̃}�N������`����Ȃ�������
#define _CSV_STAGE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

#define LINE_MAX		(64)					// ����̍ő吔
#define COLU_MAX		(16)					// �c��̍ő吔

#define CSV_DATA_MAX	(LINE_MAX * COLU_MAX)	// ���Əc�̍ő吔

#define ARRAY_SIZE		(8)						// �z��̃T�C�Y

//-======================================
//-	�O���錾
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CCsvStage
{

public:

	typedef enum
	{
		CSV_STAGE_000 = 0,	// �X�e�[�W_000�̃e�L�X�g
		CSV_STAGE_MAX,
	}CSV;

	typedef enum
	{
		TYPE_TEXT_NONE = 0,				// �Ȃ�
		TYPE_TEXT_WALL,					// ��
		TYPE_TEXT_BLOCK,				// �u���b�N
		TYPE_TEXT_TUTORIAL_000,			// �`���[�g���A��_000
		TYPE_TEXT_TUTORIAL_001,			// �`���[�g���A��_001
		TYPE_TEXT_TUTORIAL_002,			// �`���[�g���A��_002
		TYPE_TEXT_GOAL,					// �S�[��
		TYPE_TEXT_PLAYER,				// �v���C���[
		TYPE_TEXT_ENEMY,				// �G
		TYPE_TEXT_GIMMICK_SPEED,		// ���xUP�M�~�b�N
		TYPE_TEXT_MAX
	}TYPE_TEXT;

	typedef struct
	{
		bool bUse;				// �g�p�̗L��
		TYPE_TEXT type;			// ���
		D3DXVECTOR3 pos;		// �ʒu
	}Data;

	CCsvStage();
	~CCsvStage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CCsvStage *Create(void);

	void Load(CCsvStage::CSV csv);

	void SetObj(void);

private:

	void Divide(void);

	void SetObjData(TYPE_TEXT typeText, D3DXVECTOR3 pos);

	Data m_data[CSV_DATA_MAX];						// �f�[�^
	char m_acCsvData[CSV_DATA_MAX][ARRAY_SIZE];		// �����f�[�^
};

#endif	// ��d�C���N���[�h�h�~�̏I��

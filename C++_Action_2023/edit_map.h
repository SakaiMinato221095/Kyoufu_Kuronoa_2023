
//================================================
//=
//=	�}�b�v�G�f�B�b�g�̏����̃w�b�_�[[edit_map.h]
//= Author Sakai Minato
//=
//================================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _EDIT_MAP_H_		// ���̃}�N������`����Ȃ�������
#define _EDIT_MAP_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�O���錾
//-======================================

class CObjectX;
class CObjectBillboard;

class CObject;

//-======================================
//-	�N���X��`
//-======================================

class CEditMap
{

public:

	typedef enum
	{
		TYPE_BLOCK = 0,				// �u���b�N
		TYPE_GOAL,					// �S�[��
		TYPE_PLAYER,				// �v���C���[
		TYPE_ENEMY,					// �G
		TYPE_GIMMICK_SPEED,			// ���xUP�M�~�b�N
		TYPE_TEACH_MOVE,			// �ړ� 
		TYPE_TEACH_JUMP,			// �W�����v
		TYPE_TEACH_KAZEDAMA,		// ������
		TYPE_TEACH_DOUBLE_JUMP,		// ��i�W�����v
		TYPE_TEACH_SHOT,			// �V���b�g
		TYPE_MAX
	}TYPE;

	// �G�f�B�b�g���̃f�[�^
	typedef struct
	{
		CObjectX *pObjX;				// �G�f�B�b�g����X�t�@�C���I�u�W�F�N�g
		CObjectBillboard *pObjBill;		// �G�f�B�b�g���̃r���{�[�h�I�u�W�F�N�g
		TYPE type;						// ���݂̃^�C�v
		D3DXVECTOR3 pos;				// �ʒu
	}EditData;

	CEditMap();
	~CEditMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CEditMap *Create(void);

private:

	void InputObjMove(void);
	void InputSetObj(void);
	void InputChangeType(void);
	void InputSave(void);

	void SetEditObj(TYPE type);
	void SetAddType(void);
	void SetSubType(void);
	void SetObjMove(D3DXVECTOR3 move);

	void SetObj(void);

	EditData m_editData;		// �G�f�B�b�g���̃f�[�^
};

#endif	// ��d�C���N���[�h�h�~�̏I��


//-===============================================
//-
//-	�I�u�W�F�N�g�����̃w�b�_�[[object.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _OBJECT_H_		// ���̃}�N������`����Ȃ�������
#define _OBJECT_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�}�N����`
//-======================================

#define OBJECT_PRIORITY_MAX	(8)		// �D�揇�ʂ̐�
#define OBJECT_NUM_MAX		(8192)	// �I�u�W�F�N�g�̍ő吔

#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)					// ���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���_�t�H�[�}�b�g[3D](���_���W�E�@���E���_�t�H�[�}�b�g[3D]�E�e�N�X�`��)

//-======================================
//-	�\���̒�`
//-======================================

// ���_���̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W���i1,0f�ŌŒ�j
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

// ���_���[3D]�̍\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

//-======================================
//-	�O���錾
//-======================================

class CObject2d;
class CBgMulti;

//-======================================
//-	�N���X��`
//-======================================

class CObject
{

public:

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void IsUpdateStop(bool bIsUpdate);

	static CObject *GetObject(int nPriority,int nldx);

	virtual CObject2d *GetObject2d(void);
	virtual CBgMulti *GetBgMulti(void);

protected:

	void Release(void);

private:

	static void Debug(void);


	static CObject *m_apObject[OBJECT_PRIORITY_MAX][OBJECT_NUM_MAX];	// �I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;		// �I�u�W�F�N�g�̑���

	int m_nID;					// �������g�̃|�C���^�̔ԍ�
	int m_nPriority;			// �������g�̗D�揇�ʂ̔ԍ�

	bool m_bIsUpdate;			// �X�V�̗L��
};

#endif	// ��d�C���N���[�h�h�~�̏I��

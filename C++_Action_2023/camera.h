

//================================================
//=
//= �J�����̃w�b�^�[[camera.h]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	��d�C���N���[�h�h�~
//=======================================

#ifndef _CAMERA_H_	//���̃}�N������`����Ȃ�������
#define _CAMERA_H_	//��d�C���N���[�h�X�q�̃}�N�����`

//=======================================
//=	�C���N���[�h
//=======================================

//=======================================
//=	�N���X��`
//=======================================

// �J�����̃N���X
class CCamera
{

public:

	// �J�����̒l���
	typedef struct
	{
		D3DXVECTOR3 posV;			// ���_
		D3DXVECTOR3 posVDest;		// �ړI�̎��_

		D3DXVECTOR3 posR;			// �����_
		D3DXVECTOR3 posRDest;		// �ړI�̒����_

		D3DXVECTOR3 vecU;			// ������x�N�g��

		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 rotDest;		// �ړI�̌���

		float fLength;				// ����
	}Data;

	// �J�������[�h
	typedef enum
	{
		MODE_NORMAL = 0,	// �ʏ�
		MODE_FOLLOWING,		// �ǔ�
		MODE_EDIT,			// �G�f�B�b�g���[�h
		MODE_TITLE,			// �^�C�g��
		MODE_MAX
	}MODE;

	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void UpdateOperation(void);
	void UpdateFollowing(void);
	void UpdateEdit(void);
	void UpdateRot(void);
	void UpdateTitle(void);

	void SetCamera(void);

	void SetMode(CCamera::MODE mode);

	Data GetData(void);
private:
	
	D3DXMATRIX m_mtxProjectien;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X

	MODE m_mode;					// �J�����̃��[�h

	Data m_data;					// �J�����̒l�����i�[

};

#endif	// ��d�C���N���[�h�h�~�̏I��
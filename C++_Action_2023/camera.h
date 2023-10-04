

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

#include "data.h"

//=======================================
//=	�N���X��`
//=======================================

// �J�����̃N���X
class CCamera
{

public:

	// �J�������[�h
	typedef enum
	{
		MODE_NORMAL = 0,	// �ʏ�
		MODE_FOLLOWING,		// �ǔ�
		MODE_SHOP,			// �X
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
	void UpdateRot(void);
	void UpdateTitle(void);

	void SetCamera(void);

	void SetMode(CCamera::MODE mode);

	CDataD3DXVECTOR3 m_dataPosV;			// ���_
	CDataD3DXVECTOR3 m_dataPosVDest;		// �ړI�̎��_

	CDataD3DXVECTOR3 m_dataPosR;			// �����_
	CDataD3DXVECTOR3 m_dataPosRDest;		// �ړI�̒����_

	CDataD3DXVECTOR3 m_dataVecU;			// ������x�N�g��

	CDataD3DXVECTOR3 m_dataRot;				// ����
	CDataD3DXVECTOR3 m_dataRotDest;			// �ړI�̌���

	CDataFloat m_fDataLength;				// ����

private:
	
	void Collision(void);

	D3DXMATRIX m_mtxProjectien;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X

	MODE m_mode;					// �J�����̃��[�h

};

#endif	// ��d�C���N���[�h�h�~�̏I��
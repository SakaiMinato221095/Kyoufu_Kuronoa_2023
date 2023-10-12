
//-===============================================
//-
//-	�w�i�����̃w�b�_�[[bg.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _BG_H_		// ���̃}�N������`����Ȃ�������
#define _BG_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "main.h"

#include "object2d.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CBg : public CObject2d
{

public:

	// �w�i�̃e�N�X�`���񋓌^
	typedef enum
	{
		TEX_TITLE = 0,		// �^�C�g��
		TEX_RESULT,			// ���U���g
		TEX_MAX
	}TEX;

	// �e�N�X�`���̒��_�l���
	typedef struct
	{
		D3DXVECTOR2 m_texPos;		// �e�N�X�`���̈ʒu
		D3DXVECTOR2 m_texMove;		// �e�N�X�`���̈ړ���
	}VtxTexData;

	CBg(int nPriority = 0);
	~CBg();

	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(TEX tex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg * Create(TEX tex);

	void Set(
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR2 texPos = D3DXVECTOR2(0.0f,0.0f), 
		D3DXVECTOR2 texMove = D3DXVECTOR2(0.0f, 0.0f));

private:

	void SetVtx(void);

	void AddTexPos(void);

	void DestTexPos(void);

	VtxTexData m_vtxTexData;				// �e�N�X�`���̒��_�l���

	static int m_nTextureNldx[TEX_MAX];		// �e�N�X�`���ԍ�
};

#endif	// ��d�C���N���[�h�h�~�̏I��

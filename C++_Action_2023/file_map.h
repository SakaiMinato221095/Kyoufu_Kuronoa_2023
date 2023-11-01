
//-===============================================
//-
//-	�}�b�v�t�@�C�������̃w�b�_�[[file_map.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _FILE_MAP_H_		// ���̃}�N������`����Ȃ�������
#define _FILE_MAP_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include "edit_map.h"

//-======================================
//-	�}�N����`
//-======================================

#define MAP_OBJ_MAX	(1024)

//-======================================
//-	�O���錾
//-======================================

//-======================================
//-	�N���X��`
//-======================================

class CFileMap
{

public:

	typedef enum
	{
		TEXT_NORMAL = 0,	// �ʏ�}�b�v
		TEXT_TITLE,			// �^�C�g���}�b�v
		TEXT_MAX
	}TEXT;

	CFileMap();
	~CFileMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFileMap *Create(void);

	void Save(TEXT text);
	void Load(TEXT text);

	void SetMapObj(TEXT text);
	void ResetNumMax(TEXT text);

private:

	bool m_abDataUse[TEXT_MAX][MAP_OBJ_MAX];					// �}�b�v�f�[�^�̗L��
	CEditMap::EditData m_aMapData[TEXT_MAX][MAP_OBJ_MAX];		// �}�b�v�f�[�^
	int m_anNumMax[TEXT_MAX];									// �ő吔
};

#endif	// ��d�C���N���[�h�h�~�̏I��
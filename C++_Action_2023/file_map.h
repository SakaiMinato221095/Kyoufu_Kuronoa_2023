
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
		TEXT_MAP_NORMAL = 0,	// �ʏ�}�b�v
	}TEXT;

	CFileMap();
	~CFileMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFileMap *Create(void);

	void Save(void);
	void Load(void);

	bool SetObj(CEditMap::EditData editData);

private:

	void SetMapObj(CEditMap::EditData editData);

	CEditMap::EditData m_aMapData[MAP_OBJ_MAX];		// �}�b�v�f�[�^
	int m_nNumMax;									// �ő吔
};

#endif	// ��d�C���N���[�h�h�~�̏I��
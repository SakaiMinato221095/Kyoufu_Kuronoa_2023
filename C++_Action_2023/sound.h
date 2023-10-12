
//-===============================================
//-
//-	�T�E���h�����̃w�b�_�[[sound.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _SOUND_H_		// ���̃}�N������`����Ȃ�������
#define _SOUND_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

//-======================================
//-	�\���̒�`
//-======================================

typedef struct
{
	char *pFilename;	// �t�@�C����
	int nCntLoop;		// ���[�v�J�E���g
} SOUNDINFO;

//-======================================
//-	�N���X��`
//-======================================

class CSound
{

public:

	// �T�E���h���x��
	typedef enum
	{
		LABEL_BGM_TEST = 0,			// �e�X�gBGM
		LABEL_SE_TEST,				// �e�X�gSE
		LABEL_MAX,
	}LABEL;

	// �T�E���h�̏��
	SOUNDINFO g_aSoundInfo[LABEL_MAX] =
	{
		{ "Data/BGM/bgm000.wav",-1 },	// �e�X�gBGM
		{ "data/SE/Shot000.wav", 0 },	// �e�X�gSE
	};

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(LABEL label);
	void Stop(LABEL label);
	void Stop(void);

private:

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};

//-======================================
//- �v���g�^�C�v�錾
//-======================================

#endif	// ��d�C���N���[�h�h�~�̏I��

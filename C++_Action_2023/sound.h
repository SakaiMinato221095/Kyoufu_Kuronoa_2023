
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
		LABEL_BGM_TITLE = 0,	// �^�C�g��BGM
		LABEL_BGM_GAME,			// �Q�[��BGM
		LABEL_BGM_RESULT,		// ���U���gBGM
		
		LABEL_SE_JUMP,			// �W�����vSE
		LABEL_SE_DOUBLE_JUMP,	// ��i�W�����vSE
		LABEL_SE_KAZEDAMA,		// ������SE
		LABEL_SE_GET,			// �擾SE
		LABEL_SE_SHOT,			// ����SE
		LABEL_SE_JEWEL,			// ���SE
		LABEL_MAX,
	}LABEL;

	// �T�E���h�̏��
	SOUNDINFO g_aSoundInfo[LABEL_MAX] =
	{
		{ "Data/BGM/Brave.wav",-1 },			// �^�C�g��
		{ "Data/BGM/LIAR_PARADOX_2.wav",-1 },	// �Q�[��
		{ "Data/BGM/MusMus-BGM-116.wav",-1 },	// ���U���g
		{ "data/SE/jump.wav", 0 },				// �W�����v
		{ "data/SE/double_jump.wav", 0 },		// �_�u���W�����v
		{ "data/SE/kazedama.wav", 0 },			// ������
		{ "data/SE/get.wav", 0 },				// �擾
		{ "data/SE/shot.wav", 0 },				// ����
		{ "data/SE/jewel.wav", 0 },				// ���
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

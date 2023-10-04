
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
		LABEL_BGM_TITLE = 0,			// �^�C�g��
		LABEL_BGM_GAME,					// �Q�[��
		LABEL_BGM_CHAOS_CHARGE_SHOT,	// �ł̍U��
		LABEL_SE_SHOT_000,				// �V���b�g
		LABEL_SE_NOR_CHARGE_SHOT,		// �`���[�W�V���b�g
		LABEL_SE_DAMAGE_ENEMY_000,		// �G�̃_���[�W��000
		LABEL_SE_DAMAGE_ENEMY_001,		// �G�̃_���[�W��001
		LABEL_SE_DAMAGE_PLAYER,			// �v���C���[�̃_���[�W��
		LABEL_SE_DIED_ENEMY_000,		// �G�̎��S��000
		LABEL_SE_TLEPORT_000,			// �e���|
		LABEL_SE_EAT_000,				// �H�ׂ鉹000
		LABEL_MAX,
	}LABEL;

	// �T�E���h�̏��
	SOUNDINFO g_aSoundInfo[LABEL_MAX] =
	{
		{ "Data/BGM/Raijin.wav",-1 },				// �^�C�g��
		{ "Data/BGM/arcman.wav",-1 },				// �Q�[��
		{ "Data/BGM/ChaosChargeShot000.wav",-1 },	// �ł̍U��
		{ "data/SE/Shot000.wav", 0 },				// �V���b�g000
		{ "data/SE/NorChargeShot000.wav", 0 },		// �ʏ�`���[�W�U��
		{ "data/SE/DamageEnemy000.wav", 0 },		// �G�̃_���[�W��
		{ "data/SE/DamageEnemy001.wav", 0 },		// �G�̃_���[�W��
		{ "data/SE/DamagePlayer.wav", 0 },			// �v���C���[�̃_���[�W��
		{ "data/SE/DiedEnemy000.wav", 0 },			// �G�̃_���[�W��
		{ "data/SE/Teleport.wav", 0 },				// �e���|
		{ "data/SE/Eat000.wav", 0 },				// �H�ׂ鉹000
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

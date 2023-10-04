
//-===============================================
//-
//-	�T�E���h����[sound.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "sound.h"

//-======================================
//-	�}�N����`
//-======================================

//-======================================
//-	�ÓI�ϐ��錾
//-======================================

//-------------------------------------
//-	�R���X�g���N�^
//-------------------------------------
CSound::CSound()
{
	// �l���N���A
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;

	for (int nCount = 0; nCount < LABEL_MAX; nCount++)
	{
		m_apSourceVoice[nCount] = NULL;
		m_apDataAudio[nCount] = NULL;
		m_aSizeAudio[nCount] = NULL;
	}

}

//-------------------------------------
//-	�f�X�g���N�^
//-------------------------------------
CSound::~CSound()
{
}

//-------------------------------------
//- �T�E���h�̏���������
//-------------------------------------
HRESULT CSound::Init(HWND hWnd)
{
	// �|�C���^�錾
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);

	// XAudio2�I�u�W�F�N�g���������̗L���𔻒�
	if (FAILED(hr))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);

	// �}�X�^�[�{�C�X���������̗L���𔻒�
	if (FAILED(hr))
	{
		// ���s���b�Z�[�W
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// XAudio2�I�u�W�F�N�g�̗L���𔻒�
		if (m_pXAudio2 != NULL)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		// �|�C���^��錾
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(g_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		// �T�E���h�f�[�^�t�@�C�����������̗L���𔻒�
		if (hFile == INVALID_HANDLE_VALUE)
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);

			// �G���[��Ԃ�
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// �t�@�C���|�C���^�̐擪�𔻒�
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�

			// ���s���b�Z�[�W
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);

			// �G���[��Ԃ�
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

		// WAVE�t�@�C���̃`�F�b�N�̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �t�@�C���̏�����
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);

		// �t�@�C�����̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// 
		if (dwFiletype != 'EVAW')
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);

		// �t�@�[�}�b�g�̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �`�����N�f�[�^�̓ǂݍ���
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

		// �`�����N�f�[�^�̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);

		// �I�[�f�B�I�f�[�^�̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^��ݒ�
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);

		// �I�[�f�B�I�̃`�����N�f�[�^�̎擾
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);

		// �I�[�f�B�I�f�[�^�̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �\�[�X�{�C�X�̐���
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// �\�[�X�{�C�X�̗L���𔻒�
		if (FAILED(hr))
		{
			// ���s���b�Z�[�W
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// ���s��Ԃ�
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = g_aSoundInfo[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �T�E���h�̏I������
//-------------------------------------
void CSound::Uninit(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		// �\�[�X�{�C�X�̗L���𔻒�
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	// XAudio2�I�u�W�F�N�g�̗L���𔻒�
	if (m_pXAudio2 != NULL)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//-------------------------------------
//- �T�E���h�̃Z�O�����g�Đ�(�Đ����Ȃ��~)
//-------------------------------------
HRESULT CSound::Play(LABEL label)
{
	// �ϐ��錾
	XAUDIO2_VOICE_STATE xa2state;	// �I�[�f�B�I�̏�Ԃ��i�[
	XAUDIO2_BUFFER buffer;			// �I�[�f�B�I�o�b�t�@

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = g_aSoundInfo[label].nCntLoop;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);

	// ��Ԃ̔���
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �T�E���h�̃Z�O�����g��~(���x���w��)
//-------------------------------------
void CSound::Stop(LABEL label)
{
	// �ϐ��錾
	XAUDIO2_VOICE_STATE xa2state;	// �I�[�f�B�I�̏�Ԃ��i�[

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);

	// ��Ԃ̔���
	if (xa2state.BuffersQueued != 0)
	{// �Đ���
	 
		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//-------------------------------------
//- �T�E���h�̃Z�O�����g��~(�S��)
//-------------------------------------
void CSound::Stop(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < LABEL_MAX; nCntSound++)
	{
		// ��Ԃ̔���
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//-------------------------------------
//- �T�E���h�̃`�����N�̃`�F�b�N
//-------------------------------------
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD * pChunkSize, DWORD * pChunkDataPosition)
{
	// �ϐ��錾
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	// �t�@�C���|�C���^�̐擪�𔻒�
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�

		// ���s��Ԃ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	// �t�@�C���|�C���^�̗L���𔻒�
	while (hr == S_OK)
	{
		// �`�����N�^�C�v�̗L���𔻒�
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���

			// ���s��Ԃ�
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		// �`�����N�T�C�Y�̗L���𔻒�
		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���

			// ���s��Ԃ�
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		// �`�����N�^�C�v�̔���
		switch (dwChunkType)
		{

		case 'FFIR':

			// �`�����N�T�C�Y����
			dwRIFFDataSize = dwChunkDataSize;

			// �`�����N�T�C�Y��4����
			dwChunkDataSize = 4;

			// �t�@�C���^�C�v�̗L���𔻒�
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���

				// ���s��Ԃ�
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default:

			// �t�@�C���|�C���^�̔���
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�

				// ���s��Ԃ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		//
		dwOffset += sizeof(DWORD) * 2;

		//
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			// ������Ԃ�
			return S_OK;
		}

		//
		dwOffset += dwChunkDataSize;

		if (dwBytesRead >= dwRIFFDataSize)
		{
			// ���s��Ԃ�
			return S_FALSE;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//- �`�����N�f�[�^�̓ǂݍ���
//-------------------------------------
HRESULT CSound::ReadChunkData(HANDLE hFile, void * pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	// �ϐ��錾
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�

		// ���s��Ԃ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���

		// ���s��Ԃ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}


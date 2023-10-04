
//-===============================================
//-
//-	�[�j�Z���V��a��
//-	��{����[main.cpp]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	�C���N���[�h
//-======================================

#include "main.h"

#include "manager.h"

//-======================================
//-	���C�u�����̃����N
//-======================================

#pragma comment(lib,"d3d9.lib")			// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")		// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")		// DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v

#pragma comment(lib,"winmm.lib")		// �V�X�e���������擾

#pragma comment(lib,"dinput8.lib")		// ���͏����ɕK�v
#pragma comment (lib, "xinput.lib")		// XINPUT

//-======================================
//-	�}�N����`
//-======================================

#define CLASS_NAME			"Window class"			// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME			"�[�j�Z���V"			// �E�B���h�E�̖��O
#define ID_BUTTON_FINISH	(101)					// �I���{�^����ID

//-======================================
//-	�v���g�^�C�v�錾
//-======================================

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-======================================
//-	�O���[�o���ϐ�
//-======================================

int g_nCountFPS = 0;					//FPS�J�E���^	

//-====================================
//-	���C���֐�
//-====================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLime, int nCmdShow)
{
	// �I�����Ƀ��������[�N���o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,							// �E�B���h�E�̃X�^�C��
		WindowProc,							// �E�B���h�E�v���V�[�W��
		0,									// 0�ɂ���i�ʏ�͂��悤���Ȃ��j
		0,									// 0�ɂ���i�ʏ�͂��悤���Ȃ��j
		hInstance,							// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		// �^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),			// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			// �N���C�A���g�̈�̔w�i�F
		NULL,								// ���j���[�o�[
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),		// �t�@�C���A�C�R��
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		// ��ʃT�C�Y�̍\����

	HWND hWnd;	// �E�B���h���n���h���i�F�ʎq�j
	MSG msg;	// ���b�Z�[�W���i�[����ϐ�

	DWORD dwCurrentTime = 0;		//���ݎ���
	DWORD dwExecLastTime = 0;		//�Ō�ɏ�����������
	DWORD dwFrameCount = 0;			//�t���[���J�E���g
	DWORD dwFPSLastTime = 0;		//�Ō��FPS���v����������
	dwFrameCount = 0;				//�t���[���J�E���g��������
	dwFPSLastTime = timeGetTime();	//���ݎ������擾

	//�����̏�����
	srand((unsigned int)time(0));

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,		// �g���E�B���h�E�X�^�C��
		CLASS_NAME,					// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,				// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,				// �E�B���h�E�̍���Y���W
		(rect.right - rect.left),	// �E�B���h�E�̕�
		(rect.bottom - rect.top),	// �E�B���h�E�̍���
		NULL,						// �e�E�B���h�E�̃n���h��
		NULL,						// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					// �C���X�^���X�n���h��
		NULL);						// �E�B���h�E�쐬�f�[�^


	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		// �E�B���h�E�\����Ԃ�ݒ�
	UpdateWindow(hWnd);				// �N���C�A���g�̈���X�V

	// �}�l�[�W���̃|�C���^��錾
	CManager *pManager = NULL;

	// �}�l�[�W���𐶐�
	pManager = DBG_NEW CManager;

	// �}�l�[�W���̏�����
	if (pManager != NULL)
	{
		if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
		{
			return E_FAIL;
		}
	}

	// ���b�Z�[�W�����[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// windos�̏���

			if (msg.message == WM_QUIT)
			{// WM_���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{
				// ���b�Z�[�W��ݒ�
				TranslateMessage(&msg);	// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���

			// ���ݎ������擾
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��

			 // FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPS���v������������ۑ�
				dwFPSLastTime = dwCurrentTime;

				// �t���[���J�E���g�����Z
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60����1�b�o��

				// �����J�n�̎���[���ݎ���]��ۑ�
				dwExecLastTime = dwCurrentTime;

				if (pManager != NULL)
				{
					// �����_���[�̍X�V����
					pManager->Update();

					// �����_���[�̕`�揈��
					pManager->Draw();
				}

				// �t���[���J�E���g�����Z
				dwFrameCount++;
			}
		}
	}

	// �}�l�[�W���̏I������
	pManager->Uninit();

	// �����_���[�̔j��
	if (pManager != NULL)
	{
		// �����_���[�̏I������
		pManager->Uninit();

		// �����_���[�̊J��
		delete pManager;
		pManager = NULL;
	}

	_CrtDumpMemoryLeaks();


	//����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	// ���^�[��
	return(int)msg.wParam;
}

//-====================================
//-	�E�B���h�E�v���V�[�W��
//-====================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �ϐ��錾
	int nID;					// �Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:	// �E�B���h�E�j���̃��b�Z�[�W

		// WM_QUIZ���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		
		break;

	case WM_KEYDOWN:	// �L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				// �E�B���h�E��j������iWN_DESTROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}

			break;
		}
		break;

	case WM_COMMAND:	// �R�}���h���s���b�Z�[�W

		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{// �I���{�^���������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				// �E�B���h�E��j������iWN_DESTROY���b�Z�[�W�𑗂�j
				DestroyWindow(hWnd);
			}
		}

		break;

	case WM_LBUTTONDOWN:	// �}�E�X�E�N���b�N�̃��b�Z�[�W

		// �ΏۃE�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);

		break;

	case WM_CLOSE:	// ����{�^���̃��b�Z�[�W

		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			// �E�B���h�E��j������iWN_DESTROY���b�Z�[�W�𑗂�j
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;	// 0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// ���݂̏������J��Ԃ�
}

//-===============================================
//-
//-	�̃w�b�_�[[precompile.h]
//- Author Sakai Minato
//-
//-===============================================

//-======================================
//-	��d�C���N���[�h�h�~
//-======================================

#ifndef _PRECOMPILE_H_		// ���̃}�N������`����Ȃ�������
#define _PRECOMPILE_H_		// ��d�C���N���[�h�X�q�̃}�N�����`

//-======================================
//-	�C���N���[�h
//-======================================

#include <windows.h>
#include <time.h>

#include <stdio.h>

#include <d3dx9.h>						// �`�揈���ɕK�v

#define DIRECTINPUT_VERSION (0x0800)	// �r���h���̌x���Ώ��p�̃}�N��

#include <dinput.h>						// ���͏����ɕK�v
#include <Xinput.h>						// XINPUT

#include <xaudio2.h>					// �T�E���h�����ɕK�v

// ���������[�N�o�͗p�}�N��
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#endif	// ��d�C���N���[�h�h�~�̏I��


// UserApplication.h : UserApplication �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

//#include "resource.h"       // ���C�� �V���{��


// CUserApplicationApp:
// ���̃N���X�̎����ɂ��ẮAUserApplication.cpp ���Q�Ƃ��Ă��������B
//

class CUserApplicationApp : public CWinAppEx
{
public:
	CUserApplicationApp();

	lnq::Application*	m_app;


	// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// ����
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	//virtual void PreLoadState();
	//virtual void LoadCustomState();
	//virtual void SaveCustomState();

	//afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

//extern CUserApplicationApp theApp;

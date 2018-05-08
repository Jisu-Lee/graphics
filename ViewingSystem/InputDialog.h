#pragma once
#include "afxwin.h"
#include "ViewingSystem.h"
#include "InputDialog.h"
#include "afxdialogex.h"
#include "ViewingSystemDoc.h"
#include "ViewingSystemView.h"
#include "Matrix.h"
#include "MainFrm.h"


// InputDialog dialog

class InputDialog : public CDialog
{
	DECLARE_DYNAMIC(InputDialog)

public:
	InputDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~InputDialog();

// Dialog Data
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit m_eyeX;
	CEdit m_eyeY;
	CEdit m_eyeZ;
	CEdit m_lookAtX;
	CEdit m_lookAtY;
	CEdit m_lookAtZ;
	CEdit m_upX;
	CEdit m_upY;
	CEdit m_upZ;
	virtual BOOL OnInitDialog();
};

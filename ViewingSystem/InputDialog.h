#pragma once


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
};

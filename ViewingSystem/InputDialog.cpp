// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ViewingSystem.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// InputDialog dialog

IMPLEMENT_DYNAMIC(InputDialog, CDialog)

InputDialog::InputDialog(CWnd* pParent /*=NULL*/)
	: CDialog(InputDialog::IDD, pParent)
{

}

InputDialog::~InputDialog()
{
}

void InputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputDialog, CDialog)
END_MESSAGE_MAP()


// InputDialog message handlers

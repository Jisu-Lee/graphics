// InputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ViewingSystem.h"
#include "InputDialog.h"
#include "afxdialogex.h"
#include "ViewingSystemDoc.h"
#include "ViewingSystemView.h"
#include "Matrix.h"
#include "MainFrm.h"


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
	DDX_Control(pDX, IDC_EDIT1, m_eyeX);
	DDX_Control(pDX, IDC_EDIT2, m_eyeY);
	DDX_Control(pDX, IDC_EDIT3, m_eyeZ);
	DDX_Control(pDX, IDC_EDIT4, m_lookAtX);
	DDX_Control(pDX, IDC_EDIT5, m_lookAtY);
	DDX_Control(pDX, IDC_EDIT6, m_lookAtZ);
	DDX_Control(pDX, IDC_EDIT7, m_upX);
	DDX_Control(pDX, IDC_EDIT8, m_upY);
	DDX_Control(pDX, IDC_EDIT9, m_upZ);
}


BEGIN_MESSAGE_MAP(InputDialog, CDialog)
	ON_BN_CLICKED(IDOK, &InputDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// InputDialog message handlers


void InputDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CMainFrame*	pWin = (CMainFrame*)AfxGetMainWnd();
	CViewingSystemView* pView = (CViewingSystemView*)pWin->GetActiveView();
	CViewingSystemDoc* pDoc = (CViewingSystemDoc*)pView->GetDocument();
	CString eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ;
	GetDlgItemText(IDC_EDIT1, eyeX);
	GetDlgItemText(IDC_EDIT2, eyeY);
	GetDlgItemText(IDC_EDIT3, eyeZ);
	GetDlgItemText(IDC_EDIT4, lookAtX);
	GetDlgItemText(IDC_EDIT5, lookAtY);
	GetDlgItemText(IDC_EDIT6, lookAtZ);
	GetDlgItemText(IDC_EDIT7, upX);
	GetDlgItemText(IDC_EDIT8, upY);
	GetDlgItemText(IDC_EDIT9, upZ);
	Vertex eye = Vertex(atof(eyeX), atof(eyeY), atof(eyeZ));
	Vertex lookAt = Vertex(atof(lookAtX), atof(lookAtY), atof(lookAtZ));
	Vertex up = Vertex(atof(upX), atof(upY), atof(upZ));
	pDoc->updateEye(eye);
	pDoc->updateLookAt(lookAt);
	pDoc->updateUp(up);
	pDoc->Rendering();
	pView->Invalidate();
	CDialog::OnOK();
}


BOOL InputDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CMainFrame*	pWin = (CMainFrame*)AfxGetMainWnd();
	CViewingSystemView* pView = (CViewingSystemView*)pWin->GetActiveView();
	CViewingSystemDoc* pDoc = (CViewingSystemDoc*)pView->GetDocument();
	CString eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ;
	eyeX.Format(_T("%f"), pDoc->getEye().x);
	eyeY.Format(_T("%f"), pDoc->getEye().y);
	eyeZ.Format(_T("%f"), pDoc->getEye().z);
	lookAtX.Format(_T("%f"), pDoc->getLookAt().x);
	lookAtY.Format(_T("%f"), pDoc->getLookAt().y);
	lookAtZ.Format(_T("%f"), pDoc->getLookAt().z);
	upX.Format(_T("%f"), pDoc->getUp().x);
	upY.Format(_T("%f"), pDoc->getUp().y);
	upZ.Format(_T("%f"), pDoc->getUp().z);
	SetDlgItemText(IDC_EDIT1, eyeX);
	SetDlgItemText(IDC_EDIT2, eyeY);
	SetDlgItemText(IDC_EDIT3, eyeZ);
	SetDlgItemText(IDC_EDIT4, lookAtX);
	SetDlgItemText(IDC_EDIT5, lookAtY);
	SetDlgItemText(IDC_EDIT6, lookAtZ);
	SetDlgItemText(IDC_EDIT7, upX);
	SetDlgItemText(IDC_EDIT8, upY);
	SetDlgItemText(IDC_EDIT9, upZ);
	/*
	m_eyeX.SetWindowText(eyeX);
	m_eyeY.SetWindowText(eyeY);
	m_eyeZ.SetWindowText(eyeZ);
	m_lookAtX.SetWindowText(lookAtX);
	m_lookAtY.SetWindowText(lookAtY);
	m_lookAtZ.SetWindowText(lookAtZ);
	m_upX.SetWindowText(upX);
	m_upY.SetWindowText(upY);
	m_upZ.SetWindowText(upZ);
*/
	pDoc->Rendering();
	pView->Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

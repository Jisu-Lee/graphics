// ViewingSystemView.cpp : implementation of the CViewingSystemView class
//

#include "stdafx.h"
#include "ViewingSystem.h"

#include "ViewingSystemDoc.h"
#include "ViewingSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView

IMPLEMENT_DYNCREATE(CViewingSystemView, CView)

BEGIN_MESSAGE_MAP(CViewingSystemView, CView)
	//{{AFX_MSG_MAP(CViewingSystemView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_PARALLEL, OnParallel)
	ON_COMMAND(ID_PERSPECTIVE, OnPerspective)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView construction/destruction

CViewingSystemView::CViewingSystemView()
{
	// TODO: add construction code here

	m_initState = true;

	rButtonDownPoint = CPoint(0, 0);
	isRightButtonDown = false;
}

CViewingSystemView::~CViewingSystemView()
{
}

BOOL CViewingSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView drawing

void CViewingSystemView::OnDraw(CDC* pDC)
{
	CViewingSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	if (m_initState)
	{
		GetClientRect(&pDoc->win);

		CBitmap bmp;
		bmp.CreateBitmap(pDoc->win.Width(), pDoc->win.Width(), 1, 0x20, NULL);

		pDoc->memdc.CreateCompatibleDC(pDC);
		pDoc->memdc.SelectObject(bmp);
		pDoc->memdc.ExtFloodFill(0, 0, RGB(255, 255, 255), FLOODFILLBORDER);

		pDoc->Rendering();
		m_initState = false;
	}

	pDC->BitBlt(pDoc->win.left, pDoc->win.top, pDoc->win.Width(), pDoc->win.Height(), &pDoc->memdc, 0, 0, SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView printing

BOOL CViewingSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CViewingSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CViewingSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView diagnostics

#ifdef _DEBUG
void CViewingSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CViewingSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CViewingSystemDoc* CViewingSystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewingSystemDoc)));
	return (CViewingSystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemView message handlers

void CViewingSystemView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CViewingSystemDoc* pDoc = GetDocument();

	char szFilter[] = "Image (*.dat) |*.dat| All Files(*.*)|*.*||";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	if (dlg.DoModal() == IDOK)
		pDoc->FileOpen(dlg.GetPathName());

	Invalidate();
}

void CViewingSystemView::OnParallel() 
{
	// TODO: Add your command handler code here
	CViewingSystemDoc* pDoc = GetDocument();
	pDoc->updateViewingMode(PARALLEL);
	pDoc->Rendering();
	Invalidate();
	// 렌더링 모드 변경 구현 필요
}

void CViewingSystemView::OnPerspective() 
{
	// TODO: Add your command handler code here
	CViewingSystemDoc* pDoc = GetDocument();
	pDoc->updateViewingMode(PERSPECTIVE);
	pDoc->Rendering();
	Invalidate();
	// 렌더링 모드 변경 구현 필요
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 시점 변경에 대한 구현이 필요
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define ANGLE_HOP 0.8
#define DIST_HOP 5
#define SCALE_RATIO 0.2

void CViewingSystemView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CViewingSystemDoc* pDoc = GetDocument();
	// TODO: Add your message handler code here and/or call default
	switch (nChar){
	case VK_UP : //Arrow up - scaling plus
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->scale(1+SCALE_RATIO);
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case VK_DOWN : //Arrow down - scaling minus
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->scale(1-SCALE_RATIO);
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case 0x51 :	//Q key	- translation X plus
		pDoc->X_trans(DIST_HOP);
		pDoc->updateTransXSum(DIST_HOP);
		break;
	case 0x57 : //W key - translation X minus
		pDoc->X_trans(-DIST_HOP);
		pDoc->updateTransXSum(-DIST_HOP);
		break;
	case 0x41 : //A key - translation Y plus
		pDoc->Y_trans(DIST_HOP);
		pDoc->updateTransYSum(DIST_HOP);
		break;
	case 0x53 : //S key - translation Y minus
		pDoc->Y_trans(-DIST_HOP);
		pDoc->updateTransYSum(-DIST_HOP);
		break;
	case 0x5A : //Z key - translation Z plus
		pDoc->Z_trans(DIST_HOP);
		pDoc->updateTransZSum(DIST_HOP);
		break;
	case 0x58 : //X key - translation Z minus
		pDoc->Z_trans(-DIST_HOP);
		pDoc->updateTransZSum(-DIST_HOP);
		break;
	case 0x4F :	//O key	- rotation X clock
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->X_rotate(ANGLE_HOP);	
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case 0x50 : //P key - rotation X counterclock
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->X_rotate(-ANGLE_HOP);	
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case 0x4B : //K key - rotation Y clock
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->Y_rotate(ANGLE_HOP);	
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case 0x4C : //L key - rotation Y counterclock
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->Y_rotate(-ANGLE_HOP);	
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case 0x4E : //N key - rotation Z clock
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->Z_rotate(ANGLE_HOP);	
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	case 0x4D : //M key - rotation Z counterclock
		pDoc->X_trans(-pDoc->getTransXSum());
		pDoc->Y_trans(-pDoc->getTransYSum());
		pDoc->Z_trans(-pDoc->getTransZSum());
		pDoc->Z_rotate(-ANGLE_HOP);	
		pDoc->X_trans(pDoc->getTransXSum());
		pDoc->Y_trans(pDoc->getTransYSum());
		pDoc->Z_trans(pDoc->getTransZSum());
		break;
	}

	pDoc->Rendering();
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



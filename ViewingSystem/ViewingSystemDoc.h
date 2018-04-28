// ViewingSystemDoc.h : interface of the CViewingSystemDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWINGSYSTEMDOC_H__C9D36D04_6DB8_4D69_8C1A_1DD2C175A75B__INCLUDED_)
#define AFX_VIEWINGSYSTEMDOC_H__C9D36D04_6DB8_4D69_8C1A_1DD2C175A75B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Matrix.h"

#define		PARALLEL	0
#define		PERSPECTIVE	1


class CViewingSystemDoc : public CDocument
{
protected: // create from serialization only
	CViewingSystemDoc();
	DECLARE_DYNCREATE(CViewingSystemDoc)

// Attributes
public:
	Vertex *m_vertices;		// Object의 Vertex 정보를 저장하는 배열
	Vertex *m_vertices_origin;
	Vertex *dist;
	Face *m_faces;			// Object의 Face 정보를 저장하는 배열

	int m_numberOfVertices;	// Object의 총 Vertex 갯수
	int m_numberOfFaces;	// Object의 총 Face 갯수

	double rotate_x_sum;
	double rotate_y_sum;
	double rotate_z_sum;
	double trans_x_sum;
	double trans_y_sum;
	double trans_z_sum;

	Vertex m_eye;			// 시점
	Vertex m_lookAt;		// 바라보는곳
	Vertex m_up;			// 위쪽의 방향

	CRect win;

	CDC memdc;				// 그림을 그리는 곳 (DC)

	int m_viewingMode;		// Parallel, Perspective 구분을 위한 변후


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewingSystemDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//added by jisu
	void X_rotate(double angle);
	void Y_rotate(double angle);
	void Z_rotate(double angle);
	void X_trans(double dist);
	void Y_trans(double dist);
	void Z_trans(double dist);

	void CViewingSystemDoc::initializeVertices();

	double CViewingSystemDoc::getTransXSum();
	double CViewingSystemDoc::getTransYSum();
	double CViewingSystemDoc::getTransZSum();
	double CViewingSystemDoc::updateTransXSum(double dist);
	double CViewingSystemDoc::updateTransYSum(double dist);
	double CViewingSystemDoc::updateTransZSum(double dist);
	void CViewingSystemDoc::scale(double amount);
	
	void CViewingSystemDoc::updateViewingMode(int v);

	Vertex CrossProduct(Vertex a, Vertex b);	// 두 Vertex의 외적을 구하는 함수
	double DotProduct(Vertex a, Vertex b);		// 두 Vertex의 내적을 구하는 함수
	Vertex Normalization(Vertex vertex);		// Vertex를 정규화 시키는 함수
	void Rendering();							// 현재 모델을 그리는 함수
	void FileOpen(CString filename);			// 파일의 Object정보를 읽어오는 함수
	virtual ~CViewingSystemDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CViewingSystemDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWINGSYSTEMDOC_H__C9D36D04_6DB8_4D69_8C1A_1DD2C175A75B__INCLUDED_)

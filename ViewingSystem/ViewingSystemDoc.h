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
	Vertex *m_vertices;		// Object�� Vertex ������ �����ϴ� �迭
	Vertex *m_vertices_origin;
	Vertex *dist;
	Face *m_faces;			// Object�� Face ������ �����ϴ� �迭

	int m_numberOfVertices;	// Object�� �� Vertex ����
	int m_numberOfFaces;	// Object�� �� Face ����

	double rotate_x_sum;
	double rotate_y_sum;
	double rotate_z_sum;
	double trans_x_sum;
	double trans_y_sum;
	double trans_z_sum;

	Vertex m_eye;			// ����
	Vertex m_lookAt;		// �ٶ󺸴°�
	Vertex m_up;			// ������ ����

	CRect win;

	CDC memdc;				// �׸��� �׸��� �� (DC)

	int m_viewingMode;		// Parallel, Perspective ������ ���� ����


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

	Vertex CrossProduct(Vertex a, Vertex b);	// �� Vertex�� ������ ���ϴ� �Լ�
	double DotProduct(Vertex a, Vertex b);		// �� Vertex�� ������ ���ϴ� �Լ�
	Vertex Normalization(Vertex vertex);		// Vertex�� ����ȭ ��Ű�� �Լ�
	void Rendering();							// ���� ���� �׸��� �Լ�
	void FileOpen(CString filename);			// ������ Object������ �о���� �Լ�
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

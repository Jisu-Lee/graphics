// ViewingSystemDoc.cpp : implementation of the CViewingSystemDoc class
//

#include "stdafx.h"
#include "ViewingSystem.h"

#include <fstream>		// Visual studio 2003, 2005
using namespace std;		// Visual studio 2003, 2005

#include <cmath>

#include "ViewingSystemDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PI 3.14159265

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc

IMPLEMENT_DYNCREATE(CViewingSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CViewingSystemDoc, CDocument)
	//{{AFX_MSG_MAP(CViewingSystemDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc construction/destruction

//js - variable intialization
CViewingSystemDoc::CViewingSystemDoc() 
{
	trans_x_sum = 0.0;
	trans_y_sum = 0.0;
	trans_z_sum = 0.0;

	m_vertices = 0;
	m_vertices_origin = 0;
	m_faces = 0;

	m_numberOfVertices = 0;
	m_numberOfFaces = 0;

	m_viewingMode = PARALLEL;

	m_eye = Vertex(0.0, 0.0, 500.0);
	m_lookAt = Vertex(0.0, 0.0, 0.0);
	m_up = Vertex(0.0, 1.0, 0.0);
}

CViewingSystemDoc::~CViewingSystemDoc()
{
}

Vertex CViewingSystemDoc::getEye(){
	return m_eye;
}
Vertex CViewingSystemDoc::getLookAt(){
	return m_lookAt;
}
Vertex CViewingSystemDoc::getUp(){
	return m_up;
}

void CViewingSystemDoc::updateEye(Vertex v){
	m_eye = v;
}

void CViewingSystemDoc::updateLookAt(Vertex v){
	m_lookAt = v;
}

void CViewingSystemDoc::updateUp(Vertex v){
	m_up = v;
}
void CViewingSystemDoc::updateViewingMode(int v){
	m_viewingMode = v;
}

void CViewingSystemDoc::initializeVertices(){
	n = Normalization(m_lookAt - m_eye);
	double a = DotProduct(m_up, n);
	Vertex v_temp = m_up - n*a;
	v = Normalization(v_temp);
	w = CrossProduct(n, v);
}

double CViewingSystemDoc::updateTransXSum(double dist){
	trans_x_sum += dist;
	return trans_x_sum;
}

double CViewingSystemDoc::getTransXSum(){
	return trans_x_sum;
}

double CViewingSystemDoc::updateTransYSum(double dist){
	trans_y_sum += dist;
	return trans_y_sum;
}

double CViewingSystemDoc::getTransYSum(){
	return trans_y_sum;
}

double CViewingSystemDoc::updateTransZSum(double dist){
	trans_z_sum += dist;
	return trans_z_sum;
}

double CViewingSystemDoc::getTransZSum(){
	return trans_z_sum;
}

//Xrotate
void CViewingSystemDoc::X_rotate(double angle){
	Matrix xr;
	xr.m[5] = cos(angle*PI / 180);
	xr.m[6] = -sin(angle*PI / 180);
	xr.m[9] = sin(angle*PI / 180);
	xr.m[10] = cos(angle*PI / 180);

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = xr*(m_vertices[i]);
	}
}

//Yrotate
void CViewingSystemDoc::Y_rotate(double angle){
	Matrix yr;
	yr.m[0] = cos(angle*PI / 180);
	yr.m[2] = sin(angle*PI / 180);
	yr.m[8] = -sin(angle*PI / 180);
	yr.m[10] = cos(angle*PI / 180);

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = yr*(m_vertices[i]);
	}
}

//Zrotate
void CViewingSystemDoc::Z_rotate(double angle){
	Matrix zr;
	zr.m[0] = cos(angle*PI / 180);
	zr.m[1] = -sin(angle*PI / 180);
	zr.m[4] = sin(angle*PI / 180);
	zr.m[5] = cos(angle*PI / 180);

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = zr*(m_vertices[i]);
	}
}

//Xtrans
void CViewingSystemDoc::X_trans(double dist){
	Matrix xt;
	xt.m[3] = dist;

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = xt*(m_vertices[i]);
	}
}

//Ytrans
void CViewingSystemDoc::Y_trans(double dist){
	Matrix yt;
	yt.m[7] = dist;

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = yt*(m_vertices[i]);
	}
}

//Ztrans
void CViewingSystemDoc::Z_trans(double dist){
	Matrix zt;
	zt.m[11] = dist;

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = zt*(m_vertices[i]);
	}
}

//Scaling
void CViewingSystemDoc::scale(double amount){
	Matrix s;
	s.m[0] = amount;
	s.m[5] = amount;
	s.m[10] = amount;

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = s*(m_vertices[i]);
	}
}

void CViewingSystemDoc::initializeMatrix(){
	R_1.m[0] = w.x;
	R_1.m[1] = w.y;
	R_1.m[2] = w.z;
	R_1.m[3] = 0;
	R_1.m[4] = v.x;
	R_1.m[5] = v.y;
	R_1.m[6] = v.z;
	R_1.m[7] = 0;
	R_1.m[8] = -n.x;
	R_1.m[9] = -n.y;
	R_1.m[10] = -n.z;
	R_1.m[11] = 0;
	R_1.m[12] = 0;
	R_1.m[13] = 0;
	R_1.m[14] = 0;
	R_1.m[15] = 1;

	T_1.m[0] = 1;
	T_1.m[1] = 0;
	T_1.m[2] = 0;
	T_1.m[3] = -m_eye.x;
	T_1.m[4] = 0;
	T_1.m[5] = 1;
	T_1.m[6] = 0;
	T_1.m[7] = -m_eye.y;
	T_1.m[8] = 0;
	T_1.m[9] = 0;
	T_1.m[10] = 1;
	T_1.m[11] = -m_eye.z;
	T_1.m[12] = 0;
	T_1.m[13] = 0;
	T_1.m[14] = 0;
	T_1.m[15] = 1;

	double n1 = -1.0, f = -500.0, r = 0.5;
	double l = -0.5, t = 0.5, b = -0.5;

	P.m[0] = 2.0 * n1 / (r - l);
	P.m[1] = 0;
	P.m[2] = (r + l) / (r - l);
	P.m[3] = 0;
	P.m[4] = 0;
	P.m[5] = 2.0 * n1 / (t - b);
	P.m[6] = (t + b) / (t - b);
	P.m[7] = 0;
	P.m[8] = 0;
	P.m[9] = 0;
	P.m[10] = -1.0 * (f + n1) / (f - n1);
	P.m[11] = -2.0 * f*n1 / (f - n1);
	P.m[12] = 0;
	P.m[13] = 0;
	P.m[14] = -1.0;
	P.m[15] = 0;
}

BOOL CViewingSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc serialization

void CViewingSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc diagnostics

#ifdef _DEBUG
void CViewingSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CViewingSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewingSystemDoc commands

void CViewingSystemDoc::FileOpen(CString filename)
{

	// View로부터 넘어온 파일명으로부터 파일을 연다.
	ifstream fin(filename.AllocSysString());	// Visual studio 2005

	CString check, dump;
	int numberOfVertices, numberOfFaces;
	trans_x_sum = 0;
	trans_y_sum = 0;
	trans_z_sum = 0;

	// 첫 줄의 세 단어를 가져온다.
	// dat파일을 메모장으로 열어 저장된 정보를 확인하기 바람.
	fin >> check.GetBuffer(100) >> dump.GetBuffer(100) >> numberOfVertices;

	if (check == "VERTEX")
	{
		m_numberOfVertices = numberOfVertices;

		// 얻어온 Vertex의 갯수로 배열을 생성
		if (m_vertices == 0){
			m_vertices = new Vertex[numberOfVertices];
			m_vertices_origin = new Vertex[numberOfVertices];
			dist = new Vertex[numberOfVertices];
		}
		else 
		{
			delete[] m_vertices;
			delete[] m_vertices_origin;
			delete[] dist;
			m_vertices = new Vertex[numberOfVertices];
			m_vertices_origin = new Vertex[numberOfVertices];
			dist = new Vertex[numberOfVertices];
		}

		double num1, num2, num3;
		// 이어지는 Vertex 정보를 배열에 저장
		for (int i = 0; i < numberOfVertices; i++)
		{
			fin >> num1 >> num2 >> num3;

			m_vertices[i] = Vertex(num1, num2, num3);
			m_vertices_origin[i] = Vertex(num1, num2, num3);
			dist[i] = Vertex(0, 0, 0);
		}

		fin >> check.GetBuffer(100) >> dump.GetBuffer(100) >> numberOfFaces;

		if (check == "FACE")
		{
			m_numberOfFaces = numberOfFaces;

			// 얻어온 Face의 갯수로 배열을 생성
			if (m_faces == 0)
				m_faces = new Face[numberOfFaces];
			else 
			{
				delete[] m_faces;
				m_faces = new Face[numberOfFaces];
			}

			int num4, num5, num6;
			// 이어지는 Face 정보를 배열에 저장
			for (int i = 0; i < numberOfFaces; i++)		// Visual studio 6.0, 2003
			//for (int i = 0; i < numberOfFaces; i++)	// Visual studio 2005
			{
				fin >> num4 >> num5 >> num6;

				m_faces[i] = Face(num4, num5, num6);
			}

			// 현재 모델을 그림. default rendering mode = PARALLEL
			Rendering();
		}
	}
}

void CViewingSystemDoc::Rendering()
{
	// DC를 하얀색으로 지우는 함수
	memdc.FillRect(win, &CBrush(RGB(255, 255, 255)));

	// 렌더링 모드에 따른 구현이 필요함
	CPoint center = CPoint(win.Width()/2, win.Height()/2);
	initializeVertices();
	initializeMatrix();

	axis = new Vertex[4];
	axis[0] = Vertex(0, 0, 0);
	axis[1] = Vertex(300, 0, 0);
	axis[2] = Vertex(0, 300, 0);
	axis[3] = Vertex(0, 0, 300);

	int i;
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = T_1*(m_vertices_origin[i]);
	}
	for (i = 0; i < 4; i++){
		axis[i] = T_1*(axis[i]);
	}
	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i] = R_1*(m_vertices[i]);
	}
	for (i = 0; i < 4; i++){
		axis[i] = R_1*(axis[i]);
	}
	if (m_viewingMode == PARALLEL)
	{
		for (i = 0; i < m_numberOfVertices; i++){
			m_vertices[i].x /= win.Width();
			m_vertices[i].y /= win.Height();
		}
		for (i = 0; i < 4; i++){
			axis[i].x /= win.Width();
			axis[i].y /= win.Height();
		}
	}
	else if (m_viewingMode == PERSPECTIVE)
	{
		for (i = 0; i < m_numberOfVertices; i++){
			m_vertices[i] = P*(m_vertices[i]);
		}
		for (i = 0; i < 4; i++){
			axis[i] = P*(axis[i]);
		}
	}

	for (i = 0; i < m_numberOfVertices; i++){
		m_vertices[i].x /= m_vertices[i].h;
		m_vertices[i].y /= m_vertices[i].h;
		m_vertices[i].z /= m_vertices[i].h;
		m_vertices[i].h /= m_vertices[i].h;
	}
	for (i = 0; i < 4; i++){
		axis[i].x /= axis[i].h;
		axis[i].y /= axis[i].h;
		axis[i].z /= axis[i].h;
		axis[i].h /= axis[i].h;
	}


	CPoint drawingPoint[5];
	drawingPoint[0] = CPoint(axis[1].x*center.x + center.x, -axis[1].y*center.y + center.y);
	drawingPoint[1] = CPoint(axis[0].x*center.x + center.x, -axis[0].y*center.y + center.y);
	drawingPoint[2] = CPoint(axis[2].x*center.x + center.x, -axis[2].y*center.y + center.y);
	drawingPoint[3] = CPoint(axis[0].x*center.x + center.x, -axis[0].y*center.y + center.y);
	drawingPoint[4] = CPoint(axis[3].x*center.x + center.x, -axis[3].y*center.y + center.y);
	memdc.Polyline(drawingPoint, 5);

	for (int i = 0; i < m_numberOfFaces; i++)
	{
		CPoint drawingPoint[4];

		drawingPoint[0] = CPoint(int(m_vertices[m_faces[i].v1].x*center.x + center.x), int(-m_vertices[m_faces[i].v1].y*center.y + center.y));
		drawingPoint[1] = CPoint(int(m_vertices[m_faces[i].v2].x*center.x + center.x), int(-m_vertices[m_faces[i].v2].y*center.y + center.y));
		drawingPoint[2] = CPoint(int(m_vertices[m_faces[i].v3].x*center.x + center.x), int(-m_vertices[m_faces[i].v3].y*center.y + center.y));
		drawingPoint[3] = CPoint(int(m_vertices[m_faces[i].v1].x*center.x + center.x), int(-m_vertices[m_faces[i].v1].y*center.y + center.y));

		memdc.Polyline(drawingPoint, 4);
	}

	CString str1, str2, str3, str4;
	str1.Format("Eye x : %d", int(m_eye.x));
	str2.Format("Eye y : %d", int(m_eye.y));
	str3.Format("Eye z : %d", int(m_eye.z));
	str4.Format("Projection : %s", m_viewingMode? "Perspective" : "Parallel");

	memdc.TextOut(10, 10, str1);
	memdc.TextOut(10, 30, str2);
	memdc.TextOut(10, 50, str3);
	memdc.TextOut(10, 70, str4);

}

Vertex CViewingSystemDoc::Normalization(Vertex vertex)
{
	double dis = sqrt(pow(vertex.x, 2.0) + pow(vertex.y, 2.0) + pow(vertex.z, 2.0));

	return Vertex(vertex.x/dis, vertex.y/dis, vertex.z/dis);
}

double CViewingSystemDoc::DotProduct(Vertex a, Vertex b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vertex CViewingSystemDoc::CrossProduct(Vertex a, Vertex b)
{
	return Vertex(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

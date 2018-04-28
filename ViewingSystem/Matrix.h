// Matrix.h: interface for the Matrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__E2559E10_6977_4DBC_B101_DCBA0C07C86A__INCLUDED_)
#define AFX_MATRIX_H__E2559E10_6977_4DBC_B101_DCBA0C07C86A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct Vertex
{
	double x;
	double y;
	double z;
	double h;

	Vertex()
	{
	}
	
	Vertex(double v1, double v2, double v3, double vh = 1.0)
	{
		x = v1;
		y = v2;
		z = v3;
		h = vh;
	}

	Vertex operator+(Vertex vertex)
	{
		return Vertex(x + vertex.x, y + vertex.y, z + vertex.z);
	}

	Vertex operator-(Vertex vertex)
	{
		return Vertex(x - vertex.x, y - vertex.y, z - vertex.z);
	}

	Vertex operator*(int number)
	{
		return Vertex(x * number, y * number, z * number);
	}

	Vertex operator*(double number)
	{
		return Vertex(x * number, y * number, z * number);
	}

	Vertex operator/(double number)
	{
		return Vertex(x / number, y / number, z / number);
	}
};

struct Face
{
	int v1;
	int v2;
	int v3;

	Face()
	{
	}

	Face(int f1, int f2, int f3)
	{
		v1 = f1;
		v2 = f2;
		v3 = f3;
	}
};

class Matrix  
{
public:
	Matrix();
	virtual ~Matrix();

	double m[16];

	void operator=(Matrix b);
	Matrix operator+(Matrix b);
	Matrix operator-(Matrix b);
	Matrix operator*(Matrix b);
	Vertex operator*(Vertex b);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                             Matrix Class ����
//
//	Matrix A, B, C, D, temp;		// �⺻ �����ڷ� 4*4�� ũ�⸦ ���� ���� ����� �����Ѵ�.
//	for (int i = 0; i < 16; i++)	// B, C ��Ŀ� ���ϴ� ���� ����
//	{
//		B.m[i] = i;
//		C.m[i] = i * 2;
//	}
//
//	A = B * C;		// B�� C ����� ������ ����� A�� ����ȴ�.
//	A = B * C * D;	// B, C, D ����� ������ ����� A�� ����ȴ�.
//
//	Vertex r, v;
//
//	// 4*4 ��İ� Vertex v�� ������ ����� Vertex r�� ����ȴ�.
//	r = B * v;
//	
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
};

#endif // !defined(AFX_MATRIX_H__E2559E10_6977_4DBC_B101_DCBA0C07C86A__INCLUDED_)

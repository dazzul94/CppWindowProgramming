#pragma once
#include <windows.h>

class CPerson
{
public:
	LPCTSTR	m_pName;   // �̸�
	int		m_Age;     // ����  

	CPerson(LPCTSTR pName, int age);
	void Print(HDC hdc, int x, int y);

};

class CStudent : public CPerson
{
	int		m_Number;    // �й�   
	int		m_Grade;     // �г�

public:

	CStudent(LPCTSTR pName, int age, int num);
	void    Print(HDC hdc, int x, int y);
};

class CProfessor : public CPerson
{
	LPCTSTR m_pMajor;  // ����
	LPCTSTR m_pDep;   // �а�

public:
	CProfessor(LPCTSTR pName, int age, LPCTSTR m_Major);
	void Print(HDC hdc, int x, int y);
};


#pragma once
#include <windows.h>

class CPerson
{
public:
	LPCTSTR	m_pName;   // 이름
	int		m_Age;     // 나이  

	CPerson(LPCTSTR pName, int age);
	void Print(HDC hdc, int x, int y);

};

class CStudent : public CPerson
{
	int		m_Number;    // 학번   
	int		m_Grade;     // 학년

public:

	CStudent(LPCTSTR pName, int age, int num);
	void    Print(HDC hdc, int x, int y);
};

class CProfessor : public CPerson
{
	LPCTSTR m_pMajor;  // 전공
	LPCTSTR m_pDep;   // 학과

public:
	CProfessor(LPCTSTR pName, int age, LPCTSTR m_Major);
	void Print(HDC hdc, int x, int y);
};


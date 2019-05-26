#include "student_v02.h"

CPerson::CPerson(LPCTSTR pName, int age)
{
	m_pName = pName;
	m_Age = age;
}

void CPerson::Print(HDC hdc, int x, int y)
{
	TCHAR buf[256];
	wsprintf(buf, L"<�̸�> : %s  <����> : %d ", m_pName, m_Age);
	TextOut(hdc, x, y, buf, lstrlen(buf));
}


CStudent::CStudent(LPCTSTR pName, int age, int num) : CPerson(pName, age)
{
	m_Number = num;

}

//����� ������ ����Ѵ�.
void CStudent::Print(HDC hdc, int x, int y)
{
	TCHAR buf[256];

	wsprintf(buf, L"<�̸�> : %s  <����> : %d <�й�> : %d", m_pName, m_Age, m_Number);
	TextOut(hdc, x, y, buf, lstrlen(buf));

}

CProfessor::CProfessor(LPCTSTR pName, int age, LPCTSTR pMajor) : CPerson(pName, age)
{
	m_pMajor = pMajor;
}

void CProfessor::Print(HDC hdc, int x, int y)
{
	TCHAR buf[256];
	wsprintf(buf, L"<�̸�> : %s  <����> : %d  <����> : %s", m_pName, m_Age, m_pMajor);
	TextOut(hdc, x, y, buf, lstrlen(buf));

}
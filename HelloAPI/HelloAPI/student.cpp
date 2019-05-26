#include "student.h"
// 기본 생성자
CStudent::CStudent()
{
	// nothing
}

// name, age 받는 생성자 
// 만들면 기본 생성자는 명시적으로 만들어줘야한다.
CStudent::CStudent(LPCTSTR pName, int pAge)
{
	m_pName = pName;
	m_Age = pAge;
}

void CStudent::SetName(LPCTSTR pName)
{
	m_pName = pName;
}
void CStudent::SetAge(int p_Age)
{
	m_Age = p_Age;
}
void CStudent::Print(HDC hdc, int x, int y)
{
	TCHAR buf[256];
	wsprintf(buf, L"<이름> : %s, <나이> : %d", m_pName, m_Age);
	TextOut(hdc, x, y, buf, lstrlen(buf));
}
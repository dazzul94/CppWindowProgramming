#include "student.h"
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
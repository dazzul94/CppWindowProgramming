#include "student.h"
// �⺻ ������
CStudent::CStudent()
{
	// nothing
}

// name, age �޴� ������ 
// ����� �⺻ �����ڴ� ��������� ���������Ѵ�.
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
	wsprintf(buf, L"<�̸�> : %s, <����> : %d", m_pName, m_Age);
	TextOut(hdc, x, y, buf, lstrlen(buf));
}
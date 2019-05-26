#pragma once
#include <windows.h>
class CStudent
{
public:
	LPCTSTR m_pName;
	int m_Age;
	int m_Number;
	int m_Grade;

	CStudent();	// �⺻ ������ 
	// ������ (Ŭ���� �̸��� ����.)
	CStudent(LPCTSTR pName, int age);

	void SetName(LPCTSTR pName);
	void SetAge(int p_Age);
	void Print(HDC hdc, int x, int y);
};

// Ŭ������ Ư¡ 
/*
1. ĸ��ȭ: ��������� ���� �����ϴ� ���� �ݵ�� 
		����Լ��� ���ؼ� Set
2. ���: ��� > ����, �л�
	- ��� (�̸�, ����)
	- ���� (�̸�, ����, ����, �а�)
	- ��� (�̸�, ����, �й�, �г�)
=> ������ �Լ� �Ѵ� ��ӹ޴´�.
*/
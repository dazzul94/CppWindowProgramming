#pragma once
#include <windows.h>
class CStudent
{
public:
	LPCTSTR m_pName;
	int m_Age;
	int m_Number;
	int m_Grade;

	CStudent();	// 기본 생성자 
	// 생성자 (클래스 이름과 같다.)
	CStudent(LPCTSTR pName, int age);

	void SetName(LPCTSTR pName);
	void SetAge(int p_Age);
	void Print(HDC hdc, int x, int y);
};

// 클래스의 특징 
/*
1. 캡슐화: 멤버변수에 값을 설정하는 것은 반드시 
		멤버함수를 통해서 Set
2. 상속: 사람 > 교수, 학생
	- 사람 (이름, 나이)
	- 교수 (이름, 나이, 전공, 학과)
	- 사람 (이름, 나이, 학번, 학년)
=> 변수와 함수 둘다 상속받는다.
*/
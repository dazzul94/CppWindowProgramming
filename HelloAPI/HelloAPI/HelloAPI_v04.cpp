#include <windows.h>
#include "student.h"
/*
4강. 차일드 윈도우 생성과 버튼 컨트롤
*/
// 차일드 컨트롤 ID를 2000으로 설정
#define ID_OK_BTN	2000

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName = L"ChildWin";


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);     //메인윈도우 클래스 등록
	OutputDebugString(L"메인윈도우 클래스 등록\n");

	WndClass.lpfnWndProc = ChildWndProc;      //차일드 윈도우 프로시저
	WndClass.lpszClassName = ChildClassName; //차일드 윈도우 클래스이름
	RegisterClass(&WndClass);
	OutputDebugString(L"차일드 윈도우 클래스 등록\n");

	OutputDebugString(L"메인 윈도우 생성시작\n");
	hWnd = CreateWindow(lpszClass,			//윈도우클래스 이름
		L"윈도우 프로그래밍",			    //윈도우타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
		200, 200,							//윈도우가 보일때 X Y좌표
		600, 600,							//윈도우의 폭과 높이				
		(HWND)NULL,							//부모윈도우 핸들
		(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
		hInstance,							//인스턴스핸들
		NULL);								//여분의 데이터

	OutputDebugString(L"메인 윈도우 생성완료\n");
	ShowWindow(hWnd, nCmdShow);
	OutputDebugString(L"메인 윈도우 show완료\n");

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성";
	switch (iMessage) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		CStudent newStudent;
		HDC hdc = BeginPaint(hWnd, &ps);
		newStudent.SetName(L"김다솔");
		newStudent.SetAge(26);
		newStudent.Print(hdc, 100, 100);	// TextOut 함수 들어있음 
		//TextOut(hdc, 100, 100, text, lstrlen(text));
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_PAINT 발생처리\n");
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:
	{
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_CREATE 발생처리\n");
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_CREATE 발생처리에서 차일드 윈도우 생성시작\n");
		HWND hChildWnd = CreateWindow(
			ChildClassName,     		// 차일드 윈도우 클래스 이름 
			L"차일드 윈도우",            	// 윈도우 타이틀 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 
			150,       		// 윈도우 보일 때 x 좌표 
			150,       		// 윈도우 보일 때 y 좌표 
			260,       		// 윈도우 폭
			200,       		// 윈도우 높이
			hWnd,         		// 부모 윈도우
			(HMENU)1000,        	// 차일드 윈도우ID 
			g_hInst,           		// 인스턴스 핸들 
			(LPVOID)NULL);      	// 여분의 데이터			
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_CREATE 발생처리에서 차일드 윈도우 생성완료\n");

		ShowWindow(hChildWnd, SW_SHOW);
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_CREATE 발생처리에서 차일드 윈도우 show 완료\n");


		// 지역대학 버튼 생성
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_CREATE 발생처리에서 지역대학버튼 생성시작\n");
		hChildWnd = CreateWindow(
			L"button",        		// 윈도우 클래스 이름 
			// -> 버튼 컨드롤이므로 자동으로 생성된다.
			L"지역대학",			// 윈도우 타이틀 
			WS_CHILD | WS_VISIBLE, 	// 윈도우 스타일 
			20,       		// 윈도우 보일 때 x 좌표 
			400,       		// 윈도우 보일 때 y 좌표 
			100,       		// 윈도우 폭
			30,       		// 윈도우 높이
			hWnd,         		// 부모 윈도우
			(HMENU)ID_OK_BTN,   	// 컨트롤 ID
			g_hInst,           		// 인스턴스 핸들 
			(LPVOID)NULL);      	// 여분의 데이터
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_CREATE 발생처리에서 지역대학버튼 생성완료\n");

		if (!hChildWnd) 	return -1;
		return 0;
	}
	case WM_COMMAND:
	{
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_COMMAND 발생처리\n");
		if (LOWORD(wParam) == ID_OK_BTN) // 2000
		{
			// 메시지 팝업 
			// MessageBox(hWnd, L"[지역대학] 버튼이 클릭되었다", L"지역대학", MB_OKCANCEL);
			if (MessageBox(hWnd,
				L"[지역대학] 버튼이 클릭되었다",
				L"지역대학",
				MB_OKCANCEL) == IDOK)
			{
				MessageBox(hWnd,
					L"확인 버튼 눌림",
					L"확인", MB_OK);
				OutputDebugString(L"(메인 윈도우)WinProc의 WM_COMMAND 확인 message box 띄우기\n");
			}
			else
			{
				MessageBox(hWnd,
					L"취소 버튼 눌림",
					L"취소", MB_OK);
				OutputDebugString(L"(메인 윈도우)WinProc의 WM_COMMAND 취소 message box 띄우기\n");
			}

			OutputDebugString(L"(메인 윈도우)WinProc의 WM_COMMAND 지역대학 message box 띄우기\n");
			// MB_OK => 확인 버튼 나옴 (종류 여러가지 있음)
			/*
			1. MB_ABORTRETRYIGNORE - Abort, Retry, Ignore 세 개의 버튼이 나타난다.
			2. MB_OK - OK버튼 하나만 나타난다.
			3. MB_OKCANCLE - OK, Cancel 두개의 버튼이 나타난다.
			4. MB_RETRYCANCLE - Retry, Cancel 두개의 버튼이 나타난다.
			5. MB_YESNO - Yes, No 두개의 버튼이 나타난다.
			6. MB_YESNOCANCEL - Yes, No, Cancel 세개의 버튼이 나타난다.
			*/
		}

		OutputDebugString(L"(메인 윈도우)WinProc의 WM_COMMAND 처리완료\n");
		return 0;	// default
	}
	case WM_DESTROY:
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_DESTORY 처리시작\n");
		PostQuitMessage(0);
		OutputDebugString(L"(메인 윈도우)WinProc의 WM_DESTORY 처리완료\n");
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"차일드 윈도우생성";
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		OutputDebugString(L"(차일드 윈도우)ChildWinProc의 WM_WM_PAINT 처리완료\n");
		return 0;
	}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
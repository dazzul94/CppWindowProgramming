// Visual C++ 윈도우 프로그래밍 과제 20190525

#include <windows.h>
#define ID_OK_BTN_LEFT		2000
#define ID_OK_BTN_RIGHT		3000
#define ID_OK_BTN_INSIDE	4000

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName_left = L"ChildWin_left";
LPCTSTR ChildClassName_right = L"ChildWin_right";


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc_left(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc_right(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

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
	RegisterClass(&WndClass);
	OutputDebugString(L"메인 윈도우 클래스 등록\n");

	// 왼쪽 차일드 윈도우(ChildClassName_left)
	WndClass.lpfnWndProc = ChildWndProc_left;      
	WndClass.lpszClassName = ChildClassName_left; 
	RegisterClass(&WndClass);
	OutputDebugString(L"왼쪽 차일드 클래스 등록\n");

	// 오른쪽 차일드 윈도우(ChildClassName_right)
	WndClass.lpfnWndProc = ChildWndProc_right;
	WndClass.lpszClassName = ChildClassName_right;
	RegisterClass(&WndClass);
	OutputDebugString(L"오른쪽 차일드 클래스 등록\n");

	hWnd = CreateWindow(lpszClass,			
		L"Visual C++ 프로그래밍",			    
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   
		200, 200,							
		600, 600,											
		(HWND)NULL,							
		(HMENU)NULL,						
		hInstance,							
		NULL);								

	ShowWindow(hWnd, nCmdShow);
	OutputDebugString(L"메인 윈도우 creatWindow");

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text1 = L"Visual C++ 프로그래밍 출석수업대체시험";
	LPCTSTR text2 = L"201834-154131 김다솔";
	switch (iMessage) {
	case WM_PAINT:
	{
		OutputDebugString(L"=============메인 윈도우 콜백 함수의 WM_PAINT\n");
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text1, lstrlen(text1));
		TextOut(hdc, 100, 120, text2, lstrlen(text2));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:
	{
		OutputDebugString(L"=============메인 윈도우 콜백 함수의 WM_CREATE\n");
		HWND hChildWnd = CreateWindow(
			ChildClassName_left,     		
			L"출석수업",            	
			WS_OVERLAPPEDWINDOW | WS_CHILD,  
			20,       		
			150,       		 
			260,       		
			200,       		
			hWnd,         		
			(HMENU)1000,        	 
			g_hInst,           		 
			(LPVOID)NULL);      				

		ShowWindow(hChildWnd, SW_SHOW);
		hChildWnd = CreateWindow(
			ChildClassName_right,
			L"신청기간",
			WS_OVERLAPPEDWINDOW | WS_CHILD,
			300,
			150,
			260,
			200,
			hWnd,
			(HMENU)1000,
			g_hInst,
			(LPVOID)NULL);


		ShowWindow(hChildWnd, SW_SHOW);

		// 대체시험일 버튼 (ID_OK_BTN_LEFT)
		hChildWnd = CreateWindow(
			L"button",        		 
			L"대체시험일",			
			WS_CHILD | WS_VISIBLE, 	 
			50,       		 
			400,       		 
			200,       		
			30,       		
			hWnd,         		
			(HMENU)ID_OK_BTN_LEFT,
			g_hInst,           		 
			(LPVOID)NULL);      	

		// 대체시험일 버튼 (ID_OK_BTN_RIGHT)
		hChildWnd = CreateWindow(
			L"button",
			L"제출방법",
			WS_CHILD | WS_VISIBLE,
			320,
			400,
			200,
			30,
			hWnd,
			(HMENU)ID_OK_BTN_RIGHT,
			g_hInst,
			(LPVOID)NULL);

		if (!hChildWnd) 	return -1;
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_OK_BTN_LEFT) 
		{
			MessageBox(hWnd, L"2019.6.9.(일) 제출", L"대체시험일", MB_OK);
		}
		else if (LOWORD(wParam) == ID_OK_BTN_RIGHT) 
		{
			MessageBox(hWnd, L"온라인제출", L"제출방법", MB_OK);
		}

		return 0;	
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK ChildWndProc_left(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"참석이 불가능한 경우";
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:
	{
		HWND hChildWnd = CreateWindow(
			L"button",
			L"대체시험형태",
			WS_CHILD | WS_VISIBLE,
			10,
			60,
			150,
			30,
			hWnd,
			(HMENU)ID_OK_BTN_INSIDE,
			g_hInst,
			(LPVOID)NULL);

		if (!hChildWnd) 	return -1;
		return 0;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_OK_BTN_INSIDE)
		{
			MessageBox(hWnd, L"실습과제물", L"대체시험형태", MB_OK);
		}
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
LRESULT CALLBACK ChildWndProc_right(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"3.11(월)-5.8(수)";
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
// Visual C++ ������ ���α׷��� ���� 20190525

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
	OutputDebugString(L"���� ������ Ŭ���� ���\n");

	// ���� ���ϵ� ������(ChildClassName_left)
	WndClass.lpfnWndProc = ChildWndProc_left;      
	WndClass.lpszClassName = ChildClassName_left; 
	RegisterClass(&WndClass);
	OutputDebugString(L"���� ���ϵ� Ŭ���� ���\n");

	// ������ ���ϵ� ������(ChildClassName_right)
	WndClass.lpfnWndProc = ChildWndProc_right;
	WndClass.lpszClassName = ChildClassName_right;
	RegisterClass(&WndClass);
	OutputDebugString(L"������ ���ϵ� Ŭ���� ���\n");

	hWnd = CreateWindow(lpszClass,			
		L"Visual C++ ���α׷���",			    
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   
		200, 200,							
		600, 600,											
		(HWND)NULL,							
		(HMENU)NULL,						
		hInstance,							
		NULL);								

	ShowWindow(hWnd, nCmdShow);
	OutputDebugString(L"���� ������ creatWindow");

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text1 = L"Visual C++ ���α׷��� �⼮������ü����";
	LPCTSTR text2 = L"201834-154131 ��ټ�";
	switch (iMessage) {
	case WM_PAINT:
	{
		OutputDebugString(L"=============���� ������ �ݹ� �Լ��� WM_PAINT\n");
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text1, lstrlen(text1));
		TextOut(hdc, 100, 120, text2, lstrlen(text2));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:
	{
		OutputDebugString(L"=============���� ������ �ݹ� �Լ��� WM_CREATE\n");
		HWND hChildWnd = CreateWindow(
			ChildClassName_left,     		
			L"�⼮����",            	
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
			L"��û�Ⱓ",
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

		// ��ü������ ��ư (ID_OK_BTN_LEFT)
		hChildWnd = CreateWindow(
			L"button",        		 
			L"��ü������",			
			WS_CHILD | WS_VISIBLE, 	 
			50,       		 
			400,       		 
			200,       		
			30,       		
			hWnd,         		
			(HMENU)ID_OK_BTN_LEFT,
			g_hInst,           		 
			(LPVOID)NULL);      	

		// ��ü������ ��ư (ID_OK_BTN_RIGHT)
		hChildWnd = CreateWindow(
			L"button",
			L"������",
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
			MessageBox(hWnd, L"2019.6.9.(��) ����", L"��ü������", MB_OK);
		}
		else if (LOWORD(wParam) == ID_OK_BTN_RIGHT) 
		{
			MessageBox(hWnd, L"�¶�������", L"������", MB_OK);
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
	LPCTSTR text = L"������ �Ұ����� ���";
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
			L"��ü��������",
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
			MessageBox(hWnd, L"�ǽ�������", L"��ü��������", MB_OK);
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
	LPCTSTR text = L"3.11(��)-5.8(��)";
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
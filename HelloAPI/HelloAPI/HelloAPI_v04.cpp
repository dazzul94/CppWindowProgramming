#include <windows.h>
#include "student.h"
/*
4��. ���ϵ� ������ ������ ��ư ��Ʈ��
*/
// ���ϵ� ��Ʈ�� ID�� 2000���� ����
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
	RegisterClass(&WndClass);     //���������� Ŭ���� ���
	OutputDebugString(L"���������� Ŭ���� ���\n");

	WndClass.lpfnWndProc = ChildWndProc;      //���ϵ� ������ ���ν���
	WndClass.lpszClassName = ChildClassName; //���ϵ� ������ Ŭ�����̸�
	RegisterClass(&WndClass);
	OutputDebugString(L"���ϵ� ������ Ŭ���� ���\n");

	OutputDebugString(L"���� ������ ��������\n");
	hWnd = CreateWindow(lpszClass,			//������Ŭ���� �̸�
		L"������ ���α׷���",			    //������Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
		200, 200,							//�����찡 ���϶� X Y��ǥ
		600, 600,							//�������� ���� ����				
		(HWND)NULL,							//�θ������� �ڵ�
		(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
		hInstance,							//�ν��Ͻ��ڵ�
		NULL);								//������ ������

	OutputDebugString(L"���� ������ �����Ϸ�\n");
	ShowWindow(hWnd, nCmdShow);
	OutputDebugString(L"���� ������ show�Ϸ�\n");

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���������� ����";
	switch (iMessage) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		CStudent newStudent;
		HDC hdc = BeginPaint(hWnd, &ps);
		newStudent.SetName(L"��ټ�");
		newStudent.SetAge(26);
		newStudent.Print(hdc, 100, 100);	// TextOut �Լ� ������� 
		//TextOut(hdc, 100, 100, text, lstrlen(text));
		OutputDebugString(L"(���� ������)WinProc�� WM_PAINT �߻�ó��\n");
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:
	{
		OutputDebugString(L"(���� ������)WinProc�� WM_CREATE �߻�ó��\n");
		OutputDebugString(L"(���� ������)WinProc�� WM_CREATE �߻�ó������ ���ϵ� ������ ��������\n");
		HWND hChildWnd = CreateWindow(
			ChildClassName,     		// ���ϵ� ������ Ŭ���� �̸� 
			L"���ϵ� ������",            	// ������ Ÿ��Ʋ 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // ������  ��Ÿ�� 
			150,       		// ������ ���� �� x ��ǥ 
			150,       		// ������ ���� �� y ��ǥ 
			260,       		// ������ ��
			200,       		// ������ ����
			hWnd,         		// �θ� ������
			(HMENU)1000,        	// ���ϵ� ������ID 
			g_hInst,           		// �ν��Ͻ� �ڵ� 
			(LPVOID)NULL);      	// ������ ������			
		OutputDebugString(L"(���� ������)WinProc�� WM_CREATE �߻�ó������ ���ϵ� ������ �����Ϸ�\n");

		ShowWindow(hChildWnd, SW_SHOW);
		OutputDebugString(L"(���� ������)WinProc�� WM_CREATE �߻�ó������ ���ϵ� ������ show �Ϸ�\n");


		// �������� ��ư ����
		OutputDebugString(L"(���� ������)WinProc�� WM_CREATE �߻�ó������ �������й�ư ��������\n");
		hChildWnd = CreateWindow(
			L"button",        		// ������ Ŭ���� �̸� 
			// -> ��ư ������̹Ƿ� �ڵ����� �����ȴ�.
			L"��������",			// ������ Ÿ��Ʋ 
			WS_CHILD | WS_VISIBLE, 	// ������ ��Ÿ�� 
			20,       		// ������ ���� �� x ��ǥ 
			400,       		// ������ ���� �� y ��ǥ 
			100,       		// ������ ��
			30,       		// ������ ����
			hWnd,         		// �θ� ������
			(HMENU)ID_OK_BTN,   	// ��Ʈ�� ID
			g_hInst,           		// �ν��Ͻ� �ڵ� 
			(LPVOID)NULL);      	// ������ ������
		OutputDebugString(L"(���� ������)WinProc�� WM_CREATE �߻�ó������ �������й�ư �����Ϸ�\n");

		if (!hChildWnd) 	return -1;
		return 0;
	}
	case WM_COMMAND:
	{
		OutputDebugString(L"(���� ������)WinProc�� WM_COMMAND �߻�ó��\n");
		if (LOWORD(wParam) == ID_OK_BTN) // 2000
		{
			// �޽��� �˾� 
			// MessageBox(hWnd, L"[��������] ��ư�� Ŭ���Ǿ���", L"��������", MB_OKCANCEL);
			if (MessageBox(hWnd,
				L"[��������] ��ư�� Ŭ���Ǿ���",
				L"��������",
				MB_OKCANCEL) == IDOK)
			{
				MessageBox(hWnd,
					L"Ȯ�� ��ư ����",
					L"Ȯ��", MB_OK);
				OutputDebugString(L"(���� ������)WinProc�� WM_COMMAND Ȯ�� message box ����\n");
			}
			else
			{
				MessageBox(hWnd,
					L"��� ��ư ����",
					L"���", MB_OK);
				OutputDebugString(L"(���� ������)WinProc�� WM_COMMAND ��� message box ����\n");
			}

			OutputDebugString(L"(���� ������)WinProc�� WM_COMMAND �������� message box ����\n");
			// MB_OK => Ȯ�� ��ư ���� (���� �������� ����)
			/*
			1. MB_ABORTRETRYIGNORE - Abort, Retry, Ignore �� ���� ��ư�� ��Ÿ����.
			2. MB_OK - OK��ư �ϳ��� ��Ÿ����.
			3. MB_OKCANCLE - OK, Cancel �ΰ��� ��ư�� ��Ÿ����.
			4. MB_RETRYCANCLE - Retry, Cancel �ΰ��� ��ư�� ��Ÿ����.
			5. MB_YESNO - Yes, No �ΰ��� ��ư�� ��Ÿ����.
			6. MB_YESNOCANCEL - Yes, No, Cancel ������ ��ư�� ��Ÿ����.
			*/
		}

		OutputDebugString(L"(���� ������)WinProc�� WM_COMMAND ó���Ϸ�\n");
		return 0;	// default
	}
	case WM_DESTROY:
		OutputDebugString(L"(���� ������)WinProc�� WM_DESTORY ó������\n");
		PostQuitMessage(0);
		OutputDebugString(L"(���� ������)WinProc�� WM_DESTORY ó���Ϸ�\n");
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���ϵ� ���������";
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		OutputDebugString(L"(���ϵ� ������)ChildWinProc�� WM_WM_PAINT ó���Ϸ�\n");
		return 0;
	}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
#include <windows.h>
/*
2��. ���ϵ� ������ ����
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// ���� ������ ���ν���
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //���ϵ� ������ ���ν���

HINSTANCE g_hInst; // ���ϵ� �����쿡�� ���� ���� ��������
LPCTSTR lpszClass = L"HelloAPI";	// ������������ �̸�
LPCTSTR ChildClassName = L"ChildWin";	// ���ϵ��������� �̸�

// ������ Ŭ���� �����Լ�
int APIENTRY WinMain(HINSTANCE hInstance,	// ���ø����̼��� �ν��Ͻ� �ڵ�
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd;	// ���� ������ �ڵ�?
	MSG Message;
	WNDCLASS WndClass;	// ������ Ŭ���� �ѹ��� �����ϰ� �� ���Ŀ� ����� ������ ����
	g_hInst = hInstance;	// ���� ���� 

	// ���� �����쿡 ���� ���� ����
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

	/******************* ���ϵ� ������ **********************/
	WndClass.lpfnWndProc = ChildWndProc;      //���ϵ� ������ ���ν���
	WndClass.lpszClassName = ChildClassName; //���ϵ� ������ Ŭ�����̸�
	RegisterClass(&WndClass);	// ��ϸ� ���ְ� show�� ���� ������ ���ν�������

	// ���� ������ CreateWindow
	hWnd = CreateWindow(lpszClass,			//������Ŭ���� �̸�
		L"������ ���α׷���",			    //������Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
		200, 200,							//�����찡 ���϶� X Y��ǥ
		600, 600,							//�������� ���� ����				
		(HWND)NULL,							//�θ������� �ڵ�
		(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
		hInstance,							//�ν��Ͻ��ڵ�
		NULL);								//������ ������

	ShowWindow(hWnd, nCmdShow);

	// ��� �����ֱ�
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

// ���� ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
	/*
	1. wParam: WM_COMMAND�� �̺�Ʈ ����
		���� 2byte: � ������ �޽������� ǥ�����ִ� ����(ex BN_CLICK)
		���� 2byte: ��Ʈ���� ID(������ٶ� ����ϴ� ��ȣ ex 2000)
	2. lParam: ������ �ڵ�

	-> HIWORD : get wParam's high word
	-> LOWORD : get wParam's low word
	*/
	
{
	LPCTSTR text = L"���������� ����";
	switch (iMessage) {
	case WM_PAINT:	// �����찡 �����ǰų� ����ǰų� �̵��ɶ� ��������� �̺�Ʈ(���� �׷����ϱ� ������)
	{
		PAINTSTRUCT ps;	
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text, lstrlen(text));	// �ؽ�Ʈ ���
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:	// �����찡 ������ �� ��������� �̺�Ʈ( ������ �� ���ϵ� �����츦 createWindow) 
	{
		HWND hChildWnd = CreateWindow(
			ChildClassName,     		// ���ϵ� ������ Ŭ���� �̸� 
			L"���ϵ� ������",            	// ������ Ÿ��Ʋ 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // ������  ��Ÿ�� 

			// x��ǥ, y��ǥ�� ���� �������� client ������ ������ �������� ��������!
			150,       		// ������ ���� �� x ��ǥ 
			150,       		// ������ ���� �� y ��ǥ 
			260,       		// ������ ��
			200,       		// ������ ����
			hWnd,         		// �θ� ������
			(HMENU)1000,        	// ���ϵ� ������ID 
			g_hInst,           		// �ν��Ͻ� �ڵ� (��������)
			(LPVOID)NULL);      	// ������ ������

		if (!hChildWnd) 	return -1;

		ShowWindow(hChildWnd, SW_SHOW);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
// ���ϵ� ������ ���ν���
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���ϵ� ���������";
	switch (message)
	{
	case WM_PAINT:	
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));	//�ؽ�Ʈ ���
		EndPaint(hWnd, &ps);
		return 0;
	}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
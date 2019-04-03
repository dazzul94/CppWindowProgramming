#include <windows.h>
/*
*****ū Ʋ******
WndMain {
	1. ������Ŭ���� ����(WndClass) 
	2. ������Ŭ������ �������� �Ӽ��� ���� (������Ŭ������ ����ü)
	3. ���(OS���� ��û)
	4. ����(������ ��ü�� �Ӽ��� ����)
	5. �����ֱ�
	6. ���ѷ���
}
7. WinProc - ������ ���ν���(�ݹ��Լ�)
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";

// ���� �����츦 ������ش�
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	// ������ Ŭ���� ����
	// ������ Ŭ������? Ư�� �����찡 ���������� ������ �Ӽ����� ����
	// ������� �ݵ�� �ϳ��� ������ Ŭ�������� ���������.
	// -> ������ ����� �ٸ���? �ٸ� Ŭ������ ���������. ex) ��ư, �޺��ڽ�
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// ������ Ŭ���� ����ü�� �Ӽ���(�������� �ڷ��� ������ ����ü)
	WndClass.cbClsExtra = 0;	// ���࿵��
	WndClass.cbWndExtra = 0;	// ���࿵��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// �������� ������ ĥ�� �귯�� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_WAIT);	// ���콺 Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������ ����
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;	// �������� �޽��� ó�� �Լ� �̸�(WndProc�� �Ϲ����� �̸�)
	WndClass.lpszClassName = lpszClass;	// ������ Ŭ���� �̸�(���ڿ�)
	WndClass.lpszMenuName = NULL;	// ���α׷��� ����� �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;   // �����콺Ÿ��
	// ���������� ���
	RegisterClass(&WndClass);

	// ���������� ���� (���� ������ ����)
	hWnd = CreateWindow(lpszClass,			// ������Ŭ���� �̸�
		L"������ ���α׷���",			    // ������Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // �����콺Ÿ��
		200, 200,							// �����찡 ���϶� X Y��ǥ
		600, 600,							// �������� ���� ����				
		(HWND)NULL,							// �θ������� �ڵ�
		(HMENU)NULL,						// �����찡 ������ �޴��ڵ�
		hInstance,							// �ν��Ͻ��ڵ�
		NULL);								// ������ ������

	// ���������� ������ (���� ���̰�)
	ShowWindow(hWnd, nCmdShow);

	// �޽��� ����: �״�� �θ� ������� ������ ���ѷ����� ������ ��� ���ư���
	// WM_QUIT�� ��쿡��(X��ư ������ ��) false�� �����Ͽ� �޽��� ���� ����
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);	// ����
		DispatchMessage(&Message);	// OS�� ��� -> OS�� ������ ������ ���ν����� ȣ���ϰ� �� �Ŀ� ������ ���ν����� ó���Ѵ�.
	}
	return Message.wParam;
}

// CallBack �Լ� = ������ ���ν���
// OS�� �̺�Ʈ�� �����ϰ� �޼����� �� �Լ��� �����ָ�
// �� �޼���(�̺�Ʈ)������ ó���� ����Ѵ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���������� ����";
	switch (iMessage) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text, lstrlen(text));
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

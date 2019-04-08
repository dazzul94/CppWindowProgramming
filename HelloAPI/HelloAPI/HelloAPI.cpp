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

// �ݹ��Լ��ν� WndProc�� ����ҰŶ�� ProtoType�� �������ش�. 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Child Window ����
HINSTANCE g_hInst;

// ���ڿ��� ������ �� �ִ� String����(LPCTSTR)
LPCTSTR lpszClass = L"HelloAPI"; // L�� �����ڵ� ��� 

// ���� �����츦 ������ش�
/*
1. hInstance: ���ø����̼��� ���� �ν��Ͻ��ڵ�
2. hPrebInstance: ���ø����̼��� ���� �ν��Ͻ��� �ڵ�
3. lpCmdLine: Ŀ�ǵ������ ���ڰ��� �޴� ������
4. nCmdShow: �����찡 ȭ��� �������� ����·� ���������� ����(showWindow�� �Ű������� ���)
*/
int APIENTRY WinMain(
	HINSTANCE hInstance,	 // �ν��Ͻ� �ڵ� - ���α׷��� �̸�ǥ(�ּ�:������) -����ϴ� �޸��ּ�
	HINSTANCE hPrevInstance, // �ν��Ͻ� �ڵ�
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd; // ������ �ڵ�(�ü���� �����츦 ã���� �ּ� �����Ͱ�)
	MSG Message; // �޼���Ÿ��
	// ������ Ŭ���� ����
	// ������ Ŭ������? Ư�� �����찡 ���������� ������ �Ӽ����� ����
	// ������� �ݵ�� �ϳ��� ������ Ŭ�������� ���������.
	// -> ������ ����� �ٸ���? �ٸ� Ŭ������ ���������. ex) ��ư, �޺��ڽ�
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// ������ Ŭ���� ����ü�� �Ӽ���(�������� �ڷ��� ������ ����ü) -> ������ ����� ������
	WndClass.cbClsExtra = 0;	// ���࿵��(default:0)
	WndClass.cbWndExtra = 0;	// ���࿵��(default:0)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// �������� ������ ĥ�� �귯�� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_WAIT);	// ���콺 Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������ ����
	WndClass.hInstance = hInstance; // �� �������� Ŭ������ �ν��Ͻ� �ڵ�
	WndClass.lpfnWndProc = (WNDPROC)WndProc;	// ***�ʼ�����***�������� �޽��� ó�� �Լ� �̸�(WndProc�� �Ϲ����� �̸�, ���� ����ϴ� Callback�Լ��� WinProc)
	WndClass.lpszClassName = lpszClass;	// ***�ʼ�����***������ Ŭ���� �̸�(���ڿ�) -> createWindow�Ҷ� �̸����� ������
	WndClass.lpszMenuName = NULL;	// ���α׷��� ����� �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;   // �����콺Ÿ��(Horizon/Vertical)

	// ���������� ��� (�Ӽ����� �־��� ������ Ŭ������ ���)
	RegisterClass(&WndClass);

	// ���������� ���� (���� ������ ����) -> createWindow�� �����ϴ°�(�ּҰ�)
	hWnd = CreateWindow(lpszClass,			// ������Ŭ���� �̸�(������� ������Ŭ�����̸�)
		L"������ ���α׷���",			    // ������Ÿ��Ʋ(Ÿ��Ʋ�ٿ� ��Ÿ���� ���ڿ�)
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // �����콺Ÿ��(��ø������(WS_OVERLAPPEDWINDOW)-WS_MINIMIZEBOX, WS_MAXIZIXEBOX, WS_SYSMENU, WS_CAPTION, WS_THICKFRAME)
		200, 200,							// �����찡 ���϶� X,Y��ǥ(�ǿ��ʻ�ܳ� ����)
		600, 600,							// �������� ���� ����				
		(HWND)NULL,							// �θ������� �ڵ�
		(HMENU)NULL,						// �����찡 ������ �޴��ڵ�
		hInstance,							// �ν��Ͻ��ڵ�
		NULL);								// ������ ������

	// ���������� ������ (���� ���̰�)
	ShowWindow(hWnd, nCmdShow);  
	// hWnd: createWindow�� ���ϰ� 
	// nCmdShow: WinMain�� �׹�° �Ű�����

	// while���� ���ؼ� ��� �����ְ� ����(�޼���ť���� �����´�)
	// �޽��� ����: �״�� �θ� ������� ������ ���ѷ����� ������ ��� ���ư���
	// WM_QUIT�� ��쿡��(X��ư ������ ��) false�� �����Ͽ� �޽��� ���� ����
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);	// ����(�˾Ƶ������ְ� ����)- Ű���带 ������ ������ �� �̸� WM_CHAR �޽����� ��ȯ
		DispatchMessage(&Message);	// OS�� ��� -> OS�� ������ ������ ���ν����� ȣ���ϰ� �� �Ŀ� ������ ���ν����� ó���Ѵ�.
		// **����**-> �޽����� �ü���� �����Ͽ� �ü���� ������ ���ν����� ȣ���ϵ��� ��
	}
	return Message.wParam;
}

// CallBack �Լ� = ������ ���ν���
// OS�� �̺�Ʈ�� �����ϰ� �޼����� �� �Լ��� �����ָ�
// �� �޼���(�̺�Ʈ)������ ó���� ����Ѵ�
LRESULT CALLBACK WndProc(HWND hWnd,   // hWnd: �������ڵ�(createWindow�Ҷ� ���ϰ�), ��� ������ �ϳ��� �������ڵ鿡�� ������ �ϳ��� ���������ν����� ����ٴ´�
	UINT iMessage, // ������ �� �޽���
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���������� ����"; // ���ڿ��� ���� �� �ִ� String ����(L�� �����ڵ幮��)
	/*
	1. WM_QUIT: ���α׷��� ���� �� �߻��ϴ� �޽���
	2. WM_LBUTTONDOWN: ���콺�� ���� ��ư ������� �߻�
	3. WM_CHAR: Ű����κ��� ���ڰ� �Էµ� �� �߻�
	4. WM_PAINT: ȭ���� �ٽ� �׷��� �� �ʿ䰡 ������ �߻�
	5. WM_DESTROY: �����찡 �޸𸮿��� �ı��� �� �߻�
	6. WN_CREATE: �����찡 ó����������� �߻� -> **���ϵ� �����츦 ���鶧 ���ϰ���
	*/
	switch (iMessage) {
	case WM_PAINT:	// WM_PAINT: �������� ���𰡸� �׸��� ����ϴ� �޽���
		// (���� ���� ����?�����찡 ���� ��������ų� �����϶� �ü���� ������ ������ش�)
		// -> ���α׷��� ó�� �����Ǹ� ������ ���������.
	{
		PAINTSTRUCT ps; // ������ Ŭ���̾�Ʈ ����(������ȭ��)�� �׸��� ������ ������ �ִ� ����ü
		HDC hdc = BeginPaint(hWnd, &ps); // BeginPaint: device Context ����(hdc�� ����̽����ؽ�Ʈ�� �ڵ鰪)
		// x��ǥ 100, y��ǥ 100, lstrlen(text�� ���̸�ŭ ���)
		TextOut(hdc, 100, 100, text, lstrlen(text)); // ���ڿ� ������
		EndPaint(hWnd, &ps); // EndPaint: ��
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	// ���α׷��Ӵ� �� �ʿ��� �޼����� ���ؼ��� ó���Ѵ�.
	//  ������ �⺻���� �޽��� ó���� DefWindowProc�Լ��� ����Ѵ�.
	// ex) Ÿ��Ʋ ���� �ּ�ȭ, �ִ�ȭ, ������ ũ�� ���� 
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

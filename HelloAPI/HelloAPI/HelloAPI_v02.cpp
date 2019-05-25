#include <windows.h>
/*
2강. 차일드 윈도우 생성
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// 메인 윈도우 프로시져
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); //차일드 윈도우 프로시져

HINSTANCE g_hInst; // 차일드 윈도우에서 쓰기 위한 전역변수
LPCTSTR lpszClass = L"HelloAPI";	// 메인윈도우의 이름
LPCTSTR ChildClassName = L"ChildWin";	// 차일드윈도우의 이름

// 윈도우 클래스 생성함수
int APIENTRY WinMain(HINSTANCE hInstance,	// 애플리케이션의 인스턴스 핸들
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd;	// 메인 윈도우 핸들?
	MSG Message;
	WNDCLASS WndClass;	// 윈도우 클래스 한번만 선언하고 그 이후에 등록은 여러번 가능
	g_hInst = hInstance;	// 전역 변수 

	// 메인 윈도우에 대한 정보 설정
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

	/******************* 차일드 윈도우 **********************/
	WndClass.lpfnWndProc = ChildWndProc;      //차일드 윈도우 프로시저
	WndClass.lpszClassName = ChildClassName; //차일드 윈도우 클래스이름
	RegisterClass(&WndClass);	// 등록만 해주고 show는 메인 윈도우 프로시져에서

	// 메인 윈도우 CreateWindow
	hWnd = CreateWindow(lpszClass,			//윈도우클래스 이름
		L"윈도우 프로그래밍",			    //윈도우타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
		200, 200,							//윈도우가 보일때 X Y좌표
		600, 600,							//윈도우의 폭과 높이				
		(HWND)NULL,							//부모윈도우 핸들
		(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
		hInstance,							//인스턴스핸들
		NULL);								//여분의 데이터

	ShowWindow(hWnd, nCmdShow);

	// 계속 보여주기
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

// 메인 윈도우 프로시져
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
	/*
	1. wParam: WM_COMMAND의 이벤트 정보
		상위 2byte: 어떤 종류의 메시지인지 표시해주는 내용(ex BN_CLICK)
		하위 2byte: 컨트롤의 ID(등록해줄때 사용하는 번호 ex 2000)
	2. lParam: 윈도우 핸들

	-> HIWORD : get wParam's high word
	-> LOWORD : get wParam's low word
	*/
	
{
	LPCTSTR text = L"메인윈도우 생성";
	switch (iMessage) {
	case WM_PAINT:	// 윈도우가 생성되거나 변경되거나 이동될때 만들어지는 이벤트(새로 그려야하기 때문에)
	{
		PAINTSTRUCT ps;	
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, text, lstrlen(text));	// 텍스트 출력
		EndPaint(hWnd, &ps);
		return 0;
	}
	case WM_CREATE:	// 윈도우가 생성될 때 만들어지는 이벤트( 생성할 때 차일드 윈도우를 createWindow) 
	{
		HWND hChildWnd = CreateWindow(
			ChildClassName,     		// 차일드 윈도우 클래스 이름 
			L"차일드 윈도우",            	// 윈도우 타이틀 
			WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 

			// x좌표, y좌표는 메인 윈도우의 client 영역의 왼쪽위 꼭짓점을 기준으로!
			150,       		// 윈도우 보일 때 x 좌표 
			150,       		// 윈도우 보일 때 y 좌표 
			260,       		// 윈도우 폭
			200,       		// 윈도우 높이
			hWnd,         		// 부모 윈도우
			(HMENU)1000,        	// 차일드 윈도우ID 
			g_hInst,           		// 인스턴스 핸들 (전역변수)
			(LPVOID)NULL);      	// 여분의 데이터

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
// 차일드 윈도우 프로시져
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"차일드 윈도우생성";
	switch (message)
	{
	case WM_PAINT:	
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 10, 10, text, lstrlen(text));	//텍스트 출력
		EndPaint(hWnd, &ps);
		return 0;
	}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
#include <windows.h>
/*
*****큰 틀******
WndMain {
	1. 윈도우클래스 선언(WndClass) 
	2. 윈도우클래스에 윈도우의 속성을 지정 (윈도우클래스는 구조체)
	3. 등록(OS에게 요청)
	4. 생성(윈도우 객체의 속성을 지정)
	5. 보여주기
	6. 무한루프
}
7. WinProc - 윈도우 프로시져(콜백함수)
*/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";

// 메인 윈도우를 만들어준다
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	// 윈도우 클래스 선언
	// 윈도우 클래스란? 특정 윈도우가 공통적으로 가지는 속성들의 집합
	// 윈도우는 반드시 하나의 윈도우 클래스에서 만들어진다.
	// -> 윈도우 모양이 다르다? 다른 클래스로 만들어졌다. ex) 버튼, 콤보박스
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// 윈도우 클래스 구조체의 속성들(여러가지 자료들로 구성된 구조체)
	WndClass.cbClsExtra = 0;	// 예약영역
	WndClass.cbWndExtra = 0;	// 예약영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 윈도우의 배경색을 칠한 브러쉬 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_WAIT);	// 마우스 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 아이콘 지정
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;	// 윈도우의 메시지 처리 함수 이름(WndProc가 일반적인 이름)
	WndClass.lpszClassName = lpszClass;	// 윈도우 클래스 이름(문자열)
	WndClass.lpszMenuName = NULL;	// 프로그램이 사용할 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW;   // 윈도우스타일
	// 메인윈도우 등록
	RegisterClass(&WndClass);

	// 메인윈도우 생성 (눈에 보이지 않음)
	hWnd = CreateWindow(lpszClass,			// 윈도우클래스 이름
		L"윈도우 프로그래밍",			    // 윈도우타이틀
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // 윈도우스타일
		200, 200,							// 윈도우가 보일때 X Y좌표
		600, 600,							// 윈도우의 폭과 높이				
		(HWND)NULL,							// 부모윈도우 핸들
		(HMENU)NULL,						// 윈도우가 가지는 메뉴핸들
		hInstance,							// 인스턴스핸들
		NULL);								// 여분의 데이터

	// 메인윈도우 보여줌 (눈에 보이게)
	ShowWindow(hWnd, nCmdShow);

	// 메시지 루프: 그대로 두면 사라지기 때문에 무한루프를 돌려서 계속 돌아가게
	// WM_QUIT인 경우에만(X버튼 눌렀을 때) false를 리턴하여 메시지 루프 종료
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);	// 번역
		DispatchMessage(&Message);	// OS로 배달 -> OS가 적당한 윈도우 프로시저를 호출하고 그 후에 윈도우 프로시저가 처리한다.
	}
	return Message.wParam;
}

// CallBack 함수 = 윈도우 프로시저
// OS가 이벤트를 감지하고 메세지를 이 함수로 보내주면
// 각 메세지(이벤트)마다의 처리를 담당한다
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성";
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

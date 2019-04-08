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

// 콜백함수로써 WndProc을 사용할거라는 ProtoType을 선언해준다. 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Child Window 관련
HINSTANCE g_hInst;

// 문자열을 저장할 수 있는 String변수(LPCTSTR)
LPCTSTR lpszClass = L"HelloAPI"; // L은 유니코드 사용 

// 메인 윈도우를 만들어준다
/*
1. hInstance: 애플리케이션의 현재 인스턴스핸들
2. hPrebInstance: 애플리케이션의 이전 인스턴스의 핸들
3. lpCmdLine: 커맨드라인의 인자값을 받는 포인터
4. nCmdShow: 윈도우가 화면상에 보여질때 어떤상태로 보여지는지 결정(showWindow의 매개변수로 사용)
*/
int APIENTRY WinMain(
	HINSTANCE hInstance,	 // 인스턴스 핸들 - 프로그램의 이름표(주소:포인터) -사용하는 메모리주소
	HINSTANCE hPrevInstance, // 인스턴스 핸들
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd; // 윈도우 핸들(운영체제가 윈도우를 찾을때 주소 포인터값)
	MSG Message; // 메세지타입
	// 윈도우 클래스 선언
	// 윈도우 클래스란? 특정 윈도우가 공통적으로 가지는 속성들의 집합
	// 윈도우는 반드시 하나의 윈도우 클래스에서 만들어진다.
	// -> 윈도우 모양이 다르다? 다른 클래스로 만들어졌다. ex) 버튼, 콤보박스
	WNDCLASS WndClass;
	g_hInst = hInstance;

	// 윈도우 클래스 구조체의 속성들(여러가지 자료들로 구성된 구조체) -> 윈도우 모습이 결정됨
	WndClass.cbClsExtra = 0;	// 예약영역(default:0)
	WndClass.cbWndExtra = 0;	// 예약영역(default:0)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 윈도우의 배경색을 칠한 브러쉬 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_WAIT);	// 마우스 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 아이콘 지정
	WndClass.hInstance = hInstance; // 이 윈도우의 클래스의 인스턴스 핸들
	WndClass.lpfnWndProc = (WNDPROC)WndProc;	// ***필수지정***윈도우의 메시지 처리 함수 이름(WndProc가 일반적인 이름, 지금 사용하는 Callback함수가 WinProc)
	WndClass.lpszClassName = lpszClass;	// ***필수지정***윈도우 클래스 이름(문자열) -> createWindow할때 이름으로 가져옴
	WndClass.lpszMenuName = NULL;	// 프로그램이 사용할 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW;   // 윈도우스타일(Horizon/Vertical)

	// 메인윈도우 등록 (속성값을 넣어준 윈도우 클래스를 등록)
	RegisterClass(&WndClass);

	// 메인윈도우 생성 (눈에 보이지 않음) -> createWindow가 리턴하는값(주소값)
	hWnd = CreateWindow(lpszClass,			// 윈도우클래스 이름(만들었던 윈도우클래스이름)
		L"윈도우 프로그래밍",			    // 윈도우타이틀(타이틀바에 나타나는 문자열)
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,   // 윈도우스타일(중첩윈도우(WS_OVERLAPPEDWINDOW)-WS_MINIMIZEBOX, WS_MAXIZIXEBOX, WS_SYSMENU, WS_CAPTION, WS_THICKFRAME)
		200, 200,							// 윈도우가 보일때 X,Y좌표(맨왼쪽상단끝 기준)
		600, 600,							// 윈도우의 폭과 높이				
		(HWND)NULL,							// 부모윈도우 핸들
		(HMENU)NULL,						// 윈도우가 가지는 메뉴핸들
		hInstance,							// 인스턴스핸들
		NULL);								// 여분의 데이터

	// 메인윈도우 보여줌 (눈에 보이게)
	ShowWindow(hWnd, nCmdShow);  
	// hWnd: createWindow의 리턴값 
	// nCmdShow: WinMain의 네번째 매개변수

	// while문을 통해서 계속 보여주게 유지(메세지큐에서 가져온다)
	// 메시지 루프: 그대로 두면 사라지기 때문에 무한루프를 돌려서 계속 돌아가게
	// WM_QUIT인 경우에만(X버튼 눌렀을 때) false를 리턴하여 메시지 루프 종료
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);	// 번역(알아들을수있게 번역)- 키보드를 눌렀다 떼었을 때 이를 WM_CHAR 메시지로 변환
		DispatchMessage(&Message);	// OS가 배달 -> OS가 적당한 윈도우 프로시저를 호출하고 그 후에 윈도우 프로시저가 처리한다.
		// **정리**-> 메시지를 운영체제로 전달하여 운영체제가 윈도우 프로시저를 호출하도록 함
	}
	return Message.wParam;
}

// CallBack 함수 = 윈도우 프로시저
// OS가 이벤트를 감지하고 메세지를 이 함수로 보내주면
// 각 메세지(이벤트)마다의 처리를 담당한다
LRESULT CALLBACK WndProc(HWND hWnd,   // hWnd: 윈도우핸들(createWindow할때 리턴값), 모든 각각의 하나의 윈도우핸들에는 각각의 하나의 윈도우프로시저가 따라붙는다
	UINT iMessage, // 가지고 온 메시지
	WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"메인윈도우 생성"; // 문자열을 담을 수 있는 String 변수(L은 유니코드문자)
	/*
	1. WM_QUIT: 프로그램을 끝낼 때 발생하는 메시지
	2. WM_LBUTTONDOWN: 마우스의 좌측 버튼 누를경우 발생
	3. WM_CHAR: 키보드로부터 문자가 입력될 때 발생
	4. WM_PAINT: 화면을 다시 그려야 할 필요가 있을때 발생
	5. WM_DESTROY: 윈도우가 메모리에서 파괴될 때 발생
	6. WN_CREATE: 윈도우가 처음만들어질때 발생 -> **차일드 윈도우를 만들때 쓰일것임
	*/
	switch (iMessage) {
	case WM_PAINT:	// WM_PAINT: 윈도우의 무언가를 그릴때 사용하는 메시지
		// (누가 언제 생성?윈도우가 새로 만들어지거나 움직일때 운영체제가 스스로 만들어준다)
		// -> 프로그램이 처음 생성되면 무조건 만들어진다.
	{
		PAINTSTRUCT ps; // 윈도우 클라이언트 영역(윈도우화면)에 그리는 정보를 가지고 있는 구조체
		HDC hdc = BeginPaint(hWnd, &ps); // BeginPaint: device Context 마련(hdc는 디바이스컨텍스트의 핸들값)
		// x좌표 100, y좌표 100, lstrlen(text의 길이만큼 출력)
		TextOut(hdc, 100, 100, text, lstrlen(text)); // 문자열 보여줌
		EndPaint(hWnd, &ps); // EndPaint: 끝
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	// 프로그래머는 꼭 필요한 메세지에 대해서만 처리한다.
	//  나머지 기본적인 메시지 처리는 DefWindowProc함수가 담당한다.
	// ex) 타이틀 바의 최소화, 최대화, 윈도우 크기 변경 
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

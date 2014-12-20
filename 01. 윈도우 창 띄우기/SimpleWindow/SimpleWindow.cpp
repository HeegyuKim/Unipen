
#include <Windows.h>


//
// 메세지 프로시저 함수
// 이벤트가 발생했을 때 이 함수가 호출된다.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg)
	{
	//
	// 윈도우가 파괴되었을 때
	case WM_DESTROY:
		// 나가라!
		PostQuitMessage(0);
		return 0;

	// 처리되지 않은 메시지는
	default:
		// 기본 처리 함수를 이용한다.
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{
	//
	// 윈도우 클래스를 등록한다.
	WNDCLASS wc = {0};
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst; 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	
	RegisterClass(&wc);

	HWND hwnd = CreateWindow (
		wc.lpszClassName,	// 창 클래스
		L"SimpleWindow",	// 창 제목
		WS_OVERLAPPEDWINDOW,// 창 스타일
		CW_USEDEFAULT,		// 화면에서의 X 좌표
		CW_USEDEFAULT,		// 화면에서의 Y 좌표
		CW_USEDEFAULT,		// 가로 크기
		CW_USEDEFAULT,		// 세로 크기
		0,					// 부모 윈도우
		0,					// 메뉴
		hinst,				// 인스턴스 핸들
		0					// 초기 전달 값
		);
	//
	// 윈도우 창을 띄운다.
	ShowWindow(hwnd, SW_SHOW);

	//
	// 메시지 루프를 돈다.
	MSG msg = {0};
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

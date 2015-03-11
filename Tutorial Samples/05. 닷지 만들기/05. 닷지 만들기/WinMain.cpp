
#include "DodgeGame.h"
#include "resource.h"
using namespace std;



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
	srand(timeGetTime());

	const int width = 800, 
		height = 600;
	HWND hwnd;
	DodgeGame *game = nullptr;

	//
	// 윈도우 클래스를 등록한다.(hbrBackground 사라짐)
	WNDCLASS wc = {0};
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1));
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// 창 클래스
		L"닷찌!",	// 창 제목
		style,	// 창 스타일
		CW_USEDEFAULT,		// 화면에서의 X 좌표
		CW_USEDEFAULT,		// 화면에서의 Y 좌표
		rect.right - rect.left,	// 가로 크기
		rect.bottom - rect.top,	// 세로 크기
		0,				// 부모 윈도우
		0,				// 메뉴
		hinst,				// 인스턴스 핸들
		0				// 초기 전달값
		);
	try
	{
		game = new DodgeGame(hwnd);
		ShowWindow(hwnd, SW_SHOW);

		DWORD lastTime = timeGetTime();

		// 메시지 루프를 돈다.
		MSG msg = {0};
		while(msg.message != WM_QUIT)
		{
			if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				DWORD curr = timeGetTime();
				DWORD delta = curr - lastTime;

				if(delta >= 16)
				{
					lastTime = curr;
					game->Update(delta / 1000.0f);
					game->Draw();
				}
				else
					Sleep(16 - delta);
			}
		}
	}
	catch(exception& e)
	{
		MessageBoxA(hwnd, e.what(), "에러가 발생했습니다.", MB_ICONERROR);
	}

	if(game)
	{
		delete game;
		game = nullptr;
	}

	return 0;
}

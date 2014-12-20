
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// 팩토리
ID2D1HwndRenderTarget *rt = 0;	// 윈도우 렌더타겟
 
// 화면을 그릴 때 호출되는 함수
void OnDraw()
{
}
 
// 리소스들을 생성하는 함수
bool Setup()
{
	return true;
}
 
// 리소스들을 제거하는 함수
void CleanUp()
{
	d2d::SafeRelease(rt);
	d2d::SafeRelease(factory2d);
}
 
//
// 메세지 프로시저 함수
// 이벤트가 발생했을 때 이 함수가 호출된다.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg)
	{
	// 윈도우가 그려질 때
	case WM_PAINT:
		OnDraw();
		return 0;
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
	// 윈도우 클래스를 등록한다.(hbrBackground 사라짐)
	WNDCLASS wc = {0};
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// 창 클래스
		L"Custom Direct2D Window",	// 창 제목
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
 
	// 그리기 준비
	if(FAILED(d2d::Initialize(hwnd, &factory2d, &rt)) 
		|| !Setup())
	{
		// 실패할 경우 에러 메세지
		MessageBox(0, L"Setup-Failed", L"Error", MB_ICONERROR);
	}
	else 
	{
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
	}
	
	// 청소
	CleanUp();
	return 0;
}


#include <Windows.h>
#include "d2dutils.h"

#pragma comment(lib, "winmm.lib")
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// 팩토리
ID2D1HwndRenderTarget *rt = 0;	// 윈도우 렌더타겟
ID2D1SolidColorBrush *brush = 0;

float x = 400, y = 300;

// 화면을 그릴 때 호출되는 함수
void OnDraw()
{
	rt->BeginDraw();
	rt->Clear(D2D1::ColorF(D2D1::ColorF::White));

	rt->DrawEllipse (
		D2D1::Ellipse(D2D1::Point2F(x, y),
					25,
					25
					),
		brush,
		3.5f);

	rt->EndDraw();
}

void OnUpdate(float delta)
{
	float speed = 500.0f;

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		x -= speed * delta;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		x += speed * delta;
	if(GetAsyncKeyState(VK_UP) & 0x8000)
		y -= speed * delta;
	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		y += speed * delta;

}
 
// 리소스들을 생성하는 함수
bool Setup()
{
	rt->CreateSolidColorBrush (
		D2D1::ColorF(D2D1::ColorF::DeepSkyBlue),
		&brush);

	return true;
}
 
// 리소스들을 제거하는 함수
void CleanUp()
{
	d2d::SafeRelease(brush);
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
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// 창 클래스
		L"FPS 제어",	// 창 제목
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
 
		// 마지막으로 갱신한 시간을 담은 변수입니다.
		DWORD lastTime = timeGetTime();

		//
		// 메시지 루프를 돈다.
		MSG msg = {0};
		while(msg.message != WM_QUIT)
		{
			// 처리할 메세지가 있으면 처리하고
			if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// 그렇지 않다면 FPS를 제어해서 갱신과 그리기를 한다
			else
			{
				// 현재 시간을 얻어온 다음
				DWORD currTime = timeGetTime();

				// 마지막으로 갱신한 시간과의 차이(delta)를 계산한다.
				DWORD delta = currTime - lastTime;

				// 차이가 16ms이상이면 갱신합니다.
				if(delta >= 16)
				{
					// (중요)마지막 갱신 시간을 저장해야 합니다.
					lastTime = currTime;

					OnUpdate(delta / 1000.0f);
					OnDraw();
				}
				// 그렇지 않을 경우 남은 시간은 Sleep()함수로 멈춰 줍니다.
				else
					Sleep(16 - delta);
			}
		}
	}
	
	// 청소
	CleanUp();
	return 0;
}

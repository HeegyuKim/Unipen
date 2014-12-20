
#include <Windows.h>

// Direct2D 헤더 포함
#include <d2d1.h>
#include <d2d1helper.h>

// Direct2D 정적 라이브러리 링크
#pragma comment(lib, "d2d1.lib")


ID2D1Factory *factory = nullptr;
ID2D1HwndRenderTarget *target = nullptr;

DWORD width = 800, 
	height = 600;

//
// 메세지 프로시저 함수
// 이벤트가 발생했을 때 이 함수가 호출된다.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	
	switch(msg)
	{
	// 윈도우를 생성했을 때 WM_CREATE 이벤트가 전달된다.
	case WM_CREATE:
		{
			HRESULT hr = S_OK;

			// Direct2D 팩토리 생성
			hr = D2D1CreateFactory (
				D2D1_FACTORY_TYPE_SINGLE_THREADED,
				&factory );

			if(SUCCEEDED(hr))
			{
				// 윈도우 렌더타깃 생성
				hr = factory->CreateHwndRenderTarget (
						D2D1::RenderTargetProperties(),
						D2D1::HwndRenderTargetProperties (
							hwnd,
							D2D1::SizeU (
								width,
								height
								)
							),
						&target);
			}

			// 만약 실패했다면
			if(FAILED(hr))
			{
				// 에러 메세지를 띄웁니다.
				MessageBox(hwnd, L"Direct2D 초기화에 실패했습니다.", L"실패", MB_ICONERROR);

				// 그리고 애써 만든 윈도우를 부숴버립니다...^^;
				DestroyWindow(hwnd);
			}
		}
		break;

	// 윈도우에 그릴 때 WM_PAINT 메세지가 전달된다.
	case WM_PAINT:
		{
			// 렌더타겟에 그릴 때는 반드시 BeginDraw() 메서드와
			// EndDraw() 메서드의 호출 사이여야한다.

			target->BeginDraw();

			// 색상 생성, 빨간색(R = 1, G = 0, B = 0, Alpha = 1)
			D2D1::ColorF color(1, 0, 0, 1);
			target->Clear(color);

			target->EndDraw();
		}
		break;
	//
	// 윈도우가 파괴되었을 때
	case WM_DESTROY:
		// 만든 Direct2D 객체를 제거합니다.
		if(target)
		{
			target->Release();
			target = nullptr;
		}
		if(factory)
		{
			factory->Release();
			factory = nullptr;
		}

		// 나가라!
		PostQuitMessage(0);
		return 0;

	}
		
	return DefWindowProc(hwnd, msg, wp, lp);
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
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);

	DWORD width = 800,
		height = 600,
		style = WS_OVERLAPPEDWINDOW;
	RECT client = {
		0, 0, width, height
	};
	AdjustWindowRect(&client, style, false);

	HWND hwnd = CreateWindow (
		wc.lpszClassName,		// 창 클래스
		L"ClearWindow",	// 창 제목
		WS_OVERLAPPEDWINDOW,	// 창 스타일
		CW_USEDEFAULT,		// 화면에서의 X 좌표
		CW_USEDEFAULT,		// 화면에서의 Y 좌표
		client.right - client.left,		// 가로 크기
		client.bottom- client.top,		// 세로 크기
		0,				// 부모 윈도우
		0,				// 메뉴
		hinst,				// 인스턴스 핸들
		0				// 초기 전달 값
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

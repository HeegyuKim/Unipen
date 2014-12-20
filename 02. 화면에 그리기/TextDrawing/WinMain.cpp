
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// 팩토리
ID2D1HwndRenderTarget *rt = 0;	// 윈도우 렌더타겟
 
IDWriteFactory *factoryWrite = 0;
IDWriteTextFormat *formatGoongSeo = 0;
ID2D1SolidColorBrush *solidBrush = 0;
 
// 화면을 그릴 때 호출되는 함수
void OnDraw()
{
	rt->BeginDraw();
	rt->Clear(D2D1::ColorF(1, 1, 1, 1));
 
	const wchar_t *str = L"Korean Fanstasy\n미눅+喜奎!";
	rt->DrawTextW(str, wcslen(str),
		formatGoongSeo, D2D1::RectF (
			0, 0, width, height
		), solidBrush);
 
	rt->EndDraw();
}
 
// 리소스들을 생성하는 함수
bool Setup()
{
	rt->CreateSolidColorBrush (
			D2D1::ColorF(0, 0, 0),
			&solidBrush );
 
	DWriteCreateFactory (
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&factoryWrite);
 
 
	factoryWrite->CreateTextFormat (
				L"궁서",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				32.0f,
				L"ko-KR",
				&formatGoongSeo );
 
	return true;
}
 
// 리소스들을 제거하는 함수
void CleanUp()
{
	d2d::SafeRelease(formatGoongSeo);
	d2d::SafeRelease(factoryWrite);
	d2d::SafeRelease(solidBrush);
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
		L"문자 그리기",	// 창 제목
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

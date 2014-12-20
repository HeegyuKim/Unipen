
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// 팩토리
ID2D1HwndRenderTarget *rt = 0;	// 윈도우 렌더타겟
 
// 단색 브러시
ID2D1SolidColorBrush *solidBrush = 0;

// 도형 객체 3개
ID2D1Geometry *geom[3];

// 색상 3개
D2D1::ColorF color[] = {
	D2D1::ColorF(D2D1::ColorF::IndianRed),
	D2D1::ColorF(D2D1::ColorF::YellowGreen),
	D2D1::ColorF(D2D1::ColorF::Firebrick)
};

// 변환행렬 3개
D2D1::Matrix3x2F matrices[3];

// 화면을 그릴 때 호출되는 함수
void OnDraw()
{
	rt->BeginDraw();
	// 하얀색으로 지우기
	rt->Clear(D2D1::ColorF(1, 1, 1, 1));

	// 변환 행렬 초기화
	rt->SetTransform(D2D1::Matrix3x2F::Identity());

	// 원래 상태로 그리기
	for(int i = 0; i < 3; ++i)
	{
		// 브러시 색상 변경
		solidBrush->SetColor(color[i]);
		rt->DrawGeometry(geom[i], solidBrush);
	}

	for(int i = 0; i < 3; ++i)
	{
		// 브러시 색상 변경
		solidBrush->SetColor(color[i]);

		// 변환 지정
		rt->SetTransform(matrices[i]);

		// 도형 그리기!
		// 굵기는 4.5
		rt->DrawGeometry(geom[i], solidBrush, 4.5f);
	}
 
	rt->EndDraw();
}
 
// 리소스들을 생성하는 함수
bool Setup()
{
	rt->CreateSolidColorBrush (D2D1::ColorF(0, 0, 1), &solidBrush);
 
	ID2D1RectangleGeometry *rect;
	factory2d->CreateRectangleGeometry (
		D2D1::RectF(30, 30, 500, 150),
		&rect );
	
	ID2D1RoundedRectangleGeometry *roundedRect;
	factory2d->CreateRoundedRectangleGeometry (
		D2D1::RoundedRect (
			D2D1::RectF(100, 100, 200, 200),
			20,
			20 ),
		&roundedRect );
	
	ID2D1EllipseGeometry *ellipse;
	factory2d->CreateEllipseGeometry (
		D2D1::Ellipse (
			D2D1::Point2F(300, 300),
			100, 50),
		&ellipse);

	geom[0] = rect;
	geom[1] = roundedRect;
	geom[2] = ellipse;
 

	matrices[0] = D2D1::Matrix3x2F::Rotation(45);
	matrices[1] = D2D1::Matrix3x2F::Rotation(45)
		* D2D1::Matrix3x2F::Translation(150, 100);
	matrices[2] = D2D1::Matrix3x2F::Scale(1.5f, 1.5f);

	return true;
}
 
// 리소스들을 제거하는 함수
void CleanUp()
{
	// 도형들 제거하기
	for(int i = 0; i < 3; ++i)
		d2d::SafeRelease(geom[i]);

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
	wc.hCursor = LoadCursor(hinst, IDC_ARROW);
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// 창 클래스
		L"변환하기",	// 창 제목
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

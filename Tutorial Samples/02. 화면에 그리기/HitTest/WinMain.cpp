
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;

ID2D1Factory *factory2d = 0;		// 팩토리
ID2D1HwndRenderTarget *rt = 0;	// 윈도우 렌더타겟

IDWriteFactory *factoryWrite = 0;
IDWriteTextFormat *formatGoongSeo = 0;	// 문자 형식
IDWriteTextLayout *textLayout = 0;		// 문자 레이아웃
ID2D1SolidColorBrush *solidBrush = 0;	

// 텍스트의 범위
DWRITE_TEXT_RANGE range = {0};

// 화면을 그릴 때 호출되는 함수
void OnDraw()
{
	rt->BeginDraw();
	rt->Clear(D2D1::ColorF(1, 1, 1, 1));

	// 마우스 좌표를 받아와서
	// 윈도우에 대한 상대 위치로 바꾼다.
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(hwnd, &cursor);

	DWRITE_HIT_TEST_METRICS metrics = {0};
	BOOL isTrailingHit, isInside;

	// HitTestPoint() 메서드로 적중 검사를 수행한다.
	// 문자 레이아웃을 (200, 100)에 그리기 때문에
	// X좌표에 200을 빼고 Y좌표에 100을 뺀다.
	HRESULT hr = textLayout->HitTestPoint (
			cursor.x - 200,	// X 좌표
			cursor.y - 100,	// Y 좌표
			&isTrailingHit,	// 왼쪽 혹은 오른쪽에 붙어 있는가
			&isInside,		// 영역 안인가?
			&metrics		// 정보들
			);
	
	// 기존의 밑줄은 없앤다
	textLayout->SetUnderline(false, range);

	/*
	isTrailingHit는 X좌표가 그려지는 범위 내에 있을 때,
	가장 가까운 줄에 글자가 존재하는지 여부를 의미하며,
	isInside는 점의 위치가 문자 사이에 있는지를 나타내는 값이다
	설명이 어렵다면 아래 조건문을 바꿔 보면서 결과를 확인해
	보길 바란다.
	*/
	// 맞았네
	if(SUCCEEDED(hr) && isTrailingHit && isInside)
	{
		// 적중한 문자의 시작 위치와 길이를 저장하고
		range.startPosition = metrics.textPosition;
		range.length = metrics.length;

		// 적중한 문자에 밑줄을 친다.
		textLayout->SetUnderline(true, range);

		const wchar_t* success = L"성공!";
		rt->DrawText(success, wcslen(success), formatGoongSeo,
			D2D1::RectF(0, 0, 50, 0), solidBrush );
	}

	// (200, 100)위치에 문자 레이아웃을 그린다.
	rt->DrawTextLayout(
		D2D1::Point2F(200, 100),
		textLayout,
		solidBrush
		);


	rt->EndDraw();
}

// 문자의 범위를 나타내는 DWRITE_TEXT_RANGE 객체를 생성한다.
DWRITE_TEXT_RANGE MakeRange(int start, int length)
{
	DWRITE_TEXT_RANGE range = {0};
	range.startPosition = start;	// 시작 위치(0 부터)
	range.length = length;			// 문자 개수
	return range;
}

// 리소스들을 생성하는 함수
bool Setup()
{
	// 브러시 생성
	rt->CreateSolidColorBrush (
			D2D1::ColorF(0, 0, 0),
			&solidBrush );

	// 팩토리 생성
	DWriteCreateFactory (
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&factoryWrite);

	// 글꼴 형식 생성
	factoryWrite->CreateTextFormat (
				L"궁서",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				32.0f,
				L"ko-KR",
				&formatGoongSeo );

	// 그릴 문자열
	const wchar_t *str = L"Korean Fanstasy\n"
				L"미눅미눅+喜奎!\n"
				L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// 텍스트 레이아웃 생성
	factoryWrite->CreateTextLayout (
				str,			// 문자열
				wcslen(str),	// 문자열의 길이
				formatGoongSeo,	// 글꼴 형식
				400,			// 최대 가로 크기
				400,			// 최대 세로 크기
				&textLayout);	// 생성된 글꼴 레이아웃

	// 단락 정렬 설정(수직 정렬)
	textLayout->SetParagraphAlignment(
DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// 문자 정렬 설정(수평 정렬)
	textLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

	// 0번째부터 6개의 문자인 'Korean' 을 이탤릭체로
	textLayout->SetFontStyle(
		DWRITE_FONT_STYLE_ITALIC, 
		MakeRange(0,6)); 
	
	// 앞의 '미눅'을 두껍게
	textLayout->SetFontWeight(
		DWRITE_FONT_WEIGHT_HEAVY, 
		MakeRange(16,2)); 
	
	// 뒤의 '미눅'을 얇게
	textLayout->SetFontWeight(
		DWRITE_FONT_WEIGHT_THIN, 
		MakeRange(18,2)); 

	// 뒤의 '미눅'에 밑줄
	textLayout->SetUnderline(
		DWRITE_FONT_WEIGHT_THIN, 
		MakeRange(18,2)); 

	return true;
}

// 리소스들을 제거하는 함수
void CleanUp()
{
	d2d::SafeRelease(textLayout);
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
		L"적중 검사하기",	// 창 제목
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

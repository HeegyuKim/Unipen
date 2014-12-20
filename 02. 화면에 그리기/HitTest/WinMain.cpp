
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;

ID2D1Factory *factory2d = 0;		// ���丮
ID2D1HwndRenderTarget *rt = 0;	// ������ ����Ÿ��

IDWriteFactory *factoryWrite = 0;
IDWriteTextFormat *formatGoongSeo = 0;	// ���� ����
IDWriteTextLayout *textLayout = 0;		// ���� ���̾ƿ�
ID2D1SolidColorBrush *solidBrush = 0;	

// �ؽ�Ʈ�� ����
DWRITE_TEXT_RANGE range = {0};

// ȭ���� �׸� �� ȣ��Ǵ� �Լ�
void OnDraw()
{
	rt->BeginDraw();
	rt->Clear(D2D1::ColorF(1, 1, 1, 1));

	// ���콺 ��ǥ�� �޾ƿͼ�
	// �����쿡 ���� ��� ��ġ�� �ٲ۴�.
	POINT cursor;
	GetCursorPos(&cursor);
	ScreenToClient(hwnd, &cursor);

	DWRITE_HIT_TEST_METRICS metrics = {0};
	BOOL isTrailingHit, isInside;

	// HitTestPoint() �޼���� ���� �˻縦 �����Ѵ�.
	// ���� ���̾ƿ��� (200, 100)�� �׸��� ������
	// X��ǥ�� 200�� ���� Y��ǥ�� 100�� ����.
	HRESULT hr = textLayout->HitTestPoint (
			cursor.x - 200,	// X ��ǥ
			cursor.y - 100,	// Y ��ǥ
			&isTrailingHit,	// ���� Ȥ�� �����ʿ� �پ� �ִ°�
			&isInside,		// ���� ���ΰ�?
			&metrics		// ������
			);
	
	// ������ ������ ���ش�
	textLayout->SetUnderline(false, range);

	/*
	isTrailingHit�� X��ǥ�� �׷����� ���� ���� ���� ��,
	���� ����� �ٿ� ���ڰ� �����ϴ��� ���θ� �ǹ��ϸ�,
	isInside�� ���� ��ġ�� ���� ���̿� �ִ����� ��Ÿ���� ���̴�
	������ ��ƴٸ� �Ʒ� ���ǹ��� �ٲ� ���鼭 ����� Ȯ����
	���� �ٶ���.
	*/
	// �¾ҳ�
	if(SUCCEEDED(hr) && isTrailingHit && isInside)
	{
		// ������ ������ ���� ��ġ�� ���̸� �����ϰ�
		range.startPosition = metrics.textPosition;
		range.length = metrics.length;

		// ������ ���ڿ� ������ ģ��.
		textLayout->SetUnderline(true, range);

		const wchar_t* success = L"����!";
		rt->DrawText(success, wcslen(success), formatGoongSeo,
			D2D1::RectF(0, 0, 50, 0), solidBrush );
	}

	// (200, 100)��ġ�� ���� ���̾ƿ��� �׸���.
	rt->DrawTextLayout(
		D2D1::Point2F(200, 100),
		textLayout,
		solidBrush
		);


	rt->EndDraw();
}

// ������ ������ ��Ÿ���� DWRITE_TEXT_RANGE ��ü�� �����Ѵ�.
DWRITE_TEXT_RANGE MakeRange(int start, int length)
{
	DWRITE_TEXT_RANGE range = {0};
	range.startPosition = start;	// ���� ��ġ(0 ����)
	range.length = length;			// ���� ����
	return range;
}

// ���ҽ����� �����ϴ� �Լ�
bool Setup()
{
	// �귯�� ����
	rt->CreateSolidColorBrush (
			D2D1::ColorF(0, 0, 0),
			&solidBrush );

	// ���丮 ����
	DWriteCreateFactory (
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&factoryWrite);

	// �۲� ���� ����
	factoryWrite->CreateTextFormat (
				L"�ü�",
				nullptr,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				32.0f,
				L"ko-KR",
				&formatGoongSeo );

	// �׸� ���ڿ�
	const wchar_t *str = L"Korean Fanstasy\n"
				L"�̴��̴�+��Х!\n"
				L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// �ؽ�Ʈ ���̾ƿ� ����
	factoryWrite->CreateTextLayout (
				str,			// ���ڿ�
				wcslen(str),	// ���ڿ��� ����
				formatGoongSeo,	// �۲� ����
				400,			// �ִ� ���� ũ��
				400,			// �ִ� ���� ũ��
				&textLayout);	// ������ �۲� ���̾ƿ�

	// �ܶ� ���� ����(���� ����)
	textLayout->SetParagraphAlignment(
DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	// ���� ���� ����(���� ����)
	textLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);

	// 0��°���� 6���� ������ 'Korean' �� ���Ÿ�ü��
	textLayout->SetFontStyle(
		DWRITE_FONT_STYLE_ITALIC, 
		MakeRange(0,6)); 
	
	// ���� '�̴�'�� �β���
	textLayout->SetFontWeight(
		DWRITE_FONT_WEIGHT_HEAVY, 
		MakeRange(16,2)); 
	
	// ���� '�̴�'�� ���
	textLayout->SetFontWeight(
		DWRITE_FONT_WEIGHT_THIN, 
		MakeRange(18,2)); 

	// ���� '�̴�'�� ����
	textLayout->SetUnderline(
		DWRITE_FONT_WEIGHT_THIN, 
		MakeRange(18,2)); 

	return true;
}

// ���ҽ����� �����ϴ� �Լ�
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
// �޼��� ���ν��� �Լ�
// �̺�Ʈ�� �߻����� �� �� �Լ��� ȣ��ȴ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg)
	{
	// �����찡 �׷��� ��
	case WM_PAINT:
		OnDraw();
		return 0;
	//
	// �����찡 �ı��Ǿ��� ��
	case WM_DESTROY:
		// ������!
		PostQuitMessage(0);
		return 0;
 
	// ó������ ���� �޽�����
	default:
		// �⺻ ó�� �Լ��� �̿��Ѵ�.
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}
 
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{
	//
	// ������ Ŭ������ ����Ѵ�.(hbrBackground �����)
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
		wc.lpszClassName,		// â Ŭ����
		L"���� �˻��ϱ�",	// â ����
		style,	// â ��Ÿ��
		CW_USEDEFAULT,		// ȭ�鿡���� X ��ǥ
		CW_USEDEFAULT,		// ȭ�鿡���� Y ��ǥ
		rect.right - rect.left,	// ���� ũ��
		rect.bottom - rect.top,	// ���� ũ��
		0,				// �θ� ������
		0,				// �޴�
		hinst,				// �ν��Ͻ� �ڵ�
		0				// �ʱ� ���ް�
		);
 
	// �׸��� �غ�
	if(FAILED(d2d::Initialize(hwnd, &factory2d, &rt)) 
		|| !Setup())
	{
		// ������ ��� ���� �޼���
		MessageBox(0, L"Setup-Failed", L"Error", MB_ICONERROR);
	}
	else 
	{
		//
		// ������ â�� ����.
		ShowWindow(hwnd, SW_SHOW);
 
		//
		// �޽��� ������ ����.
		MSG msg = {0};
		while(GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	// û��
	CleanUp();
	return 0;
}

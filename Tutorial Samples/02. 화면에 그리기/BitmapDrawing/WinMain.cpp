
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// ���丮
ID2D1HwndRenderTarget *rt = 0;	// ������ ����Ÿ��
IWICImagingFactory *wic = 0;
ID2D1Bitmap *bitmapFood = 0,
			*bitmapHeegyu = 0,
			*bitmapMinuk = 0;
 
void OnDraw()
{
	rt->BeginDraw();
	rt->Clear(D2D1::ColorF(1, 1, 1, 1));
 
	rt->DrawBitmap(
		bitmapFood, 
		D2D1::RectF(0, 0, 800, 300)
		);
	
	rt->DrawBitmap(
		bitmapHeegyu, 
		D2D1::RectF(600, 300, 800, 600),
		1, 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		);
 
	rt->DrawBitmap(
		bitmapMinuk, 
		D2D1::RectF(0, 300, 300, 600),
		1, 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR
		);
 
	rt->DrawBitmap(
		bitmapMinuk, 
		D2D1::RectF(300, 300, 600, 600),
		1, 
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
		);
 
 
	rt->EndDraw();
}
 
bool Setup()
{
	CoInitialize(0);
 
	CoCreateInstance (
		CLSID_WICImagingFactory,
		0,
		CLSCTX_INPROC_SERVER,
		__uuidof(IWICImagingFactory),
		(void**)&wic);
 
	d2d::LoadBitmap (
		L"food.jpg",
		wic,
		rt,
		&bitmapFood );
 
	d2d::LoadBitmap (
		L"heegyu.jpg",
		wic,
		rt,
		&bitmapHeegyu );
 
	d2d::LoadBitmap (
		L"minuk.jpg",
		wic,
		rt,
		&bitmapMinuk );
 
	return true;
}
 
void CleanUp()
{
	d2d::SafeRelease(bitmapFood);
	d2d::SafeRelease(bitmapHeegyu);
	d2d::SafeRelease(bitmapMinuk);
	d2d::SafeRelease(wic);
	d2d::SafeRelease(rt);
	d2d::SafeRelease(factory2d);
	CoUninitialize();
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
		L"��Ʈ�� �׸���",	// â ����
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

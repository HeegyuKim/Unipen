
#include <Windows.h>
#include "d2dutils.h"
 
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// ���丮
ID2D1HwndRenderTarget *rt = 0;	// ������ ����Ÿ��
 
// �ܻ� �귯��
ID2D1SolidColorBrush *solidBrush = 0;

// ���� ��ü 3��
ID2D1Geometry *geom[3];

// ���� 3��
D2D1::ColorF color[] = {
	D2D1::ColorF(D2D1::ColorF::IndianRed),
	D2D1::ColorF(D2D1::ColorF::YellowGreen),
	D2D1::ColorF(D2D1::ColorF::Firebrick)
};

// ��ȯ��� 3��
D2D1::Matrix3x2F matrices[3];

// ȭ���� �׸� �� ȣ��Ǵ� �Լ�
void OnDraw()
{
	rt->BeginDraw();
	// �Ͼ������ �����
	rt->Clear(D2D1::ColorF(1, 1, 1, 1));

	// ��ȯ ��� �ʱ�ȭ
	rt->SetTransform(D2D1::Matrix3x2F::Identity());

	// ���� ���·� �׸���
	for(int i = 0; i < 3; ++i)
	{
		// �귯�� ���� ����
		solidBrush->SetColor(color[i]);
		rt->DrawGeometry(geom[i], solidBrush);
	}

	for(int i = 0; i < 3; ++i)
	{
		// �귯�� ���� ����
		solidBrush->SetColor(color[i]);

		// ��ȯ ����
		rt->SetTransform(matrices[i]);

		// ���� �׸���!
		// ����� 4.5
		rt->DrawGeometry(geom[i], solidBrush, 4.5f);
	}
 
	rt->EndDraw();
}
 
// ���ҽ����� �����ϴ� �Լ�
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
 
// ���ҽ����� �����ϴ� �Լ�
void CleanUp()
{
	// ������ �����ϱ�
	for(int i = 0; i < 3; ++i)
		d2d::SafeRelease(geom[i]);

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
	wc.hCursor = LoadCursor(hinst, IDC_ARROW);
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// â Ŭ����
		L"��ȯ�ϱ�",	// â ����
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

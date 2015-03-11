
#include <Windows.h>
#include "d2dutils.h"

#pragma comment(lib, "winmm.lib")
 
int width = 800, 
	height = 600;
HWND hwnd;
ID2D1Factory *factory2d = 0;		// ���丮
ID2D1HwndRenderTarget *rt = 0;	// ������ ����Ÿ��
ID2D1SolidColorBrush *brush = 0;

float x = 400, y = 300;

// ȭ���� �׸� �� ȣ��Ǵ� �Լ�
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
 
// ���ҽ����� �����ϴ� �Լ�
bool Setup()
{
	rt->CreateSolidColorBrush (
		D2D1::ColorF(D2D1::ColorF::DeepSkyBlue),
		&brush);

	return true;
}
 
// ���ҽ����� �����ϴ� �Լ�
void CleanUp()
{
	d2d::SafeRelease(brush);
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
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// â Ŭ����
		L"FPS ����",	// â ����
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
 
		// ���������� ������ �ð��� ���� �����Դϴ�.
		DWORD lastTime = timeGetTime();

		//
		// �޽��� ������ ����.
		MSG msg = {0};
		while(msg.message != WM_QUIT)
		{
			// ó���� �޼����� ������ ó���ϰ�
			if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// �׷��� �ʴٸ� FPS�� �����ؼ� ���Ű� �׸��⸦ �Ѵ�
			else
			{
				// ���� �ð��� ���� ����
				DWORD currTime = timeGetTime();

				// ���������� ������ �ð����� ����(delta)�� ����Ѵ�.
				DWORD delta = currTime - lastTime;

				// ���̰� 16ms�̻��̸� �����մϴ�.
				if(delta >= 16)
				{
					// (�߿�)������ ���� �ð��� �����ؾ� �մϴ�.
					lastTime = currTime;

					OnUpdate(delta / 1000.0f);
					OnDraw();
				}
				// �׷��� ���� ��� ���� �ð��� Sleep()�Լ��� ���� �ݴϴ�.
				else
					Sleep(16 - delta);
			}
		}
	}
	
	// û��
	CleanUp();
	return 0;
}

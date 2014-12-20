
#include <Windows.h>

// Direct2D ��� ����
#include <d2d1.h>
#include <d2d1helper.h>

// Direct2D ���� ���̺귯�� ��ũ
#pragma comment(lib, "d2d1.lib")


ID2D1Factory *factory = nullptr;
ID2D1HwndRenderTarget *target = nullptr;

DWORD width = 800, 
	height = 600;

//
// �޼��� ���ν��� �Լ�
// �̺�Ʈ�� �߻����� �� �� �Լ��� ȣ��ȴ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	
	switch(msg)
	{
	// �����츦 �������� �� WM_CREATE �̺�Ʈ�� ���޵ȴ�.
	case WM_CREATE:
		{
			HRESULT hr = S_OK;

			// Direct2D ���丮 ����
			hr = D2D1CreateFactory (
				D2D1_FACTORY_TYPE_SINGLE_THREADED,
				&factory );

			if(SUCCEEDED(hr))
			{
				// ������ ����Ÿ�� ����
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

			// ���� �����ߴٸ�
			if(FAILED(hr))
			{
				// ���� �޼����� ���ϴ�.
				MessageBox(hwnd, L"Direct2D �ʱ�ȭ�� �����߽��ϴ�.", L"����", MB_ICONERROR);

				// �׸��� �ֽ� ���� �����츦 �ν������ϴ�...^^;
				DestroyWindow(hwnd);
			}
		}
		break;

	// �����쿡 �׸� �� WM_PAINT �޼����� ���޵ȴ�.
	case WM_PAINT:
		{
			// ����Ÿ�ٿ� �׸� ���� �ݵ�� BeginDraw() �޼����
			// EndDraw() �޼����� ȣ�� ���̿����Ѵ�.

			target->BeginDraw();

			// ���� ����, ������(R = 1, G = 0, B = 0, Alpha = 1)
			D2D1::ColorF color(1, 0, 0, 1);
			target->Clear(color);

			target->EndDraw();
		}
		break;
	//
	// �����찡 �ı��Ǿ��� ��
	case WM_DESTROY:
		// ���� Direct2D ��ü�� �����մϴ�.
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

		// ������!
		PostQuitMessage(0);
		return 0;

	}
		
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{
	//
	// ������ Ŭ������ ����Ѵ�.
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
		wc.lpszClassName,		// â Ŭ����
		L"ClearWindow",	// â ����
		WS_OVERLAPPEDWINDOW,	// â ��Ÿ��
		CW_USEDEFAULT,		// ȭ�鿡���� X ��ǥ
		CW_USEDEFAULT,		// ȭ�鿡���� Y ��ǥ
		client.right - client.left,		// ���� ũ��
		client.bottom- client.top,		// ���� ũ��
		0,				// �θ� ������
		0,				// �޴�
		hinst,				// �ν��Ͻ� �ڵ�
		0				// �ʱ� ���� ��
		);
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
	return 0;
}

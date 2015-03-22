
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d2d1helper.h>


ID3D11Device *device = nullptr;
ID3D11DeviceContext *context = nullptr;
IDXGISwapChain *swapChain = nullptr;
ID2D1RenderTarget *rt = nullptr;

template <typename T>
inline void SafeRelease(T &t)
{
	if (t)
	{
		t->Release();
		t = nullptr;
	}
}


bool Setup(HWND hwnd)
{
	// ������ ũ�� ������
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	// ����ü�� ���� �غ�
	DXGI_SWAP_CHAIN_DESC desc = { 0 };
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.SampleDesc.Count = 1;
	

	// Direct3D11 ��ġ�� ���ư� ��ȯ�罽 ����
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_REFERENCE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, // �ʼ�!
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		nullptr,
		&context
		);
	
	
	IDXGISurface *buffer = nullptr;
	ID2D1Factory *factory = nullptr;

	if (SUCCEEDED(hr))
	{
		// ����ü���� ����Ÿ�� ���۸� IDXGISurface�������� ���´�
		hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer));
	}
	if (SUCCEEDED(hr))
	{
		// D2D1���丮 ����
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	}
	if (SUCCEEDED(hr))
	{
		float dpiX, dpiY;

		// ����ũ�� DPI�� ���ɴϴ�
		factory->GetDesktopDpi(&dpiX, &dpiY);

		hr = factory->CreateDxgiSurfaceRenderTarget(
			buffer,
			D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(desc.BufferDesc.Format, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpiX,
			dpiY
			),
			&rt
			);
	}

	// �ʿ� ���� ���ҽ��� ����
	SafeRelease(buffer);
	SafeRelease(factory);

	return SUCCEEDED(hr);
}



void CleanUp()
{
	SafeRelease(rt);
	SafeRelease(swapChain);
	SafeRelease(context);
	SafeRelease(device);
}

//
// �޼��� ���ν��� �Լ�
// �̺�Ʈ�� �߻����� �� �� �Լ��� ȣ��ȴ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_PAINT:
		rt->BeginDraw();
		rt->Clear(D2D1::ColorF(D2D1::ColorF::AliceBlue));
		rt->EndDraw();
		swapChain->Present(0, 0);
		break;
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
	// ������ Ŭ������ ����Ѵ�.
	WNDCLASS wc = { 0 };
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(
		wc.lpszClassName,	// â Ŭ����
		L"SimpleWindow",	// â ����
		WS_OVERLAPPEDWINDOW,// â ��Ÿ��
		CW_USEDEFAULT,		// ȭ�鿡���� X ��ǥ
		CW_USEDEFAULT,		// ȭ�鿡���� Y ��ǥ
		CW_USEDEFAULT,		// ���� ũ��
		CW_USEDEFAULT,		// ���� ũ��
		0,					// �θ� ������
		0,					// �޴�
		hinst,				// �ν��Ͻ� �ڵ�
		0					// �ʱ� ���� ��
		);

	if (Setup(hwnd))
	{
		//
		// ������ â�� ����.
		ShowWindow(hwnd, SW_SHOW);

		//
		// �޽��� ������ ����.
		MSG msg = { 0 };
		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		MessageBox(nullptr, TEXT("�ʱ�ȭ ���� �� ������ �߻��߽��ϴ�."), TEXT("����"), MB_ICONERROR);
	}

	CleanUp();
	return 0;
}

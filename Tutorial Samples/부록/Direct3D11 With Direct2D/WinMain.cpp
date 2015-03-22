
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
	// 윈도우 크기 얻어오기
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	// 스왑체인 생성 준비
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
	

	// Direct3D11 장치와 문맥과 교환사슬 생성
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_REFERENCE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, // 필수!
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
		// 스왑체인의 렌더타겟 버퍼를 IDXGISurface형식으로 얻어온다
		hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer));
	}
	if (SUCCEEDED(hr))
	{
		// D2D1팩토리 생성
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	}
	if (SUCCEEDED(hr))
	{
		float dpiX, dpiY;

		// 데스크톱 DPI를 얻어옵니다
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

	// 필요 없는 리소스는 해제
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
// 메세지 프로시저 함수
// 이벤트가 발생했을 때 이 함수가 호출된다.
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
	// 윈도우 클래스를 등록한다.
	WNDCLASS wc = { 0 };
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	RegisterClass(&wc);

	HWND hwnd = CreateWindow(
		wc.lpszClassName,	// 창 클래스
		L"SimpleWindow",	// 창 제목
		WS_OVERLAPPEDWINDOW,// 창 스타일
		CW_USEDEFAULT,		// 화면에서의 X 좌표
		CW_USEDEFAULT,		// 화면에서의 Y 좌표
		CW_USEDEFAULT,		// 가로 크기
		CW_USEDEFAULT,		// 세로 크기
		0,					// 부모 윈도우
		0,					// 메뉴
		hinst,				// 인스턴스 핸들
		0					// 초기 전달 값
		);

	if (Setup(hwnd))
	{
		//
		// 윈도우 창을 띄운다.
		ShowWindow(hwnd, SW_SHOW);

		//
		// 메시지 루프를 돈다.
		MSG msg = { 0 };
		while (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		MessageBox(nullptr, TEXT("초기화 과정 중 오류가 발생했습니다."), TEXT("에러"), MB_ICONERROR);
	}

	CleanUp();
	return 0;
}

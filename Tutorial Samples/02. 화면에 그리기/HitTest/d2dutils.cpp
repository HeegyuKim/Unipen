#include "d2dutils.h"
using namespace d2d;
 
HRESULT d2d::Initialize (
	HWND hwnd,
	ID2D1Factory **factory,
	ID2D1HwndRenderTarget **rt
	)
{
	HRESULT hr = S_OK;
 
	//
	// Direct2D 팩토리를 생성
	hr = D2D1CreateFactory (
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		factory );
 
 
	if(SUCCEEDED(hr))
	{
		RECT client; 
		GetClientRect(hwnd, &client);
 
		hr = (*factory)->CreateHwndRenderTarget (
			D2D1::RenderTargetProperties (),
			D2D1::HwndRenderTargetProperties(
					hwnd,
					D2D1::SizeU(
						client.right - client.left, 
						client.bottom - client.top )
					),
			rt );
					
	}
 
	return hr;
}

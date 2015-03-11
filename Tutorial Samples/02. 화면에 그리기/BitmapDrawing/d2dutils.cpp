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


HRESULT d2d::LoadBitmap (
	const wchar_t* filename,
	IWICImagingFactory* wic,
	ID2D1RenderTarget* rt,
	ID2D1Bitmap **bitmap )
{
	HRESULT hr = S_OK;
	IWICBitmapFrameDecode *frame = nullptr;
	IWICBitmapDecoder *decoder = nullptr;
	IWICFormatConverter *conv = nullptr;
 
	// 디코더 생성
	hr = wic->CreateDecoderFromFilename (
			filename,
			0,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&decoder );
 
	// 프레임 얻기
	if(SUCCEEDED(hr))
		hr = decoder->GetFrame (0, &frame);
 
	// 변환기 생성
	if(SUCCEEDED(hr))
		hr = wic->CreateFormatConverter(&conv);
	
	// 변환기 초기화
	if(SUCCEEDED(hr))
		hr = conv->Initialize (
				frame,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				0,
				1.0f,
				WICBitmapPaletteTypeCustom );
 
	// 비트맵 생성
	if(SUCCEEDED(hr))
		hr = rt->CreateBitmapFromWicBitmap (
				conv,
				bitmap );
	
	// 해제
	d2d::SafeRelease(frame);
	d2d::SafeRelease(decoder);
	d2d::SafeRelease(conv);
 
	// 결과 반환
	return hr;
}

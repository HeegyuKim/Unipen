
// include guard
#ifndef _d2dutils_h_
#define _d2dutils_h_
 
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>


// 정적 라이브러리링크
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
 
namespace d2d {
 
// Direct2D 팩토리와
// 윈도우 렌더타겟을 생성해 주는 함수
HRESULT Initialize (
	HWND hwnd,
	ID2D1Factory **factory,
	ID2D1HwndRenderTarget **rt
	);
 

HRESULT LoadBitmap (
	const wchar_t* filename,
	IWICImagingFactory* wic,
	ID2D1RenderTarget* rt,
	ID2D1Bitmap **bitmap );

// COM 인터페이스를 해제해주는 함수
template <typename T>
inline void SafeRelease(T t) {
	if(t)
		t->Release();
}
 
template <typename T>
inline void SafeDelete(T t) {
	if(t)
		delete t;
}
}
#endif

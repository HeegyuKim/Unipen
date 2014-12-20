
// include guard
#ifndef _d2dutils_h_
#define _d2dutils_h_
 
#include <d2d1.h>
#include <d2d1helper.h>
#include <wincodec.h>


// ���� ���̺귯����ũ
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
 
namespace d2d {
 
// Direct2D ���丮��
// ������ ����Ÿ���� ������ �ִ� �Լ�
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

// COM �������̽��� �������ִ� �Լ�
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


#include "Window.h"

namespace unipen {


LPCTSTR Window::s_className = L"UnipenWindow";


bool Window::s_registered = false;


/*!
	* @brief 기본적으로 윈도우 메세지를 처리하는 함수입니다.
	*/
LRESULT CALLBACK 
	Window::WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);

	if(window)
		return window->ProcessMessage(msg, wp, lp);
	else
		return DefWindowProc(hwnd, msg, wp, lp);
}
	


void Window::Register() {
	WNDCLASS wc = {0};
	wc.lpszClassName = s_className;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = (HINSTANCE)GetModuleHandle(0);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	RegisterClass(&wc);

	s_registered = true;
}



/*!
	* @brief 제목 문자열을 가지는 윈도우를 생성한다.
	* @param title 제목 문자열
	*/
Window::Window(LPCTSTR title) {
	if(!s_registered)
		Register();

	m_window = CreateWindowW ( s_className, title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, (HINSTANCE)GetModuleHandle(0), 0);

	SetWindowLongW(m_window, GWL_USERDATA, (LONG)this);
}

/*!
	* @brief 윈도우 객체를 제거한다.
	*/
Window::~Window() {
	Dispose();	
}

/*!
	* @brief 윈도우의 제목 문자열을 설정한다.
	* @param title 지정한 제목 문자열
	*/
void Window::SetTitle(LPCTSTR title) {
	SetWindowText(m_window, title);
}
	
/*!
	* @brief 윈도우의 위치를 지정한다.
	* @param x 지정할 x좌표
	* @param y 지정할 y좌표
	*/
void Window::SetPosition(int x, int y) {
	SetWindowPos(m_window, nullptr, x, y, 0, 0, SWP_NOSIZE);
}
	
/*!
	* @brief 윈도우의 클라이언트 영억의 크기를 지정한다.
	* @param width 지정할 가로 크기
	* @param height 지정할 세로 크기
	*/
void Window::SetClientSize(int width, int height) {

}
	
/*!
	* @brief 윈도우의 크기를 지정한다.
	* @param width 지정할 가로 크기
	* @param height 지정할 세로 크기
	*/
void Window::SetSize(int width, int height) {
	SetWindowPos(m_window, nullptr, 0, 0, width, height, SWP_NOMOVE);
}


/*!
* @brief 윈도우의 스타일을 지정한다.
* @param style 지정할 스타일 값.
*/
void Window::SetStyle(DWORD style) {
	SetWindowLong(m_window, GWL_STYLE, style);
}
	
/*!
	* @brief 윈도우의 크기를 반환한다.
	* @return 윈도우의 크기를 저장한 SIZE 객체
	*/
SIZE Window::GetSize() const {
	RECT size = {0};
	GetWindowRect(m_window, &size);
	SIZE s = { 
		size.right - size.left,
		size.bottom - size.top
	};
	return s;
}

/*!
	* @brief 윈도우의 클라이언트 영역의 위치와 크기를 반환한다,
	* @return 윈도우 클라이언트 영역의 위치와 크기를 저장한 RECT객체.
	*/
RECT Window::GetClientRect() const {
	RECT client = {0};
	::GetClientRect(m_window, &client);
	return client;
}

/*!
	* @brief 윈도우의 클라이언트 영역의 위치를 반환한다,
	* @return 윈도우 클라이언트 영역의 위치를 저장한 POINT객체.
	*/
POINT Window::GetPosition() const {
	RECT rect = {0};
	GetWindowRect(m_window, &rect);
	POINT p = { 
		rect.left,
		rect.top
	};
	return p;
}


///< 윈도우의 스타일 값을 반환한다.
DWORD Window::GetStyle() const {
	return GetWindowLong(m_window, GWL_STYLE);
}


///< @brief 윈도우를 파괴한다.
void Window::Dispose() {
	if(m_window) {
		DestroyWindow(m_window);
		m_window = nullptr;
	}
}


///< 윈도우 핸들을 반환한다.
HWND Window::GetHandle() const {
	return m_window;
}

LRESULT Window::ProcessMessage(UINT msg, WPARAM wp, LPARAM lp) {
	switch(msg) {
	case WM_DESTROY:
		if(IsQuitOnDestroy())
			PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(m_window, msg, wp, lp);
}


void Run() {
	MSG msg = {0};
	while(GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

}
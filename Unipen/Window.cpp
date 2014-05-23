
#include "Window.h"

namespace unipen {


LPCTSTR Window::s_className = L"UnipenWindow";


bool Window::s_registered = false;


/*!
	* @brief �⺻������ ������ �޼����� ó���ϴ� �Լ��Դϴ�.
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
	* @brief ���� ���ڿ��� ������ �����츦 �����Ѵ�.
	* @param title ���� ���ڿ�
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
	* @brief ������ ��ü�� �����Ѵ�.
	*/
Window::~Window() {
	Dispose();	
}

/*!
	* @brief �������� ���� ���ڿ��� �����Ѵ�.
	* @param title ������ ���� ���ڿ�
	*/
void Window::SetTitle(LPCTSTR title) {
	SetWindowText(m_window, title);
}
	
/*!
	* @brief �������� ��ġ�� �����Ѵ�.
	* @param x ������ x��ǥ
	* @param y ������ y��ǥ
	*/
void Window::SetPosition(int x, int y) {
	SetWindowPos(m_window, nullptr, x, y, 0, 0, SWP_NOSIZE);
}
	
/*!
	* @brief �������� Ŭ���̾�Ʈ ������ ũ�⸦ �����Ѵ�.
	* @param width ������ ���� ũ��
	* @param height ������ ���� ũ��
	*/
void Window::SetClientSize(int width, int height) {

}
	
/*!
	* @brief �������� ũ�⸦ �����Ѵ�.
	* @param width ������ ���� ũ��
	* @param height ������ ���� ũ��
	*/
void Window::SetSize(int width, int height) {
	SetWindowPos(m_window, nullptr, 0, 0, width, height, SWP_NOMOVE);
}


/*!
* @brief �������� ��Ÿ���� �����Ѵ�.
* @param style ������ ��Ÿ�� ��.
*/
void Window::SetStyle(DWORD style) {
	SetWindowLong(m_window, GWL_STYLE, style);
}
	
/*!
	* @brief �������� ũ�⸦ ��ȯ�Ѵ�.
	* @return �������� ũ�⸦ ������ SIZE ��ü
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
	* @brief �������� Ŭ���̾�Ʈ ������ ��ġ�� ũ�⸦ ��ȯ�Ѵ�,
	* @return ������ Ŭ���̾�Ʈ ������ ��ġ�� ũ�⸦ ������ RECT��ü.
	*/
RECT Window::GetClientRect() const {
	RECT client = {0};
	::GetClientRect(m_window, &client);
	return client;
}

/*!
	* @brief �������� Ŭ���̾�Ʈ ������ ��ġ�� ��ȯ�Ѵ�,
	* @return ������ Ŭ���̾�Ʈ ������ ��ġ�� ������ POINT��ü.
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


///< �������� ��Ÿ�� ���� ��ȯ�Ѵ�.
DWORD Window::GetStyle() const {
	return GetWindowLong(m_window, GWL_STYLE);
}


///< @brief �����츦 �ı��Ѵ�.
void Window::Dispose() {
	if(m_window) {
		DestroyWindow(m_window);
		m_window = nullptr;
	}
}


///< ������ �ڵ��� ��ȯ�Ѵ�.
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
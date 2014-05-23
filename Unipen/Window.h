
#ifndef _Unipen_Window_h_
#define _Unipen_Window_h_


#include "Entity.h"


#include <Windows.h>


namespace unipen {

/*!
 * @class Window
 * @date 2014/05/21
 * @author 김희규
 * @brief 윈도우를 생성하고 관리해주는 클래스
 * @warning WNDCLASS 값을 인자로 받는 생성자를 호출하는 경우, 윈도우 클래스의
 * lpfnWndProc 값이 Window::WindowProc이 아니면 가상 함수를 오버라이드해서
 * 윈도우 이벤트를 처리할 수 없습니다.
 */
class Window : public Entity {
public:
	/*!
	 * @brief 기본적으로 윈도우 메세지를 처리하는 함수입니다.
	 */
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	
private:
	
	///< 생성할 윈도우의 정보를 가진 클래스 이름.
	static LPCTSTR s_className;

	///< 윈도우 클래스가 등록되어있는지 여부를 나타내는 변수.
	static bool s_registered;

	///< 윈도우 클래스를 등록하는 함수입니다.
	static void Register();
public:
	/*!
	 * @brief 제목 문자열을 가지는 윈도우를 생성한다.
	 * @param title 제목 문자열
	 */
	Window(LPCTSTR title);

	/*!
	 * @brief 윈도우 객체를 제거한다.
	 */
	virtual ~Window();

	/*!
	 * @brief 윈도우의 제목 문자열을 설정한다.
	 * @param title 지정한 제목 문자열
	 */
	void SetTitle(LPCTSTR title);
	
	/*!
	 * @brief 윈도우의 위치를 지정한다.
	 * @param x 지정할 x좌표
	 * @param y 지정할 y좌표
	 */
	void SetPosition(int x, int y);
	
	/*!
	 * @brief 윈도우의 클라이언트 영억의 크기를 지정한다.
	 * @param width 지정할 가로 크기
	 * @param height 지정할 세로 크기
	 */
	void SetClientSize(int width, int height);
	
	/*!
	 * @brief 윈도우의 크기를 지정한다.
	 * @param width 지정할 가로 크기
	 * @param height 지정할 세로 크기
	 */
	void SetSize(int width, int height);

	/*!
	 * @brief 윈도우의 스타일을 지정한다.
	 * @param style 지정할 스타일 값.
	 */
	void SetStyle(DWORD style);

	/*!
	 * @brief 윈도우의 크기를 반환한다.
	 * @return 윈도우의 크기를 저장한 SIZE 객체
	 */
	SIZE GetSize() const;

	/*!
	 * @brief 윈도우의 클라이언트 영역의 위치와 크기를 반환한다,
	 * @return 윈도우 클라이언트 영역의 위치와 크기를 저장한 RECT객체.
	 */
	RECT GetClientRect() const;

	/*!
	 * @brief 윈도우의 클라이언트 영역의 위치를 반환한다,
	 * @return 윈도우 클라이언트 영역의 위치를 저장한 POINT객체.
	 */
	POINT GetPosition() const;


	///< 윈도우의 스타일 값을 반환한다.
	DWORD GetStyle() const;


	///< @brief 윈도우를 파괴한다.
	void Dispose();


	///< 윈도우 핸들을 반환한다.
	HWND GetHandle() const;


	/*!
	 * @brief 윈도우가 파괴될 때 메세지 루프를 종료하는 PostQuitMessage()함수를
	 * 호출하는 기능을 활성화할지를 지정한다.
	 * @param enable true면 활성화이고, false이면 비활성화이다.
	 */
	void SetQuitOnDestroy(bool enable) _do(m_quitOnDestroy = enable);

	/*!
	 * @brief 윈도우가 파괴될 때 메세지 루프를 종료하는 PostQuitMessage()함수를
	 * 호출하는 기능의 활성화여부를 반환한다.
	 * @return true면 활성화이고, false이면 비활성화이다.
	 */
	inline bool IsQuitOnDestroy() const _is(m_quitOnDestroy);


	/*!
	 * @brief 윈도우의 가시성을 설정한다.
	 * @param flag ShowWindow() 함수에서 사용되는 윈도우에 적용할 속성
	 */
	inline void SetState(DWORD flag) { ShowWindow(m_window, flag); }

	
	///< @brief 윈도우가 보이는지를 반환한다.
	inline bool IsVisible() const _is(static_cast<bool>(IsWindowVisible(m_window)));

protected:
	
	/*!
	 * @brief 윈도우 이벤트를 처리하는 가상 함수이다.
	 * 이 함수를 오버라이드해서 윈도우 이벤트를 처리할 수 있다.
	 * @param msg 처리할 이벤트 메세지
	 * @param wp 이벤트 메세지의 정보
	 * @param lp 이벤트 메세지의 정보
	 * @return 처리한 결과를 나타내는 LRESULT 값.
	 */
	virtual LRESULT ProcessMessage(UINT msg, WPARAM wp, LPARAM lp);

private:
	
	HWND m_window; ///< 가르키는 윈도우의 핸들

	bool m_quitOnDestroy; ///< 윈도우가 파괴될 때 메세지 루프를 탈출할 것인가를 나타냄

};


void Run();

}


#endif
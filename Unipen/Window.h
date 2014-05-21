
#ifndef _Unipen_Window_h_
#define _Unipen_Window_h_


#include "Entity.h"


#include <Windows.h>


namespace unipen {

/*!
 * @class Window
 * @date 2014/05/21
 * @author �����
 * @brief �����츦 �����ϰ� �������ִ� Ŭ����
 * @warning WNDCLASS ���� ���ڷ� �޴� �����ڸ� ȣ���ϴ� ���, ������ Ŭ������
 * lpfnWndProc ���� Window::WindowProc�� �ƴϸ� ���� �Լ��� �������̵��ؼ�
 * ������ �̺�Ʈ�� ó���� �� �����ϴ�.
 */
class Window : public Entity {
public:
	/*!
	 * @brief �⺻������ ������ �޼����� ó���ϴ� �Լ��Դϴ�.
	 */
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	
private:
	
	///< ������ �������� ������ ���� Ŭ���� �̸�.
	static LPCTSTR s_className;

	///< ������ Ŭ������ ��ϵǾ��ִ��� ���θ� ��Ÿ���� ����.
	static bool s_registered;

	///< ������ Ŭ������ ����ϴ� �Լ��Դϴ�.
	static void Register();
public:
	/*!
	 * @brief ���� ���ڿ��� ������ �����츦 �����Ѵ�.
	 * @param title ���� ���ڿ�
	 */
	Window(LPCTSTR title);

	/*!
	 * @brief ������ ��ü�� �����Ѵ�.
	 */
	virtual ~Window();

	/*!
	 * @brief �������� ���� ���ڿ��� �����Ѵ�.
	 * @param title ������ ���� ���ڿ�
	 */
	void SetTitle(LPCTSTR title);
	
	/*!
	 * @brief �������� ��ġ�� �����Ѵ�.
	 * @param x ������ x��ǥ
	 * @param y ������ y��ǥ
	 */
	void SetPosition(int x, int y);
	
	/*!
	 * @brief �������� Ŭ���̾�Ʈ ������ ũ�⸦ �����Ѵ�.
	 * @param width ������ ���� ũ��
	 * @param height ������ ���� ũ��
	 */
	void SetClientSize(int width, int height);
	
	/*!
	 * @brief �������� ũ�⸦ �����Ѵ�.
	 * @param width ������ ���� ũ��
	 * @param height ������ ���� ũ��
	 */
	void SetSize(int width, int height);

	/*!
	 * @brief �������� ��Ÿ���� �����Ѵ�.
	 * @param style ������ ��Ÿ�� ��.
	 */
	void SetStyle(DWORD style);

	/*!
	 * @brief �������� ũ�⸦ ��ȯ�Ѵ�.
	 * @return �������� ũ�⸦ ������ SIZE ��ü
	 */
	SIZE GetSize() const;

	/*!
	 * @brief �������� Ŭ���̾�Ʈ ������ ��ġ�� ũ�⸦ ��ȯ�Ѵ�,
	 * @return ������ Ŭ���̾�Ʈ ������ ��ġ�� ũ�⸦ ������ RECT��ü.
	 */
	RECT GetClientRect() const;

	/*!
	 * @brief �������� Ŭ���̾�Ʈ ������ ��ġ�� ��ȯ�Ѵ�,
	 * @return ������ Ŭ���̾�Ʈ ������ ��ġ�� ������ POINT��ü.
	 */
	POINT GetPosition() const;


	///< �������� ��Ÿ�� ���� ��ȯ�Ѵ�.
	DWORD GetStyle() const;


	///< @brief �����츦 �ı��Ѵ�.
	void Dispose();


	///< ������ �ڵ��� ��ȯ�Ѵ�.
	HWND GetHandle() const;


	/*!
	 * @brief �����찡 �ı��� �� �޼��� ������ �����ϴ� PostQuitMessage()�Լ���
	 * ȣ���ϴ� ����� Ȱ��ȭ������ �����Ѵ�.
	 * @param enable true�� Ȱ��ȭ�̰�, false�̸� ��Ȱ��ȭ�̴�.
	 */
	void SetQuitOnDestroy(bool enable) _do(m_quitOnDestroy = enable);

	/*!
	 * @brief �����찡 �ı��� �� �޼��� ������ �����ϴ� PostQuitMessage()�Լ���
	 * ȣ���ϴ� ����� Ȱ��ȭ���θ� ��ȯ�Ѵ�.
	 * @return true�� Ȱ��ȭ�̰�, false�̸� ��Ȱ��ȭ�̴�.
	 */
	inline bool IsQuitOnDestroy() const _is(m_quitOnDestroy);


	/*!
	 * @brief �������� ���ü��� �����Ѵ�.
	 * @param flag ShowWindow() �Լ����� ���Ǵ� �����쿡 ������ �Ӽ�
	 */
	inline void SetState(DWORD flag) { ShowWindow(m_window, flag); }

	
	///< @brief �����찡 ���̴����� ��ȯ�Ѵ�.
	inline bool IsVisible() const _is(static_cast<bool>(IsWindowVisible(m_window)));

protected:
	
	/*!
	 * @brief ������ �̺�Ʈ�� ó���ϴ� ���� �Լ��̴�.
	 * �� �Լ��� �������̵��ؼ� ������ �̺�Ʈ�� ó���� �� �ִ�.
	 * @param msg ó���� �̺�Ʈ �޼���
	 * @param wp �̺�Ʈ �޼����� ����
	 * @param lp �̺�Ʈ �޼����� ����
	 * @return ó���� ����� ��Ÿ���� LRESULT ��.
	 */
	virtual LRESULT ProcessMessage(UINT msg, WPARAM wp, LPARAM lp);

private:
	
	HWND m_window; ///< ����Ű�� �������� �ڵ�

	bool m_quitOnDestroy; ///< �����찡 �ı��� �� �޼��� ������ Ż���� ���ΰ��� ��Ÿ��

};


void Run();

}


#endif
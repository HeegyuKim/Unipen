
#include "DodgeGame.h"
#include "resource.h"
using namespace std;



//
// �޼��� ���ν��� �Լ�
// �̺�Ʈ�� �߻����� �� �� �Լ��� ȣ��ȴ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch(msg)
	{
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
	srand(timeGetTime());

	const int width = 800, 
		height = 600;
	HWND hwnd;
	DodgeGame *game = nullptr;

	//
	// ������ Ŭ������ ����Ѵ�.(hbrBackground �����)
	WNDCLASS wc = {0};
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON1));
	RegisterClass(&wc);
 
	DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	RECT rect = {0, 0, width, height};
	AdjustWindowRect(&rect, style, false);
 
	hwnd = CreateWindow (
		wc.lpszClassName,		// â Ŭ����
		L"����!",	// â ����
		style,	// â ��Ÿ��
		CW_USEDEFAULT,		// ȭ�鿡���� X ��ǥ
		CW_USEDEFAULT,		// ȭ�鿡���� Y ��ǥ
		rect.right - rect.left,	// ���� ũ��
		rect.bottom - rect.top,	// ���� ũ��
		0,				// �θ� ������
		0,				// �޴�
		hinst,				// �ν��Ͻ� �ڵ�
		0				// �ʱ� ���ް�
		);
	try
	{
		game = new DodgeGame(hwnd);
		ShowWindow(hwnd, SW_SHOW);

		DWORD lastTime = timeGetTime();

		// �޽��� ������ ����.
		MSG msg = {0};
		while(msg.message != WM_QUIT)
		{
			if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				DWORD curr = timeGetTime();
				DWORD delta = curr - lastTime;

				if(delta >= 16)
				{
					lastTime = curr;
					game->Update(delta / 1000.0f);
					game->Draw();
				}
				else
					Sleep(16 - delta);
			}
		}
	}
	catch(exception& e)
	{
		MessageBoxA(hwnd, e.what(), "������ �߻��߽��ϴ�.", MB_ICONERROR);
	}

	if(game)
	{
		delete game;
		game = nullptr;
	}

	return 0;
}

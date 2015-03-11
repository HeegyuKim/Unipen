
#include <Windows.h>


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
	//
	// ������ Ŭ������ ����Ѵ�.
	WNDCLASS wc = {0};
	wc.lpszClassName = L"Unipen Window";
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst; 
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	
	RegisterClass(&wc);

	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	RECT rect = {	// ���ϴ� ũ��� ���� 800, ���� 600�̴�.
		0, 0,
		800, 600
	};

	// AdjustWindowRect() �Լ��� ���ؼ�
	// Ư�� ��Ÿ���� ���� �������� Ŭ���̾�Ʈ ������ ũ�⸦ ���Ѵ�
	// ������ ���ڴ� �޴��� ���η�, ���� ������ false�� �ش�.
	AdjustWindowRect(&rect, windowStyle, false);

	// ����, ���� ����ϱ�
	DWORD width = rect.right - rect.left;
	DWORD height= rect.bottom- rect.top;

	HWND hwnd = CreateWindow (
		wc.lpszClassName,		// â Ŭ����
		L"AdjustWindow",	// â ����
		windowStyle,			// â ��Ÿ��
		CW_USEDEFAULT,		// ȭ�鿡���� X ��ǥ
		CW_USEDEFAULT,		// ȭ�鿡���� Y ��ǥ
		width,		// ���� ũ��
		height,		// ���� ũ��
		0,				// �θ� ������
		0,				// �޴�
		hinst,				// �ν��Ͻ� �ڵ�
		0				// �ʱ� ���� ��
		);
	//
	// ������ â�� ����.
	ShowWindow(hwnd, SW_SHOW);

	//
	// �޽��� ������ ����.
	MSG msg = {0};
	while(GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

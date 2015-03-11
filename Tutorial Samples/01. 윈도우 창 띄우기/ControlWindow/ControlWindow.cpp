
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

	HWND hwnd = CreateWindow (
		wc.lpszClassName,		// â Ŭ����
		L"ControlWindow",	// â ����
		WS_OVERLAPPEDWINDOW,	// â ��Ÿ��
		CW_USEDEFAULT,		// ȭ�鿡���� X ��ǥ
		CW_USEDEFAULT,		// ȭ�鿡���� Y ��ǥ
		CW_USEDEFAULT,		// ���� ũ��
		CW_USEDEFAULT,		// ���� ũ��
		0,				// �θ� ������
		0,				// �޴�
		hinst,				// �ν��Ͻ� �ڵ�
		0				// �ʱ� ���� ��
		);

	// ��ġ�� �ٲ��� �ʰ� ũ�⸸ �ٲ۴�(SWP_NOMOVE).
	SetWindowPos(hwnd, NULL,
		0, 0,
		450, 300,
		SWP_NOMOVE );

	// ũ��� �ٲ��� �ʰ� ��ġ�� �ٲ۴�(SWP_NOSIZE).
	SetWindowPos(hwnd, NULL,
		450, 300,
		0, 0,
		SWP_NOSIZE );

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

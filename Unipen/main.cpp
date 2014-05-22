

#include "Window.h"

using namespace unipen;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window window(L"Hello world");

	window.SetState(SW_SHOW);
	window.SetQuitOnDestroy(true);
	
	Run();

	return 0;
}
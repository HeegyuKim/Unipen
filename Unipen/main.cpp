

#include "Window.h"
#include "SoundManager.h"
using namespace unipen;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window window(L"Hello world");

	window.SetState(SW_SHOW);
	window.SetState(true);
	window.SetQuitOnDestroy(true);
	
	Run();

	return 0;
}
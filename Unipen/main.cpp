

#include "Window.h"

using namespace unipen;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Window window(L"Hello world");

<<<<<<< HEAD
	window.SetState(SW_SHOW);
=======
	window.SetState(true);
>>>>>>> heegyu
	window.SetQuitOnDestroy(true);
	
	Run();

	return 0;
}
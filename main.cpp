#include "application.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	Application* pApp = new Application ( );
	pApp->run();
}
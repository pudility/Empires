#include "application.h"

#if __APPLE__
#include <iostream>

int main( int argc, const char * argv[] )
{
    std::cout << "Running on MacOS" << std::endl;
    Application* pApp = new Application ( );
    pApp->run();
}
#elif _WIN32
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    std::cout << "Running on WIN23" << std::endl;
    Application* pApp = new Application ( );
    pApp->run();
}
#endif

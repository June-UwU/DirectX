#include <Windows.h>
#include "App.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		App app;
		app.Run();
	}
	catch (const Appception& e)
	{
		MessageBoxA(nullptr, e.what(), nullptr, MB_OK);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), nullptr, MB_OK);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "no info..you are on your own", nullptr, MB_OK);
	}
}

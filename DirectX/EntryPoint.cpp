#include <Windows.h>
#include "Window.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window window = Window(720, 1280, "DirectX");

		MSG message;
		std::string hanky;
		std::stringstream stream;
		while (GetMessage(&message, window.GetHandle(), 0, 0) > 0)
		{
			if (window.mse.MiddleDown())
			{
				hanky.clear();
				stream << "[mouse pos]" << window.mse.GetX() << "::" << window.mse.GetY() << std::endl;
				hanky = stream.str();
				OutputDebugStringA((LPCSTR)hanky.c_str());
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
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

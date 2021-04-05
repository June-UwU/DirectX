#include "Window.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window window = Window(720, 1280, "DirectX");

		MSG message;
		while (GetMessage(&message, window.GetHandle(), 0, 0) > 0)
		{
			if (window.kbd.KeyDown(VK_MENU))
			{
				MessageBoxA(nullptr, "space pressed", nullptr, MB_OK);
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

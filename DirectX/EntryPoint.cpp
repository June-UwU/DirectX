#include "Window.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	try
	{
		Window window = Window();

		MSG message;
		INT res;
		while ((res = GetMessage(&message, window.GetHandle(), 0, 0)) > 0)
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	catch (const Appception& e)
	{
		MessageBox(nullptr,(LPCWSTR) e.what(), nullptr, MB_OK);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, (LPCWSTR)e.what(), nullptr, MB_OK);
	}
	catch (...)
	{
		MessageBox(nullptr, (LPCWSTR)"no info..you are on your own", nullptr, MB_OK);
	}
}

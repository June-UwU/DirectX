#include "Window.h"

Window::Window()
	:Instance(GetModuleHandle(nullptr))
{
	const wchar_t CLASSNAME[] = L"DirectX";
	WNDCLASSEX wc = {};

	wc.hInstance = Instance;
	wc.lpfnWndProc = DefWindowProc;
	wc.lpszClassName = CLASSNAME;

	RegisterClassEx(&wc);

	handle = CreateWindowEx(0, CLASSNAME, L"DirectX", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, NULL, Instance, 0);

	ShowWindow(handle, SW_SHOW);
}

HWND Window::GetHandle()
{
	return handle;
}

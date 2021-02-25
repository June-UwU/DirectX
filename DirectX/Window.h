#pragma once
#include <Windows.h>

class Window
{
	Window();
	HWND GetHandle();
private:
	HINSTANCE Instance;
	HWND handle;
};


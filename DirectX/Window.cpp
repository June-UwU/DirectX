#include "Window.h"


Window::WindowsProp Window::WindowsProp::Prop;
Window::Window()
{
	handle = CreateWindowEx(0,WindowsProp::GetName(), L"DirectX ", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, WindowsProp::GetInstance(), nullptr);

	ShowWindow(handle, SW_SHOWDEFAULT);
	throw WND_ERROR(ERROR_INVALID_FUNCTION);

}


HWND Window::GetHandle()
{
	return handle;
}

LRESULT Window::Proc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
		switch (msg)
		{
		case WM_QUIT:
		{
			PostQuitMessage(0);
			return 0;
		}break;
		}
		return DefWindowProc(handle, msg, wParam, lParam);
}

Window::WindowsProp::WindowsProp()
	:instance(GetModuleHandle(nullptr))
{
	WNDCLASS wc = { 0 };
	 
	wc.lpfnWndProc = Window::Proc;
	wc.hInstance = instance;
	wc.lpszClassName = WCname;
	wc.style = CS_OWNDC;

	RegisterClass(&wc);

}

const wchar_t* Window::WindowsProp::GetName()
{
	return WCname;
}

HINSTANCE Window::WindowsProp::GetInstance()
{
	return Prop.instance;
}

Window::Winception::Winception(int line, const char* file, HRESULT hr) noexcept
	:hr(hr)
	,Appception(line , file)
{
}

std::string Window::Winception::TranslateHRESULT() const noexcept
{
	LPTSTR temp = {};
	DWORD count = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
		0x0009, temp, 0, nullptr);
	if (count == 0)
	{
		return "unidentified error";
	}

	return (char*)temp;
}

const char* Window::Winception::what() const noexcept
{
	std::ostringstream oss;
	oss << "WINDOWS ERROR!" << std::endl
		<< "[CODE] 0x" << std::hex <<hr <<std::endl
		<< "[DESCRIPTION]" << TranslateHRESULT()
		<< "[LINE]" << GetLine() << std::endl
		<< "[FILE]" << GetFile() << std::endl;
	data = oss.str();
	return data.c_str();
}


HRESULT Window::Winception::GetError() noexcept
{
	return hr;
}

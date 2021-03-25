#include "Window.h"


Window::WindowsProp Window::WindowsProp::Prop;
Window::Window()
{
	handle = CreateWindowEx(0,WindowsProp::GetName(), L"DirectX ", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, WindowsProp::GetInstance(), this);
	
	/*BOOL cond = SetProcessPreferredUILanguages(0X1001, NULL, 0);
	if (cond)
	{
		OutputDebugString(L"work dammit...!");
	}*/
	//throw WND_ERROR(ERROR_INVALID_FUNCTION);
	//throw Appception(__LINE__,__FILE__);
	//throw std::invalid_argument("shit");
}


HWND Window::GetHandle()
{
	return handle;
}

LRESULT Window::Proc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCT* const pCreate = (CREATESTRUCT*)(lParam);
		Window const* pWnd = (Window*)pCreate->lpCreateParams;
		SetWindowLongPtr(handle, GWLP_USERDATA, LONG_PTR(pCreate));
		SetWindowLongPtr(handle, GWLP_WNDPROC, LONG_PTR(Tans));
		return pWnd->Tans(handle, msg, wParam, lParam);
	}
	
	return DefWindowProc(handle, msg, wParam, lParam);
}

LRESULT Window::Tans(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = (Window *)GetWindowLongPtr(handle, GWLP_USERDATA);
	ShowWindow(handle, SW_SHOWDEFAULT);
	return pWnd->MessHandle(handle, msg, wParam, lParam);
}

LRESULT Window::MessHandle(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		Result = 0;
	}break;
	case WM_QUIT:
	{
		Result = 0;	
	}break;
	default:
	{
		Result = DefWindowProc(handle, msg, wParam, lParam);
	}
	}
	return Result;
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
		MAKELANGID(SUBLANG_ENGLISH_UK ,LANG_ENGLISH), temp, 0, nullptr);
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

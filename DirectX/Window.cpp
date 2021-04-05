#include "Window.h"


Window::WindowsProp Window::WindowsProp::Prop;
Window::Window(int WindowHeight, int WindowWidth,const char* WindowName)
	:WindowHeight(WindowHeight)
	,WindowWidth(WindowWidth)
{
	RECT wr{ 0 };
	wr.left = 100;
	wr.right = wr.left + WindowWidth;
	wr.top = 100;
	wr.bottom = wr.top + WindowHeight;
	if (AdjustWindowRectEx(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false,WS_EX_OVERLAPPEDWINDOW)==0)
	{
		throw WND_LAST_ERROR();
	}
	handle = CreateWindowExA(0,WindowsProp::GetName(), WindowName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,nullptr, nullptr, WindowsProp::GetInstance(), this);
	
	/*BOOL cond = SetProcessPreferredUILanguages(0X1001, NULL, 0);
	if (cond)
	{
		OutputDebugString(L"work dammit...!");
	}*/
	//throw WND_ERROR(ERROR_ARENA_TRASHED);
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
		SetWindowLongPtr(handle, GWLP_USERDATA, LONG_PTR(pWnd));
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
		/*KEYBOARD MESSAGE HANDLING*/
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
	{
		if (!(lParam << 30 & 1) || kbd.ENABLE_AUTO_REPEAT)
		{
			kbd.KeyPressedEvent(unsigned char(wParam));
		}
	}break;
	case WM_SYSKEYUP:
	case WM_KEYUP:
	{
 		kbd.KeyReleasedEvent(unsigned char(wParam));
	}break;
	case WM_KILLFOCUS:
	{
		kbd.ClearState();
	}break;
	case WM_CLOSE:
	{
		Result = 0;
		PostQuitMessage(0);
	}break;
	case WM_CHAR:
	{
		kbd.CharEvent(wParam);
	}break;
	/*MOUSE MESSAGE HANDLING*/
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.LeftMousePressEvent(pt.x,pt.y);
	}break;
	case WM_LBUTTONUP:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.LeftMouseReleaseEvent(pt.x, pt.y);
	}break;
	case WM_MBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.MiddleMousePressEvent(pt.x, pt.y);
	}break;
	case WM_MBUTTONUP:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.MiddleMouseReleaseEvent(pt.x, pt.y);
	}break;
	case WM_RBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.RightMousePressEvent(pt.x, pt.y);
	}break;
	case WM_RBUTTONUP:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.RightMouseReleaseEvent(pt.x, pt.y);
	}break;
	case WM_MOUSEMOVE:
	{
		POINTS pt = MAKEPOINTS(lParam);
		mse.MouseMove(pt.x, pt.y);
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

const char* Window::WindowsProp::GetName()
{
	return WCname;
}

HINSTANCE Window::WindowsProp::GetInstance()
{
	return Prop.instance;
}

Window::Winception::Winception(int line, const char* file, HRESULT hr) noexcept
	:Appception(line , file)
	,hr(hr)
{
}

std::string Window::Winception::TranslateHRESULT() const noexcept
{
	char* temp { 0 };
	DWORD count = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
		LANG_SYSTEM_DEFAULT,LPSTR(&temp), 0, nullptr);
	if (count == 0)
	{
		return "unidentified error";
	}
	std::string ErrorString = temp;

	LocalFree(temp);

	return ErrorString;
}

const char* Window::Winception::what() const noexcept
{
	std::ostringstream oss;
	oss << "WINDOWS ERROR!" << std::endl
		<< "[CODE] 0x" << std::hex << hr << std::endl
		<< "[DESCRIPTION]" << TranslateHRESULT() << std::endl
		<< "[LINE]" << std::dec << (unsigned int)GetLine() << std::endl
		<< "[FILE]" << GetFile() << std::endl;
	data = oss.str();
	return data.c_str();
}


HRESULT Window::Winception::GetError() noexcept
{
	return hr;
}

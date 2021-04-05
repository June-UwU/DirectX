#pragma once
#include <Windows.h>
#include "Appception.h"
#include "KeyBoard.h"
#include "Mouse.h"
class Window
{
public:
	Window(int Windowheight,int WindowWidth,const char* WindowName);
	Window(Window& rhs) = delete;
	Window operator=(Window& rhs) = delete;
	HWND GetHandle();
public:
	KeyBoard kbd;
	Mouse mse;
private:
	class Winception : public Appception
	{
	public:
		Winception(int line , const char* ,HRESULT hr) noexcept;
		std::string TranslateHRESULT() const noexcept;
		const char* what() const noexcept override;
		HRESULT GetError() noexcept;
	private:
		HRESULT hr;
	};
	class WindowsProp
	{
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowsProp();
		WindowsProp operator=(WindowsProp& rhs) = delete;
		WindowsProp(WindowsProp& Prop) = delete;
		static constexpr const char* WCname = "DIRECTX";
		HINSTANCE instance;
	    static WindowsProp Prop;
	};
private:
	int WindowWidth;
	int WindowHeight;
	static LRESULT CALLBACK Proc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Tans(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT MessHandle(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND handle;
};

#define WND_ERROR(hr) Winception(__LINE__,__FILE__,hr)
#define WND_LAST_ERROR() Winception(__LINE__,__FILE__,GetLastError())
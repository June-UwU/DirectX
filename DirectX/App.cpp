#include "App.h"

App::App()
	:window(720,1280,"DirectX")
{
}

void App::DoFrame()
{
	window.Graphics().ClearBackBuffer(0, 0, 1000);
	window.Graphics().EndFrame();
}

int App::Run()
{
	while (true)
	{
		if (const auto ecode = window.ProcessMessage())
		{
			return *ecode;
		}
		DoFrame();
	}
}

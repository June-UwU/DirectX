#include "App.h"


App::App()
	:window(720,1280,"DirectX")
{
}

void App::DoFrame()
{
	const float var = sin(Chrono.Peek()) / 2.0f + 0.5f;
	window.Graphics().ClearBackBuffer(var, var, 0);
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

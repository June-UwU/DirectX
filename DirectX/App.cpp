#include "App.h"

App::App()
	:window(720,1280,"DirectX")
{
}

void App::DoFrame()
{
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

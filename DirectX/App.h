#pragma once
#include "Window.h"
#include "Timer.h"
class App
{
public:
	App();
	void DoFrame();
	int Run();
private:
	Timer Chrono;
	Window window;
};


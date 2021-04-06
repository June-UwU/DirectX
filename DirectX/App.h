#pragma once
#include "Window.h"
class App
{
public:
	App();
	void DoFrame();
	int Run();
private:
	Window window;
};


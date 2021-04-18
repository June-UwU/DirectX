#pragma once
#include "Logger.h"
#include <d3d11.h>
class GraphicsOutput
{
public:
	GraphicsOutput(HWND handle);
	GraphicsOutput(GraphicsOutput& RHS) = delete;
	GraphicsOutput& operator=(GraphicsOutput& Rhs) = delete;
	void EndFrame();
	void ClearBackBuffer(float Red, float Green, float Blue) noexcept;
	~GraphicsOutput();
private:
	ID3D11Device* Device = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11DeviceContext* DeviceContext = nullptr;
	ID3D11RenderTargetView* Target = nullptr;
};


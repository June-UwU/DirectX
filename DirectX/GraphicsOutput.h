#pragma once
#include "Logger.h"
#include "Appception.h"
#include <wrl.h>
#include <d3d11.h>
class GraphicsOutput
{
public:
	GraphicsOutput(HWND handle);
	GraphicsOutput(GraphicsOutput& RHS) = delete;
	GraphicsOutput& operator=(GraphicsOutput& Rhs) = delete;
	void EndFrame();
	void ClearBackBuffer(float Red, float Green, float Blue) noexcept;
	class Exception : public Appception
	{
		using Appception::Appception;
	};
	class Hrception : public Appception
	{
	public:
		Hrception(int line, const char*, HRESULT hr) noexcept;
		std::string TranslateHRESULT()  const noexcept;
		const char* what()				const noexcept override;
		HRESULT		GetError()			noexcept;
	private:
		HRESULT hr;
	};
	~GraphicsOutput() = default;
private:
	Microsoft::WRL::ComPtr <ID3D11Device>			 Device			= nullptr;
	Microsoft::WRL::ComPtr <IDXGISwapChain>         SwapChain		= nullptr;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext>    DeviceContext   = nullptr;
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> Target			= nullptr;
};


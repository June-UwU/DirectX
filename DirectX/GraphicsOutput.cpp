#include "GraphicsOutput.h"

#pragma comment(lib,"d3d11.lib")

GraphicsOutput::GraphicsOutput(HWND handle)
{
	DXGI_SWAP_CHAIN_DESC Descriptor{};
	/*BUFFER INFO*/
	Descriptor.BufferDesc.Width = 0; //telling the descriptor to figure it out using handle
	Descriptor.BufferDesc.Height = 0;//telling the descriptor to figure it out using handle
	Descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;//layout of the pixel
	Descriptor.BufferDesc.RefreshRate.Numerator = 0;//pick whatever refresh rete in there
	Descriptor.BufferDesc.RefreshRate.Denominator = 0;
	Descriptor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;//no height and 
	Descriptor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //scanline order for interlaced display
	Descriptor.SampleDesc.Count = 1;//sampling (anti aliasing)
	Descriptor.SampleDesc.Quality = 0;//sampling (anti aliasing)
	Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//use this buffer as render target in the pipeline
	Descriptor.BufferCount = 1;//one front buffer and one back buffer
	Descriptor.OutputWindow = handle;
	Descriptor.Windowed = true;
	Descriptor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;//swaping method
	Descriptor.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Descriptor,
		&SwapChain,
		&Device,
		nullptr,
		&DeviceContext
	);

	ID3D11Resource* BackBuffer = nullptr;

	SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&BackBuffer));

	Device->CreateRenderTargetView(BackBuffer, nullptr, &Target);

	BackBuffer->Release();
}

GraphicsOutput::~GraphicsOutput()
{
	if (Device)
	{
		Device->Release();
	}
	if (SwapChain)
	{
		SwapChain->Release();
	}
	if (DeviceContext)
	{
		DeviceContext->Release();
	}
	if (Target)
	{
		Target->Release();
	}
}

void GraphicsOutput::EndFrame()
{
	SwapChain->Present(1u, 0);
}

void GraphicsOutput::ClearBackBuffer(float Red, float Green, float Blue) noexcept
{
	const float Color[] = {
		Red,
		Green,
		Blue,
		1.0f
	};

	DeviceContext->ClearRenderTargetView(Target, Color);
}

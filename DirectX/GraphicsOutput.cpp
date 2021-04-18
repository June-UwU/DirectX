#include "GraphicsOutput.h"

#pragma comment(lib,"d3d11.lib")

GraphicsOutput::GraphicsOutput(HWND handle)
{
	LOG_INFO("Initiated Graphics OutPut")
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
	LOG_DEF("Allocating Back Buffer")
	LOG_DEF("SIZE\t: [" + std::to_string(sizeof(BackBuffer)) +"]")

	Device->CreateRenderTargetView(BackBuffer, nullptr, &Target);

	BackBuffer->Release();
	LOG_DEF("Released Back Buffer")
}

GraphicsOutput::~GraphicsOutput()
{
	if (Device)
	{
		Device->Release();
		LOG_DEF("Released Graphics Device")
	}
	if (SwapChain)
	{
		SwapChain->Release();
		LOG_DEF("Released Swap Chain")
	}
	if (DeviceContext)
	{
		DeviceContext->Release();
		LOG_DEF("Released Device Context")
	}
	if (Target)
	{
		Target->Release();
		LOG_DEF("Released Target")
	}
}

void GraphicsOutput::EndFrame()
{
	SwapChain->Present(1u, 0);
	LOG_DEF("Presenting Swap Chain")
}

void GraphicsOutput::ClearBackBuffer(float Red, float Green, float Blue) noexcept
{
	const float Color[] = {
		Red,
		Green,
		Blue,
		1.0f
	};
	//to be cleared after debugging
	LOG_INFO("Clearing BackBuffer")
	LOG_INFO("RED :" +std::to_string(Red)+" GREEN :" + std::to_string(Green) + " BLUE :" + std::to_string(Blue) + " AA :" + std::to_string(Color[3])  )

	DeviceContext->ClearRenderTargetView(Target, Color);
}

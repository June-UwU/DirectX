#include "GraphicsOutput.h"

#pragma comment(lib,"d3d11.lib")

#define GFX_THROW_FAILED(hrcall) if(FAILED(hr = hrcall)) throw GraphicsOutput::Hrception(__LINE__,__FILE__,hrcall)

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

	HRESULT hr;

	GFX_THROW_FAILED(D3D11CreateDeviceAndSwapChain(
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
	));

	Microsoft::WRL::ComPtr <ID3D11Resource> BackBuffer = nullptr;

	GFX_THROW_FAILED(SwapChain->GetBuffer(0, __uuidof(ID3D11Resource),&BackBuffer));
	LOG_DEF("Allocating Back Buffer")
	LOG_DEF("SIZE\t: [" + std::to_string(sizeof(BackBuffer)) +"]")

	GFX_THROW_FAILED ( Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, &Target));

	BackBuffer->Release();
	LOG_DEF("Released Back Buffer")
}


void GraphicsOutput::EndFrame()
{
	HRESULT hr;
	GFX_THROW_FAILED (SwapChain->Present(1u, 0));
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

	DeviceContext->ClearRenderTargetView(Target.Get(), Color);
}


GraphicsOutput::Hrception::Hrception(int line, const char* file, HRESULT hr) noexcept
	:Appception(line, file)
	, hr(hr)
{
}

std::string GraphicsOutput::Hrception::TranslateHRESULT() const noexcept
{
	char* temp{ 0 };
	DWORD count = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr,
		LANG_SYSTEM_DEFAULT, LPSTR(&temp), 0, nullptr);
	if (count == 0)
	{
		return "unidentified error";
	}
	std::string ErrorString = temp;

	LocalFree(temp);

	return ErrorString;
}

const char* GraphicsOutput::Hrception::what() const noexcept
{
	std::ostringstream oss;
	oss << "GRAPHICS ERROR!" << std::endl
		<< "[CODE] 0x" << std::hex << hr << std::endl
		<< "[DESCRIPTION]" << TranslateHRESULT() << std::endl
		<< "[LINE]" << std::dec << (unsigned int)GetLine() << std::endl
		<< "[FILE]" << GetFile() << std::endl;
	data = oss.str();
	return data.c_str();
}


HRESULT GraphicsOutput::Hrception::GetError() noexcept
{
	return hr;
}
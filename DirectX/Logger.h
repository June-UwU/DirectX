#pragma once
#include "Appception.h"
#include <Windows.h>

class Logger
{
public:
	Logger();
	enum class Level
	{
		INFO,
		WARN,
		CRITICAL
	};
	void LogWrite(std::string log , Level level);
private:
	class Winception : public Appception
	{
	public:
		Winception(int line, const char*, HRESULT hr) noexcept;
		std::string TranslateHRESULT() const noexcept;
		const char* what() const noexcept override;
		HRESULT GetError() noexcept;
	private:
		HRESULT hr;
	};
private:
	HANDLE ConsoleHandle;
};
	static Logger Log ;


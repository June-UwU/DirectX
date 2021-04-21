#pragma once
#ifdef ENABLE_LOG

#include <sstream>
#include "Appception.h"
#include <Windows.h>

class Logger
{
public:
	Logger();
	enum class Level
	{
		DEF,
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

#endif //  ENABLE_LOG

#ifdef ENABLE_LOG
#define LOG_INFO(string) Log.LogWrite(string , Logger::Level::INFO);
#define LOG_WARN(string) Log.LogWrite(string , Logger::Level::WARN);
#define LOG_CRIT(string) Log.LogWrite(string , Logger::Level::CRITICAL);
#define LOG_DEF(string)  Log.LogWrite(string , Logger::Level::DEF);
#endif // ENABLE_LOG

#ifndef ENABLE_LOG
#define LOG_INFO(string)
#define LOG_WARN(string)
#define LOG_CRIT(string)
#define LOG_DEF(string)
#endif // !ENABLE_LOG







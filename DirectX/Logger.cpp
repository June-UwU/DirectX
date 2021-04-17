#include "Logger.h"


Logger::Logger()
{
	AllocConsole();

	ConsoleHandle = GetStdHandle(STD_ERROR_HANDLE);
	if (ConsoleHandle == INVALID_HANDLE_VALUE)
	{
		throw Winception(__LINE__, __FILE__, GetLastError());
	}
}

void Logger::LogWrite(std::string log , Level level)
{
	LPDWORD written=0;
	switch (level)
	{
	case Level::INFO:
	{
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_GREEN);
		WriteFile(ConsoleHandle, log.c_str(), log.size(), written, NULL);
	}break;
	case Level::WARN:
	{
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
		WriteFile(ConsoleHandle, log.c_str(), log.size(), written, NULL);
	}break;
	case Level::CRITICAL:
	{
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		WriteFile(ConsoleHandle, log.c_str(), log.size(), written, NULL);
	}break;
	default:
	{
		SetConsoleTextAttribute(ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_BLUE);
		WriteFile(ConsoleHandle, log.c_str(), log.size(), written, NULL);
	}
	}

}



Logger::Winception::Winception(int line, const char* file, HRESULT hr) noexcept
	:Appception(line, file)
	, hr(hr)
{
}

std::string Logger::Winception::TranslateHRESULT() const noexcept
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

const char* Logger::Winception::what() const noexcept
{
	std::ostringstream oss;
	oss << "LOGGER ERROR!" << std::endl
		<< "[CODE] 0x" << std::hex << hr << std::endl
		<< "[DESCRIPTION]" << TranslateHRESULT() << std::endl
		<< "[LINE]" << std::dec << (unsigned int)GetLine() << std::endl
		<< "[FILE]" << GetFile() << std::endl;
	data = oss.str();
	return data.c_str();
}


HRESULT Logger::Winception::GetError() noexcept
{
	return hr;
}

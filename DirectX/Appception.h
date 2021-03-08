#pragma once
#include <exception>
#include <sstream>
#include <string>
class Appception : public std::exception
{
public:
	Appception(int line, const char* file) noexcept;
	const int GetLine() const noexcept;
	const std::string GetFile() const noexcept;
	virtual const char* Type() const noexcept;
	virtual const char* what() const noexcept override;
private:
	int line;
	std::string file;
protected:
	mutable std::string data;
};


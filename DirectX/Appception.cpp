#include "Appception.h"

Appception::Appception(int line, const char* file) noexcept
    :line(line)
    ,file(file)
{

}

const int Appception::GetLine() const noexcept
{
    return line;
}

const std::string Appception::GetFile() const noexcept
{
    return file;
}

const char* Appception::Type() const noexcept
{
    return "General Exception";
}

const char* Appception::what() const noexcept
{
    std::ostringstream temp;
    temp << Type() << std::endl
        << "[FILE]" << file << std::endl
        << "[LINE]" << std::dec << line << std::endl;
    data = temp.str();
    return data.c_str();
}


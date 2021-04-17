#pragma once
#include <chrono>
class Timer
{
public:
	float Mark() noexcept;
	float Peek() noexcept;
private:
	std::chrono::steady_clock::time_point Last;
};


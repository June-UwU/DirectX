#include "Timer.h"

float Timer::Mark() noexcept
{
	auto Old = Last;
	Last = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> Ret = Old - Last;

	return Ret.count();
}

float Timer::Peek() noexcept
{
	return (Last - std::chrono::high_resolution_clock::now()).count();
}

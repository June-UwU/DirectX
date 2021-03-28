#include "KeyBoard.h"

void KeyBoard::KeyPressedEvent(unsigned char code) noexcept
{
	Bindings[code] = 1;
	KeyEventQueue.push(KeyBoard::KeyEvent(KeyBoard::KeyEvent::TYPE::Press, code));
	TrimBuffer(KeyEventQueue);
}

void KeyBoard::KeyReleasedEvent(unsigned char code) noexcept
{
	Bindings[code] = 0;
	KeyEventQueue.push(KeyBoard::KeyEvent(KeyBoard::KeyEvent::TYPE::Press, code));
	TrimBuffer(KeyEventQueue);
}

void KeyBoard::ClearState() noexcept
{
	Bindings.reset();
}

template<typename T>
static void KeyBoard::TrimBuffer(std::queue<T>& Buffer) noexcept
{
	while (Buffer.size() > MAX_QUEUE_LENGTH)
	{
		Buffer.pop();
	}
}
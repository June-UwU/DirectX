#include "KeyBoard.h"

void KeyBoard::KeyPressedEvent(unsigned char code) noexcept
{
	Bindings[code] = 1;
	KeyEventQueue.emplace(KeyBoard::KeyEvent(KeyBoard::KeyEvent::TYPE::Press, code));
	TrimBuffer(KeyEventQueue);
}

void KeyBoard::KeyReleasedEvent(unsigned char code) noexcept
{
	Bindings[code] = 0;
	KeyEventQueue.emplace(KeyBoard::KeyEvent(KeyBoard::KeyEvent::TYPE::Press, code));
	TrimBuffer(KeyEventQueue);
}

void KeyBoard::ClearState() noexcept
{
	Bindings.reset();
}


#include "KeyBoard.h"

bool KeyBoard::KeyDown(unsigned char code) noexcept
{
	return Bindings[code];
}

std::optional<KeyBoard::KeyEvent> KeyBoard::GetEvent() noexcept
{
	if (!KeyEventQueue.empty())
	{
		KeyEvent Ret = KeyEventQueue.front();
		KeyEventQueue.pop();
		return Ret;
	}
	return {};
}

std::optional<char> KeyBoard::GetCharBuffer() noexcept
{
	if (!CharQueue.empty()) 
	{
		char ret = CharQueue.front();
		CharQueue.pop();
		return ret;
	}
	return {};
}

void KeyBoard::FLushCharQueue() noexcept
{
	CharQueue = std::queue<char>();
}

void KeyBoard::FlushEventQueue() noexcept
{
	KeyEventQueue = std::queue < KeyBoard::KeyEvent>();
}

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

void KeyBoard::CharEvent(char letter) noexcept
{
	CharQueue.push(letter);
	TrimBuffer(CharQueue);
}

template<typename T>
static void KeyBoard::TrimBuffer(std::queue<T>& Buffer) noexcept
{
	while (Buffer.size() > MAX_QUEUE_LENGTH)
	{
		Buffer.pop();
	}
}
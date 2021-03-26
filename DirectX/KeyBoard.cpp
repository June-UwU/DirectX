#include "KeyBoard.h"

KeyBoard::KeyBoard() noexcept
{
}

bool KeyBoard::CharQueueEmpty() noexcept
{
	return CharQueue.empty();
}

std::optional<KeyBoard::KeyEvent> KeyBoard::GetEvent() noexcept
{
	if (KeyQueue.size() > -1)
	{
		KeyEvent Event = KeyQueue.front();
		KeyQueue.pop();
		return Event;
	}
	return {};
}

std::optional<char> KeyBoard::ReadChar() noexcept
{
	if (CharQueue.size() > -1)
	{
		char Event = CharQueue.front();
		CharQueue.pop();
		return Event;
	}
	return {};
}

void KeyBoard::FlushQueue() noexcept
{
	CharQueue = std::queue<char>();
	KeyQueue = std::queue<KeyEvent>();
}

void KeyBoard::CharEvent(char character) noexcept
{
	CharQueue.emplace(character);
	TrimBuffer(CharQueue);
}

void KeyBoard::KeyPressedEvent(char code) noexcept
{
	Bindings[code] = true;
	KeyQueue.emplace(KeyEvent(KeyEvent::KeyEvent::Type::KeyDown, code));
	TrimBuffer(KeyQueue);
}

void KeyBoard::KeyReleasedEvent(char code) noexcept
{
	Bindings[code];
	KeyQueue.emplace(KeyEvent(KeyEvent::Type::KeyUp, code));
	TrimBuffer(KeyQueue);
}

void KeyBoard::ClearBindings() noexcept
{
	Bindings.reset();
}

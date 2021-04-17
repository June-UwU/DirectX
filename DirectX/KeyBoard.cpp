#include "KeyBoard.h"

bool KeyBoard::KeyDown(unsigned char code) noexcept
{
	LOG_DEF("Setting Proper Bindings:\t["+std::to_string(code)+"]")
	return Bindings[code];
}

std::optional<KeyBoard::KeyEvent> KeyBoard::GetEvent() noexcept
{
	LOG_DEF("Pulling char for key event buffer")
	if (!KeyEventQueue.empty())
	{
		LOG_INFO("Pull Sucessful")
		KeyEvent Ret = KeyEventQueue.front();
		KeyEventQueue.pop();
		return Ret;
	}
	LOG_WARN("BUFFER EMPTY!")
	return {};
}

std::optional<char> KeyBoard::GetCharBuffer() noexcept
{
	LOG_DEF("Pulling Char For Char Event Buffer")
	if (!CharQueue.empty()) 
	{
		LOG_INFO("PULL SUCESSFUL")
		char ret = CharQueue.front();
		CharQueue.pop();
		return ret;
	}
	LOG_WARN("BUFFER EMPTY!")
	return {};
}

void KeyBoard::FLushCharQueue() noexcept
{
	LOG_INFO("Flushing Character Queue")
	CharQueue = std::queue<char>();
}

void KeyBoard::FlushEventQueue() noexcept
{
	LOG_INFO("Flushing Event Queue")
	KeyEventQueue = std::queue < KeyBoard::KeyEvent>();
}

void KeyBoard::KeyPressedEvent(unsigned char code) noexcept
{
	LOG_DEF("Key Pressed["+std::to_string(code)+"]")
	Bindings[code] = 1;
	KeyEventQueue.push(KeyBoard::KeyEvent(KeyBoard::KeyEvent::TYPE::Press, code));
	TrimBuffer(KeyEventQueue);
}

void KeyBoard::KeyReleasedEvent(unsigned char code) noexcept
{
	LOG_DEF("Key Released[" + std::to_string(code) + "]")
	Bindings[code] = 0;
	KeyEventQueue.push(KeyBoard::KeyEvent(KeyBoard::KeyEvent::TYPE::Press, code));
	TrimBuffer(KeyEventQueue);
}

void KeyBoard::ClearState() noexcept
{
	LOG_INFO("BINGINGS RESET")
	Bindings.reset();
}

void KeyBoard::CharEvent(char letter) noexcept
{
	LOG_INFO("KEY CHAR EVENT")
	CharQueue.push(letter);
	TrimBuffer(CharQueue);
}

template<typename T>
static void KeyBoard::TrimBuffer(std::queue<T>& Buffer) noexcept
{
	//LOG_INFO("BUFFER TRIM INITIALISED[SIZE:"+std::to_string(Buffer.size())+"]")
	while (Buffer.size() > MAX_QUEUE_LENGTH)
	{
		Buffer.pop();
	}
	//LOG_INFO("BUFFER TRIM DONE[SIZE:" + std::to_string(Buffer.size()) + "]")
}
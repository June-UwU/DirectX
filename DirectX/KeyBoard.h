#pragma once
#include "Logger.h"
#include <bitset>
#include <queue>
#include <optional>

class KeyBoard
{
	friend class Window;
private:
	//private internal classes
	class KeyEvent
	{
	public:
		enum class TYPE
		{
			Press,
			Release
		};
	private:
		TYPE type;
		unsigned char code;
	public:
		KeyEvent(TYPE type, unsigned char code) noexcept
			:type(type)
			, code(code)
		{}
		bool IsKeyPress() noexcept
		{
			return type == KeyEvent::TYPE::Press;
		}
		bool IsKeyRelease() noexcept
		{
			return type == KeyEvent::TYPE::Release;
		}
	};
public:
	KeyBoard() = default;
	//Client side
	bool KeyDown(unsigned char code) noexcept;
	std::optional<KeyBoard::KeyEvent> GetEvent() noexcept;
	std::optional<char> GetCharBuffer() noexcept;
	void FLushCharQueue()  noexcept;
	void FlushEventQueue() noexcept;
	//auto repeat variable
	bool ENABLE_AUTO_REPEAT = 1;
private:
	static const unsigned int	   MAX_BITSET_LENGTH = 256u;
	static const unsigned int      MAX_QUEUE_LENGTH  = 16u;
	std::bitset<MAX_BITSET_LENGTH> Bindings;
	std::queue<char>			   CharQueue ;
	std::queue<KeyBoard::KeyEvent> KeyEventQueue ;
private:
	void KeyPressedEvent(unsigned char code)  noexcept;
	void KeyReleasedEvent(unsigned char code) noexcept;
	void CharEvent(char letter)				  noexcept;
	void ClearState()						  noexcept;
	template <typename T>
	static void TrimBuffer(std::queue<T>& Buffer) noexcept;
};


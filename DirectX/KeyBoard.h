#pragma once

#include <bitset>
#include <queue>
#include <optional>
class KeyBoard
{
	friend class Window;
private:
	class KeyEvent
	{
	public:
		enum class Type
		{
			Invalid,
			KeyDown,
			KeyUp,
		};
		KeyEvent(Type type, unsigned char code)
			:type(type)
			, code(code)
		{}
		const bool IsPressed() noexcept
		{
			return type == Type::KeyDown;
		}
		const bool IsReleased() noexcept
		{
			return type == Type::KeyUp;
		}
		Type type;
		unsigned char code;
	};
public:
	KeyBoard() noexcept;
	KeyBoard(const KeyBoard& rhs) = delete;
	KeyBoard& operator =(const KeyBoard& rhs) = delete;
	bool CharQueueEmpty() noexcept;
	std::optional<KeyEvent> GetEvent() noexcept;
	std::optional<char> ReadChar() noexcept;
	void FlushQueue() noexcept;
	bool  AutoRepeatEnable = true;
private:
	void CharEvent(char  character) noexcept;
	void KeyPressedEvent(char code) noexcept;
	void KeyReleasedEvent(char code) noexcept;
	void ClearBindings() noexcept;
	template <typename T>
	void TrimBuffer(std::queue<T>& buffer) noexcept;
private:
	static const std::size_t Max_KeyCodes = 256u;
	static const std::size_t Max_Queue_Size = 16u;
	std::bitset<Max_KeyCodes> Bindings;
	std::queue<KeyEvent> KeyQueue;
	std::queue<char> CharQueue;
};

template<typename T>
inline void KeyBoard::TrimBuffer(std::queue<T>& buffer) noexcept
{
	while (buffer.size() > Max_Queue_Size)
	{
		buffer.pop();
	}
}

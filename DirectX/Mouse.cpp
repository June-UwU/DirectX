#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() noexcept
{
	return std::pair<int, int>(CurrentMousePosX,CurrentMousePosY);
}

int Mouse::GetX() noexcept
{
	return CurrentMousePosX;
}

int Mouse::GetY() noexcept
{
	return CurrentMousePosY;
}

std::optional < Mouse:: MouseEvent > Mouse::ReadBuffer() noexcept
{
	if (MouseQueue.size() > 0u)
	{
		MouseEvent ret = MouseQueue.front();
		MouseQueue.pop();
		return ret;
	}
	return {};
}

bool Mouse::LeftDown() noexcept
{
	return LeftPress;
}

bool Mouse::RightDown() noexcept
{
	return RightPress;
}

bool Mouse::MiddleDown() noexcept
{
	return MiddlePress;
}

void Mouse::Reset() noexcept
{
	LeftPress = RightPress = MiddlePress = false;
	FlushQueue();
}

void Mouse::FlushQueue() noexcept
{
	MouseQueue = std::queue<MouseEvent>();
}

void Mouse::MouseMove(int UpdateX, int UpdateY) noexcept
{
	CurrentMousePosX = UpdateX;
	CurrentMousePosY = UpdateY;

	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::Move, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::LeftMousePressEvent(int x, int y) noexcept
{
	LeftPress = true;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::LPress, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::LeftMouseReleaseEvent(int x, int y) noexcept
{
	LeftPress = false;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::LRelease, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::RightMousePressEvent(int x, int y) noexcept
{
	RightPress = true;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::RPress, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::RightMouseReleaseEvent(int x, int y) noexcept
{
	RightPress = false;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::RRelease, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::MiddleMousePressEvent(int x, int y) noexcept
{
	MiddlePress = true;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::MPress, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::MiddleMouseReleaseEvent(int x, int y) noexcept
{
	MiddlePress = false;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::MRelease, *this));
	TrimBuffer(MouseQueue);
}
/*Avoided MouseEvent construction below this for emplace testing purposes may or may not be changed in testing */

void Mouse::ScrollEventUp(int x, int y) noexcept
{
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(Mouse::MouseEvent::TYPE::ScrollUp,*this);
	TrimBuffer(MouseQueue);
}

void Mouse::ScrollEventDown(int x, int y) noexcept
{
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(Mouse::MouseEvent::TYPE::ScrollDown, *this);
	TrimBuffer(MouseQueue);
}

void Mouse::TrimBuffer(std::queue<MouseEvent>& buffer) noexcept
{
	while(MouseQueue.size() > MAX_QUEUE_SIZE)
	{
		MouseQueue.pop();
	}
}



#include "Mouse.h"

std::pair<int, int> Mouse::GetPos() noexcept
{
	LOG_INFO("Getting mouse pos :\t X["+ std::to_string(CurrentMousePosX) + "]" + "Y[" + std::to_string(CurrentMousePosX) +"]")
	return std::pair<int, int>(CurrentMousePosX,CurrentMousePosY);
}

int Mouse::GetX() noexcept
{
	LOG_WARN("XPOS RETRIVAL\t["+std::to_string(CurrentMousePosX)+"]")
	return CurrentMousePosX;
}

int Mouse::GetY() noexcept
{
	LOG_WARN("YPOS RETRIVAL\t[" + std::to_string(CurrentMousePosY) + "]")
	return CurrentMousePosY;
}

std::optional < Mouse:: MouseEvent > Mouse::ReadBuffer() noexcept
{
	LOG_DEF("Mouse Queue Read")
	if (MouseQueue.size() > 0u)
	{
		LOG_INFO("Read Sucessful")
		MouseEvent ret = MouseQueue.front();
		MouseQueue.pop();
		return ret;
	}
	LOG_WARN("QUEUE EMPTY")
	return {};
}

bool Mouse::LeftDown() noexcept
{
	LOG_DEF("Left Mouse Down Check")
	return LeftPress;
}

bool Mouse::RightDown() noexcept
{
	LOG_DEF("Right Mouse Down Check")
	return RightPress;
}

bool Mouse::MiddleDown() noexcept
{
	LOG_DEF("Middle Mouse Down Check")
	return MiddlePress;
}

void Mouse::Reset() noexcept
{
	LOG_INFO("Mouse Binding Reset Check")
	LeftPress = RightPress = MiddlePress = false;
	FlushQueue();
}

void Mouse::FlushQueue() noexcept
{
	LOG_INFO("Mouse Queue Flush")
	MouseQueue = std::queue<MouseEvent>();
}

void Mouse::MouseMove(int UpdateX, int UpdateY) noexcept
{
	LOG_INFO("MOUSE MOVE :\t X[" + std::to_string(CurrentMousePosX) + "]" + "Y[" + std::to_string(CurrentMousePosX) + "]")
	CurrentMousePosX = UpdateX;
	CurrentMousePosY = UpdateY;

	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::Move, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::LeftMousePressEvent(int x, int y) noexcept
{
	LOG_DEF("Left Mouse Down ")
	LeftPress = true;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::LPress, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::LeftMouseReleaseEvent(int x, int y) noexcept
{
	LOG_DEF("Left Mouse Up")
	LeftPress = false;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::LRelease, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::RightMousePressEvent(int x, int y) noexcept
{
	LOG_DEF("Right Mouse Down ")
	RightPress = true;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::RPress, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::RightMouseReleaseEvent(int x, int y) noexcept
{
	LOG_DEF("Right Mouse Up ")
	RightPress = false;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::RRelease, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::MiddleMousePressEvent(int x, int y) noexcept
{
	LOG_DEF("Middle Mouse Down ")
	MiddlePress = true;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::MPress, *this));
	TrimBuffer(MouseQueue);
}

void Mouse::MiddleMouseReleaseEvent(int x, int y) noexcept
{
	LOG_DEF("Middle Mouse Up")
	MiddlePress = false;
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(MouseEvent(Mouse::MouseEvent::TYPE::MRelease, *this));
	TrimBuffer(MouseQueue);
}
/*Avoided MouseEvent construction below this for emplace testing purposes may or may not be changed in testing */

void Mouse::ScrollEventUp(int x, int y) noexcept
{
	LOG_DEF("Scroll Up ")
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(Mouse::MouseEvent::TYPE::ScrollUp,*this);
	TrimBuffer(MouseQueue);
}

void Mouse::ScrollEventDown(int x, int y) noexcept
{
	LOG_DEF("Scroll Down ")
	CurrentMousePosX = x;
	CurrentMousePosY = y;
	MouseQueue.emplace(Mouse::MouseEvent::TYPE::ScrollDown, *this);
	TrimBuffer(MouseQueue);
}

void Mouse::TrimBuffer(std::queue<MouseEvent>& buffer) noexcept
{
	//LOG_INFO("TRIM BUFFER\t["+ std::to_string(buffer.size())+"]")
	while(MouseQueue.size() > MAX_QUEUE_SIZE)
	{
		MouseQueue.pop();
	}
	//LOG_INFO("TRIM BUFFER DONE\t[" + std::to_string(buffer.size()) + "]")
}



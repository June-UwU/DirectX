#pragma once
#include "Logger.h"
#include <queue>
#include <optional>
#include <utility>
class Mouse
{
	friend class Window;
public:
	class MouseEvent
	{
	public:
		enum class TYPE
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			MPress,
			MRelease,
			ScrollUp,
			ScrollDown,
			Move
		};
		MouseEvent(int x, int y, TYPE type) noexcept
			:x(x)
			, y(y)
			, type(type)
		{};
		MouseEvent(TYPE type,const Mouse& Master) noexcept
			:type(type)
			,x(Master.CurrentMousePosX)
			,y(Master.CurrentMousePosY)
			,LeftDown(Master.LeftPress)
			,RightDown(Master.RightPress)
			,MiddleDown(Master.MiddlePress)
		{}
		int GetX() noexcept
		{
			return x;
		};
		int GetY() noexcept
		{
			return y;
		};
	private:
		bool LeftDown = false;
		bool RightDown = false;
		bool MiddleDown = false;
		TYPE type;
		int x;
		int y;
	};
public:
	std::pair<int, int> GetPos() noexcept;
	int GetX() noexcept;
	int GetY() noexcept;
	std::optional<MouseEvent> ReadBuffer() noexcept;
	bool LeftDown() noexcept;
	bool RightDown() noexcept;
	bool MiddleDown() noexcept;
	void Reset() noexcept;
	void FlushQueue() noexcept;
private:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse operator=(const Mouse&) = delete;
	void MouseMove(int UpdateX, int UpdateY) noexcept;
	void LeftMousePressEvent(int x ,int y) noexcept;
	void LeftMouseReleaseEvent(int x, int y) noexcept;
	void RightMousePressEvent(int x, int y) noexcept;
	void RightMouseReleaseEvent(int x, int y) noexcept;
	void MiddleMousePressEvent(int x, int y) noexcept;
	void MiddleMouseReleaseEvent(int x, int y) noexcept;
	void ScrollEventUp(int x, int y) noexcept;
	void ScrollEventDown(int x, int y) noexcept;
	void TrimBuffer(std::queue<MouseEvent>& buffer) noexcept;
private:
	static constexpr int MAX_QUEUE_SIZE = 16u;
	bool LeftPress    = false;
	bool RightPress	  = false;
	bool MiddlePress  = false;
	int  CurrentMousePosX;
	int	 CurrentMousePosY;
	std::queue<MouseEvent> MouseQueue;
};


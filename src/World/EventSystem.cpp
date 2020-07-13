
#include "EventSystem.h"

Int2 EventSystem::MousePosition;
Int2 EventSystem::MousePositionDelta;
std::chrono::steady_clock::time_point lastUpdateTime;
float EventSystem::LastFrameDuration = 0;
Callback<float> EventSystem::UpdateCallback;
Callback<int> EventSystem::KeyDownCallback;
Callback<int> EventSystem::KeyUpCallback;
Callback<int, int, int, int, int, int> EventSystem::MouseUpdateCallback;

Callback<> EventSystem::LeftMouseButtonDownCallback;
Callback<> EventSystem::LeftMouseButtonUpCallback;

Callback<> EventSystem::MiddleMouseButtonDownCallback;
Callback<> EventSystem::MiddleMouseButtonUpCallback;

Callback<> EventSystem::RightMouseButtonDownCallback;
Callback<> EventSystem::RightMouseButtonUpCallback;

Callback<> EventSystem::MouseMovementCallback;
Callback<> EventSystem::MouseWheelCallback;

Callback<> EventSystem::ScreenUpdateCallback;

void EventSystem::OnUpdate()
{
	auto current = std::chrono::steady_clock::now();
	LastFrameDuration = (float) (std::chrono::duration_cast<std::chrono::nanoseconds>(current - lastUpdateTime).count() / 1e9);
	lastUpdateTime = std::chrono::steady_clock::now();
	UpdateCallback.Invoke(LastFrameDuration);
	MousePositionDelta = Int2(0, 0);
}

void EventSystem::OnKeyDown(int key)
{
	KeyDownCallback.Invoke(key);
}

void EventSystem::OnKeyUp(int key)
{
	KeyUpCallback.Invoke(key);
}

void EventSystem::OnMouseUpdate(int button, int state, int wheel, int direction, int x, int y)
{
    MousePositionDelta = Int2(x, y) - MousePosition;
	MousePosition = Int2(x, y);

	MouseUpdateCallback.Invoke(button, state, wheel, direction, x, y);

    auto btn = (MouseButton)button;
	auto btnState = (MouseButtonState)state;

	switch (btn)
	{
		case EventSystem::MouseButton::Left:
			MouseButtonClick(LeftMouseButtonDownCallback, LeftMouseButtonUpCallback, btnState);
			break;
		case EventSystem::MouseButton::Middle:
			MouseButtonClick(MiddleMouseButtonDownCallback, MiddleMouseButtonUpCallback, btnState);
			break;
		case EventSystem::MouseButton::Right:
			MouseButtonClick(RightMouseButtonDownCallback, RightMouseButtonUpCallback, btnState);
			break;
		default:
			break;
	}

	if (MousePositionDelta != Int2(0,0))
	{
		MouseMovementCallback.Invoke();
	}

	if (direction != 0 && direction != -2)
	{
		MouseWheelCallback.Invoke();
	}
}

void EventSystem::MouseButtonClick(Callback<> downCallback, Callback<> upCallback, EventSystem::MouseButtonState btnState)
{
	switch (btnState)
	{
		case EventSystem::MouseButtonState::Down:
			downCallback.Invoke();
			break;
		case EventSystem::MouseButtonState::Up:
			upCallback.Invoke();
			break;
		default:
			break;
	}
}

void EventSystem::ScreenUpdate()
{
	ScreenUpdateCallback.Invoke();
}

void EventSystem::Start()
{
	lastUpdateTime = std::chrono::steady_clock::now();
}

#include "Button.h"

Button::Button(IPointInside &pointInside) : pointInside(pointInside)
{
    leftButtonDownCallbackId = EventSystem::LeftMouseButtonDownCallback.Register([this]{ this->OnLeftMouseButtonDown();});
    leftButtonUpCallbackId = EventSystem::LeftMouseButtonUpCallback.Register([this] {this->OnLeftMouseButtonUp(); });
    this->drag = false;
    this->updateCallbackId = -1;
    this->active = true;
}

bool Button::IsMouseOver() const
{
	return pointInside.IsPointInside(EventSystem::MousePosition);
}

void Button::OnMousePositionUpdate()
{
	if (!active)
	{
		return;
	}
	if (drag)
	{
		DragCallback.Invoke(EventSystem::MousePositionDelta);
		return;
	}
    totalDelta += EventSystem::MousePositionDelta;
    if (abs(totalDelta.x + totalDelta.y) > DragThreshold)
    {
        drag = true;
        DragCallback.Invoke(totalDelta);
    }
}

void Button::OnLeftMouseButtonDown()
{
		if (!active)
	{
		return;
	}
	if (!pointInside.IsPointInside(EventSystem::MousePosition))
	{
		return;
	}
	totalDelta = {0, 0};
	updateCallbackId =	EventSystem::MouseMovementCallback.Register([this] {this->OnMousePositionUpdate(); });
}

void Button::OnLeftMouseButtonUp()
{
	if (!active)
	{
		return;
	}

	if (!drag && pointInside.IsPointInside(EventSystem::MousePosition))
	{
		ClickCallback.Invoke(EventSystem::MousePosition);
	}
	drag = false;
    EventSystem::MouseMovementCallback.Deregister(updateCallbackId);
}

Button::~Button()
{
    EventSystem::LeftMouseButtonDownCallback.Deregister(leftButtonDownCallbackId);
    EventSystem::LeftMouseButtonUpCallback.Deregister(leftButtonUpCallbackId);
}



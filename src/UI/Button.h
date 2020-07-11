#pragma once

#include "../Primitives/Color.h"
#include "../Canvas2D/Canvas2D.h"
#include "../Helpers/Callback.h"
#include "../World/EventSystem.h"
#include "IPointInside.h"

constexpr int DragThreshold = 2;

/* Handles detection of clicking and dragging */
class Button
{
	public:
	
	IPointInside& pointInside;
	bool active;
	Callback<Int2> DragCallback;
	Callback<Int2> ClickCallback;

	explicit Button(IPointInside& pointInside);
	~Button();
	
	bool IsMouseOver();

	private:
	
	Int2 totalDelta;
	bool drag;
	int updateCallbackId; /* Saved for later callback deregistering*/
    int leftButtonDownCallbackId;
    int leftButtonUpCallbackId;
	void OnLeftMouseButtonDown();
	void OnLeftMouseButtonUp();
	void OnMousePositionUpdate();

};
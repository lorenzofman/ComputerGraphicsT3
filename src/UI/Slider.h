#pragma once

#include <functional>
#include "../Primitives/Float2.h"
#include "../Helpers/Callback.h"
#include "../World/EventSystem.h"
#include "../Primitives/Color.h"
#include "Button.h"
#include "../Primitives/CircleButton.h"

/* Generic class which handles Slider manipulation (calling the registered value whenever value changes) */
class Slider
{
	public:
	Slider(Float2 center, float width, float height, Color backgroundColor, Color fillColor, Color marker);
	void Draw() const;
	Callback<float> valueChangeCallback;
	Float2 center;
	float width;
	float height;
	CircleButton handle;
	float value = 0.5f;

	private:
	Color backgroundColor;
	Color fillColor;
	void Drag(Int2 delta);
};
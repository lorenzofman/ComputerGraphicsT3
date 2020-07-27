#include "Slider.h"
#include "../Helpers/Utils.h"

Slider::Slider(Float2 center, float width, float height, Color backgroundColor, Color fillColor, Color marker) :
		center(center), width(width), height(height), backgroundColor(backgroundColor), fillColor(fillColor),
		handle(CircleButton(center, height/2, marker))
{
	handle.DragCallback.Register([this] (Int2 delta){this->Drag(delta);});
}

void Slider::Draw() const
{
	float start = center.x - width / 2;
	float mid = handle.circle.pos.x;
	float end = center.x + width / 2;
	float bottom = center.y - height / 2;
	float top = center.y + height / 2;

	Canvas2D::SetColor(backgroundColor);
	Canvas2D::DrawFilledRect(Float2(start, bottom), Float2(end, top));

	Canvas2D::SetColor(fillColor);
	Canvas2D::DrawFilledRect(Float2(start, bottom), Float2(mid, top));
	handle.Draw();
}

void Slider::Drag(Int2 delta)
{
	float start = center.x - width / 2;
	float end = center.x + width / 2;
	handle.circle.pos += {(float) delta.x, 0};
	handle.circle.pos.x = Utils::Clamp(handle.circle.pos.x, start, end);
	float mid = handle.circle.pos.x;

	value = (mid - start) / width;
	valueChangeCallback.Invoke(value);
}
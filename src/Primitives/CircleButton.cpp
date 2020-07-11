#include "CircleButton.h"
constexpr float ButtonMouseOverColorMultiplier = 0.8f;

CircleButton::CircleButton(Float2 pos, float radius, Color color) : circle(Circle(pos, radius)), Button((IPointInside&)circle), color(color)
{

}

void CircleButton::Draw()
{
    if (IsMouseOver())
    {
        Canvas2D::SetColor(color * ButtonMouseOverColorMultiplier);
    }
    else
    {
        Canvas2D::SetColor(color);
    }
    Canvas2D::DrawFilledCircle(circle.pos, circle.radius, 32);
}
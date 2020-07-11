#include "Rect.h"

Rect::Rect(Float2 bottomLeft, Float2 topRight)
{
    this->bottomLeft = bottomLeft;
    this->topRight = topRight;
}

bool Rect::IsPointInside(Int2 point)
{
    auto x = (float) point.x;
    auto y = (float) point.y;
    return x >= bottomLeft.x && x <= topRight.x && y >= bottomLeft.y && y <= topRight.y;
}

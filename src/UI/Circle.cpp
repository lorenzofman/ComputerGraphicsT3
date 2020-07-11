#include "Circle.h"

bool Circle::IsPointInside(Int2 point)
{
    Float2 fPoint = Float2((float)point.x, (float)point.y);
    return Float2::DistanceSq(fPoint, pos) < radius * radius;
}

Circle::Circle(Float2 pos, float radius) : radius(radius)
{
    this->pos = pos;
}

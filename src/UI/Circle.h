#pragma once

#include "IPointInside.h"
#include "../Primitives/Int2.h"
#include "../Primitives/Float2.h"
#include "../Primitives/Color.h"

/* Structure to represent a circle */
class Circle : IPointInside
{
    public:
    Circle(Float2 pos, float radius);
    Float2 pos;
    const float radius;
    bool IsPointInside(Int2 point) override;
};
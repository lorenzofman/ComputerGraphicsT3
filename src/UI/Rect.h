#pragma once

#include "IPointInside.h"
#include "../Primitives/Int2.h"
#include "../Primitives/Float2.h"
#include "../Primitives/Color.h"

/* Structure to store a rectangle information */
class Rect : IPointInside
{
    public:
    Rect(Float2 bottomLeft, Float2 topRight);
    Float2 bottomLeft;
    Float2 topRight;
    bool IsPointInside(Int2 point) override;
};
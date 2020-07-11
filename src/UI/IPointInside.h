#pragma once

#include "../Primitives/Int2.h"
/* Common interface for classes to implement distinct shaped-buttons */
class IPointInside
{
    public:

    virtual bool IsPointInside(Int2 point) = 0;
};
#pragma once

#include "Float3.h"

struct Edge
{
    Float3 p1;
    Float3 p2;
    Edge(Float3 p1, Float3 p2)
    {
        this->p1 = p1;
        this->p2 = p2;
    }
};

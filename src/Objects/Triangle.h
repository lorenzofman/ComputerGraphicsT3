#pragma once

#include "../Primitives/Float3.h"

struct Triangle
{
	Float3 a;
	Float3 b;
	Float3 c;

	Triangle(Float3 a, Float3 b, Float3 c)
    {
	    this->a = a;
	    this->b = b;
	    this->c = c;
    }
};
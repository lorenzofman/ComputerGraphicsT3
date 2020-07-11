#pragma once

#include <utility>
#include <vector>
#include "Triangle.h"

struct Object
{
	std::vector<Triangle> triangles;
	explicit Object(std::vector<Triangle> triangles)
	{
        this->triangles = std::move(triangles);
    }

    void Translate(Float3 displacement)
    {
	    for (auto tri : triangles)
        {
	        tri.a += displacement;
            tri.b += displacement;
            tri.c += displacement;
        }
    }
};
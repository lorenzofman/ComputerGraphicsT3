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
	    for (int i = 0; i< triangles.size(); i++)
        {
	        triangles[i].a += displacement;
			triangles[i].b += displacement;
			triangles[i].c += displacement;
        }
    }
};
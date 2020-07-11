#pragma once

#include <utility>
#include <vector>
#include "Triangle.h"

struct Object
{
	std::vector<Triangle> triangles;
	explicit Object(std::vector<Triangle> triangles);
};

Object::Object(std::vector<Triangle> triangles)
{
	this->triangles = std::move(triangles);
}

#pragma once

#include "Object.h"

class ObjectCreator
{
    public:

    static Object BuildCylinder(int segments, int rings, float radius, float height);
	static Object BuildSphere(int segments, int rings, float radius);

    static std::vector<Triangle> TriangulateGrid(int w, int h, const Float3 *matrix);
};
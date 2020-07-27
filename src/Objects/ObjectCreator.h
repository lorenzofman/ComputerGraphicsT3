#pragma once

#include "Object.h"

class ObjectCreator
{
    public:
	static Object BuildCube(float edge);
	static Object BuildBox(float width, float height, float depth);
	static Object BuildCircle(int segments, float radius);
	static Object BuildCylinder(int segments, float radius, float height);
	static Object BuildFlatRoundedRectangle(float height, float width, float depth, int segments);
	static Object BuildMotorCylinder(int segments, float radius, float height);
    static std::vector<Face> ExtrudeFace(const Face& face, Float3 direction);
};
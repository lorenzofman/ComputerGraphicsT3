#pragma once

#include "Object.h"

class ObjectCreator
{
    public:

	static Object BuildCube(float edgeSize);
	static Object Circle(int segments, float radius);
	static Object BuildCylinder(int segments, float radius, float height);
	static Object BuildFlatRoundedRectangle(float height, float width, float depth, int segments);
//	static Object BuildSphere(int segments, int rings, float radius);
//    static std::vector<Face> GridFace(int w, int h, const Float3 *matrix);
    static std::vector<Face> ExtrudeFace(const Face& face, Float3 direction);
};
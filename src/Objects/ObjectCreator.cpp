#include "ObjectCreator.h"
#include "../Primitives/Constants.h"

Object ObjectCreator::BuildCylinder()
{

	//return Object();
}

Object ObjectCreator::BuildSphere(int segments, int rings, float radius)
{
	auto matrix = new Float3[segments * rings];
	float ringStep = PI / (float) rings;
	float segmentStep = (2 * PI) / (float) segments;
	float r = radius;

	float theta;
	float phi;

	for (int i = 0; i < rings; i++)
	{
		phi = ringStep * (float) i;
		for (int j = 0; j < segments; j++)
		{
			theta = segmentStep * (float) j;
			matrix[i * segments + j] = Float3(
					r * cosf(theta) * cosf(phi),
					r * sinf(phi),
					r * sinf(theta) * cosf(phi));
		}
	}

	std::vector<Triangle> tris;
	return Object(tris);
}



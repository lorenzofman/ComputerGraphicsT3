#include "ObjectCreator.h"
#include "../Primitives/Constants.h"

Object ObjectCreator::BuildCylinder(int segments, int rings, float radius, float height)
{
    auto matrix = new Float3[segments * rings];
    float ringStep = height / (float) rings;
    float segmentStep = (2 * PI) / (float) segments;
    float r = radius;

    float theta;
    float phi;

    for (int i = 0; i < rings; i++)
    {
        phi = ringStep * ((float) i - rings / 2);
        for (int j = 0; j < segments; j++)
        {
            theta = segmentStep * (float) j;
            matrix[i * segments + j] = Float3(
                    r * cosf(theta),
                    r * sinf(phi),
                    r * sinf(theta));
        }
    }

    return Object(TriangulateGrid(segments, rings, matrix));
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
		phi = ringStep * ((float) i - rings / 2);
		for (int j = 0; j < segments; j++)
		{
			theta = segmentStep * (float) j;
			matrix[i * segments + j] = Float3(
					r * cosf(theta) * cosf(phi),
					r * sinf(phi),
					r * sinf(theta) * cosf(phi));
		}
	}

    return Object(TriangulateGrid(segments, rings, matrix));
}

std::vector<Triangle> ObjectCreator::TriangulateGrid(int w, int h, const Float3 *matrix)
{
    std::vector<Triangle> tris;

    for (int i = 0; i < h - 1; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tris.emplace_back(matrix[i * w + j],
                    matrix[i * w + j + 1],
                    matrix[(i + 1) * w + j]);
        }
    }
    int last = w * h - 1;
    for (int j = 0; j < w - 1; j++)
    {
        tris.emplace_back(
                matrix[(h - 1) * w + j],
                matrix[(h - 1) * w + j + 1],
                matrix[last]
        );
    }
    return tris;
}
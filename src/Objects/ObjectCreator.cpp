#include "ObjectCreator.h"
#include "../Primitives/Constants.h"

Object ObjectCreator::Circle(int segments, float radius)
{
	std::vector<Float3> points;
	float step = 2 * PI / (float) segments;
	for (int i = 0; i < segments; i++)
	{
		float f = step * (float) i;
		points.emplace_back(cosf(f) * radius, sinf(f) * radius, 0);
	}
	std::vector<Face> faces;
	faces.emplace_back(points);
	return Object(faces);
}


Object ObjectCreator::BuildCylinder(int segments, float radius, float height)
{
	auto circle = ObjectCreator::Circle(segments, radius);
	return Object(ExtrudeFace(circle.faces[0], {0, 0, height}));
}

//Object ObjectCreator::BuildSphere(int segments, int rings, float radius)
//{
//	auto matrix = new Float3[segments * rings];
//	float ringStep = PI / (float) rings;
//	float segmentStep = (2 * PI) / (float) segments;
//	float r = radius;
//
//	float theta;
//	float phi;
//
//	for (int i = 0; i < rings; i++)
//	{
//		phi = ringStep * ((float) i - rings / 2);
//		for (int j = 0; j < segments; j++)
//		{
//			theta = segmentStep * (float) j;
//			matrix[i * segments + j] = Float3(
//					r * cosf(theta) * cosf(phi),
//					r * sinf(phi),
//					r * sinf(theta) * cosf(phi));
//		}
//	}
//
//    return Object(GridFace(segments, rings, matrix));
//}
//
//std::vector<Face> ObjectCreator::GridFace(int w, int h, const Float3 *matrix)
//{
//    std::vector<Face> faces;
//
//    for (int i = 0; i < h; i++)
//    {
//        for (int j = 0; j < w; j++)
//        {
//            faces.emplace_back(matrix[GetIdx(i, j, w, h)],
//							   matrix[i * w + j + 1],
//							   matrix[(i + 1) * w + j]);
//        }
//    }
//}

Object ObjectCreator::BuildCube(float edge)
{
	Object object;
	Float3 p[] =
	{
		Float3(-edge, -edge, -edge),
		Float3(-edge, -edge, +edge),
		Float3(-edge, +edge, -edge),
		Float3(-edge, +edge, +edge),
		Float3(+edge, -edge, -edge),
		Float3(+edge, -edge, +edge),
		Float3(+edge, +edge, -edge),
		Float3(+edge, +edge, +edge)
	};

	object.faces.emplace_back(p[0], p[1], p[3], p[2]);
	object.faces.emplace_back(p[0], p[1], p[5], p[4]);
	object.faces.emplace_back(p[0], p[2], p[6], p[4]);
	object.faces.emplace_back(p[1], p[3], p[7], p[5]);
	object.faces.emplace_back(p[2], p[3], p[7], p[6]);
	object.faces.emplace_back(p[4], p[6], p[7], p[5]);

	return object;
}

std::vector<Face> ObjectCreator::ExtrudeFace(const Face& face, Float3 direction)
{
	int size = face.points.size();
	std::vector<Face> faces;

	Face top = face;
	Face bottom = face;

	top.Translate(direction * 0.5);
	bottom.Translate(direction * -0.5);

	faces.push_back(top);
	faces.push_back(bottom);


	for (int i = 0; i < size - 1; i++)
	{
		faces.emplace_back(
				bottom.points[i],
				top.points[i],
				top.points[i + 1],
				bottom.points[i + 1]);
	}

	faces.emplace_back(bottom.points[size - 1], top.points[size - 1], top.points[0], bottom.points[0]);
	return faces;
}

Object ObjectCreator::BuildFlatRoundedRectangle(float height, float width, float depth, int segments)
{
	auto circle = ObjectCreator::Circle(segments, width / 2);
	Face face = circle.faces[0];
	for (int i = 0; i < segments / 2; i++)
	{
		face.points[i] += Float3(0, height / 2, 0);
	}
	for (int i = segments / 2; i < segments; i++)
	{
		face.points[i] -= Float3(0, height / 2, 0);
	}
	return Object(ExtrudeFace(face, {0, 0, depth}));
}


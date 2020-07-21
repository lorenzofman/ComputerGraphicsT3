#include "ObjectCreator.h"
#include "../Primitives/Constants.h"

Object ObjectCreator::BuildCircle(int segments, float radius)
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
	auto circle = ObjectCreator::BuildCircle(segments, radius);
	return Object(ExtrudeFace(circle.faces[0], {0, 0, height}));
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
	auto circle = ObjectCreator::BuildCircle(segments, width / 2);
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

Object ObjectCreator::BuildCube(float edge)
{
	return BuildBox(edge, edge, edge);
}

Object ObjectCreator::BuildBox(float width, float height, float depth)
{
	auto halfWidth = width / 2;
	auto halfHeight = height / 2;
	auto halfDepth = depth / 2;

	Object object;
	Float3 p[] =
	{
		Float3(-halfWidth, -halfHeight, -halfDepth),
		Float3(-halfWidth, -halfHeight, +halfDepth),
		Float3(-halfWidth, +halfHeight, -halfDepth),
		Float3(-halfWidth, +halfHeight, +halfDepth),
		Float3(+halfWidth, -halfHeight, -halfDepth),
		Float3(+halfWidth, -halfHeight, +halfDepth),
		Float3(+halfWidth, +halfHeight, -halfDepth),
		Float3(+halfWidth, +halfHeight, +halfDepth)
	};

	object.faces.emplace_back(p[0], p[1], p[3], p[2]);
	object.faces.emplace_back(p[0], p[1], p[5], p[4]);
	object.faces.emplace_back(p[0], p[2], p[6], p[4]);
	object.faces.emplace_back(p[1], p[3], p[7], p[5]);
	object.faces.emplace_back(p[2], p[3], p[7], p[6]);
	object.faces.emplace_back(p[4], p[6], p[7], p[5]);

	return object;
}


#pragma once

#include <utility>
#include <vector>
#include "../Primitives/Float3.h"

struct Face
{
	Face() = default;

	explicit Face(Float3 a, Float3 b, Float3 c, Float3 d)
	{
		std::vector<Float3> vec = {a, b, c, d};
		this->points = std::move(vec);
	}
	explicit Face(std::vector<Float3> points)
	{
		this->points = std::move(points);
	}

	std::vector<Float3> points;

	void Translate(Float3 displacement)
	{
		for (auto & point : points)
		{
			point += displacement;
		}
	}

	void Rotate(Float3 rotation)
	{
		for (auto & point : points)
		{
			point = point.Rotate(rotation);
		}
	}

};
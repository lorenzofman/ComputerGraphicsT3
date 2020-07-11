#pragma once

#include <cmath>
#include "../Primitives/Float2.h"

class Utils
{
	public:
	/* Class to store utilities function (usually methods that C++17 implemented but we can't use it yet) */
	template <typename T>
	T Clamp(const T& n, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(n, upper));
	}

	static Float2 Bhaskara(float a, float b, float c)
	{
		auto delta = b * b - 4 * a * c;
		if (delta < 0)
		{
			return {NAN, NAN};
		}
		auto sq = sqrtf(delta);
		return Float2(-b - sq, -b + sq) * (1 / (2 * a));
	}
};
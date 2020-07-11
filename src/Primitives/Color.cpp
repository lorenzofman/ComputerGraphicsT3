#include "Color.h"

Color::Color()
{
	r = g = b = a = .0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::operator*(float const& constant) const
{
	return {r * constant, g * constant, b * constant, a * constant};
}

void Color::operator*=(float const& constant)
{
	r *= constant;
	g *= constant;
	b *= constant;
	a *= constant;
}
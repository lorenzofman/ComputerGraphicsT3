#include <cmath>

#include "Float2.h"
#include "Int2.h"
Float2::Float2()
{
	x = y = 0;
}

Float2::Float2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Float2 Float2::operator+(Float2 const& obj) const
{
	return {x + obj.x, y + obj.y};
}

void Float2::operator+=(Float2 const& obj)
{
	x += obj.x;
	y += obj.y;
}

Float2 Float2::operator-() const
{
	return {-x, -y};
}

Float2 Float2::operator-(Float2 const& obj) const
{
	return {x - obj.x, y - obj.y};
}

void Float2::operator-=(Float2 const& obj)
{
	x -= obj.x;
	y -= obj.y;
}

Float2 Float2::operator*(float const &constant) const
{
	return {x * constant, y * constant};
}

void Float2::operator*=(float const& constant)
{
	x *= constant;
	y *= constant;
}

void Float2::Rotate(float rot)
{
	float x0 = x;
	x = (float) (x0 * cosf(rot) - y * sinf(rot));
	y = (float) (x0 * sinf(rot) + y * cosf(rot));
}

float Float2::GetLength() const
{
	return Float2::Distance(*this, Float2(0, 0));
}

void Float2::Normalize()
{
	*this *= 1 / GetLength();
}

Float2 Float2::GetNormalized() const
{
	return *this * (1 / GetLength());
}


float Float2::Distance(Float2 a, Float2 b)
{
	return sqrtf(DistanceSq(a,b));
}

float Float2::DistanceSq(Float2 a, Float2 b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	return dx * dx + dy * dy;
}

float Float2::Angle(Float2 a, Float2 b)
{
	Float2 dif = b - a;
	return atan2f(dif.y, dif.x);
}

Float2 Float2::Scale(const Float2 &constant) const
{
    return {this->x * constant.x, this->y * constant.y};
}

Float2::Float2(const Int2 & vec2)
{
    this->x = (float) vec2.x;
    this->y = (float) vec2.y;
}

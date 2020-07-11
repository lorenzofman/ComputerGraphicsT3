#include <cmath>

#include "Int2.h"
#include "Float2.h"

Int2::Int2()
{
	x = y = 0;
}

Int2::Int2(int x, int y)
{
	this->x = x;
	this->y = y;
}

Int2 Int2::operator+(Int2 const& obj) const
{
	return {x + obj.x, y + obj.y};
}

void Int2::operator+=(Int2 const& obj)
{
	x += obj.x;
	y += obj.y;
}

Int2 Int2::operator-(const Int2 &obj) const
{
    return {x - obj.x, y - obj.y};
}

void Int2::operator-=(Int2 const& obj)
{
	x -= obj.x;
	y -= obj.y;
}

bool Int2::operator==(Int2 const& obj) const
{
	return x == obj.x && y == obj.y;
}

bool Int2::operator!=(Int2 const& obj) const
{
	return ! (*this == obj);
}

Int2 Int2::operator*(int constant) const
{
	return {x * constant, y * constant};
}

void Int2::operator*=(int constant)
{
	x *= constant;
	y *= constant;
}

void Int2::Rotate(double rot)
{
	int x0 = x;
	x = (int)(x0 * cos(rot) - y * sin(rot));
	y = (int)(x0 * sin(rot) + y * cos(rot));
}



Int2::Int2(const Float2 & vec2)
{
    this->x = (int) vec2.x;
    this->y = (int) vec2.y;
}



#pragma once
#pragma pack (push, 1)
/* Float normalized RGBA color */
struct Color
{
	float r;
	float g;
	float b;
	float a;
	Color();
	Color(float r, float g, float b, float a = 1);
	Color operator * (float const& constant) const;
	void operator *= (float const& constant);
};
#pragma pack (pop)

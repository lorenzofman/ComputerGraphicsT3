#pragma once
struct Int2;
/* Bi-dimensional structure to store a point or a vector with floating point precision */
struct Float2
{
	float x, y;

	Float2();
	Float2(float x, float y);
    Float2(const Int2&);
	Float2 operator + (Float2 const& obj) const;
	void operator += (Float2 const& obj);

	Float2 operator -() const;
	Float2 operator - (Float2 const& obj) const;
	void operator -= (Float2 const& obj);
	
	Float2 operator * (float const& constant) const;
	void operator *= (float const& constant);
	void Rotate(float rot);
    Float2 Scale (Float2 const& constant) const;
	float GetLength() const;
	void Normalize();
	Float2 GetNormalized() const;

	static float Distance(Float2 a, Float2 b);
	static float DistanceSq(Float2 a, Float2 b);
	static float Angle(Float2 a, Float2 b);

	static const Float2 Zero;
	static const Float2 One;
	static const Float2 Up;
	static const Float2 Down;
	static const Float2 Right;
	static const Float2 Left;
};
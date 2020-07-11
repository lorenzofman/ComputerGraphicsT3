#pragma once

/* Bi-dimensional structure to store a discrete point or vectors with integer precision */
struct Float2;
struct Int2
{
	int x, y;

	Int2();
	Int2(int x, int y);
    Int2(const Float2&);
    Int2 operator + (Int2 const& obj) const;
    Int2 operator - (Int2 const& obj) const;
    Int2 operator * (int constant) const;

    bool operator == (Int2 const& obj) const;
    bool operator != (Int2 const& obj) const;

    void operator += (Int2 const& obj);
	void operator -= (Int2 const& obj);
	void operator *= (int constant);

	void Rotate(double rot);
};
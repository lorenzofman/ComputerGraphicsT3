#pragma once

#include "../Primitives/Float2.h"

class Crankshaft
{
	public:
	Crankshaft(float rpm, float radius, float rodLength);

	void Update(float deltaTime);

	virtual void Draw(Float2 pistonPin, Float2 crankPosition) = 0;

	private:
	void UpdateVelocity(float deltaTime);

	float angularVelocity;
	float angle;
	float radius;
	float rodLength;

	Float2 CalculateCrankPosition() const;

	float CalculatePosition() const;

	static float Square(float f);
};
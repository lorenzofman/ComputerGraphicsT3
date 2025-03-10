#pragma once

#include "../Primitives/Float2.h"
#include "../Primitives/Constants.h"

class Crankshaft
{
	public:

	Crankshaft(float rpm, float radius, float rodLength, float initialRotation = PI / 2);

	void Update(float deltaTime);


	void UpdateRpm(float rpm);

	protected:
	float rotation;
	virtual void Draw(Float2 pistonPin, Float2 crankPosition) = 0;

	private:
	void UpdateVelocity(float deltaTime);

	float angularVelocity;
	float radius;
	float rodLength;

	Float2 CalculateCrankPosition() const;

	float CalculatePosition() const;

	static float Square(float f);
};
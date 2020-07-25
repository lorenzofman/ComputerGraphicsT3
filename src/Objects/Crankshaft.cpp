#include <cmath>
#include "Crankshaft.h"
#include "../World/Screen.h"

Crankshaft::Crankshaft(float rpm, float radius, float rodLength, float initialRotation)
{
	angularVelocity = 2 * PI * rpm / 60;
	rotation = initialRotation;
	this->radius = radius;
	this->rodLength = rodLength;
}

void Crankshaft::Update(float deltaTime)
{
	UpdateVelocity(deltaTime);

	Float2 crankPosition = CalculateCrankPosition();

	float pistonPinHeight = CalculatePosition();

	Float2 pistonPin = Float2(0, pistonPinHeight);

	Draw(pistonPin, crankPosition);
}

void Crankshaft::UpdateVelocity(float deltaTime)
{
	rotation -= angularVelocity * deltaTime;

	if (rotation <= -TAU)
	{
		rotation += TAU;
	}
}

Float2 Crankshaft::CalculateCrankPosition() const
{
	return Float2(cosf(rotation), sinf(rotation)) * radius;
}

float Crankshaft::CalculatePosition() const
{
	float relativeAngle = rotation - PI / 2;
	return radius * cosf(relativeAngle) + sqrtf(Square(rodLength) - Square(radius * sinf(relativeAngle)));
}

float Crankshaft::Square(float f)
{
	return f * f;
}

void Crankshaft::UpdateRpm(float rpm)
{
	angularVelocity = 2 * PI * rpm / 60;
}

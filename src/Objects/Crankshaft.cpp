#include <cmath>
#include <iostream>
#include "Crankshaft.h"
#include "../World/Screen.h"
#include "../Primitives/Constants.h"

Crankshaft::Crankshaft(float rpm, float radius, float rodLength)
{
	angle = PI / 2;
	angularVelocity = 2 * PI * rpm / 60;
	this->radius = radius;
	this->rodLength = rodLength;
}

void Crankshaft::Update(float deltaTime)
{
	UpdateVelocity(deltaTime);

	Float2 crankPosition = CalculateCrankPosition();

	float pistonPinHeight = CalculatePosition();

	Float2 pistonPin = Float2(0, pistonPinHeight);

	std:: cout << Float2::Distance(pistonPin, crankPosition) << std::endl;

	Draw(pistonPin, crankPosition);
}

void Crankshaft::UpdateVelocity(float deltaTime)
{
	angle += angularVelocity * deltaTime;

	if (angle >= TAU)
	{
		angle -= TAU;
	}
}

Float2 Crankshaft::CalculateCrankPosition() const
{
	return Float2(cosf(angle), sinf(angle)) * radius;
}

float Crankshaft::CalculatePosition() const
{
	float relativeAngle = angle - PI / 2;
	return radius * cosf(relativeAngle) + sqrtf(Square(rodLength) - Square(radius * sinf(relativeAngle)));
}

float Crankshaft::Square(float f)
{
	return f * f;
}

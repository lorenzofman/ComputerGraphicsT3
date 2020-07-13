#pragma once

#include "../Primitives/Float2.h"

class Crankshaft
{
	public:
	Crankshaft(float rpm, float radius, float rodLength);

	void Update(float deltaTime);
	virtual void Draw(Float2 pin, Float2 pos) = 0;

	private:
	float angularVelocity;
	float angle = 0;
	float halfStroke;
	float rodLength;
};
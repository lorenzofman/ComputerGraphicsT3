#pragma once

class Crankshaft
{
	public:
    explicit Crankshaft(float rpm, float radius, float rodLength);

	void Update(float deltaTime);
	void Draw();

	private:
	float angularVelocity;
	float angle;
	float halfStroke;
	float rodLength;
};
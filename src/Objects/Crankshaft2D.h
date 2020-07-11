#pragma once

class Crankshaft2D
{
	public:
    explicit Crankshaft2D(float rpm, float radius, float rodLength);

	void Update(float deltaTime);
	void Draw() const;

	private:
	float angularVelocity;
	float angle = 0;
	float halfStroke;
	float rodLength;
};
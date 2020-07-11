#pragma once

class Crankshaft3D
{
	public:
	explicit Crankshaft3D(float rpm, float radius, float rodLength);

	void Update(float deltaTime);
	void Draw() const;

	private:
	float angularVelocity;
	float angle = 0;
	float halfStroke;
	float rodLength;
};
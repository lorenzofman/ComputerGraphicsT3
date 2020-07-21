#pragma once

#include "Crankshaft.h"
#include "../World/Camera.h"

class Crankshaft3D : public Crankshaft
{
	public:
	Crankshaft3D(float rpm, float radius, float rodLength, float pistonSize, Camera& camera, float pos, float initialRotation);

	void Draw(Float2 pistonPin, Float2 crankPosition) override;

	private:
	Camera& camera;
	Object rod;
	Object crankCounterWeight;
	Object piston;
	Object crank;
	float pistonSize;

	static void AlignWithVector(Float2 a, Float2 b, Object& object);
};
#pragma once

#include "Crankshaft3D.h"

class Motor
{
	public:

	Motor(float rpm, float radius, float rodLength, float pistonSize, Camera& camera);

	void UpdateRpm(float rpm);

	void Update(float tick);

	void InvertBitFlag(uint i);

	private:
	std::vector<Crankshaft3D> crankshafts;
};